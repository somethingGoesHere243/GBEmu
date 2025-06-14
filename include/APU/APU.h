#pragma once
#include <SDL3/SDL.h>

using byte = uint8_t;
using address = unsigned short;

// APU contains 4 channels
struct ch1 {
	// Wave state
	int wavePosition{ 0 };
	int timer{ 1 };
	// Volume envelope state
	int initialPeriodTimer{ 0 }; // Set on channel trigger
	bool envelopeDirection{ false };
	int periodTimer{ 0 };
	int volume{ 0 };
	// Sweep state
	int shadowFreq{ 0 };
	int sweepTimer{ 0 };
	bool sweepEnabled{ false };
	bool subtractionOccured{ false };
	// Length control state
	int lengthTimer{ 0 };
	bool disabled{ false };

	void reset() {
		wavePosition = 0;
		timer = 1;
		initialPeriodTimer = 0;
		envelopeDirection = false;
		periodTimer = 0;
		volume = 0;
		shadowFreq = 0;
		sweepTimer = 0;
		sweepEnabled = false;
		subtractionOccured = false;
		//lengthTimer = 0;
		disabled = false;
	}
};

struct ch2 {
	// Wave state
	int wavePosition{ 0 };
	int timer{ 1 };
	// Volume envelope state
	int initialPeriodTimer{ 0 }; // Set on channel trigger
	bool envelopeDirection{ false };
	int periodTimer{ 0 };
	int volume{ 0 };
	// Length control state
	int lengthTimer{ 0 };
	bool disabled{ false };

	void reset() {
		wavePosition = 0;
		timer = 1;
		initialPeriodTimer = 0;
		envelopeDirection = false;
		periodTimer = 0;
		volume = 0;
		//lengthTimer = 0;
		disabled = false;
	}
};

struct ch3 {
	// Wave state
	int wavePosition{ 0 };
	int timer{ 1 };
	// Volume envelope state
	int initialPeriodTimer{ 0 }; // Set on channel trigger
	bool envelopeDirection{ false };
	int periodTimer{ 0 };
	int volume{ 0 };
	// Length control state
	int lengthTimer{ 0 };
	bool disabled{ false };

	void reset() {
		wavePosition = 0;
		timer = 1;
		initialPeriodTimer = 0;
		envelopeDirection = false;
		periodTimer = 0;
		volume = 0;
		//lengthTimer = 0;
		disabled = false;
	}
};

struct ch4 {
	// Random noise state
	int LFSR{ 0 }; // Linear feedback shift register
	int timer{ 1 };
	// Volume envelope state
	int initialPeriodTimer{ 0 }; // Set on channel trigger
	bool envelopeDirection{ false };
	int periodTimer{ 0 };
	int volume{ 0 };
	// Length control state
	int lengthTimer{ 0 };
	bool disabled{ false };

	void reset() {
		LFSR = 0;
		timer = 1;
		initialPeriodTimer = 0;
		envelopeDirection = false;
		periodTimer = 0;
		volume = 0;
		//lengthTimer = 0;
		disabled = false;
	}
};

class GBAPU {
private:
	SDL_AudioStream* audioStream;
	SDL_AudioSpec audioSpec;

	// Store whether APU is currently powered on
	bool isOn{ true };

	//Channel 1 sweep: address FF10
	byte NR10{ 0x80 };

	//Channel 1 length timer and duty cycle: address FF11
	byte NR11{ 0xBF };

	//Channel 1 volume and envelope: address FF12
	byte NR12{ 0xF3 };

	//Channel 1 period low: address FF13
	byte NR13{ 0xFF };

	//Channel 1 period high and control: address FF14
	byte NR14{ 0xBF };

	//Channel 2 length timer and duty cycle: address FF16
	byte NR21{ 0x3F };

	//Channel 2 volume and envelope: address FF17
	byte NR22{ 0 };

	//Channel 1 period low: address FF18
	byte NR23{ 0xFF };

	//Channel 2 period high and control: address FF19
	byte NR24{ 0xBF };

	//Channel 3 DAC enable: address FF1A
	byte NR30{ 0x7F };

	//Channel 3 length timer: address FF1B
	byte NR31{ 0xFF };

	//Channel 3 output level: address FF1C
	byte NR32{ 0x9F };

	//Channel 3 period low: address FF1D
	byte NR33{ 0xFF };

	//Channel 3 period high and control: address FF1E
	byte NR34{ 0xBF };

	//Channel 4 length timer: address FF20
	byte NR41{ 0xFF };

	//Channel 4 volume and envelope: address FF21
	byte NR42{ 0 };

	//Channel 4 frequency and randomness: address FF22
	byte NR43{ 0 };

	//Channel 4 control: address FF23
	byte NR44{ 0xBF };

	//Master volume and VIN panning: address FF24
	byte NR50{ 0x77 };

	//Sound panning: address FF25
	byte NR51{ 0xF3 };

	//Audio master control: address FF26
	byte NR52{ 0xF1 };

	//Wave Ram: addresses FF30 - FF3F
	byte WaveRam[0x10]{ 0 };
	bool waveRamAccessible = false;

	//Gameboy APU has 4 audio channels computing different types of audio
	ch1 ch1;
	float calculateChannel1();
	void triggerChannel1();

	ch2 ch2;
	float calculateChannel2();
	void triggerChannel2();

	ch3 ch3;
	float calculateChannel3();
	void triggerChannel3();

	ch4 ch4;
	float calculateChannel4();
	void triggerChannel4();

	//Frame sequencer triggers 3 functions
	void updateLengthCtr();
	void updateSweep();
	void updateVolEnv();

public:
	GBAPU();

	~GBAPU();

	// Resets the APU to its default state
	void reset();

	// Set the APU to its powered down state
	void powerDown();

	// Store one frames worth of audio samples
	float samples[1596]; // Gives frequency 47880Hz
	int currSample{ 0 };

	// Need to add 1 sample every 22 cycles
	int cyclesSinceLastSample{ 0 };

	// Allow memory to read/write to the registers
	byte read(address addr);
	void write(address addr, byte newVal);

	//Frame sequencer controls timing of the APU
	int frameSequencerTicks{ 0 };
	void tickFrameSequencer();

	// Calculate all 4 audio channels and mixes their output into one audio buffer
	void update();

	// Push samples to audio stream
	void pushToStream();
};