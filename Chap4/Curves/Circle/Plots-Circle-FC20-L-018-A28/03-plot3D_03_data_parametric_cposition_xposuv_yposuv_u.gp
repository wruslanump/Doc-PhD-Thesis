
## FILE: plot3D_03_data_parametric_cposition_xposuv_yposuv_u.gp
# wruslan@HPLaptop-01-ub20:~/WRY-UMP-Thesis/Chap4/plot3D-codes$ date
# Mon 11 Sep 2023 06:28:27 PM +08

clear
set size square
set autoscale
set grid

set xlabel "position-x(u)"
set ylabel "position-y(u)"
set zlabel "u(t)"
## set title  "TEARDROP Plot3D parametric curve, cpos-x(u) vs cpos-y(u) vs u(t)"
set title  "Plot3D parametric curve, cpos-x(u) vs cpos-y(u) vs u(t)"

splot "data_calc_u_next.txt" using 8:9:2 with lines linewidth 2 linecolor black title "path u(t)"


# COMMAND
# gnuplot -p plot3D_03_data_parametric_cposition_xposuv_yposuv_u.gp

