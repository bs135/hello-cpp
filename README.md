# hello-cpp

This is the hello-cpp project.

## install dependencies

```bash
sudo apt install -y build-essential \
    libssl-dev \
    cmake \
    nlohmann-json-dev \
    libspdlog-dev

```

## Building and installing

For first time

```bash
rm -rf build
cmake -S . -B build
```

build using cmake command

```bash
cmake --build build

# run
./build/hello-cpp

# clean
cmake --build build --target clean

```

```bash
cd build
make

# run
./hello-cpp

# clean
make clean
```

## Licensing
