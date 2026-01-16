# DNP3 Outstation for Raspberry Pi (RPI_slavednp3)

This project implements a **DNP3 outstation (slave)** running on a **Raspberry Pi** (tested on Raspberry Pi 3 Model B), using the **OpenDNP3** library.

The code is **cross-compiled for ARM** on an Ubuntu 22.04 virtual machine and then deployed to the Raspberry Pi via SSH.


---

## 1. Dependencies and Environment

These instructions assume:

- Host dev environment: **Ubuntu 22.04** (VM, e.g. VirtualBox)
- Target: **Raspberry Pi OS (32-bit)**  
- Toolchain: **ARM cross-compiler (arm-linux-gnueabihf)**

On Ubuntu, install the required packages:

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    gdb \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf

Create a base folder for projects:
mkdir -p ~/projetos
cd ~/projetos


---

## 2. Clone OpenDNP3 and This Project
### 2.1. Clone the OpenDNP3 library

```bash

cd ~/projetos
git clone https://github.com/dnp3/opendnp3.git

// This repository contains the OpenDNP3 library that will be used as a dependency.


### 2.2. Clone this outstation project

```bash
cd ~/projetos
git clone https://github.com/renfernand/RPI_slavednp3.git
cd RPI_slavednp3

---

## 3. Configure SSH Access to the Raspberry Pi

On the Raspberry Pi (target):

Habilite o SSH (via raspi-config ou interface gráfica):

```bash
sudo raspi-config


//Interface Options -> SSH -> Enable
//discover the ip

```bash
hostname -I

//test the ssh from ubuntu

```bash
ssh pi@<IP_DA_RPI>


---

## 4. Build (Cross-Compile for Raspberry Pi)

```bash
cd ~/projetos/RPI_slavednp3
cmake -S . -B build-rpi \
  -G Ninja \
  -DCMAKE_C_COMPILER=arm-linux-gnueabihf-gcc \
  -DCMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++ \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build-rpi


---

## 5. Deploy and Run on the Raspberry Pi

O script deploy_rpi.sh (já no repositório) faz:

Build

Cópia do binário (e da libopendnp3.so se necessário) via scp

Execução do outstation na Raspberry via ssh

cd ~/projetos/RPI_slavednp3
./deploy_rpi.sh


O script espera que:

RPI_USER, RPI_IP, RPI_DIR estejam corretos dentro do deploy_rpi.sh

A Raspberry esteja acessível via SSH

O binário e a biblioteca possam ser copiados para ${RPI_DIR}

---

## 6. Project Structure (Resumo)

RPI_slavednp3/
├── CMakeLists.txt        # Configuração do projeto
├── src/
│   └── main.cpp          # Código principal do DNP3 outstation
├── deploy_rpi.sh         # Script para build + deploy + run na Raspberry
├── README.md             # Este arquivo
└── (outros arquivos de build/config)


O OpenDNP3 fica em: ~/projetos/opendnp3

Este projeto referencia a biblioteca OpenDNP3 via CMake (instruções no CMakeLists.txt)

---
## 7. License

This project is licensed under the MIT License.
For details, see the LICENSE
 file.

The OpenDNP3 library is licensed under its own terms (Apache 2.0);
check the OpenDNP3 repository for its license details.
