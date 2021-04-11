#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>


namespace nbsim{

    class Particle{
    public:
    Particle(Eigen::Vector3d,Eigen::Vector3d);
    ~Particle();
    Eigen::Vector3d getPosition();
    Eigen::Vector3d getVelocity();
    void integrateTimestep(Eigen::Vector3d acceleration,double timestep);
    private:
    Eigen::Vector3d current_position, current_velocity;
    };
}
#endif