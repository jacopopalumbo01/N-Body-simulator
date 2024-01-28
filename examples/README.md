# N-Body examples 
These examples reflect the history of the project development. We experimented different structures to describe the particles and the system, hence some examples may not be working anymore. We decided to keep them as an admonishment of our past mistakes, as well as a vestige of the project history. Among the currently working examples you can try an example with four spinning body clusters [here](/examples/example_galaxy/example_rotating_disk.cpp). You can also test yourself the performance of Barnes-Hut algorithm versus the standard direct-sum [here](/examples/example_speedup/example_BHspeedup.cpp). Another performance evaluation test for the speedup of the parallel OpenMP version can be found [here](/examples/example_speedup/example_speedup.cpp). FInally, an example that uses the Mpi-OpenMP hybrid can be tried [at this location](/examples/example_MPI/example_mpi.cpp).

## Usage
Enter any example folder and follow these instructions to run the code:

``` bash
# create new directory for compilation and execution
$ mkdir build

# enter the directory
$ cd build

# generate make files with cmake 
$ cmake ..

# compile
$ make

# run the executable with
$ ./NameOfTheExecutable
```

Each example generates a `.part` file, which stores the positions of the simulated objects over time.
In order to visualize the simulation with Python, move to the [graphics](/graphics/) folder and follow the instructions in the README. 
Make sure the `.part` file is present in said folder, since you will need it for the graphic rendering,