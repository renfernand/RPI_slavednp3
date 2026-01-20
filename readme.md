# DNP3 Outstation for Raspberry Pi (RPI_slavednp3)

This project implements a **DNP3 outstation (slave)** running on a **Raspberry Pi** (tested on Raspberry Pi 3 Model B), using the **OpenDNP3** library.

This version was compiled and run directly on the Raspberry Pi.

This version also supports GPIOs for digital input and output according to the Codebox:


BUTTON_1 = GPIO17 |  LED_1 = GPIO22 

BUTTON_3 = GPIO18 |  LED_3 = GPIO24

BUTTON_4 = GPIO27 |  LED_4 = GPIO25

---
## 1. Basic Tools to compile in the Raspberry

build-essential → gcc, g++, make, libc

cmake → sistema de build do projeto

ninja-build → build rápido (usado no projeto)

git → clonar / atualizar repositório

lib GPIO (libgpiod)

```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build git
sudo apt install -y libgpiod-dev gpiod

```
Permissão para acessar GPIO (importante)
Sem isso, o programa compila mas não acessa os GPIOs.

```bash
sudo usermod -aG gpio $USER
logout

```


---
## 2. To build the version
To build the version, follow these steps:

### 2.1 Create a Project folder on the Raspberry Pi

```bash

mkdir -p ~/project
cd ~/project

```

### 2.2 Clone the openDNP3 folder: see link

```bash

cd ~/projetos
git clone https://github.com/dnp3/opendnp3.git

```

### 2.3 Clone the RPI_slavednp3 folder: see link

```bash

cd ~/projetos
git clone https://github.com/renfernand/RPI_slavednp3 

```


---
## 3. To compile and run the code


```bash
  cd ~/Projects/RPI_slavednp3
  mkdir -p build
  cd build
  cmake -G Ninja ..
  ninja

```

In order to run:

```bash

   ./slavednp3

```

---
## 4. License

This project is licensed under the MIT License.
For details, see the LICENSE
 file.

The OpenDNP3 library is licensed under its own terms (Apache 2.0);
check the OpenDNP3 repository for its license details.
