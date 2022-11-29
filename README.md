# hello-cpp

This is the hello-cpp project.

## install dependencies

```bash
sudo apt install -y \
    build-essential \
    libssl-dev \
    cmake \
    nlohmann-json3-dev \
    # libspdlog-dev

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
