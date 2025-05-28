FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Paquetes esenciales
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    unzip \
    git \
    ninja-build \
    gdb \
    pkg-config \
    ca-certificates \
    software-properties-common \
    wget \
    gcc \
    g++ \
    libopus-dev \
    libopusfile-dev \
    libxmp-dev \
    libfluidsynth-dev \
    fluidsynth \
    libwavpack1 \
    libwavpack-dev \
    libfreetype-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxi-dev \
    libxinerama-dev \
    libxcursor-dev \
    libasound2-dev \
    libpulse-dev \
    libudev-dev \
    libdbus-1-dev \
    libsamplerate0-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libwebp-dev

# Instalar CMake 3.27.9
RUN curl -LO https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-x86_64.sh && \
    chmod +x cmake-3.27.9-linux-x86_64.sh && \
    ./cmake-3.27.9-linux-x86_64.sh --skip-license --prefix=/usr && \
    rm cmake-3.27.9-linux-x86_64.sh

# Crear usuario devuser
RUN useradd -ms /bin/bash devuser

USER devuser

# Crear directorio de trabajo
RUN mkdir -p /home/devuser/app/build

# Setear directorio por defecto
WORKDIR /home/devuser/app/build

# Entrypoint por defecto para debug
CMD ["/bin/bash"]
