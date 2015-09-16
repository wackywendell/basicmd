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

double random_gaussian(double odummy);


class Atoms {
    public:
        uint N;
        VecArray x;
        VecArray v;
        VecArray f;
    
    public:
        Atoms(uint N);
        
        void randomize_locations(flt box_length);
        void randomize_velocities(flt temperature);
        
        // flt temperature();
        // flt kinetic_energy();
};
