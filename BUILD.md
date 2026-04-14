# How to build on Linux based on Debian

#### Install packages:

```bash
sudo apt install -y make cmake autoconf libtool pkg-config gcc g++ libssl-dev binutils-dev
```

#### Install 32-bit cross compile packages

```bash
sudo apt-get install -y gcc-multilib g++-multilib
```

#### Install 32/64-bit Microsoft Windows cross compile packages

```bash
sudo apt-get install -y gcc-mingw-w64 g++-mingw-w64
```

#### Install 32/64-bit ARM cross compile packages

```bash
sudo apt-get install -y gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
sudo apt-get install -y gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

#### Install 32/64-bit MIPS cross compile packages

```bash
sudo apt-get install -y gcc-mips-linux-gnu g++-mips-linux-gnu
sudo apt-get install -y gcc-mips64-linux-gnuabi64 g++-mips64-linux-gnuabi64
```

#### Install 64-bit RISC-V cross compile packages

```bash
sudo apt-get install -y gcc-riscv64-linux-gnu g++-riscv64-linux-gnu
```

#### Clone this repo:

```bash
git clone https://github.com/z0mb13w4r/code-samples.git
```

#### Build individual example:

```bash
cd <example directory>
make
```

To show the makefile options.

```bash
make help
```

To cross-compile the example as ARM (32-bit).

```bash
make CROSS=ARM32
```

To cross-compile the example as ARM (64-bit).

```bash
make CROSS=ARM64
```

To cross-compile the example as MIPS (32-bit).

```bash
make CROSS=MIPS32
```

To cross-compile the example as MIPS (64-bit).

```bash
make CROSS=MIPS64
```

To cross-compile the example as RISC-V (64-bit).

```bash
make CROSS=RISCV64
```

To cross-compile the example as generic (32-bit).

```bash
make CROSS=LINUX32
```

To cross-compile the example as Microsoft Windows (32-bit).

```bash
make CROSS=WIN32
```

To cross-compile the example as Microsoft Windows (64-bit).

```bash
make CROSS=WIN64
```

