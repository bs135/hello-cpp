# hello-cpp

This is the hello-cpp project.

## development environment

### build tools

```bash
sudo apt install -y build-essential cmake
```

### libraries dependencies

```bash
sudo apt install -y nlohmann-json3-dev
```

### hiredis

- Refs: `/cloudbox/hung/var-fslc-yocto/sources/meta-openembedded/meta-oe/recipes-extended/hiredis/hiredis_0.14.0.bb`

```bash
git clone https://github.com/redis/hiredis.git
cd hiredis

git checkout 685030652cd98c5414ce554ff5b356dfe8437870

make
sudo make install

```

### redis++

- Refs: `var-fslc-yocto/sources/meta-openembedded/meta-oe/recipes-extended/redis-plus-plus/redis-plus-plus_1.2.2.bb`

```bash
git clone https://github.com/sewenew/redis-plus-plus.git
cd redis-plus-plus

git checkout 8ac506e6eb0e5c5b2625785b67400bde705773a1

mkdir build
cd build

# REDIS_PLUS_PLUS_CXX_STANDARD=17 cmake ..
cmake -DREDIS_PLUS_PLUS_CXX_STANDARD=17 ..

make
sudo make install

```

### yocto custom

```bash
# Add the following line to the file `redis-plus-plus_1.2.2.bb`

EXTRA_OECMAKE += " -DREDIS_PLUS_PLUS_CXX_STANDARD=17 "
```

## Building and installing

```bash
# init cmake
mkdir build
cd build

cmake ..

# make
make
# or
VERBOSE=1 make -j15

# run
./hello-cpp

# clean
make clean
```

## doxygen

install

```bash

sudo apt install -y doxygen
```

generate docs

```bash
doxygen Doxyfile

```

## References

- [journalctl](https://www.freedesktop.org/software/systemd/man/journalctl.html)
- [cpp styleguide](https://google.github.io/styleguide/cppguide.html)

## Licensing
