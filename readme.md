# DNP3 Outstation for Raspberry Pi (RPI_slavednp3)

This project implements a **DNP3 outstation (slave)** running on a **Raspberry Pi** (tested on Raspberry Pi 3 Model B), using the **OpenDNP3** library.

This version was compiled and run directly on the Raspberry Pi.

This version also supports GPIOs for digital input and output according to the Codebox:
BUTTON_1 = GPIO17 |  LED_1 = GPIO22
BUTTON_3 = GPIO18 |  LED_3 = GPIO24
BUTTON_4 = GPIO27 |  LED_4 = GPIO25

---
## 1. To build the version
To build the version, follow these steps:

### 1.1 Create a Project folder on the Raspberry Pi

```bash

mkdir -p ~/project
cd ~/project

```

### 1.2 Clone the openDNP3 folder: see link

```bash

cd ~/projetos
git clone https://github.com/dnp3/opendnp3.git

```

### 1.3 Clone the RPI_slavednp3 folder: see link

```bash

cd ~/projetos
git clone https://github.com/renfernand/RPI_slavednp3 

```


---
## 2. To compile and run the code



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
## 2. License

This project is licensed under the MIT License.
For details, see the LICENSE
 file.

The OpenDNP3 library is licensed under its own terms (Apache 2.0);
check the OpenDNP3 repository for its license details.
