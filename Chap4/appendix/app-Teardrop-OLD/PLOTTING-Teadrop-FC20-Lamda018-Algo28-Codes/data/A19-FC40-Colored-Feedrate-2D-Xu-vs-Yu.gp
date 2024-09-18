#!/usr/bin/gnuplot -persist

## File: 01-FCXX-plot2D-Xu-vs-Yu-color-frate.gp
## Date: Jun 11 Jun 2023 10:07:52 AM +08
## Gnuplpot Version 5.2 patchlevel 8

clear
set size square
set autoscale
set grid
NO_ANIMATION = 1

set terminal png size 800,800 enhanced font "Helvetica,10"

## ===================== AUTOMATED OUTPUT FILE ======================

# CHANGE PART 1 OF 3
set output "TEARDROP-FC40-Colored-Feedrate-Profile-data_ngcode.png"

# CHANGE PART 2 OF 3
set title  "Teardrop FC40 Feedrate Colored Profile  (Color scale = Feedrate)" 

## ==================================================================
set xlabel "position x(u)"
set xrange [ -40.00000 : +40.0000 ] noreverse nowriteback
set x2range [ * : * ] noreverse writeback

set ylabel "position y(u)"
set yrange [ -40.00000 : +40.0000 ] noreverse nowriteback
set y2range [ * : * ] noreverse writeback

set zrange [ * : * ] noreverse writeback
# set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

## COLOR SETTINGS
# ===================================================================
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
set palette defined ( 0 'purple', 8 'blue', 16 'green', 24 'yellow', 32 'orange', 40 'red' )

#  FIXED RANGE COLOR FIXED - NOT AUTORANGE (WHICH TAKES (MAX, MIN))
set cbrange [0:40] noreverse writeback


## PLOT EXECUTION
## ==================================================================
## Using X-Value:Y-Value:FRate-Value ==> 5:7:3

## CHANGE PART 3 OF 3
plot  'FC40-data_ngcode.ngc' using 5:7:3 with lines linewidth 3 linecolor palette title "(x(u), y(u)) point"

## ==================================================================
## INFO DATA COLUMNS IN NGC FILE
## ==================================================================
# [Col 1] G01 
# [Col 2] F    
# [Col 3] FRate-Value = 3.000000 
# [Col 4} X[    
# [Col 5] X-Value = 0.000000] 
# [Col 6] Y[    
# [Col 7] Y-Value = 0.000000] 
# [Col 8] (#u= 
# [Col 9] U-Value = 0.000000000 
# [Col10] eps= 
# [Col11] eps-Value = 0.000000117829 
# [Col12] Xfrate= 
# [Col13] Xfrate-Value = -2.121320 
# [Col14] Yfrate= 
# [Col15] Yfrate-Value = -2.121320 
# [Col16] frlimit=  
# [Col17] frlimit-Value = 0.000000 
# [Col18] frdiff=
# [Col19] frdiff-Value = -3.000000000 
# [Col20] frcmd= 
# [Col21] frcmd-Value = 10.000 
# [Col22} #) 

## ==================================================================
## ALHAMDULILLAH 3 TIMES
## ==================================================================

