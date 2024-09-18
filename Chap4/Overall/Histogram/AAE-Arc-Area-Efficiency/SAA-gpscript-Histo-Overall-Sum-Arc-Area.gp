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
set title "Overall Total Sum-Arc-Area SAA for each curve \n at Feedrate Commands FC10, FC20, FC30 and FC40 \n with all lamda = 0.18" 

set xlabel "Curve Type"
set ylabel "Total Sum-Arc-Area SAA (mm)"

## SETTING X-RANGE NOT NEEDED
set xrange  [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback

## IMPORTANT TO SET Y-RANGE  <============================== REQUIRED
set yrange [ 1E-7 : 1E-3] noreverse writeback
set y2range [ * : * ] noreverse writeback

set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault

NO_ANIMATION = 1

## ==============================
## IMPORTANT 3 LINES BELOW, 

## OFFSET FROM LEFT X-AXIS, 
set offset -1

## X-AXIS CLUSTER LABELS INSIDE "XXX"   
set xtics ("Circle" 1, "Ellipse" 2, "Teardrop" 3, "Butterfly" 4, "Snailshell" 5, "SkwAstroid" 6, "Ribbon-10L" 7, "Ribbon-100L" 8, "Astepi" 9, "SnaHyp" 10)

## COLUMN NAME FOR LEGEND
plot 'SAA-data-for-Histo-Sum-Arc-Area.txt' using 1:xtic(1) title "CURVE-TYPE", '' using 2 title "FC10", '' using 3 title "FC20", '' using 4 title "FC30", '' using 5 title "FC40"

## ==================================================================
## ALHAMDULILLAH 3 TIMES.
## ==================================================================

