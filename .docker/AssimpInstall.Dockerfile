FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    apt-utils sudo git curl vim unzip openssh-client wget gnupg2 lsb-release software-properties-common \
    build-essential cmake \
    libopenblas-dev \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libxrender-dev

RUN sudo apt-get update && \
    sudo apt-get upgrade -y

RUN sudo apt-get install -y assimp-utils libassimp-dev