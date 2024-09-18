
## File: plot2D-calc-u-next-01-u-versus-xpos-ypos.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "x(u) and y(u) points"
set title  "Plot 2D X and Y position coordinates of parametric curve" 

# COMMENT RANGES FOR DEFAULT
set xrange [ 0.0 : +1.0]
set yrange [ -50.0 : +40.0]

## PLOT CHECK
## plot   "FC10-data_calc_u_next.txt" using 2:8 with lines lw 2 title "(u, x(u)) point"
## replot "FC10-data_calc_u_next.txt" using 2:9 with lines lw 2 title "(u, y(u)) point"

## PLOT CHECK
plot   "FC20-data_calc_u_next.txt" using 2:8 with lines lw 2 title "(u, x(u)) point"
replot "FC20-data_calc_u_next.txt" using 2:9 with lines lw 2 title "(u, y(u)) point"

## PLOT CHECK
## plot   "FC30-data_calc_u_next.txt" using 2:8 with lines lw 2 title "(u, x(u)) point"
## replot "FC30-data_calc_u_next.txt" using 2:9 with lines lw 2 title "(u, y(u)) point"

## PLOT CHECK
## plot   "FC40-data_calc_u_next.txt" using 2:8 with lines lw 2 title "(u, x(u)) point"
## replot "FC40-data_calc_u_next.txt" using 2:9 with lines lw 2 title "(u, y(u)) point"



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
# eps[11]
# rho[12] 
# curr_tang_accn[13] 
# curr_frate[14] 
# frate_limit[15] 
# x_frate[16] 
# y_frate17]

# DTStamp_FHdata_calc_u_next 2022-06-23 12:23:39 179309410 

# EXECUTION
# gnuplot -p plot2D_calc_u_next_00_u_versus_u_next.gp


