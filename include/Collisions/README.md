# Boundary class
This class represents the boundaries of the n-body problem. You can extend this class to create new custom boundaries.

## CubeBoundary
This type of boundary is determined by 6 planes (which correspond to the six faces of a cube). When a particle hits a plane, we consider the force component which is
perpendicular to the plane and we invert it. 
