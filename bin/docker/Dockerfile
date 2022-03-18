FROM ubuntu:20.04

RUN apt-get update -y --fix-missing
RUN apt-get install -y \
    apt-utils \
    curl \
    dialog \
    sudo \
    wget

# removes most of the clutter from apt-get output
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

ENV LANG C.UTF-8
ENV TZ=Europe/Warsaw
RUN sudo ln -snf /usr/share/zoneinfo/$TZ /etc/localtime

# refer to https://docs.zephyrproject.org/3.0.0/getting_started/index.html
RUN wget https://apt.kitware.com/kitware-archive.sh
RUN sudo bash kitware-archive.sh && rm kitware-archive.sh

RUN sudo apt-get update -y --fix-missing
RUN sudo apt-get upgrade -y
RUN sudo apt-get install -y --no-install-recommends \
    git \
    cmake \
    ninja-build \
    gperf \
    ccache \
    dfu-util \
    device-tree-compiler \
    wget \
    python3-dev \
    python3-pip \
    python3-setuptools \
    python3-tk \
    python3-wheel \
    xz-utils file \
    make \
    gcc \
    gcc-multilib \
    g++-multilib \
    libsdl2-dev

RUN pip3 install -U west
RUN west init ~/zephyrproject --mr v3.0.0
RUN cd ~/zephyrproject && west update && west zephyr-export
RUN pip3 install --user -r ~/zephyrproject/zephyr/scripts/requirements.txt

RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.13.2/zephyr-sdk-0.13.2-linux-x86_64-setup.run
RUN chmod +x zephyr-sdk-0.13.2-linux-x86_64-setup.run && ./zephyr-sdk-0.13.2-linux-x86_64-setup.run -- -d ~/zephyr-sdk-0.13.2
RUN rm zephyr-sdk-0.13.2-linux-x86_64-setup.run

# nRF command line tools
RUN wget https://nsscprodmedia.blob.core.windows.net/prod/software-and-other-downloads/desktop-software/nrf-command-line-tools/sw/versions-10-x-x/10-15-4/nrf-command-line-tools_10.15.4_amd64.deb
RUN sudo apt-get install -y ./nrf-command-line-tools_10.15.4_amd64.deb && rm nrf-command-line-tools_10.15.4_amd64.deb

# JLink
RUN curl --data "accept_license_agreement=accepted&submit=Download%20software" -o JLink.deb https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb
RUN sudo apt-get install -y ./JLink.deb && rm JLink.deb