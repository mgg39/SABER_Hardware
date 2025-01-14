#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# 

echo "This script was generated under a different operating system."
echo "Please update the PATH and LD_LIBRARY_PATH variables below, before executing this script"
exit

if [ -z "$PATH" ]; then
  PATH=D:/Vivado2018_installed/SDK/2018.1/bin;D:/Vivado2018_installed/Vivado/2018.1/ids_lite/ISE/bin/nt64;D:/Vivado2018_installed/Vivado/2018.1/ids_lite/ISE/lib/nt64:D:/Vivado2018_installed/Vivado/2018.1/bin
else
  PATH=D:/Vivado2018_installed/SDK/2018.1/bin;D:/Vivado2018_installed/Vivado/2018.1/ids_lite/ISE/bin/nt64;D:/Vivado2018_installed/Vivado/2018.1/ids_lite/ISE/lib/nt64:D:/Vivado2018_installed/Vivado/2018.1/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=
else
  LD_LIBRARY_PATH=:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='D:/SABER_FPGA/project_1/project_1.runs/Top_zynq_ultra_ps_e_0_0_synth_1'
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

EAStep vivado -log Top_zynq_ultra_ps_e_0_0.vds -m64 -product Vivado -mode batch -messageDb vivado.pb -notrace -source Top_zynq_ultra_ps_e_0_0.tcl
