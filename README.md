# hello-cpp

This is the hello-cpp project.

## install dependencies

```bash
sudo apt install -y \
    build-essential \
    cmake \
    nlohmann-json3-dev \

```

## Building and installing

```bash
# init cmake
mkdir build && cd build
cmake ..

# make
VERBOSE=1 make -j15
# or


# run
./hello-cpp

# clean
make clean
```

## Licensing
