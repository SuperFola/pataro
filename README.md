# Pataro

![CMake badge](https://img.shields.io/github/workflow/status/ArkScript-lang/Ark/CMake?logo=cmake&style=for-the-badge)

A C++ 17 Rogue Like library built on top of [lib TCOD](https://github.com/libtcod/libtcod).

Pataro means *Walker Male* in Quenya.

Read **[ARCHITECTURE.md](ARCHITECTURE.md)** before diving in.

## Deps

* download [tcod 1.16.6](https://github.com/libtcod/libtcod/releases/tag/1.16.6) and put it under tcod/
* CMake >= 3.8

### Building

First, clone the repository and refresh the submodules to get vcpkg, then bootstrap vcpkg and install it.

Then you can compile using CMake, don't forget to point to vcpkg toolchain cmake file.

```shell
git clone https://github.com/SuperFola/Pataro.git
cd Pataro
git submodule update --init --recursive
(cd vcpkg && ./bootstrap-vcpkg && ./vcpkg integrate install)
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
```

## Controls

- Move/attack with the arrows (`up`, `down`, `left`, `right`)
- Take a screenshot with `F3`
- Collect objects with `g`
- Open the inventory with `i`

## Roadmap

- [x] generation of the world map (rooms + corridors)
- [x] field of view handling
- [x] explored tiles handling
- [x] the player can move and attack
- [x] monsters spawn, can follow the player (if they are in their field of view) and attack them
- [x] everyone has health points, attack power, and AI
- [ ] transitionning from libtcod event system to SDL event system
- [x] the world map moves with the player
- [x] GUI about the player, events...
- [x] inventory GUI
- [x] items handling, generation and spawn
- [x] spells and ranged combat
- [ ] travelling between levels / floors
- [ ] saving player progress on a given map + level
- [ ] loading preconfigured maps/levels (eg the overworld with shops...)
- [ ] add a game menu
- [ ] dungeons and character progression
- [ ] (generic?) scripting engine to configure Pataro's engine