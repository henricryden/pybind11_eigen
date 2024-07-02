FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:git-core/ppa

ARG GCC_VER=10
SHELL ["/bin/bash", "-c"]
RUN apt-get update &&  apt-get -qqy --no-install-suggests --no-install-recommends install \
         build-essential \
         gcc-${GCC_VER} \
         g++-${GCC_VER} \
         gdb \
         cmake \
         git \ 
         wget \
         curl \
         tar \
         libeigen3-dev

RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt-get update && apt-get -qqy install \
    python3.11 \
    python3.11-dev \
    python3.10 \
    python3.10-dev \
    python3.9 \
    python3.9-dev


# Install micromamba
ENV MAMBA_ROOT_PREFIX=/opt/micromamba
ENV PATH=$MAMBA_ROOT_PREFIX/bin:$PATH
RUN curl -Ls https://micro.mamba.pm/api/micromamba/linux-64/latest | tar -xvj bin/micromamba
RUN micromamba shell init --shell=bash --prefix=$MAMBA_ROOT_PREFIX

# Create environments
RUN micromamba create -n py3.9 python=3.9 -y -c conda-forge
RUN micromamba create -n py3.10 python=3.10 -y -c conda-forge
RUN micromamba create -n py3.11 python=3.11 -y -c conda-forge

# Activate py3.10 environment by default
RUN echo "micromamba activate py3.10" >> ~/.bashrc

# Clean up
RUN micromamba clean --all --yes