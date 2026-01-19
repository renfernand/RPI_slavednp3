# DNP3 Outstation for Raspberry Pi (RPI_slavednp3)

This project implements a **DNP3 outstation (slave)** running on a **Raspberry Pi** (tested on Raspberry Pi 3 Model B), using the **OpenDNP3** library.

The code is **cross-compiled for ARM** on an Ubuntu 22.04 virtual machine and then deployed to the Raspberry Pi via SSH.

---
## 1. Para compilar e rodar o codigo

```bash
  cd ~/Projects/RPI_slavednp3
  mkdir -p build
  cd build
  cmake -G Ninja ..
  ninja

```

Para rodar:

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
