
## File: plot2D-calc-u-next-09B-u-versus-diff-fratelimit-currfrate.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "diff-frate (mm/s)"
set title  "Plot 2D (u,diff) Difference Feedrate Limit minus Current Feedrate" 


# COMMENT RANGES FOR DEFAULT
set xrange [ 0.0 : +1.0]
set yrange [ -1.0E-5 : 4.0E-5]

## 07-SPIRAL EPSILON
## set yrange [ 0.00000099 : 0.000001005]  
## set yrange [ +9.930E-07   : +1.001E-6]


## PLOT CHECK

## plot     "FC10-data_calc_u_next.txt" using 2:19 with lines lw 2 lc "blue" title "diff = (fratelimit - currfrate) > 0"
plot     "FC20-data_calc_u_next.txt" using 2:19 with lines lw 2 lc "blue" title "diff = (fratelimit - currfrate) > 0"
## plot     "FC30-data_calc_u_next.txt" using 2:19 with lines lw 2 lc "blue" title "diff = (fratelimit - currfrate) > 0"
## plot     "FC40-data_calc_u_next.txt" using 2:19 with lines lw 2 lc "blue" title "diff = (fratelimit - currfrate) > 0"

# DATA COLUMNS INDEX = COLUMN NUMBER
# rtime[1] 
# u[2] 
# u_next[3] 
# t_interpol[4] 
# first_order[5] 
# second_order[6] 
# diff[7] 
# pos_x[8]
# pos_y[9]
# pos_r[10] 
# eps[11]   ABOUT 0.000000621355
# rho[12] 
# curr_tang_accn[13] 
# curr_frate[14] 
# frate_limit[15] 
# x_frate[16] 
# y_frate17]
# frate_cmd[18]
# diff_frate[19]

# DTStamp_FHdata_calc_u_next 2022-06-23 12:23:39 179309410 

# EXECUTION
# gnuplot -p plot2D_calc_u_next_00_u_versus_u_next.gp


