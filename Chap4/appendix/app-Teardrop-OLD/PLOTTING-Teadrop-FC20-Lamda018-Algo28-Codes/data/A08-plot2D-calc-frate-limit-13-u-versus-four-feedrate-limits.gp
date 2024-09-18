
## File: plot2D-calc-frate-limit-13-u-versus-four-feedrate-limits.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter u"
set ylabel "feedrate (mm/s)"
set title  "Plot 2D Four constraint components of Feedrate Limit" 


# COMMENT RANGES FOR DEFAULT
set xrange [ 0.0 : +1.0]
set yrange [ 0.0 : +60.0] 


## PLOT CHECK 
## plot   "FC10-data_calc_u_next.txt"      using 2:18 with lines lw 2 title "limit-1 User set Frate Command"
## replot "FC10-data_calc_frate_limit.txt" using 2:5 with lines  lw 2 title "limit-2 Min/Max Machine Velocity"
## replot "FC10-data_calc_frate_limit.txt" using 2:6 with lines  lw 2 title "limit-3 Contour Accuracy Error"
## replot "FC10-data_calc_frate_limit.txt" using 2:7 with lines  lw 2 title "limit-4 Acceleration confinement"

## PLOT CHECK 
plot   "FC20-data_calc_u_next.txt"      using 2:18 with lines lw 2 title "limit-1 User set Frate Command"
replot "FC20-data_calc_frate_limit.txt" using 2:5 with lines  lw 2 title "limit-2 Min/Max Machine Velocity"
replot "FC20-data_calc_frate_limit.txt" using 2:6 with lines  lw 2 title "limit-3 Contour Accuracy Error"
replot "FC20-data_calc_frate_limit.txt" using 2:7 with lines  lw 2 title "limit-4 Acceleration confinement"

## PLOT CHECK 
## plot   "FC30-data_calc_u_next.txt"      using 2:18 with lines lw 2 title "limit-1 User set Frate Command"
## replot "FC30-data_calc_frate_limit.txt" using 2:5 with lines  lw 2 title "limit-2 Min/Max Machine Velocity"
## replot "FC30-data_calc_frate_limit.txt" using 2:6 with lines  lw 2 title "limit-3 Contour Accuracy Error"
## replot "FC30-data_calc_frate_limit.txt" using 2:7 with lines  lw 2 title "limit-4 Acceleration confinement"

## PLOT CHECK 
## plot   "FC40-data_calc_u_next.txt"      using 2:18 with lines lw 2 title "limit-1 User set Frate Command"
## replot "FC40-data_calc_frate_limit.txt" using 2:5 with lines  lw 2 title "limit-2 Min/Max Machine Velocity"
## replot "FC40-data_calc_frate_limit.txt" using 2:6 with lines  lw 2 title "limit-3 Contour Accuracy Error"
## replot "FC40-data_calc_frate_limit.txt" using 2:7 with lines  lw 2 title "limit-4 Acceleration confinement"


# DATA COLUMNS INDEX = COLUMN NUMBER
# rtime[1], 
# u[2], 
# u_next[3], 
# FRate_limit_1[4], 
# FRate_limit_2[5], 
# FRate_limit_3[6], 
# FRate_limit_4[7], 
# FRate_limit[8], 
# eps_N[9], 
# rho_N[10] 

# DTStamp_FHdata_calc_u_next 2022-06-23 12:23:39 179309410 

# EXECUTION
# gnuplot -p plot2D_calc_u_next_00_u_versus_u_next.gp


