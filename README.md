# GBEmu

## Building

To build the project, CMake is the only requirement.

## Current Control Scheme:  
DPAD UP : W  
DPAD LEFT : A  
DPAD DOWN : S  
DPAD RIGHT : D  
B BUTTON : O  
A BUTTON : P  
START BUTTON : ENTER  
SELECT BUTTON : SHIFT  

## TODO:  
Add remaining MBC types  
Add CGB functionality  
Add Customisable Control Scheme  

## Third Party Dependancies

SDL3: https://github.com/libsdl-org/SDL  
Nlohmann json (Only for testing): https://github.com/nlohmann/json

## Documentation used:  
Pandocs: https://gbdev.io/pandocs/  
OPCode reference: https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7  
APU documentation: https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware

## CPU tested with:  
The SM83 per-instruction tests: https://github.com/SingleStepTests/sm83  
Blargg Test Roms: https://github.com/retrio/gb-test-roms  

## PPU tested with: 
dmg-acid2: https://github.com/mattcurrie/dmg-acid2  
scribbltests: https://github.com/Hacktix/scribbltests  

Various other tests used (not all passed) from: https://github.com/wilbertpol/mooneye-gb  

Many public domain ROM's can be found at: https://itch.io/games/downloadable/free/tag-gameboy-rom  
And demos can be found at: https://privat.bahnhof.se/wb800787/gb/demos/