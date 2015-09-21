#include "lennardjones.hpp"

class VelocityVerlet {
public:
  Atoms &atoms;
  LennardJones &forces;
  flt dt;

public:
  VelocityVerlet(Atoms &atoms, LennardJones &forces, flt dt)
      : atoms(atoms), forces(forces), dt(dt){};

  flt energy() { return atoms.kinetic_energy() + forces.potential_energy(); }

  void timestep();
};
