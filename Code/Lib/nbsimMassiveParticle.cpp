#include "nbsimMassiveParticle.h"

namespace nbsim{
    MassiveParticle::MassiveParticle(Eigen::Vector3d init_position, Eigen::Vector3d init_velocity,double init_mass):Particle(init_position,init_velocity){
        
        mass=init_mass;   
    };
    MassiveParticle::~MassiveParticle(){};
    double MassiveParticle::getMu(){
        
        return mass*6.67408e-11;
    };
    void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> attractor){
        attractor_all.insert(attractor);
    };
    void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> attractor){
        attractor_all.erase(attractor);
    };
    void MassiveParticle::calculateAcceleration(){
        acceleration<<0,0,0;
        for(auto attractor:attractor_all){
            
            Eigen::Vector3d r_i=getPosition()-attractor->getPosition();
            acceleration+=-attractor->getMu()/r_i.dot(r_i)*r_i.normalized();
        }
    };
    void MassiveParticle::integrateTimestep(const double& timestep){
        current_position+=current_velocity*timestep;
        current_velocity+=acceleration*timestep;
    };
}