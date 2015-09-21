#include <Eigen/Dense>

#include <random>
#include <iostream>

// Use 2D or 3D based on compiler switch
#ifdef VEC2D
#define NDIM 2
#else
#ifndef VEC3D
#define VEC3D
#endif
#endif
#ifdef VEC3D
#define NDIM 3
#endif

// Use 'double' for simulations
typedef double flt;
// For ease of use
typedef unsigned int uint;

typedef Eigen::Matrix<flt, NDIM, 1> Vec;
typedef Eigen::Matrix<flt, Eigen::Dynamic, NDIM> VecArray;
typedef Eigen::Matrix<flt, Eigen::Dynamic, 1> VecD;

/// For taking the "remainder" function on a vector; needed for periodic
/// boundary conditions.
Vec vec_remainder(Vec r, Vec l);
Vec vec_remainder(Vec r, flt l);

class Atoms {
public:
  uint N;
  flt L;
  VecArray x;
  VecArray v;
  VecArray f;
  VecD m;

public:
  Atoms(uint N, flt box_length);

  void randomize_locations();
  void randomize_velocities(flt temperature);
  void scale_velocities(flt T, bool subtract_com);

  /// "nearest" distance between particles i and j, given periodic boundary
  /// conditions.
  Vec dist(uint i, uint j);

  flt kinetic_energy();
  /// We calculate temperature via the equipartition theorem
  flt temperature(bool subtract_com);
};
