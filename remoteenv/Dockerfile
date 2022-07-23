# CLion remote docker environment (How to build docker container, run and stop it)
#
# NOte adapted to use ubuntu 22.04
#
# Build and run:
#   docker build -t remoteenv:0.1.0 remoteenv
#   docker run -d --cap-add sys_ptrace -p127.0.0.1:2222:22 --name remoteenv:0.1.0
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2222"
#
# stop:
#   docker stop remoteenv
#
# ssh credentials (test user):
#   user@password

FROM ubuntu:22.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y  \
      ssh \
      build-essential \
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

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

RUN useradd -m user \
  && yes password | passwd user

RUN usermod -s /bin/bash user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]