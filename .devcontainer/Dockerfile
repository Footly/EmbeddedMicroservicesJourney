FROM ubuntu:22.04 as base

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get -y upgrade \
    && apt-get -y install git build-essential apt-utils bzr wget cmake ninja-build libusb-dev usbutils libncurses5 libncursesw5 cu curl libusb-1.0-0-dev dfu-util udev\
    && apt-get clean

#download GNU ARM Toolchain
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz \
    && tar -xf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz \
    && rm arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz

#Add arm-none-eabi tools to path
ENV PATH="$PATH:/home/dev/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin"