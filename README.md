# eeelcollector
This is the implementation of a coding challenge. It sacrifices project setup for development speed. It is based
on jason turners cpp best practies project. (https://github.com/cpp-best-practices/cppbestpractices) Unfortunately,
the github pipeline seems to be broken for gcc11 builds in the latest template release. 

## Limitations 
- I am used to gitlab ci so I skipped the part of fixing the pipeline. Especially, as I completly consumed my monthly minute limit
with the first runs.
- I am only builing currently on gcc9, as I don't have the time for setting up a multi compiler regression

Even with this limitations I get at least a manual asan and a usable set of standard compiler flags for the build types.

# Dependency Management
This project uses conan as dependency manager, which has to to usable and present in the system. 
https://conan.io/


# Notes on building, warnings ... etc
## Warnings and build
This cmake project is targeted to the latest compiler and software versions. E.g. gtest is build during configure step. 
As gtest is a fairly old project, it will generate a lot of warnings. 
I also had to adjust the warnings to include those headers with -Werror, -Wall etc...
Normally I would try to find a way to encapsulate gtest a little more, but given the limited the time I'll take the
short circuit.
## CI
Normally I would take the time to have a full ci pipeline running before starting any programming work. C++ is a difficult
topic. Especially if you don't have paid subscriptions to gitlab/github or alternative jenkins available.
Nevertheless, the first project setup is always very time consuming, compared to other languages.

 

## More Details
 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [Troubleshooting](README_troubleshooting.md)
 * [Docker](README_docker.md)
 * 
