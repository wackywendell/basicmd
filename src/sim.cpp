#include "verlet.hpp"

int main() {
    /// 8 atoms, box of length 3.0.
    Atoms atoms = Atoms(8, 3.0);
    for(uint i=atoms.N / 2; i< atoms.N; i++){
        atoms.m(i) = pow(1.4, 3);
    }
    /// Put them in random places
    atoms.randomize_locations();
    
    /// The "standard" Lennard-Jones potential, 
    /// truncated and shifted at r = 2.5 sigma
    // LennardJones forces = LennardJones(atoms, 1.0, 1.0, 2.5);
    
    /// The "WCA" potential,
    /// equivalent to Lennard-Jones truncated and shifted at r = 2^(1/6) sigma
    LennardJones forces = LennardJones(atoms, 1.0, 1.0, pow(2, 1.0/6.0));
    
    /// Let's see what our potential energy is...
    flt U = forces.potential_energy() / atoms.N;
    std::cout << "U (rand):  " << U << std::endl;
    
    // We place the atoms randomly until they aren't overlapping too much.
    // This is not an efficient method, especially if we had more atoms,
    // but its simple.
    while(not (U < 1000)){
        atoms.randomize_locations();
        U = forces.potential_energy() / atoms.N;
        std::cout << "U (rand):  " << U << std::endl;
    }
    
    /// Randomize the velocities, reset the forces
    atoms.randomize_velocities(1.0);
    atoms.f.setZero();
    
    /// Let's "relax" the simulation, by running it with a "velocity-scaling"
    /// thermostat for a while.
    VelocityVerlet verlet = VelocityVerlet(atoms, forces, 0.0001);
    for(uint i=0; i<10000; i++){
        /// Take an energy-conserving step...
        verlet.timestep();
        // then rescale the velocities (definitely not energy-conserving!)
        atoms.scale_velocities(1.0, false);
        
        // And let's see what the potential energy is.
        if(i % 1000 == 0){
            U = forces.potential_energy() / atoms.N;
            std::cout << "U (relax): " << U << std::endl;
        }
    }
    
    /// Now let's do an energy-conserving run.
    verlet.dt = 0.002;
    for(uint i=0; i<50000; i++){
        verlet.timestep();
        if(i % 500 == 0){
            U = forces.potential_energy() / atoms.N;
            flt K = atoms.kinetic_energy() / atoms.N;
            
            /// Energy should stay *very* close to its original value, 
            /// within ~0.001 at all times.
            /// Temperature should be roughly stable at 1.0, but that is
            /// not a conserved quantity, so it will fluctuate. 
            std::cout 
                << "E (run):   " << (U+K) 
                << "    T: " << atoms.temperature(false)
                << std::endl;
        }
    }
    return 0;
}
