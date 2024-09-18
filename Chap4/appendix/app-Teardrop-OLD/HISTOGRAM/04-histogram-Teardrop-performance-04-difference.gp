#!/usr/bin/gnuplot -persist

# wruslan@HPLaptop-01-ub20:~$ date
# Sat 07 Oct 2023 10:53:56 AM +08
# wruslan@HPLaptop-01-ub20:~$ uname -a
# Linux HPLaptop-01-ub20 5.15.0-84-lowlatency 
# #93~20.04.1-Ubuntu SMP PREEMPT Thu Sep 7 08:19:49 UTC 2023 
# x86_64 x86_64 x86_64 GNU/Linux

## BISMILLAH HIRRAHMA NIRRAHIM
## ======================================================================= 

clear
set autoscale
set grid
## CAN BE RECTANGULAR
## set size square  

set boxwidth 0.9 absolute
set style fill solid 1.00 border lt -1
set key fixed right top vertical Right noreverse noenhanced autotitle nobox

set style histogram clustered gap 1 title textcolor lt -1
unset parametric
set datafile missing '-'

set style data histograms
set xtics border in scale 0,0 nomirror rotate by -45  autojustify
set xtics norangelimit 

## ==================================================================
set title "Teardrop Performance 04: 100*(SAL - SCL)/SAL for each curve \n at Feedrate Commands FC10, FC20, FC30 and FC40 \n with all lamda = 0.18" 

set xlabel "Run Type"
set ylabel "Percent Difference 100*(SAL - SCL)/SAL (%)"

## SETTING X-RANGE NOT NEEDED
set xrange  [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback

## IMPORTANT TO SET Y-RANGE  <============================== REQUIRED
set yrange [ -3.0E-6 : 6.0E-6] noreverse writeback
set y2range [ * : * ] noreverse writeback

set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

NO_ANIMATION = 1

## ==============================
## IMPORTANT 3 LINES BELOW, 

## OFFSET FROM LEFT X-AXIS, 
set offset -0.2

## X-AXIS CLUSTER LABELS INSIDE "XXX"   
set xtics ("[FC10 Teardrop L0.18]" -0.18, "[FC20 Teardrop L0.18]" 0.0, "[FC30 Teardrop L0.18]" 0.18, "[FC40 Teardrop L0.18]" 0.35) 

## COLUMN NAME FOR LEGEND
plot 'data-Teardrop-histogram-performance-04-difference.txt' using 1:xtic(1) title "RUN-TYPE", '' using 2 title "[FC10 Teardrop L0.18]", '' using 3 title "[FC20 Teardrop L0.18]", '' using 4 title "[FC30 Teardrop L0.18]", '' using 5 title "[FC40 Teardrop L0.18]"

## ==================================================================
## ALHAMDULILLAH 3 TIMES.
## ==================================================================

