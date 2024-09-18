
## FILE: plot3D_03_data_parametric_cposition_xposuv_yposuv_u.gp
# wruslan@HPLaptop-01-ub20:~/WRY-UMP-Thesis/Chap4/plot3D-codes$ date
# Mon 11 Sep 2023 06:28:27 PM +08

clear
set size square
set autoscale
set grid

set xlabel "cpos-x(u)"
set ylabel "cpos-y(u)"
set zlabel "u(t)"
## set title  "TEARDROP Plot3D parametric curve, cpos-x(u) vs cpos-y(u) vs u(t)"
set title  "BUTTERFLY Plot3D parametric curve, cpos-x(u) vs cpos-y(u) vs u(t)"

## splot "Algo20-TEARDROP-FC20-data_ngcode.txt" using 5:7:9 with linespoints 
splot "Algo20-BUTTERFLY-FC20-data_ngcode.txt" using 5:7:9 with linespoints 


# DATA COLUMNS INDEX = COLUMN NUMBER
# G01 F    3.000000 X[    0.000000] Y[    0.000000] (#u= 0.000000000 eps= 0.000000471228 Xfrate= -2.121320 Yfrate= -2.121320 frlimit=  0.000000 frdiff= -3.000000000 frcmd= 20.000 #) 
# G01 F    3.000000 X[   -0.014135] Y[   -0.014138] (#u= 0.000094261 eps= 0.000000471628 Xfrate= -2.120920 Yfrate= -2.121720 frlimit= 19.988716 frdiff= 16.988716359 frcmd= 20.000 #) 
# G01 F    3.000000 X[   -0.028268] Y[   -0.028278] (#u= 0.000188558 eps= 0.000000472028 Xfrate= -2.120520 Yfrate= -2.122121 frlimit= 19.988710 frdiff= 16.988710298 frcmd= 20.000 #) 
# G01 F    3.000000 X[   -0.042397] Y[   -0.042421] (#u= 0.000282890 eps= 0.000000472429 Xfrate= -2.120119 Yfrate= -2.122521 frlimit= 19.988704 frdiff= 16.988704231 frcmd= 20.000 #) 

# COMMAND
# gnuplot -p plot3D_03_data_parametric_cposition_xposuv_yposuv_u.gp

