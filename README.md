
# Flocking Simulation

<img width="720" height="466" alt="C++3_5秒_完成" src="https://github.com/user-attachments/assets/1e0646f8-d75e-4d5f-bafe-43ee60023a13" />


A flocking and steering behavior simulation implemented in C++ with OpenGL.

Multiple particles move together by responding to nearby particles.
The simulation combines centering, velocity matching, collision avoidance,
and leader-following behaviors to create flock-like motion.

## Features

- Flocking behavior simulation
- Centering behavior
- Velocity matching
- Collision avoidance
- Leader-following behavior
- Dynamic leader switching
- OpenGL visualization
- Adjustable behavior parameters

## Controls

- `K` / `k`: Increase or decrease centering strength
- `M` / `m`: Increase or decrease velocity matching strength
- `A` / `a`: Increase or decrease collision avoidance strength

## Implementation

Each particle calculates its acceleration based on nearby particles.

The simulation uses three main behaviors:

- Centering: Moves particles toward nearby group members.
- Velocity Matching: Encourages particles to move in similar directions.
- Collision Avoidance: Prevents particles from getting too close.
  
One particle acts as the leader. The leader changes direction and is
periodically replaced by another particle. The remaining particles follow
the leader while also applying the flocking behaviors.

## Credits

Some source files and the PBA framework were provided as course starter code
by Jerry Tessendorf.

My work focuses on implementing and modifying the flocking behaviors,
leader-following behavior, collision avoidance, velocity matching,
and particle movement.

## Academic Context

This project was developed as part of a
Physically-Based Modeling and Animation course assignment.
