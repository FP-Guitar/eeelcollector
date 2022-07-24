# eeelcollector
This is the implementation of a coding challenge. It sacrifices project setup for development speed. It is based
on jason turners cpp best practies project. (https://github.com/cpp-best-practices/cppbestpractices) Unfortunately,
it is a little disapointing, as a lot of the ci stuff seems not to be working correctly on unpaid private 
github repositories.

## Limitations 
- I am used to gitlab ci so I skipped the part of fixing the pipeline. Especially, as I completely consumed my monthly minute limit
with the first runs.
- ~~ I am only builing currently on gcc9, as I don't have the time for setting up a multi compiler regression ~~
- I switched to Unbuntu 22.04 remote and deployment environment for having a recent gcc, as I decided to use this project
  to familiarize myself a little with ranges and other new c++20 features. I do not like to hazzle around with glibc/abi and
  other issues, for this reason I like to keep deployment and compile environment as close as possible.
  - Notes:
    - ranges still not supported sufficiently with clang, which makes running clang-tidy impossible. Won't use ranges. :(


### Functionaliy:
#### Trigger
- Will allow core.ServiceName.digits...lz4 and core.digits.lz4. The first name is, if not taking the example into account not valid
- Deleting and recreating a file will trigger collection. 
- Trying to monitor an non existing or non directory directory for trigger fails will produce a lot of error logs. Assumption.
  Directory may be temporarily unavailable. Didn't implement corner case of initialization.
- No persistence between service restarts
- 
# Dependency Management
This project uses conan as dependency manager, which has to to usable and present in the system. 
https://conan.io/

# Building release
Prerequiste: Docker installed
From directory root:
`docker build  . -f deployment/Dockerfile -t eeelcollector:latest`

example of running

```fish
docker run --user (id -u):(id -g) -v /tmp/output:/output -v  /tmp/foo:/watchme -v /tmp/collect:/collect -it eeelcollector -w /watchme -c /collect/directory  /collect/file.txt -l 0 -o /output
- 
```
# Development
Use the docker file in `development` for a usable environment. Intended use is with CLion full remote mode.
https://www.jetbrains.com/help/clion/remote-projects-support.html

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
