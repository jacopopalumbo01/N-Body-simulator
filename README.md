# N-body

## About
Serial and parallel N-body simulator developed for Polimi Advanced Methods for Scientific Computing project
---

## Students
1. Jacopo Palumbo (jacopo.palumbo@mail.polimi.it)
2. Giorgio Daneri (giorgio.daneri@mail.polimi.it)
3. Elia Vaglietti (elia.vaglietti@mail.polimi.it)

## Installation of submodules
### Google Benchmark
```bash
# Update all submodules
$ git submodule update --init --recursive

# Make a build directory to place the build output.
$ cmake -E make_directory "build"

# Generate build system files with cmake, and download any dependencies.
$ cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../

# Build the library
$ cmake --build "build" --config Release
```
