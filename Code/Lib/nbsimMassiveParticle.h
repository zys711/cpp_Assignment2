#ifndef nbsimMassiveParticle_h
#define nbsimMassiveParticle_h
#include "nbsimParticle.h"
#include <Eigen/Dense>
#include <set>
#include <memory>
#include <iostream>

namespace nbsim{
    class MassiveParticle: public Particle{
        public:
        MassiveParticle(Eigen::Vector3d init_position, Eigen::Vector3d init_velocity, double init_mass);
        ~MassiveParticle();
        double getMu();
        void addAttractor(std::shared_ptr<MassiveParticle> attractor);
        void removeAttractor(std::shared_ptr<MassiveParticle> attractor);
        void calculateAcceleration();
        void integrateTimestep(const double& timestep);
        private:
        Eigen::Vector3d acceleration;
        std::set<std::shared_ptr<MassiveParticle>> attractor_all;
        double mass;
    };
}
#endif