#include "verlet.hpp"

void VelocityVerlet::timestep() {
  VecArray a = (atoms.f.array().colwise() / atoms.m.array()).matrix();
  atoms.x += atoms.v * dt;
  atoms.x += a * (dt * dt / 2);

  atoms.v += a * (dt / 2);

  atoms.f.setZero();
  forces.set_forces();
  a = (atoms.f.array().colwise() / atoms.m.array()).matrix();
  atoms.v += a * (dt / 2);
}
