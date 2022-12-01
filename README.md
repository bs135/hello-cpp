# hello-cpp

This is the hello-cpp project.

## development environment

### build tools

```bash
sudo apt install -y \
    build-essential \
    cmake
```

### libraries dependencies

```bash
sudo apt install -y \
    nlohmann-json3-dev
```

### hiredis

```bash
git clone https://github.com/redis/hiredis.git
cd hiredis

git checkout 685030652cd98c5414ce554ff5b356dfe8437870

make
sudo make install

```

### redis++

```bash
git clone https://github.com/sewenew/redis-plus-plus.git
cd redis-plus-plus

git checkout 8ac506e6eb0e5c5b2625785b67400bde705773a1

mkdir build
cd build

REDIS_PLUS_PLUS_CXX_STANDARD=17 cmake ..

make
sudo make install

```

## Building and installing

```bash
# init cmake
mkdir build
cd build

cmake ..

# make
VERBOSE=1 make -j15
# or
make

# run
./hello-cpp

# clean
make clean
```

## Licensing
