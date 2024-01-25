# Install
This library is intended to be used as a static library. There are a few steps to follow to build and use the library. 

## Requirements
- Boost library
- MPI
- OpenMP
- CMake
- Make
- g++
- mk modules (not mandatory)

## How To Compile The Library
Our CMakeLists is built for systems with mk modules installed. If you don't have it, no problem, you just need to modify the following line of ```CMakeLists.txt```:
```
18 # Include Boost Library for mk modules
19 add_compile_options(-I$ENV{mkBoostInc} -L$ENV{mkBoostLib} -lboost_iostreams -lboost_serialization)
```
Instead of ```$ENV{mkBoostInc}``` and ```$ENV{mkBoostLib}``` insert the path where your boost library is installed. Then you can compile as follows.

```bash
$ mkdir build

$ cd build

# Compile
$ cmake ..

$ make
```

You have succesfully built the static library named "libn-body-sim.a"! Now you are ready to use the simulator.

## Building The Examples
Inside the folder ```/examples``` you can find some examples of usage of the library. Most of the examples are included for "historical reasons" and don't work with the actual status of the library. You can compile an example as follows:

```bash
$ mkdir build

$ cd build

# Compile
$ cmake ..

$ make
```

The examples that we reccomend to watch at the current time are:
- ```/example_MPI```, MPI usage, only works with ```NBodyEnv::RKDiscretizer```
- ```/example_speedup```, speedup between serial and parallel version
- ```/example_galaxy```, galaxy example
- ```/example_BH```, Barnes Hut

### Note
Remember to modify the file ```CMakeLists.txt``` if you don't have mk modules installed on your machine.

## Compile Your Files
Always remember to include the library headers file in your cpp file as follows:
```cpp
#include <N-Body-sim.hpp>
```

To use the library we recommend you to read the full documentation.
Now that you have written your first N-body project, you are ready to compile and run. You should always remember to include the static library and the header file. 

```bash
$ g++ yourFile.cpp -IPATH/TO/LIBRARY/inc -LPATH/TO/LIBRARY/build -ln-body-sim -fopenmp -o yourFile.o
```

The optimal solution is to use as a template a ```CMakeLists.txt``` included in the examples.