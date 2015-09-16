#include "atoms.hpp"

std::random_device rand_device;
std::default_random_engine rand_engine(rand_device());
std::normal_distribution<> norm_distribution(0.0, 1.0);
std::uniform_real_distribution<> lin_distribution(0.0, 1.0);

Atoms::Atoms(uint N) : N(N), x(VecArray::Zero(N, NDIM)), v(VecArray::Zero(N, NDIM)), f(VecArray::Zero(N, NDIM)) {}

void Atoms::randomize_locations(flt L){
    for(uint i=0; i<N; i++) for(uint j=0; j<NDIM; j++) {
        x(i,j) = lin_distribution(rand_engine) * L;
    }
}

void Atoms::randomize_velocities(flt T){
    for(uint i=0; i<N; i++) for(uint j=0; j<NDIM; j++) {
        v(i,j) = norm_distribution(rand_engine) * sqrt(T);
    }
}

int main() {
    Atoms atoms = Atoms(10);
    atoms.randomize_locations(10);
    std::cout << atoms.x << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << (atoms.x.rowwise().squaredNorm()) << std::endl;
    return 0;
}
