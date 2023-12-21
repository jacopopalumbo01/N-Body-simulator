# N-Body examples 
These examples reflect the history of the project development. We experimented different structures to describe the particles and the system, hence some examples may not be working anymore. We decided to keep them as an admonishment of our past mistakes, as well as a vestige of the project history. 

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
In order to visualize the simulation, move to the `graphics` folder and follow the instructions in the README. 
Make sure the `.part` file is present in said folder, since you will need it for the graphic rendering,