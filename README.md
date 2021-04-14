PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment2)


Purpose
-------

This project serves as a starting point for the PHAS0100 Assignment 2 Gravitational N-body Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.


Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Build Instructions
------------------

Build and run instructions are left as an excercise for the student. Examples of how to build using cmake were given in lectures and in the other CMake example projects.


Instructions
------------

build file has already been created:
```
cd build
cmake ..
make
```

Tests run as:
```
ctest
```

Command Line App
----------------
This app is a solar system simulator. 8 planets and the fixed star Sun have already been set up. There are two input values, stepsize(year) and totaltime(year).
To run this app, and with two parameters:
```
./bin/solarSystemSimulator -s stepsize -t totaltime
```

Result
------

The example result with stepsize 0.000274 year(1 day) and totaltime 1 year:
```
Sun
 original position:-0.00670894
  0.0060565
 0.00010651
 current position:-0.00830539
 0.00294565
0.000168637
Mercury
 original position:  0.230275
 -0.351957
-0.0508834
 current position:-0.146209
 -1.04648
-0.074043
Venus
 original position:-0.453178
-0.563815
0.0180571
 current position:   0.169022
   0.751123
0.000189264
Earth
 original position:  -0.185741
   0.972886
4.83111e-05
 current position:  -0.099235
     1.0015
0.000108855
Mars
 original position: 0.614263
  1.38167
0.0136846
 current position: -2.52688
  1.26325
0.0882352
Jupiter
 original position:   3.0346
 -4.08225
-0.050909
 current position:   4.32888
  -1.39283
-0.0910674
Saturn
 original position:    5.4834
  -8.33624
-0.0732546
 current position:  6.83329
  -6.8811
-0.152439
Uranus
 original position:  15.3436
  12.4673
-0.152634
 current position:  14.2433
  13.3617
-0.135071
Neptune
 original position:  29.4537
 -5.22631
-0.571104
 current position:  29.5955
 -4.08302
-0.597839

 r_com is:-2.19125e-06
 1.97065e-06
-7.94825e-09

 p_total is:-4.83694e-05
 2.58709e-05
-5.22848e-07
CPU time used: 3.83 ms
Wall clock time passed: 3.83 ms
```

The benchmark timesteps are 1 hour, 1 day, 2 days, 3 days, and 5 days. Also the squared errors was calculated compared with earth position (−0.194, 0.969, 0.000109).


| Timestep (year)  | CPU time(ms) |  Wall clock time(ms)  |      Earth position result        | Squared error from know Earth position | 
|------------------|--------------|-----------------------|-----------------------------------|----------------------------------------|
|0.00001142(1 hour)|    87.07     |         87.07         | -0.190369,  0.970186, 0.000108606 |         1.4590757155236015e-05         | 
| 0.0000274(1 day) |    3.83      |         3.83          | -0.099235,  1.0015,   0.000108855 |          0.01003665522502103           | 
| 0.000548(2 days) |    1.94      |         1.94          | -0.00361647,1.02468,  0.000109513 |          0.039346150895524075          |
| 0.000822(3 days) |    1.29      |         1.29          | 0.0893585,  1.03906,  0.000110542 |          0.08520044312462778           |
| 0.001370(5 days) |    0.77      |         0.76          | 0.274966,   1.04348,  0.000113782 |          0.22547637957886751           |

From the result we can see with the timestep decreases (for loop count increases), the benchmark time increases roughly linearly. Also, the sqaured error increases as timestep increases.