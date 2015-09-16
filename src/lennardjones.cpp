#include "lennardjones.hpp"

void LennardJones::set_forces(){
    for(uint i=0; i<atoms.N; i++){
        for(uint j=0; j<i; j++){
            Vec dist = atoms.dist(i, j);
            flt dist_squared = dist.squaredNorm() / (sigma*sigma);
            
            if(dist_squared > (cut*cut)) continue;
            
            // sigma^6 / r^6
            flt dist_neg6 = 1.0 / (dist_squared*dist_squared*dist_squared);
            
            // sigma^12 / r^12
            flt dist_neg12 = dist_neg6 * dist_neg6;
            
            // 4 epsilon * (12 sigma^12 / r^13 - 6 sigma^6 / r^7) / r
            flt fmag = (12 * dist_neg12 - 6 * dist_neg6) * 4 * epsilon / dist_squared;
            
            Vec f = dist * fmag;
            
            atoms.f.row(i) += f;
            atoms.f.row(j) -= f;
        }
    }
}

flt LennardJones::potential_energy(){
    flt E = 0;
    for(uint i=0; i<atoms.N; i++){
        for(uint j=0; j<i; j++){
            flt dist_squared = atoms.dist(i, j).squaredNorm() / (sigma*sigma); // r^2 / sigma^2
            if(dist_squared > (cut*cut)) continue;
            
            // sigma^6 / r^6
            flt dist_neg6 = 1.0 / (dist_squared*dist_squared*dist_squared);
            
            // sigma^12 / r^12
            flt dist_neg12 = dist_neg6 * dist_neg6;
            
            // std::cout << "Distance: " << sqrt(dist_squared) 
            //     << "  neg6: " << dist_neg6
            //     << "  neg12: " << dist_neg12
            //     << "  eps: " << epsilon
            //     << "  E0: " << E0
            //     << "  Eij: " << (4*epsilon*(dist_neg12 - dist_neg6 - E0))
            //     << std::endl;
                
            
            E += dist_neg12 - dist_neg6 - E0;
        }
    }
    
    return E*4*epsilon;
}
