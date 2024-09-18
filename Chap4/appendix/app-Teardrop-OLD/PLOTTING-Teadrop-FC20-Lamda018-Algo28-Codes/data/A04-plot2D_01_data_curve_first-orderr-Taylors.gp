
## FILE: plot3D_01_data_curve_cposition_xpos_ypos_u.gp

clear
set size square
set autoscale
set grid

set xlabel "parameter (u)"
set ylabel "first-order-Taylors-approx(u)"
set title "Plot2D curve (u) vs first-order-Taylors-approx(u)"


# set yrange [-40.0 : +40.0]
set xrange [0.0 : 1.0]

## plot "FC10-data_calc_u_next.txt" using 2:5 with lines linecolor black linewidth 2 title "first-order(u)" 
plot "FC20-data_calc_u_next.txt" using 2:5 with lines linecolor black linewidth 2 title "first-order(u)" 
## plot "FC30-data_calc_u_next.txt" using 2:5 with lines linecolor black linewidth 2 title "first-order(u)" 
## plot "FC40-data_calc_u_next.txt" using 2:5 with lines linecolor black linewidth 2 title "first-order(u)" 


## 3D-PLOT TEARDROP CHECK
## splot "data_calc_u_next.txt" using 8:9:2 with lines linecolor black linewidth 2 title "u-direction" 

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
# eps[11] chord-error
# rho[12] radius of curvature 
# curr_tang_accn[13] 
# curr_frate[14] 
# frate_limit[15] 
# x_frate[16] 
# y_frate[17] 
# frate_command[18], 
# diff_frate[19]

# ALHAN DULILLAH 3 TIMES.
