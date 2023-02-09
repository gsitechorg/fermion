# Baryon Simulator

## Initializing the Environment

```shell
mamba env create --force -f environment.yml
conda activate baryon
```

## Building

The following will compile the library and tests, and install the library to
`build/baryon-inst` which may be reference from dependent `CMakeList.txt` file
by exporting `$CMAKE_PREFIX_PATH`:

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=baryon-inst ..
make
make install
# To use the library in your dependency:
export CMAKE_PREFIX_PATH="$PWD/baryon-inst"
```

## Testing

Once you've executed `make` successfully, you may run the tests via:

```shell
./build/test/test-baryon
```
