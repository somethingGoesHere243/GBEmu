#include "APU/APU.h"

#include <SDL3/SDL.h>
#include <iostream>

GBAPU::GBAPU() {
	SDL_Init(SDL_INIT_AUDIO);

	constexpr int numOfChannels = 2;
	constexpr int frequency = 47880;
	audioSpec = { SDL_AUDIO_F32, numOfChannels, frequency };
	audioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);

	SDL_ResumeAudioStreamDevice(audioStream);
}

GBAPU::~GBAPU() {
	SDL_DestroyAudioStream(audioStream);
}

void GBAPU::reset() {
	NR10 = 0x80;
	NR11 = 0xBF;
	NR12 = 0xF3;
	NR13 = 0xFF;
	NR14 = 0xBF;
	NR21 = 0x3F;
	NR22 = 0;
	NR23 = 0xFF;
	NR24 = 0xBF;
	NR30 = 0x7F;
	NR31 = 0xFF;
	NR32 = 0x9F;
	NR33 = 0xFF;
	NR34 = 0xBF;
	NR41 = 0xFF;
	NR42 = 0;
	NR43 = 0;
	NR44 = 0xBF;
	NR50 = 0x77;
	NR51 = 0xF3;
	NR52 = 0xF1;

	ch1.reset();
	ch2.reset();
	ch3.reset();
	ch4.reset();

	currSample = 0;
	cyclesSinceLastSample = 0;
	frameSequencerTicks = 0;
	isOn = true;
}

void GBAPU::powerDown() {
	NR10 = 0;
	NR11 = 0;
	NR12 = 0;
	NR13 = 0;
	NR14 = 0;
	NR21 = 0;
	NR22 = 0;
	NR23 = 0;
	NR24 = 0;
	NR30 = 0;
	NR31 = 0;
	NR32 = 0;
	NR33 = 0;
	NR34 = 0;
	NR42 = 0;
	NR43 = 0;
	NR44 = 0;
	NR50 = 0;
	NR51 = 0;
	NR52 = 0;

	ch1.reset();
	ch2.reset();
	ch3.reset();
	ch4.reset();

	currSample = 0;
	cyclesSinceLastSample = 0;
	waveRamAccessible = false;
	isOn = false;
}

byte GBAPU::read(address addr) {
	// Check if address is inside Wave Ram
	if (addr - 0xFF30 < 0x10 && addr - 0xFF30 >= 0) {
		return WaveRam[addr - 0xFF30];
	}
	// When read the values of most APU registers are ORed with certain values
	switch (addr) {
	case 0xFF10:
		return NR10 | 0x80;
	case 0xFF11:
		return NR11 | 0x3F;
	case 0xFF12:
		return NR12;
	case 0xFF13:
		return 0xFF;
	case 0xFF14:
		return NR14 | 0xBF;
	case 0xFF16:
		return NR21 | 0x3F;
	case 0xFF17:
		return NR22;
	case 0xFF18:
		return 0xFF;
	case 0xFF19:
		return NR24 | 0xBF;
	case 0xFF1A:
		return NR30 | 0x7F;
	case 0xFF1B:
		return 0xFF;
	case 0xFF1C:
		return NR32 | 0x9F;
	case 0xFF1D:
		return 0xFF;
	case 0xFF1E:
		return NR34 | 0xBF;
	case 0xFF20:
		return 0xFF;
	case 0xFF21:
		return NR42;
	case 0xFF22:
		return NR43;
	case 0xFF23:
		return NR44 | 0xBF;
	case 0xFF24: 
		return NR50;
	case 0xFF25:
		return NR51;
	case 0xFF26:
		return NR52 | 0x70;
	default:
		// Return garbage
		return 0xFF;
	}
}

void GBAPU::write(address addr, byte newVal) {
	// Check if address is inside Wave Ram
	if (addr - 0xFF30 < 0x10 && addr - 0xFF30 >= 0) {
		WaveRam[addr - 0xFF30] = newVal;
		return;
	}
	// Check if APU is turned off
	if (!isOn) {
		// Writes ignored except to NR41 or NR52 if attempting to power on APU (setting bit 7 to 1)
		if (addr == 0xFF11) {
			// Bits 6 & 7 are read only
			NR11 = (NR11 & 0b11000000) + (newVal & 0b00111111);
			// Update length timer with new value
			ch1.lengthTimer = 64 - (newVal & 0b00111111);
		}
		if (addr == 0xFF16) {
			// Bits 6 & 7 are read only
			NR21 = (NR21 & 0b11000000) + (newVal & 0b00111111);
			// Update length timer with new value
			ch2.lengthTimer = 64 - (newVal & 0b00111111);
		}
		if (addr == 0xFF1B) {
			NR31 = newVal;
			// Update length timer with new value
			ch3.lengthTimer = 256 - newVal;
		}
		if (addr == 0xFF20) {
			NR41 = newVal;
			// Update length timer with new value
			ch4.lengthTimer = 64 - (newVal & 0b00111111);
		}
		if (addr == 0xFF26 && (newVal & 0b10000000)) {
			NR52 = 0b10000000;
			isOn = true;
			frameSequencerTicks = 0;
		}
		return;
	}
	bool DACDisabled;
	switch (addr) {
	case 0xFF10:
		// If sweep has already performed a subtraction calculation then changing
		// bit 3 from 1 to 0 causes channel to be disabled
		if (ch1.subtractionOccured && !(newVal & 0b00001000) && (NR10 & 0b00001000)) {
			ch1.disabled = true;
			// Declare channel disabled bit 0 of NR52
			NR52 = NR52 & 0b11111110;
		}
		ch1.subtractionOccured = false;
		NR10 = newVal;
		break;
	case 0xFF11:
		NR11 = newVal;
		// Update length timer with new value
		ch1.lengthTimer = 64 - (newVal & 0b00111111);
		break;
	case 0xFF12:
		// Check for "Zombie mode" glitch
		if ((NR12 & 0b00000111) == 0 
			&& (newVal & 0b00001111) == 0b00001000 ) {
			// Causes volume of channel to increase by 1 (max value is 15)
			ch1.volume = (ch1.volume + 1) % 16;
		}
		NR12 = newVal;
		// If bits 3-7 all set to 0 channel is disabled
		DACDisabled = !((bool)(newVal & 0b11111000));
		if (DACDisabled) {
			ch1.disabled = true;
			// Declare channel disabled bit 0 of NR52
			NR52 = NR52 & 0b11111110;
		}
		break;
	case 0xFF13:
		NR13 = newVal;
		break;
	case 0xFF14:
		// Check if length timer is being enabled
		if ((newVal & 0b01000000) && !(NR14 & 0b01000000)) {
			// If frame sequencer is not set to update length control on next tick 
			if ((frameSequencerTicks % 2 == 1)) {
				// Check if length timer can be further decremented
				if (ch1.lengthTimer > 0) {
					--ch1.lengthTimer;
					if (ch1.lengthTimer == 0) {
						ch1.disabled = true;
						// Declare channel disabled bit 0 of NR52
						NR52 = NR52 & 0b11111110;
					}
				}
			}
		}

		NR14 = newVal;
		// If bit 7 is written to 1 trigger channel 1
		if (NR14 & 0b10000000) { triggerChannel1(); }
		break;
	case 0xFF16:
		NR21 = newVal;
		// Update length timer with new value
		ch2.lengthTimer = 64 - (newVal & 0b00111111);
		break;
	case 0xFF17:
		// Check for "Zombie mode" glitch
		if ((NR22 & 0b00000111) == 0
			&& (newVal & 0b00001111) == 0b00001000) {
			// Causes volume of channel to increase by 1 (max value is 15)
			ch2.volume = (ch2.volume + 1) % 16;
		}

		NR22 = newVal;
		// If bits 3-7 all set to 0 channel is disabled
		DACDisabled = !((bool)(newVal & 0b11111000));
		if (DACDisabled) {
			ch2.disabled = true;
			// Declare channel disabled bit 1 of NR52
			NR52 = NR52 & 0b11111101;
		}
		break;
	case 0xFF18:
		NR23 = newVal;
		break;
	case 0xFF19:
		// Check if length timer is being enabled
		if ((newVal & 0b01000000) && !(NR24 & 0b01000000)) {
			// If frame sequencer is not set to update length control on next tick 
			if ((frameSequencerTicks % 2 == 1)) {
				// Check if length timer can be further decremented
				if (ch2.lengthTimer > 0) {
					--ch2.lengthTimer;
					if (ch2.lengthTimer == 0) {
						ch2.disabled = true;
						// Declare channel disabled bit 1 of NR52
						NR52 = NR52 & 0b11111101;
					}
				}
			}
		}
		NR24 = newVal;
		// If bit 7 is written to 1 trigger channel 2
		if (NR24 & 0b10000000) { triggerChannel2(); }
		break;
	case 0xFF1A:
		NR30 = newVal & 0b10000000; // Can only write to bit 7
		// Value written will either enable of disable channel 3
		DACDisabled = !((bool)(NR30));
		if (DACDisabled) {
			ch3.disabled = true;
			// Declare channel disabled bit 1 of NR52
			NR52 = NR52 & 0b11111011;
		}
		break;
	case 0xFF1B:
		NR31 = newVal;
		// Update length timer with new value
		ch3.lengthTimer = 256 - (newVal);
		break;
	case 0xFF1C:
		NR32 = newVal;
		break;
	case 0xFF1D:
		NR33 = newVal;
		break;
	case 0xFF1E:
		// Check if length timer is being enabled
		if ((newVal & 0b01000000) && !(NR34 & 0b01000000)) {
			// If frame sequencer is not set to update length control on next tick 
			if ((frameSequencerTicks % 2 == 1)) {
				// Check if length timer can be further decremented
				if (ch3.lengthTimer > 0) {
					--ch3.lengthTimer;
					if (ch3.lengthTimer == 0) {
						ch3.disabled = true;
						// Declare channel disabled bit 2 of NR52
						NR52 = NR52 & 0b11111011;
					}
				}
			}
		}
		NR34 = newVal;
		// If bit 7 is written to 1 trigger channel 3
		if (NR34 & 0b10000000) { triggerChannel3(); }
		break;
	case 0xFF20:
		NR41 = newVal;
		// Update length timer with new value
		ch4.lengthTimer = 64 - (newVal & 0b00111111);
		break;
	case 0xFF21:
		NR42 = newVal;
		// If bits 3-7 all set to 0 channel is disabled
		DACDisabled = !((bool)(newVal & 0b11111000));
		if (DACDisabled) {
			ch4.disabled = true;
			// Declare channel disabled bit 3 of NR52
			NR52 = NR52 & 0b11110111;
		}
		break;
	case 0xFF22:
		NR43 = newVal;
		break;
	case 0xFF23:
		// Check if length timer is being enabled
		if ((newVal & 0b01000000) && !(NR44 & 0b01000000)) {
			// If frame sequencer is not set to update length control on next tick 
			if ((frameSequencerTicks % 2 == 1)) {
				// Check if length timer can be further decremented
				if (ch4.lengthTimer > 0) {
					--ch4.lengthTimer;
					if (ch4.lengthTimer == 0) {
						ch4.disabled = true;
						// Declare channel disabled bit 3 of NR52
						NR52 = NR52 & 0b11110111;
					}
				}
			}
		}
		NR44 = newVal;
		// If bit 7 is written to 1 trigger channel 4
		if (NR44 & 0b10000000) { triggerChannel4(); }
		break;
	case 0xFF24:
		NR50 = newVal;
		break;
	case 0xFF25:
		NR51 = newVal;
		break;
	case 0xFF26:
		// Can only write to bit 7
		NR52 = (NR52 & 0b01111111) + (newVal & 0b10000000);

		// When bit 7 of NR52 is written to 0 the APU is turned off and all its registers are reset
		if (!(NR52 & 0b10000000)) {
			powerDown();
		}
		break;
	}
}

float GBAPU::calculateChannel1() {
	// Check if channel has been disabled by length timer
	if (ch1.disabled) { return 0; }

	--ch1.timer;
	// Check if timer needs to be reset
	if (ch1.timer == 0) {
		// Lower 8 bits of period come from NR13
		// Upper 3 bits come from lower 3 bits of NR14
		int frequency = (NR14 & 0b00000111) * 256 + NR13;

		ch1.timer = (2048 - frequency) * 4;

		// Wave position incremented on each reset (can only be between 0 & 7)
		++ch1.wavePosition;
		if (ch1.wavePosition == 8) {
			ch1.wavePosition = 0;
		}
	}

	// Get correct waveform from upper 2 bits of NR11
	int waveform;
	switch (NR11 >> 6) {
	case 0:
		waveform = 0b00000001;
		break;
	case 1:
		waveform = 0b00000011;
		break;
	case 2:
		waveform = 0b00001111;
		break;
	default: // Should only be triggered for value 3
		waveform = 0b11111100;
		break;
	}
	// Current amplitude of the channel comes from the position within the waveform
	bool amplitude = waveform & (1 << ch1.wavePosition);

	// Calculate value to be sent to mixer
	return amplitude * ch1.volume;
}

void GBAPU::triggerChannel1() {
	// Check if channels DAC is on
	if (NR12 & 0b11111000) {
		// Declare channel enabled bit 0 of NR52
		NR52 = NR52 | 1;
		ch1.disabled = false;
	}

	// Initial period time comes from bits 0-2 of NR12
	ch1.initialPeriodTimer = NR12 & 0b111;
	ch1.periodTimer = ch1.initialPeriodTimer;

	// Envelope Direction comes from bit 3
	ch1.envelopeDirection = NR12 & 0b00001000; // True means upwards envelope

	int frequency = (NR14 & 0b00000111) * 256 + NR13;
	ch1.timer = (2048 - frequency) * 4;

	// Initial volume comes from bits 4-7
	ch1.volume = (NR12 >> 4) & 0b1111;

	// If length timer is at 0 reset it to its maximum value
	if (ch1.lengthTimer == 0) {
		ch1.lengthTimer = 64;
		// If frame sequencer is not set to update length control on next tick decrement the length timer
		if ((NR14 & 0b01000000) && (frameSequencerTicks % 2 == 1)) {
			--ch1.lengthTimer;
		}
	}

	// Initial shadow frequency comes from register NR13 and bits 0-2 of NR14
	ch1.shadowFreq = NR13 + 256 * (NR14 & 0b00000111);

	// Sweep period comes from bits 4-6 of NR10 (value of 0 is converted to 8)
	int sweepPeriod = (NR10 >> 4) & 0b00000111;
	if (sweepPeriod == 0) {
		ch1.sweepTimer = 8;
	}
	else {
		ch1.sweepTimer = sweepPeriod;
	}

	// Sweep shift comes from bits 0-2 of NR10
	int sweepShift = NR10 & 0b00000111;
	if (sweepPeriod != 0 || sweepShift != 0) {
		ch1.sweepEnabled = true;
	}
	ch1.subtractionOccured = false;
	if ((sweepShift > 0)) {
		// Bit 3 of NR10 determines if we should increase (0) or decrease (1) the shadow frequency
		bool sweepDecrease = NR10 & 0b00001000;

		// Calculate new frequency to be written into register NR13 & NR14
		int newFreq = sweepDecrease ? (ch1.shadowFreq - (ch1.shadowFreq >> sweepShift))
			: (ch1.shadowFreq + (ch1.shadowFreq >> sweepShift));

		// If sweep is decreasing need to store that in channel's state
		ch1.subtractionOccured = sweepDecrease;

		// Check for overflow
		if (newFreq > 2047 || newFreq < 0) {
			ch1.sweepEnabled = false;
			ch1.disabled = true;
			// Declare channel disabled bit 0 of NR52
			NR52 = NR52 & 0b11111110;
		}
	}
	ch1.wavePosition = 0;
}

float GBAPU::calculateChannel2() {
	// Check if channel has been disabled by length timer
	if (ch2.disabled) { 
		return 0; 
	}

	--ch2.timer;
	// Check if timer needs to be reset
	if (ch2.timer == 0) {
		// Lower 8 bits of period come from NR23
		// Upper 3 bits come from lower 3 bits of NR24
		int frequency = (NR24 & 0b00000111) * 256 + NR23;

		ch2.timer = (2048 - frequency) * 4;

		// Wave position incremented on each reset (can only be between 0 & 7)
		++ch2.wavePosition;
		if (ch2.wavePosition == 8) {
			ch2.wavePosition = 0;
		}
	}

	// Get correct waveform from upper 2 bits of NR21
	int waveform;
	switch (NR21 >> 6) {
	case 0:
		waveform = 0b00000001;
		break;
	case 1:
		waveform = 0b00000011;
		break;
	case 2:
		waveform = 0b00001111;
		break;
	default: // Should only be triggered for value 3
		waveform = 0b11111100;
		break;
	}
	// Current amplitude of the channel comes from the position within the waveform
	bool amplitude = waveform & (1 << ch2.wavePosition);

	// Calculate value to be sent to mixer
	return amplitude * ch2.volume;
}

void GBAPU::triggerChannel2() {
	// Check if channels DAC is on
	if (NR22 & 0b11111000) {
		// Declare channel enabled bit 1 of NR52
		NR52 = (NR52 & 0b11111101) + 2;
		ch2.disabled = false;
	}

	// Initial period time comes from bits 0-2 of NR22
	ch2.initialPeriodTimer = NR22 & 0b111;
	ch2.periodTimer = ch2.initialPeriodTimer;

	// Envelope Direction comes from bit 3
	ch2.envelopeDirection = NR22 & 0b00001000; // True means upwards envelope

	int frequency = (NR24 & 0b00000111) * 256 + NR23;
	ch2.timer = (2048 - frequency) * 4;

	// Initial volume comes from bits 4-7
	ch2.volume = (NR22 >> 4) & 0b1111;

	// If length timer is at 0 reset it to its maximum value
	if (ch2.lengthTimer == 0) {
		ch2.lengthTimer = 64;
		// If frame sequencer is not set to update length control on next tick decrement the length timer
		if ((NR24 & 0b01000000) && (frameSequencerTicks % 2 == 1)) {
			--ch2.lengthTimer;
		}
	}

	ch2.wavePosition = 0;
}

float GBAPU::calculateChannel3() {
	if (ch3.disabled) {
		return 0;
	}
	waveRamAccessible = false;
	ch3.timer -= 1;
	// Check if timer needs to be reset
	if (ch3.timer <= 0) {
		// Lower 8 bits of period come from NR33
		// Upper 3 bits come from lower 3 bits of NR34
		int frequency = (NR34 & 0b00000111) * 256 + NR33;

		ch3.timer = (2048 - frequency) * 4;

		// Wave position incremented on each reset (can only be between 0 & 31)
		++ch3.wavePosition;
		if (ch3.wavePosition == 32) {
			ch3.wavePosition = 0;
		}

		// Declare WaveRam accessible
		waveRamAccessible = true;
	}

	// Each wave ram entry contains two 4-bit samples (upper sample read first)
	int currWaveRamEntry = WaveRam[ch3.wavePosition / 2];
	int amplitude;
	if (ch3.wavePosition % 2 == 0) {
		// Read upper 4 bits
		amplitude = (currWaveRamEntry >> 4) & 0xF;
	}
	else {
		// Read lower 4 bits
		amplitude = currWaveRamEntry & 0xF;
	}
	// Amplitude is shifted by amount determined by bits 5-6 of NR32
	int amplitudeShift = (NR32 >> 5) & 0b00000011;
	switch (amplitudeShift) {
	case 0:
		amplitude = amplitude >> 4;
		break;
	case 1:
		amplitude = amplitude;
		break;
	case 2:
		amplitude = amplitude >> 1;
		break;
	case 3:
		amplitude = amplitude >> 2;
		break;
	}
	return amplitude;
}

void GBAPU::triggerChannel3() {
	// Check if channels DAC is on
	if (NR30 & 0b10000000) {
		// Declare channel enabled bit 2 of NR52
		NR52 = (NR52 & 0b11111011) + 4;
		ch3.disabled = false;
	}

	// Initial period time comes from bits 0-2 of NR32
	ch3.initialPeriodTimer = NR32 & 0b111;
	ch3.periodTimer = ch3.initialPeriodTimer;

	// Envelope Direction comes from bit 3
	ch3.envelopeDirection = NR32 & 0b00001000; // True means upwards envelope

	// Initial volume comes from bits 4-7
	ch3.volume = (NR32 >> 4) & 0b1111;

	// If length timer is at 0 reset it to its maximum value
	if (ch3.lengthTimer == 0) {
		ch3.lengthTimer = 256;
		// If frame sequencer is not set to update length control on next tick decrement the length timer
		if ((NR34 & 0b01000000) && (frameSequencerTicks % 2 == 1)) {
			--ch3.lengthTimer;
		}
	}
}

float GBAPU::calculateChannel4() {
	// Check if channel has been disabled by length timer
	if (ch4.disabled) {
		return 0;
	}

	--ch4.timer;
	// Check if timer needs to be reset
	if (ch4.timer == 0) {
		// Divisor for frequency determined by bits 0-2 of NR43
		int divisor = ((NR43 & 0b00000111) == 0) ? 8 : ((NR43 & 0b00000111) * 16);

		// Frequency divisor shifted an amount determined by bits 4-7 of NR43
		int shift = (NR43 >> 4) & 0b00001111;

		ch4.timer = (divisor << shift) * 4;

		// Calculate XOR of bits 0 and 1 in LFSR
		bool storedBit = (ch4.LFSR & 1) ^ ((ch4.LFSR >> 1) & 1);

		// Right shift LFSR and replace bit 14 with the stored bit
		ch4.LFSR = (ch4.LFSR >> 1) + storedBit * (1 << 14);

		// If bit 3 of NR43 is set also replace bit 6 with stored bit
		if (NR43 & 0b00001000) {
			ch4.LFSR = (ch4.LFSR & ~(1 << 6)) + storedBit * (1 << 6);
		}
	}

	// Current amplitude of the channel comes from the compliment of bit 0 of LFSR
	bool amplitude = !(ch4.LFSR & 1);

	// Calculate value to be sent to mixer
	return amplitude * ch4.volume;
}

void GBAPU::triggerChannel4() {
	// Check if channels DAC is on
	if (NR42 & 0b11111000) {
		// Declare channel enabled bit 3 of NR52
		NR52 = (NR52 & 0b11110111) + 8;
		ch4.disabled = false;
	}

	// Initially all 15 bits of LFSR are set to 1
	ch4.LFSR = (1 << 16) - 1;

	// Initial period time comes from bits 0-2 of NR42
	ch4.initialPeriodTimer = NR42 & 0b111;
	ch4.periodTimer = ch4.initialPeriodTimer;

	// Envelope Direction comes from bit 3
	ch4.envelopeDirection = NR42 & 0b00001000; // True means upwards envelope

	// Initial volume comes from bits 4-7
	ch4.volume = (NR42 >> 4) & 0b1111;

	// If length timer is at 0 reset it to its maximum value
	if (ch4.lengthTimer == 0) {
		ch4.lengthTimer = 64;
		// If frame sequencer is not set to update length control on next tick decrement the length timer
		if ((NR44 & 0b01000000) && (frameSequencerTicks % 2 == 1)) {
			--ch4.lengthTimer;
		}
	}
}

void GBAPU::tickFrameSequencer() {
	// Frame sequencer ticks are values between 0 & 7
	// Length control updated on ticks 0, 2, 4 & 6
	// Sweep updated on ticks 2 & 6
	// Volume envelope updated on tick 7
	switch (frameSequencerTicks) {
	case 2:
	case 6:
		updateSweep();
		[[fallthrough]];
	case 0:
	case 4:
		updateLengthCtr();
		break;
	case 7:
		updateVolEnv();
	}

	++frameSequencerTicks;
	if (frameSequencerTicks == 8) {
		frameSequencerTicks = 0;
	}
}

void GBAPU::updateLengthCtr() {
	// Check if APU is turned on
	if (!isOn) {
		return;
	}
	// Check if length control enabled for channel 1 (bit 6 of NR14)
	if (NR14 & 0b01000000) {
		if (ch1.lengthTimer > 0) {
			--ch1.lengthTimer;
		}
		if (ch1.lengthTimer == 0) {
			ch1.disabled = true;
			// Declare channel disabled bit 0 of NR52
			NR52 = NR52 & 0b11111110;
		}
	}

	// Check if length control enabled for channel 2 (bit 6 of NR24)
	if (NR24 & 0b01000000) {
		if (ch2.lengthTimer > 0) {
			--ch2.lengthTimer;
		}
		if (ch2.lengthTimer == 0) {
			ch2.disabled = true;
			// Declare channel disabled bit 1 of NR52
			NR52 = NR52 & 0b11111101;
		}
	}

	// Check if length control enabled for channel 3 (bit 6 of NR34)
	if (NR34 & 0b01000000) {
		if (ch3.lengthTimer > 0) {
			--ch3.lengthTimer;
		}
		if (ch3.lengthTimer == 0) {
			ch3.disabled = true;
			// Declare channel disabled bit 2 of NR52
			NR52 = NR52 & 0b11111011;
		}
	}

	// Check if length control enabled for channel 4 (bit 6 of NR44)
	if (NR44 & 0b01000000) {
		if (ch4.lengthTimer > 0) {
			--ch4.lengthTimer;
		}
		if (ch4.lengthTimer == 0) {
			ch4.disabled = true;
			// Declare channel disabled bit 3 of NR52
			NR52 = NR52 & 0b11110111;
		}
	}
}

void GBAPU::updateSweep() {
	// Only channel 1 has a sweep function
	if (ch1.sweepTimer > 0) {
		--ch1.sweepTimer;
	}
	if (ch1.sweepTimer == 0) {
		// Sweep period comes from bits 4-6 of NR10 (value of 0 is converted to 8)
		int sweepPeriod = (NR10 >> 4) & 0b00000111;
		if (sweepPeriod == 0) {
			ch1.sweepTimer = 8;
		}
		else {
			ch1.sweepTimer = sweepPeriod;
		}
		// Check if sweep is enabled (and sweepPeriod non-zero)
		if (ch1.sweepEnabled && sweepPeriod != 0) {
			// Bit 3 of NR10 determines if we should increase (0) or decrease (1) the shadow frequency
			bool sweepDecrease = NR10 & 0b00001000;
			// Bits 0-2 of NR10 determines amount to shift frequency by
			int sweepShift = (NR10 & 0b00000111);

			// Calculate new frequency to be written into register NR13 & NR14
			int newFreq = sweepDecrease ? (ch1.shadowFreq - (ch1.shadowFreq >> sweepShift)) 
										: (ch1.shadowFreq + (ch1.shadowFreq >> sweepShift));

			// If sweep is decreasing need to store that in channel's state
			ch1.subtractionOccured = sweepDecrease;

			// Check for overflow
			if (newFreq > 2047) {
				ch1.sweepEnabled = false;
				ch1.disabled = true;
				// Declare channel disabled bit 0 of NR52
				NR52 = NR52 & 0b11111110;
			}
			else if (sweepShift > 0) {
				ch1.shadowFreq = newFreq;
				// Update registers NR13 & NR14
				NR13 = newFreq & 0xFF;
				byte temp = NR14 & 0b11111000;
				byte temp2 = (newFreq >> 8) & 0b00000111;
				NR14 = (NR14 & 0b11111000) + ((newFreq >> 8) & 0b00000111);

				// Again check for overflow
				newFreq = sweepDecrease ? (ch1.shadowFreq - (ch1.shadowFreq >> sweepShift))
										: (ch1.shadowFreq + (ch1.shadowFreq >> sweepShift));
				if (newFreq > 2047) {
					ch1.sweepEnabled = false;
					ch1.disabled = true;
					// Declare channel disabled bit 0 of NR52
					NR52 = NR52 & 0b11111110;
				}
			}

		}
	}
}

void GBAPU::updateVolEnv() {
	// Check if channel 1 period is disabled (bits 0-2 of NR12 all 0)
	if ((NR12 & 0b00000111) != 0) {
		// Decrement period timer
		if (ch1.periodTimer > 0) {
			--ch1.periodTimer;
		}
		if (ch1.periodTimer == 0) {
			// Reset timer
			ch1.periodTimer = ch1.initialPeriodTimer;
			// Update volume of channel
			if (ch1.envelopeDirection && ch1.volume < 0xF) { ++ch1.volume; }
			else if (!ch1.envelopeDirection && ch1.volume > 0) { --ch1.volume; }
		}
	}

	// Check if channel 2 period is disabled (bits 0-2 of NR22 all 0)
	if ((NR22 & 0b00000111) != 0) {
		// Decrement period timer
		if (ch2.periodTimer > 0) {
			--ch2.periodTimer;
		}
		if (ch2.periodTimer == 0) {
			// Reset timer
			ch2.periodTimer = ch2.initialPeriodTimer;
			// Update volume of channel
			if (ch2.envelopeDirection && ch2.volume < 0xF) { ++ch2.volume; }
			else if (!ch2.envelopeDirection && ch2.volume > 0) { --ch2.volume; }
		}
	}

	// Check if channel 3 period is disabled (bits 0-2 of NR32 all 0)
	if ((NR32 & 0b00000111) != 0) {
		// Decrement period timer
		if (ch3.periodTimer > 0) {
			--ch3.periodTimer;
		}
		if (ch3.periodTimer == 0) {
			// Reset timer
			ch3.periodTimer = ch3.initialPeriodTimer;
			// Update volume of channel
			if (ch3.envelopeDirection && ch3.volume < 0xF) { ++ch3.volume; }
			else if (!ch3.envelopeDirection && ch3.volume > 0) { --ch3.volume; }
		}
	}

	// Check if channel 4 period is disabled (bits 0-2 of NR42 all 0)
	if ((NR42 & 0b00000111) != 0) {
		// Decrement period timer
		if (ch4.periodTimer > 0) {
			--ch4.periodTimer;
		}
		if (ch4.periodTimer == 0) {
			// Reset timer
			ch4.periodTimer = ch4.initialPeriodTimer;
			// Update volume of channel
			if (ch4.envelopeDirection && ch4.volume < 0xF) { ++ch4.volume; }
			else if (!ch4.envelopeDirection && ch4.volume > 0) { --ch4.volume; }
		}
	}
}

void GBAPU::update() {
	float ch1Output = 0;
	float ch2Output = 0;
	float ch3Output = 0;
	float ch4Output = 0;

	// Check if APU is turned on
	if (isOn) {
		ch1Output = calculateChannel1();
		ch2Output = calculateChannel2();
		ch3Output = calculateChannel3();
		ch4Output = calculateChannel4();
	}

	++cyclesSinceLastSample;
	if (cyclesSinceLastSample == 88) {
		cyclesSinceLastSample = 0;
		if (currSample < 798) {
			// Get volume from bits 0-2 (right ear) and 4-6 (left ear) of NR 50
			int rightVol = (NR50 & 0b00000111) + 1;
			int leftVol = ((NR50 >> 4) & 0b00000111) + 1;

			// Check which channels should be heard (determined by bits of NR51)
			float leftSample = 0;
			float rightSample = 0;
			if (NR51 & 0b00000001) {
				rightSample += ch1Output;
			}
			if (NR51 & 0b00000010) {
				rightSample += ch2Output;
			}
			if (NR51 & 0b00000100) {
				rightSample += ch3Output;
			}
			if (NR51 & 0b00001000) {
				rightSample += ch4Output;
			}
			if (NR51 & 0b00010000) {
				leftSample += ch1Output;
			}
			if (NR51 & 0b00100000) {
				leftSample += ch2Output;
			}
			if (NR51 & 0b01000000) {
				leftSample += ch3Output;
			}
			if (NR51 & 0b10000000) {
				leftSample += ch4Output;
			}
			// Convert samples to a value between -1 and 1
			leftSample = (leftSample / 30) - 1;
			rightSample = (rightSample / 30) - 1;
			// Apply volume adjustment
			samples[2 * currSample] = leftSample * leftVol / 200;
			samples[2 * currSample + 1] = rightSample * rightVol / 200;
			
			++currSample;
		}
		
	}
}

void GBAPU::pushToStream() {
	SDL_PutAudioStreamData(audioStream, samples, sizeof(samples));

	currSample = 0;
}