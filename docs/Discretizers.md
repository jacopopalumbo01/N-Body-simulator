# Discretizer
To solve the ODEs system for computing new positions of each particle you need to choose your preferred discretizer. Actually this library exposes three possible discretizers.

## EulerDiscretizer
Implements an explicit Euler discretizer, which is not A-stable (absolutely stable). It's the fastest and the worse at the same time.

```c++
NBodyEnv::EulerDiscretizer();
```

## RKDiscretizer
Implements the Runge-Kutta methods using a Butcher table. There are several discretizing method available with RKDiscretizer. The avilable methods are:

### Explicit Methods
- Forward Euler ```DISC_FEULER```
- Explicit Midpoint ```DISC_EXPMID```
- Heun ```DISC_HEUN```
- Ralston ```DISC_RALSTON```
- Runge Kutta third order ```DISC_KUTTA3```
- Heun third order ```DISC_HEUN3```
- Van der Houwen's/Wray third-order method ```DISC_WRAY3```
- Ralston's third-order method ```DISC_RALSTON3```
- Third-order Strong Stability Preserving Runge-Kutta ```DISC_SSPRK3```
- Runge-Kutta fourth order ```DISC_RK4```
- Runge-Kutta 3-8 ```DISC_RK38```
- Ralston's fourth-order method ```DISC_RALSTON4```

### Implicit Methods
- Backward Euler ```DISC_BEULER```
- Implicit Midpoint ```DISC_IMPMID```
- Crank-Nicolson ```DISC_CRANKNIC```

To use RKDiscretizer follow this example:
```c++
// Example for RK4
NBodyEnv::RKDiscretizer rk = NBodyEnv::RKDiscretizer(DISC_RK4);

NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rk, 1.0);
```

## VerletDiscretizer
Implements a Verlet discretizer (multi-step method).


[Back to Index](Index.md)