#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimMyFunctions.h"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
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

TEST_CASE("check if the massive particle moves as excepted when no attractors","[MassiveParticle]"){
    Eigen::Vector3d test_position(1,0,0),test_velocity(0,1,0);
    double test_mass=1,test4_timestep=0.01, test4_time=5;
    nbsim::MassiveParticle test4_massive_particle(test_position,test_velocity,test_mass);
    for(double i=0;i<test4_time;i+=test4_timestep){
        test4_massive_particle.integrateTimestep(test4_timestep);
    }
    REQUIRE(test4_massive_particle.getVelocity().isApprox(test_velocity,0));
    REQUIRE(test4_massive_particle.getPosition().isApprox(test_position+test_velocity*test4_time,0.01));
}

TEST_CASE("check if two massive particles move together as excepted","[MassiveParticle]"){
    Eigen::Vector3d test_position1(1,0,0),test_velocity1(0,0.5,0),test_position2(-1,0,0),test_velocity2(0,-0.5,0);
    double test_mass=1/(6.67408e-11),test5_timestep=0.001, test5_time=2*M_PI;
    //nbsim::MassiveParticle test5_massive_particle1(test_position1,test_velocity1,test_mass),test5_massive_particle2(test_position2,test_velocity2,test_mass);
    std::shared_ptr<nbsim::MassiveParticle> ptr_particle1(new nbsim::MassiveParticle(test_position1,test_velocity1,test_mass)),ptr_particle2(new nbsim::MassiveParticle(test_position2,test_velocity2,test_mass));
    ptr_particle1->addAttractor(ptr_particle2);
    ptr_particle2->addAttractor(ptr_particle1);
    for(double i=0;i<test5_time;i+=test5_timestep){
        ptr_particle1->calculateAcceleration();
        ptr_particle1->integrateTimestep(test5_timestep);
        ptr_particle2->calculateAcceleration();
        ptr_particle2->integrateTimestep(test5_timestep);
    }
    double test_distance=(ptr_particle1->getPosition()-ptr_particle2->getPosition()).norm();
    REQUIRE(std::abs(test_distance)-2<0.01);
    
}