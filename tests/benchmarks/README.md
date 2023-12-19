## Installation of submodules
### Google Benchmark
Google benchmark is a useful method to test the time taken for the execution of the simulation with an increasing numbers of particles in the system. Inthe future it will be capacle of roughly estimating the complexity of the algorithm used for the numerical resolution of the problem. To install the benchmark on your machine you need to follow these instructions (compilation might take same time). 

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
