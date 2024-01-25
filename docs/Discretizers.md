# Discretizer
To solve the ODEs system for computing new positions of each particle you need to choose your preferred discretizer. Actually this library exposes three possible discretizers.

## EulerDiscretizer
Implements an explicit Euler discretizer, which is not A-stable (absolutely stable). It's the fastest and the worse at the same time.

```c++
NBodyEnv::EulerDiscretizer();
```

## RKDiscretizer
Implements the Runge-Kutta methods using a Butcher table. There are several discretizing method available with RKDiscretizer.