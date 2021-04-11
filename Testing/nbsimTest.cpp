#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimMyFunctions.h"
#include "nbsimParticle.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <math.h>

TEST_CASE("check if the particle moves as excepted when no acceleration","[Particle]"){
    
    Eigen::Vector3d zero_acceleration(0,0,0),test_position(0,0,0),test_velocity(1,1,1);
    nbsim::Particle test1_particle(test_position,test_velocity);
    double test1_timestep=0.01, test1_time=5;
    for(double i=0;i<test1_time;i+=test1_timestep){
        test1_particle.integrateTimestep(zero_acceleration,test1_timestep);
    }
    REQUIRE(test1_particle.getVelocity().isApprox(test_velocity,0));
    REQUIRE(test1_particle.getPosition().isApprox(test_position+test_velocity*test1_time,0.01));

}

TEST_CASE("check if the particle moves as excepted when constant acceleration","[Particle]"){
    Eigen::Vector3d constant_acceleration(1,1,1),test_position(0,0,0),test_velocity(1,1,1);
    nbsim::Particle test2_particle(test_position,test_velocity);
    double test2_timestep=0.01, test2_time=5;
    for(double i=0;i<test2_time;i+=test2_timestep){
        test2_particle.integrateTimestep(constant_acceleration,test2_timestep);
    }
    REQUIRE(test2_particle.getVelocity().isApprox(test_velocity+constant_acceleration*test2_time,0.01)); //v=v_0+a*t
    REQUIRE(test2_particle.getPosition().isApprox(test_position+test_velocity*test2_time+0.5*constant_acceleration*test2_time*test2_time,0.01)); //d=d_0+0.5*a*t^2

}

TEST_CASE("check if the particle moves as excepted when a fictitious centripetal acceleration applied","[Particle]"){
    
    Eigen::Vector3d test_position(1,0,0),test_velocity(0,1,0);
    nbsim::Particle test3_particle(test_position,test_velocity);
    
    double test3_timestep=0.001, test3_time=2*M_PI;
    for(double i=0;i<test3_time;i+=test3_timestep){
        Eigen::Vector3d centripetal_acceleration=-test3_particle.getPosition();
        test3_particle.integrateTimestep(centripetal_acceleration,test3_timestep);
    }
    REQUIRE(test3_particle.getVelocity().isApprox(test_velocity,0.01));
    REQUIRE(test3_particle.getPosition().isApprox(test_position,0.01));
    
}