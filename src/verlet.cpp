#include "verlet.hpp"

void VelocityVerlet::timestep() {
    atoms.x += atoms.v * dt;
    atoms.x += atoms.f * (dt*dt/2);
    
    atoms.v += atoms.f * (dt/2);
    
    atoms.f.setZero();
    forces.set_forces();
    atoms.v += atoms.f * (dt/2);
}
