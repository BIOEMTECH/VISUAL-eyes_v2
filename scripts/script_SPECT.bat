cd /opt/Xilinx/14.3/ISE_DS
source settings64.sh

cd /home/bioemtech/Projects/VisualEyes-v2.3.0/scripts/xilinx/sp605_geye_24samples_50MHz_pos500_4x32bitsMPMC_wait80cycles
impact -batch download.cmd
xmd -tcl download.tcl


