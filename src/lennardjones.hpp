#include "atoms.hpp"

/// The Lennard-Jones potential,
/// U = 4 epsilon (sigma^12 / r^12 - sigma^6 / r^6)
class LennardJones {
public:
  Atoms &atoms;
  flt sigma;
  flt epsilon;
  flt cut;
  flt E0;

public:
  LennardJones(Atoms &atoms, flt sigma = 1.0, flt epsilon = 1.0, flt cut = 2.5)
      : atoms(atoms), sigma(sigma), epsilon(epsilon), cut(cut) {
    flt cut_neg6 = pow(cut, -6);
    flt cut_neg12 = cut_neg6 * cut_neg6;
    E0 = cut_neg12 - cut_neg6;
  }

  void set_forces();
  flt potential_energy();
};
