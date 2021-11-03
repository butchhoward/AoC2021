# Advent of Code 2021
[![Build Status](https://github.com/butchhoward/AoC2021/workflows/check-build/badge.svg)](https://github.com/butchhoward/AoC2021/actions)

Having a bit of fun with [Advent of Code](https://adventofcode.com/)

No real plan, just doing it as it comes with whatever feels right that day.


# Notes

## MacOS gcc Woes

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

```
ln -s /usr/local/bin/gcc-10 /usr/local/bin/gcc
ln -s /usr/local/bin/gcc-10 /usr/local/bin/cc
ln -s /usr/local/bin/g++-10 /usr/local/bin/g++
ln -s /usr/local/bin/cpp-10 /usr/local/bin/cpp
ln -s /usr/local/bin/c++-10 /usr/local/bin/c++
```

I waste some time trying to figure out why `gcc --version` still reports Clang but `g++ --version` reports GCC. Never figured it out. Gave up since this project does not care. For some reason MacOS points raw `gcc` at the XCode stuff regardless of what is in the `$PATH`.

```
+AoC2020 $ gcc --version
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
Apple clang version 11.0.0 (clang-1100.0.33.16)
Target: x86_64-apple-darwin19.6.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
+AoC2020 $
+AoC2020 $ g++ --version
g++ (Homebrew GCC 10.2.0) 10.2.0
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

+AoC2020 $ which gcc
/usr/local/bin/gcc
+AoC2020 $ which g++
/usr/local/bin/g++
+AoC2020 $ $(which gcc) --version
gcc (Homebrew GCC 10.2.0) 10.2.0
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
