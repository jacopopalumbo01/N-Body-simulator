# N-body Simulator for Gravitational Objects
Project developed for Advanced Methods for Scientific Computing course of the HPC Engineering degree at Politecnico di Milano.

## Students

1. Jacopo Palumbo (jacopo.palumbo@mail.polimi.it)
  
2. Giorgio Daneri (giorgio.daneri@mail.polimi.it)
  
3. Elia Vaglietti (elia.vaglietti@mail.polimi.it)
  

## Overview

This project is an N-body gravitational simulator designed to model the interactions between multiple celestial objects under the influence of gravity. The N-body problem is a classical problem in physics and astrodynamics that involves predicting the motions of a group of celestial bodies as they interact with each other through gravitational forces.

## N-Body Problem

The N-body problem is a generalization of the two-body problem, where the gravitational interaction between multiple celestial objects is considered simultaneously. In the case of N bodies, each body exerts a gravitational force on every other body, resulting in a complex system of coupled differential equations. Solving these equations allows for the prediction of the positions and velocities of each body over time.

### Analytical Considerations

#### Well-Posedness

The N-body problem can't be solved analytically in an efficient way and is also chaotic, meaning that small changes in initial conditions can lead to significant differences in the long-term behavior of the system. This sensitivity to initial conditions is a hallmark of unstable systems. Therefore, predicting the precise trajectories of N bodies over extended periods can be inherently challenging.


#### Approximations

To address the analytical complexities, various approximations are often employed, including:

1. **Hierarchical Methods:** In many astronomical scenarios, hierarchical structures exist, such as stars orbiting within galaxies or planets orbiting within a solar system. Hierarchical methods, like the Barnes-Hut algorithm, exploit this structure to reduce the computational complexity of the simulation.
  
2. **Time-Stepping Methods:** Numerical integrators, such as the Verlet or Runge-Kutta method, are commonly used to approximate the solutions to the differential equations governing the N-body problem. The choice of integration method and time step is critical for balancing accuracy and computational efficiency.
  
3. **Regularization Techniques:** Singularities arising from close encounters between particles can lead to numerical instability. Regularization techniques, such as softening potentials, are applied to mitigate these issues.
  

## Main Application: Gravitational Objects in a Simplicial Way

This simulator is particularly well-suited for modeling scenarios where objects interact gravitationally in a simplicial way. In a simplicial interaction, each object influences the others in a straightforward and direct manner, forming a network of gravitational connections. This could be applied to various astrophysical and cosmological scenarios, such as the gravitational interaction between stars in a galaxy, planets in a solar system, or galaxies in a galaxy cluster.

## Technical Details

### Particle Interactions

The simulation employs a numerical integration method to solve the gravitational N-body problem. The gravitational force acting on each particle is calculated based on Newton's law of gravitation:

<span style="font-size: x-large;">$F_{ij} = G\frac{m_i m_j}{r_{ij}^2} \frac{\mathbf{r_{ij}}}{|{\mathbf{r_{ij}}|}}$</span>

where:

- $F_{ij}$​ is the gravitational force between particles $i$ and $j$,
  
- $G$ is the gravitational constant,
  
- $m_i$​ and $mj$​ are the masses of particles $i$ and $j$,
  
- $r_{ij}$​ is the vector pointing from particle $i$ to particle $j$, and
  
- $\mathbf{r_{ij}}​$ is the distance between particles $i$ and $j$.
  

The total force acting on each particle is the sum of the individual forces from all other particles in the simulation.

### Integration Method

To update the positions and velocities of particles over time, the simulator uses a numerical integration method. The input is the acceleration that has been computed with the above formula. We are interested in the new velocities and positions of the bodies at each time step of the simulation, therefore we need to approximate the integral of the acceleration.
The choice of integration method is crucial for accuracy and stability. The user can configure the simulation parameters, including the integration time step, to achieve a balance between accuracy and computational efficiency. We offer a wide array of numerical methods, ranging from simple Forward Euler method and the more precise and stable Verlet method, as well as several Runge-Kutta multistage methods. More information can be found in the docs folder [link](/docs/). The integration method is passed as template parameter to the particle system.

## Project Structure

The project is structured as follows:

- **examples** folder contains tests of the code of incremental complexity. Bear in mind that the structure of the project has changed throughout its development, therefore some examples may be obsolete and not working anymore. We kept them as an historical record of our work over the project.
  
- **graphics** folder includes the python scripts necessary for parsing the output files produced by the examples and creating the plot of the system over time. This is one of two ways to visualize the simulation graphically and surely the less impressive one. If you'd like a more beautiful and immersive simulation, head over the folder [link](/examples/example_OF/) and check out the OpenFrameworks library. The relative git repository is included in the submodules, have a look at it if you are interested.
  
- **inc** folder contains all the *hpp* files that constitute the core of the simulator. It is further partitioned in all the classes that describe its structure.
  
- **src** folder contains all the *cpp* files that implement the method declared in the files above.
  
- **docs** folder contains a brief description of the main classes and relative methods, as well as a detailed report on the project structure, the numerical methods involved and the tests that were run to asses its performance.
  
- **tests/benchmarks** folder allows you to test the code and extract performance parameters depending on the number of particles involved in the simulation. It is based on the Google Benchmark repository, which is linked above.
  

## Getting Started

To run the simulator, follow these steps:

1. Clone the repository to your local machine.
  
2. Choose one of the provideed examples, or build one yourself. Bear in mind that not all of examples work due to past major changes in the project structure. You can find further information the dedicated folder.
  
3. Try the benchmark utilities to test the time required for the code execution. Future implementations will feature an estimation of the algorithm complexity. You can infere the scalability of the program with respect to the number of objects included in the simulation. Further information in the **tests/Benchmarks** folder.

## How To Run Your Code
This library is intended to be used as a static library. There are a few steps to follow to build and use the library. 

The first thing to do is compile the library. We have configured a CMakeFile to make this step as easy as possible.
Requirements:
- boost library
- mpi

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

Always remember to include the library headers file in your cpp file as follows:
```cpp
#include <N-Body-sim.hpp>
```

To use the library we recommend you to read the full documentation.
Now that you have written your first N-body project, you are ready to compile and run. You should always remember to include the static library and the header file. 
```bash
$ g++ yourFile.cpp -IPATH/TO/LIBRARY/inc -LPATH/TO/LIBRARY/build -ln-body-sim -o yourFile.o
```

## Running With mpi
You should check the folder ```examples/example_MPI```. Remember to initialize and finalize mpi with:
```cpp
// Initialize the MPI environment
MPI_Init(NULL, NULL);

// Finalize the MPI environment.
MPI_Finalize();
```
In the actual version, only systems with ```RKDiscretizer``` as discretization method have an mpi implementation.