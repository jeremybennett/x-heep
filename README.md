Minimal configuration of a core-v-mcu

# Prerequisite

1. Install [Conda](https://phoenixnap.com/kb/how-to-install-anaconda-ubuntu-18-04-or-20-04) as described in the link, 
and create the Conda enviroment with python 3.8:

```bash
conda update conda
conda env create -f environment.yml
```

Activate the environment with

```bash
conda activate core-v-mini-mcu
```
2. Install the required Python tools:

```
pip3 install --user -r python-requirements.txt
```

Add '--root user_builds' to set your build foders for the pip packages
and add that folder to the `PATH` variable

3. Install the required apt tools:

```
sudo apt install lcov libelf1 libelf-dev libftdi1-2 libftdi1-dev libncurses5 libssl-dev libudev-dev libusb-1.0-0 lsb-release texinfo makeinfo autoconf cmake flex bison libexpat-dev gawk
```

In general, have a look at the [Install required software](https://docs.opentitan.org/doc/ug/install_instructions/#system-preparation) section of the OpenTitan documentation.

4. Install the RISC-V Compiler:

```
git clone --branch 2022.01.17 --recursive https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain
./configure --prefix=/home/yourusername/tools/riscv --with-abi=ilp32 --with-arch=rv32imc --with-cmodel=medlow
make
```

Then, set the `RISCV` env variable as:

```
export RISCV=/home/yourusername/tools/riscv
```

5. Install the Verilator:

```
export VERILATOR_VERSION=4.210

git clone https://github.com/verilator/verilator.git
cd verilator
git checkout v$VERILATOR_VERSION

autoconf
./configure --prefix=/home/yourusername/tools/verilator/$VERILATOR_VERSION
make
make install
```
Then, set the `PATH` env variable to as:

```
export PATH=/home/yourusername/tools/verilator/$VERILATOR_VERSION/bin:$PATH
```

In general, have a look at the [Install Verilator](https://docs.opentitan.org/doc/ug/install_instructions/#verilator) section of the OpenTitan documentation.

If you want to see the vcd waveforms generated by the Verilator simulation, install GTKWAVE:

```
sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
sudo apt-get install -y gtkwave
```

# Adding external IPs

This repository relies on [vendor](https://docs.opentitan.org/doc/ug/vendor_hw/) to add new IPs.
In the ./util folder, the vendor.py scripts implements what is describeb above.

# Compiling with Makefile

You can compile the example applications and the platform using the Makefile. Type 'make help' for more information.

## Generate core-v-mini-mcu package

First, you have to generate the SystemVerilog package and C header file of the core-v-mini-mcu:

```
make mcu-gen
```

To change the default cpu type (i.e., cv32e20) and the default bus type (i.e., onetoM) type:

```
make mcu-gen CPU=cv32e40p BUS=NtoM
```

## Compiling Software

Don't forget to set the `RISCV` env variable to the compiler folder (without the `/bin` included).

```
make app-helloworld
```

or for FPGAs,

```
make app-helloworld TARGET=pynq-z2
```


This will create the executable file to be loaded in your target system (ASIC, FPGA, Simulation).

## Simulating

This project supports simulation with Verilator, Synopsys VCS, and Siemens Questasim.

### Compiling for Verilator

To simulate your application with Verilator, first compile the HDL:

```
make verilator-sim
```

then, go to your target system built folder

```
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim-verilator
```

and type to run your compiled software:

```
./Vtestharness +firmware=../../../sw/applications/hello_world/hello_world.hex
```

or to execute all these three steps type:

```
make run-helloworld
```


### Compiling for VCS

To simulate your application with VCS, first compile the HDL:

```
make vcs-sim
```

then, go to your target system built folder

```
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim-vcs
```

and type to run your compiled software:

```
./openhwgroup.org_systems_core-v-mini-mcu_0 +firmware=../../../sw/applications/hello_world/hello_world.hex
```

### Compiling for Questasim

To simulate your application with Questasim, first set the env variable `MODEL_TECH` to your Questasim bin folder, then compile the HDL:

```
make questasim-sim
```

then, go to your target system built folder

```
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim-modelsim/
```

and type to run your compiled software:

```
make run PLUSARGS="c firmware=../../../sw/applications/hello_world/hello_world.hex"
```

You can also use vopt for HDL optimized compilation:

```
make questasim-sim-opt
```

then go to

```
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim_opt-modelsim/
```
and 

```
make run PLUSARGS="c firmware=../../../sw/applications/hello_world/hello_world.hex"
```
Questasim version must be >= Questasim 2019.3

### UART DPI

To simulate the UART, we use the LowRISC OpenTitan [UART DPI](https://github.com/lowRISC/opentitan/tree/master/hw/dv/dpi/uartdpi). 
Read how to interact with it in the Section "Interact with the simulated UART" [here](https://docs.opentitan.org/doc/ug/getting_started_verilator/).
The output of the UART DPI module is printed in the `uart0.log` file in the simulation folder.

For example, to see the "hello world!" output of the Verilator simulation:

```
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim-verilator
./Vtestharness +firmware=../../../sw/applications/hello_world/hello_world.hex
cat uart0.log
```
## Debug

Follow the [Debug](./Debug.md) guide to debug core-v-mini-mcu.

## Execute From Flash

Follow the [ExecuteFromFlash](./ExecuteFromFlash.md) guide to exxecute code directly from the FLASH with modelsim, FPGA, or ASIC.

## Emulation

This project supports emulation on FPGAs.

### Xilinx Pynq-Z2 Flow


To build and program the bitstream for your FPGA with vivado, type:

```
make vivado-fpga FPGA_BOARD=pynq-z2
```

or add the flag `use_bscane_xilinx` to use the native Xilinx scanchain:

```
make vivado-fpga FPGA_BOARD=pynq-z2 FUSESOC_FLAGS=--flag=use_bscane_xilinx
```

Only Vivado 2021.2 has been tried.

To run SW, follow the [Debug](./Debug.md) guide 
to load the binaries with the HS2 cable over JTAG, 
or follow the [ExecuteFromFlash](./ExecuteFromFlash.md) 
guide if you have a FLASH attached to the FPGA.

# ASIC Implementation

This project can be implemented using standard cells based ASIC flow. (work in progress)

## Synthesis with Synopsys Design Compiler

First, you need to provide technology-dependent implementations of some of the cells which require specific instantiation.

Then, please provide a set_libs.tcl and set_constraints.tcl scripts to set link and target libraries, and constraints as the clock.

To generate and run synthesis scripts with DC, execute:

```
make asic
```

This relies on a fork of [edalize](https://github.com/davideschiavone/edalize) that contains templates for Design Compiler.


## Files are formatted with Verible

We use version v0.0-1824-ga3b5bedf

See: [Install Verible](https://docs.opentitan.org/doc/ug/install_instructions/)

To format your RTL code type:

```
make verible
```
