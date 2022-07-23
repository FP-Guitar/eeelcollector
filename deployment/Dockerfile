# CLion remote deployment environment (How to build deployment container, run and stop it)
#
# Build and run:
#   deployment build -t clion/remote-alpine:1.0 -f Dockerfile-alpine .
#   deployment run -d --cap-add sys_ptrace --privileged -p127.0.0.1:2222:22 clion/remote-alpine:1.0
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
#
# stop:
#   deployment stop clion_remote_env
#
# ssh credentials (test user):
#   root@root

FROM ubuntu:22.04 as build

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y build-essential \
      gcc \
      g++ \
      gdb \
      clang \
      make \
      ninja-build \
      cmake \
      autoconf \
      automake \
      locales-all \
      dos2unix \
      rsync \
      tar \
      python3 \
      python3-dev \
      cppcheck \
      python3-pip \
      clang-tidy \
      vim \
  && apt-get clean
RUN apt-get install -y python3-pip clang-tidy

RUN pip3 install conan

ADD . /eeelcollector
WORKDIR /eeelcollector
RUN cmake -S . -B ./buildRelease -DCMAKE_BUILD_TYPE="Release" -DENABLE_DEVELOPER_MODE=OFF -GNinja

WORKDIR /eeelcollector/buildRelease
RUN cmake --build .
RUN ctest
RUN cmake --install . --prefix .

FROM ubuntu:22.04 as Release
RUN mkdir eeelcollector
WORKDIR eeelcollector
COPY --from=build eeelcollector/buildRelease/bin .


ENTRYPOINT ["/eeelcollector/eeelcollector"]
