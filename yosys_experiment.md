# Prerequisite

Yosys experiment based on the Antmicro's plug-ins. See this [guide](https://github.com/antmicro/surelog-uhdm-ibex-guide)


1. Install the required apt tools (assuming you have the one in the README):

```bash
sudo apt-get -y install gperf
curl -sSL https://get.haskellstack.org/ | sh
sudo apt-get install -y shunit2



sudo apt-get install build-essential clang  \
    libreadline-dev tcl-dev libffi-dev \
    graphviz xdot pkg-config libboost-system-dev \
    libboost-python-dev libboost-filesystem-dev zlib1g-dev

```

2. Install the Surelog and UHDM tools:

```bash
mkdir -p /home/yourusername/tools/surelog
mkdir -p /home/yourusername/tools/uhdm
# Yosys, Yosys plugins and Surelog will be installed in the $PREFIX location
export PREFIX=/home/yourusername/tools/surelog
# This variable is required in Yosys build system to link against Surelog and UHDM
export UHDM_INSTALL_DIR=/home/yourusername/tools/uhdm
export PATH=$PREFIX/bin:$UHDM_INSTALL_DIR/bin:$PATH
```

```bash
git clone https://github.com/chipsalliance/Surelog
cd Surelog && git checkout bf19da37874169891b928419a721176219222f68
git submodule update --init --recursive
pip3 install orderedmultidict
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_POSITION_INDEPENDENT_CODE=ON -S . -B build
cmake --build build -j $(nproc)
cmake --install build
cd -
```

3. Install Yosys

```bash
git clone https://github.com/yosyshq/yosys
cd yosys && git checkout 4da3f2878bb873726c6ac9233fe937d8c788993c
make -j$(nproc) install
cd -
```

