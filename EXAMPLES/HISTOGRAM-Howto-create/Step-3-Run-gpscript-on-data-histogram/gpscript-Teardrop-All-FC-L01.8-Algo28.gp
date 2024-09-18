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
set title "Teardrop u-point distribution\n with feedrate commands FC 10, 20, 30 and 40 mm/s \n lamda = 0.18 for the full u-bin range [0.0 .. 1.0]" 

set xlabel "parameter u-bin range"
set ylabel "u-point bin counts"

## SETTING X-RANGE NOT NEEDED
set xrange  [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback

## IMPORTANT TO SET Y-RANGE
set yrange [ 0.00000 : 2500. ] noreverse writeback
set y2range [ * : * ] noreverse writeback

set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

NO_ANIMATION = 1

## IMPORTANT 3 LINES BELOW, OFFSET FROM LEFT X-AXIS, X-AXIS CLUSTER LABELS INSIDE "XXX"   
set offset -1
set xtics ("[0.0 - 0.1)" 1, "[0.1 - 0.2)" 2, "[0.2 - 0.3)" 3, "[0.3 - 0.4)" 4, "[0.4 - 0.5)" 5, "[0.5 - 0.6)" 6, "[0.6 - 0.7)" 7, "[0.7 - 0.8)" 8, "[0.8 - 0.9)" 9, "[0.9 - 1.0)" 10)

plot 'data-histogram-Teardrop-L018-for-gpscript.txt' using 1:xtic(1) title "BINS", '' using 2 title "FC10", '' using 3 title "FC20", '' using 4 title "FC30", '' using 5 title "FC40"

## ==================================================================
## ALHAMDULILLAH 3 TIMES.
## ==================================================================

