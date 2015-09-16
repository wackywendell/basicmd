#include "verlet.hpp"

void VelocityVerlet::timestep() {
    atoms.x += atoms.v * dt;
    atoms.x += atoms.f * (dt*dt/2);
    
    atoms.v += atoms.f * (dt/2);
    
    atoms.f.setZero();
    forces.set_forces();
    atoms.v += atoms.f * (dt/2);
}

int main() {
    Atoms atoms = Atoms(8, 3.0);
    atoms.randomize_locations();
    
    // LennardJones forces = LennardJones(atoms, 1.0, 1.0, 2.5);
    LennardJones forces = LennardJones(atoms, 1.0, 1.0, pow(2, 1.0/6.0));
    flt U = forces.potential_energy() / atoms.N;
    std::cout << "U (rand):  " << U << std::endl;
    
    while(not (U < 2)){
        atoms.randomize_locations();
        U = forces.potential_energy() / atoms.N;
        std::cout << "U (rand):  " << U << std::endl;
    }
    
    atoms.randomize_velocities(1.0);
    atoms.f.setZero();
    
    VelocityVerlet verlet = VelocityVerlet(atoms, forces, 0.00001);
    for(uint i=0; i<10000; i++){
        verlet.timestep();
        atoms.scale_velocities(1.0, false);
        U = forces.potential_energy() / atoms.N;
        if(i % 1000 == 0){
            std::cout << "U (relax): " << U << std::endl;
        }
        if(U <= 0){
            break;
        }
    }
    
    verlet.dt = 0.002;
    for(uint i=0; i<50000; i++){
        verlet.timestep();
        if(i % 500 == 0){
            U = forces.potential_energy() / atoms.N;
            flt K = atoms.kinetic_energy() / atoms.N;
            
            std::cout 
                << "E (run):   " << (U+K) 
                << "    T: " << atoms.temperature(false)
                << std::endl;
        }
    }
    return 0;
}
