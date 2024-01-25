# Types 

## ParticleType
The type of particle.
```c++
enum ParticleType
{
gravitational,
em
};
```


## Pos
Represent a position in a 3d space.
```c++
NBodyEnv::Pos(double xPos, double yPos, double zPos);


double NBodyEnv::Pos::getDistance(Pos pos);
/*
*   Returns the distance between the Pos of the called method 
*   and the Pos passed
*/
```

## Vel
Represent a velocity in a 3d space.
```c++
NBodyEnv::Vel(double xVel, double yVel, double zVel);
```

## Acc
Represent an acceleration in a 3d space.
```c++
NBodyEnv::Acc(double xAcc, double yAcc, double zAcc);
```

## Force
Represent a force in a 3d space.
```c++
NBodyEnv::Force(double xForce, double yForce, double zForce);

void NBodyEnv::Forceinvert();
/*
*   Inverts the force
*/
```

## Particle
[See Particle docs](Particle.md)

## System
[See System docs](System.md)

## EulerDiscretizer
[See Discretizers docs](Discretizers.md)

## RKDiscretizer
[See Discretizers docs](Discretizers.md)

## VerletDiscretizer
[See Discretizers docs](Discretizers.md)

[Back to Index](Index.md)
