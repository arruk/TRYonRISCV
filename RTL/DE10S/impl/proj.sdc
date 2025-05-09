## Generated SDC file "proj.out.sdc"

## Copyright (C) 2024  Intel Corporation. All rights reserved.
## Your use of Intel Corporation's design tools, logic functions 
## and other software and tools, and any partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Intel Program License 
## Subscription Agreement, the Intel Quartus Prime License Agreement,
## the Intel FPGA IP License Agreement, or other applicable license
## agreement, including, without limitation, that your use is for
## the sole purpose of programming logic devices manufactured by
## Intel and sold by Intel or its authorized distributors.  Please
## refer to the applicable agreement for further details, at
## https://fpgasoftware.intel.com/eula.


## VENDOR  "Altera"
## PROGRAM "Quartus Prime"
## VERSION "Version 23.1std.1 Build 993 05/14/2024 SC Lite Edition"

## DATE    "Mon Mar  3 17:55:50 2025"

##
## DEVICE  "5CSXFC6D6F31C6"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {CLK} -period 1.000 -waveform { 0.000 0.500 } [get_ports {CLK}]


#**************************************************************
# Create Generated Clock
#**************************************************************



#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

set_clock_uncertainty -rise_from [get_clocks {CLK}] -rise_to [get_clocks {CLK}] -setup 0.170
set_clock_uncertainty -rise_from [get_clocks {CLK}] -rise_to [get_clocks {CLK}] -hold 0.060
set_clock_uncertainty -rise_from [get_clocks {CLK}] -fall_to [get_clocks {CLK}] -setup 0.170
set_clock_uncertainty -rise_from [get_clocks {CLK}] -fall_to [get_clocks {CLK}] -hold 0.060
set_clock_uncertainty -fall_from [get_clocks {CLK}] -rise_to [get_clocks {CLK}] -setup 0.170
set_clock_uncertainty -fall_from [get_clocks {CLK}] -rise_to [get_clocks {CLK}] -hold 0.060
set_clock_uncertainty -fall_from [get_clocks {CLK}] -fall_to [get_clocks {CLK}] -setup 0.170
set_clock_uncertainty -fall_from [get_clocks {CLK}] -fall_to [get_clocks {CLK}] -hold 0.060


#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************



#**************************************************************
# Set False Path
#**************************************************************



#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

