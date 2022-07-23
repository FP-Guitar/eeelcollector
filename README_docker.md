## Docker Instructions
I created two dockerfiles:

- `deployment/Dockerfile` will do a realease build of the program. The resulting container image uses
ubuntu 22.04 as base. I decided to switch to ubuntu 22.04 to have a recent gcc.
- `remoteenv/Dockerfile` will contain a remote setup usable with CLion or any other IDE which 
is capable of remote development over ssh. This keeps my local enviorment clean and is the exact same
environment in which the program will later be deployed. This should reduce the risc of glibc/abi etc.
incompabilities significantly.

### Note
I replaced the original process  from the template by a full dockerized build and deplyoment. The instructions
below are still useful if it is intended to have a full ci run with different compilers/os
running. Which is strongly encouraged for c++ projects. For clarity of the repo structure i decided to delete everything related
to this setup.

