#include "atoms.hpp"

std::random_device rand_device;
std::default_random_engine rand_engine(rand_device());
std::normal_distribution<> norm_distribution(0.0, 1.0);
std::uniform_real_distribution<> lin_distribution(0.0, 1.0);

Vec vec_remainder(Vec r, Vec l) {
  for (uint k = 0; k < NDIM; k++) {
    r(k) = remainder(r(k), l(k));
  }
  return r;
}

Vec vec_remainder(Vec r, flt l) {
  for (uint k = 0; k < NDIM; k++) {
    r(k) = remainder(r(k), l);
  }
  return r;
}

Atoms::Atoms(uint N, flt L)
    : N(N), L(L), x(VecArray::Zero(N, NDIM)), v(VecArray::Zero(N, NDIM)),
      f(VecArray::Zero(N, NDIM)), m(VecD::Ones(N)) {}

Vec Atoms::dist(uint i, uint j) {
  Vec dist = x.row(i) - x.row(j);
  return vec_remainder(dist, L);
}

void Atoms::randomize_locations() {
  for (uint i = 0; i < N; i++)
    for (uint j = 0; j < NDIM; j++) {
      x(i, j) = lin_distribution(rand_engine) * L;
    }
}

void Atoms::randomize_velocities(flt T) {
  for (uint i = 0; i < N; i++)
    for (uint j = 0; j < NDIM; j++) {
      v(i, j) = norm_distribution(rand_engine) * sqrt(T);
    }
}

void Atoms::scale_velocities(flt T, bool subtract_com) {
  flt T0 = temperature(subtract_com);
  flt scale_factor = sqrt(T / T0);
  v *= scale_factor;
}

flt Atoms::kinetic_energy() {
  flt mass_v_sum = v.rowwise().squaredNorm().transpose() * m;
  return mass_v_sum / 2.0;
}

flt Atoms::temperature(bool subtract_com) {
  int degrees_of_freedom;
  if (subtract_com && N > 0)
    degrees_of_freedom = (N - 1) * NDIM;
  else
    degrees_of_freedom = N * NDIM;

  return kinetic_energy() * 2.0 / degrees_of_freedom;
}
