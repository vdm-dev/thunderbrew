# Thunderbrew

[![Push](https://github.com/thunderbrewhq/thunderbrew/actions/workflows/push.yml/badge.svg)](https://github.com/thunderbrewhq/thunderbrew/actions/workflows/push.yml)

Welcome to Thunderbrew, a fork of [Whoa](https://github.com/whoahq/whoa), an unofficial open source implementation of the World of Warcraft 3.3.5a (build 12340) game client in C++11.

## Supported Platforms

Currently, Windows 10+, macOS 10.14+ (including recent versions of macOS on M1 and M2 processors), and Ubuntu 22.04 are supported.

## Building

On Ubuntu, the following packages are required to build Thunderbrew:

```bash
sudo apt install -y libglx-dev libxext-dev libopengl-dev libglvnd-dev
```

To build, ensure you have installed a recent version of CMake and an appropriate C++ build environment, and run the following from the `whoa` directory:

```
mkdir build && cd build
cmake ..
make install
```

Assuming all went well, you should see a `dist/bin` directory appear in the `build` directory. The `dist/bin` directory will contain a `Whoa` executable.

## Running

The data directory must either be a fully extracted MPQ archive set for World of Warcraft 3.3.5a (build 12340), or a directory that contains a `Data` subdirectory with 3.3.5a MPQ archives. 

Thunderbrew will attempt change its working directory at startup to the directory that contains the Whoa binary. You can either move your `Whoa` binary to the same directory that contains `Data/` and `WTF/`, launching it from there, or you can supply a different directory with the `-datadir \path\to\game_dir` command line switch. Note that the `-datadir` parameter must be specified with backslashes (\\), even on MacOS and Linux.

Assuming all goes well, you should be greeted by the login screen, complete with its flying dragon animation loop.

Whoa is very much a work-in-progress: it does not fully connect to a realm server, does not play back sound or music, and does not support customizing settings. These things will be supported over time.

![Whoa in action](./docs/img/login.png)

## Contributing

Please follow the guidelines contained in [CONTRIBUTING.md](./CONTRIBUTING.md) when making contributions.

## FAQ

**Why?**

It's fascinating to explore the development practices used to build a modern major video game.

**Why 3.3.5a?**

The game and its libraries have become significantly more complex in the intervening 10+ years. By picking 3.3.5a, it's possible to imagine this implementation will eventually be complete.

**Can I use this in my own development projects?**

It's probably a bad idea. The original game is closed source, and this project is in no way official.

## Legal

This project is released into the public domain.

World of Warcraft: Wrath of the Lich King ©2008 Blizzard Entertainment, Inc. All rights reserved. Wrath of the Lich King is a trademark, and World of Warcraft, Warcraft and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.
