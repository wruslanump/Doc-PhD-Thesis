
## File: plot2D-calc-u-next-09A-u-versus-FRateLimit-CurrFrate.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "feedrate (mm/s)
set title  "Plot 2D Feedrate Command, Calculated Feedrate Limit and Current Feedrate" 


# COMMENT RANGES FOR DEFAULT
set xrange [ 0.0 : +1.0]
set yrange [ 0.0 : + 30.0]

## 07-SPIRAL EPSILON
## set yrange [ 0.00000099 : 0.000001005]  
## set yrange [ +9.930E-07   : +1.001E-6]


## PLOT CHECK

## plot   "FC10-data_calc_u_next.txt" using 2:18 with lines linewidth 2   title "frate-command(u)"
## replot "FC10-data_calc_u_next.txt" using 2:15 with lines linewidth 2   title "  frate-limit(u)"
## replot "FC10-data_calc_u_next.txt" using 2:14 with lines linewidth 2   title "   curr-frate(u)"

plot   "FC20-data_calc_u_next.txt" using 2:18 with lines linewidth 2   title "frate-command(u)"
replot "FC20-data_calc_u_next.txt" using 2:15 with lines linewidth 2   title "  frate-limit(u)"
replot "FC20-data_calc_u_next.txt" using 2:14 with lines linewidth 2   title "   curr-frate(u)"

## plot   "FC30-data_calc_u_next.txt" using 2:18 with lines linewidth 2   title "frate-command(u)"
## replot "FC30-data_calc_u_next.txt" using 2:15 with lines linewidth 2   title "  frate-limit(u)"
## replot "FC30-data_calc_u_next.txt" using 2:14 with lines linewidth 2   title "   curr-frate(u)"

## plot   "FC40-data_calc_u_next.txt" using 2:18 with lines linewidth 2   title "frate-command(u)"
## replot "FC40-data_calc_u_next.txt" using 2:15 with lines linewidth 2   title "  frate-limit(u)"
## replot "FC40-data_calc_u_next.txt" using 2:14 with lines linewidth 2   title "   curr-frate(u)"

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


