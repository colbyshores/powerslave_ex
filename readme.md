# Powerslave EX Linux
Quick-and-dirty build system to get Linux binaries out of the old Powerslave EX
source code. Since Angelscript and FFmpeg broke their API in the meantime,
this will get and build old source releases as well.

## Building
```
make lib
make -j16
```

## Game files
Since the original project seems to have attracted some copyright holder asshole
the required game files are not officially distributed by its creator anymore.
Copy them to a `game_data` folder at the root of this repo before compiling,
or simply add them to the `bin` folder afterwards to be able to play.
You will need:
 - the `game.kpf` file (required)
 - the `movies` folder (optional/recommended)
 - the `music` folder (optional/recommended)
 - the `addons` folder (optional/mods)

## Running
```
./bin/run.sh
```
