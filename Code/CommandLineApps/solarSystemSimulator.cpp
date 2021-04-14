#include <iostream>
#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include "nbsimSolarSystemData.ipp"
#include <Eigen/Dense>
#include <CLI/CLI.hpp>

int main(int argc, char** argv){
    CLI::App app{"solar system simulator"};
    double step_size, total_time;
    app.add_option("-s,--timestep", step_size,  "step size, unit:year");
    app.add_option("-t,--totaltime", total_time,  "duration of simulation, unit:year");

    std::string planet_name[9];
    Eigen::Vector3d init_position, init_velocity;
    double mu;
    std::shared_ptr<nbsim::MassiveParticle> planet_ptr[9];
    CLI11_PARSE(app, argc, argv);
    for (int i=0; i<9; i++) {
		planet_name[i]=nbsim::solarSystemData[i].name;
		init_position=nbsim::solarSystemData[i].position;
		init_velocity=nbsim::solarSystemData[i].velocity;
        mu=nbsim::solarSystemData[i].mu;
        std::shared_ptr<nbsim::MassiveParticle> ptr_particle_i(new nbsim::MassiveParticle(init_position, init_velocity, mu/6.67408e-11));
		planet_ptr[i]=ptr_particle_i;
	}
    for (int i=0; i<9; i++){
		for (int j=0; j<9; j++){
			planet_ptr[i]->addAttractor(planet_ptr[j]);
            if (planet_ptr[i]==planet_ptr[j]){
                planet_ptr[i]->removeAttractor(planet_ptr[j]);
            }
		}
	}
    for (double test_time=0; test_time<total_time*365*24*60*60; test_time+=step_size*365*24*60*60){
		for (int i=0;i<9;i++){
			planet_ptr[i]->calculateAcceleration();
		}
		for (int i=0;i<9;i++){
			planet_ptr[i]->integrateTimestep(step_size*365*24*60*60);
		}	
	}
    for (int i=0;i<9;i++){
		std::cout<<planet_name[i]<<"\n original position:"<<nbsim::solarSystemData[i].position<<"\n current position:"<<planet_ptr[i]->getPosition()<<std::endl;
    }
    
    return 0;
}