# cpp20experiments
Experiments with C++20

You will need GNU 11. Currently available in Ubuntu (hirsute) Universe. Building with cmake:
```
git clone https://github.com/coffeeaddict19/cpp20experiments.git
cd cpp20experiments
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-11 -DCMAKE_CXX_COMPILER=/usr/bin/g++-11 -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
ctest
ctest -T memcheck
```
Usage, print out memory map of process (root not required):
```
/procmapwrapper bash
```
Usage, write memory pathname to file (root required):
```
sudo ./procmapwrapper bash [heap]
```
