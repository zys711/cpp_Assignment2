#include <iostream>
#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include "nbsimParticle.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include <CLI/CLI.hpp>


int main(int argc, char** argv) {
    CLI::App app{"solar system simulator"};

    //std::string filename = "default";
    //app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);
    return 0;
}