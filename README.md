# Advent of Code 2021
[![Build Status](https://github.com/butchhoward/AoC2021/workflows/check-build/badge.svg)](https://github.com/butchhoward/AoC2021/actions)

Having a bit of fun with [Advent of Code](https://adventofcode.com/)

No real plan, just doing it as it comes with whatever feels right that day.


# Notes

## MacOS gcc Woes

These (carried over from last years AoC2020) still apply with the the Apple M1 (arm64).

I want to try some C++ 20 newness.

Macos Xcode Clang sort of doesn't have all of it yet.

So, I install gnu gcc

```
brew install gcc
```

Which puts `gcc-10` and friends in a place (a Cellar somewhere with symlink in `/usr/loca/bin/`).

Which is not found because `$PATH`. So, it mess with `.bash_profile` and get the path updated.

Which leave `gcc` and `g++` still not found.  Turns out `brew` does not create those symlinks.

So, I create them:

```shell
ln -s "$(brew --prefix)/bin/gcc-11" /usr/local/bin/gcc-11
ln -s "$(brew --prefix)/bin/g++-11" /usr/local/bin/g++-11
ln -s "$(brew --prefix)/bin/cpp-11" /usr/local/bin/cpp-11
ln -s "$(brew --prefix)/bin/c++-11" /usr/local/bin/c++-11
```

I waste some time trying to figure out why `gcc --version` still reports Clang but `g++ --version` reports GCC. Never figured it out. Gave up since this project does not care. For some reason MacOS points raw `gcc` at the XCode stuff regardless of what is in the `$PATH`.

Added for CMake now. This has be be set before anything sets a language or other compiler option:

```
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")
```

I have not found a way in CMake not to have to give the path.
