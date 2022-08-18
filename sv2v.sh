#!/bin/bash

# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

# This script converts all SystemVerilog RTL files to Verilog
# using sv2v and then runs LEC (Cadence Conformal) to check if
# the generated Verilog is logically equivalent to the original
# SystemVerilog.  A similar script is used in OpenTitan, any updates
# or fixes here may need to be reflected in the OpenTitan script as well
# https://github.com/lowRISC/opentitan/blob/master/util/syn_yosys.sh
#
# The following tools are required:
#  - sv2v: SystemVerilog-to-Verilog converter from github.com/zachjs/sv2v
#  - Cadence Conformal
#
# Usage:
#   ./lec_sv2v.sh |& tee lec.log

#-------------------------------------------------------------------------
# use fusesoc to generate files and file list
#-------------------------------------------------------------------------

# copy all files to lec_out
mkdir lec_out


# add the prim_assert.sv file as it is marked as include file, but sv2v needs to convert it
cp openhwgroup.org_systems_core-v-mini-mcu_0.scr sv2v.scr

echo ../../../hw/vendor/lowrisc_opentitan/hw/ip/prim/rtl/prim_assert.sv >> sv2v.scr

# copy file list and remove incdir, RVFI define, and sim-file
egrep -v 'incdir|parameter|define|_pkg' sv2v.scr > flist_gold

egrep 'pkg' sv2v.scr | egrep -v 'define'  > flist_pkg_gold

egrep 'incdir' sv2v.scr > flist_incdir_gold
sed -i 's/\+incdir+//g' flist_incdir_gold
sed -i ':a;N;$!ba;s/\n/ -I ..\//g' flist_incdir_gold
sed -i '1s/^/-I ..\//' flist_incdir_gold


lines=$(cat flist_gold)
for line in $lines
do
  cp $line lec_out/
done

lines=$(cat flist_pkg_gold)
for line in $lines
do
  cp $line lec_out/
done

# remove all hierarchical paths
sed -i 's!.*/!!' flist_gold
sed -i 's!.*/!!' flist_pkg_gold


incdirs=$(cat flist_incdir_gold)
packages=$(cat flist_pkg_gold)

# generate revised flist by replacing '.sv' by '.v' and removing packages
sed 's/.sv/.v/' flist_gold | grep -v "_pkg.v" > flist_rev

#-------------------------------------------------------------------------
# convert all RTL files to Verilog using sv2v
#-------------------------------------------------------------------------
printf "\nSV2V ERRORS:\n"
cd lec_out

mkdir verilog
for file in *.sv; do
  module=`basename -s .sv $file`
  echo "Converting " $file
  #sv2v --define=SYNTHESIS --define=SV2V *_pkg.sv prim_assert.sv -I ../../../../hw/vendor/pulp_platform_common_cells/include/  -I ../../../../hw/vendor/openhwgroup_cv32e20/rtl/ $file > verilog/${module}.v
  sv2v --define=SYNTHESIS --define=SV2V $packages $incdirs $file > verilog/${module}.v
done

# remove *pkg.v files (they are empty files and not needed)
cd verilog
rm -f *_pkg.v prim_assert.v

cd ../../