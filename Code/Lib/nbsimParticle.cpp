#include "nbsimParticle.h"
#include <Eigen/Dense>

namespace nbsim{
    Particle::Particle(Eigen::Vector3d init_position, Eigen::Vector3d init_velocity){
        current_position=init_position;
        current_velocity=init_velocity;
    }
    Particle::~Particle(){};
    Eigen::Vector3d Particle::getPosition(){
        return current_position;
    };
    Eigen::Vector3d Particle::getVelocity(){
        return current_velocity;
    };
    void Particle::integrateTimestep(Eigen::Vector3d acceleration, double timestep){
        current_position+=current_velocity*timestep;
        current_velocity+=acceleration*timestep;
    }
}