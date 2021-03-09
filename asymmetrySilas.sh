#! /bin/bash
threshold=$1
i=$2
fname=$3
cd ~/ctG_runs
until [ $threshold -gt $i ]
do

	echo $threshold
	paste <(awk -v bar=$threshold '{if ($1 < bar/10) sum1+=$2;};{if ($1 > bar/10) sum2+=$2;}; END{print "Ab2 (ttZ) = "(sum2-sum1)/(sum1+sum2);}' b2_$fname.dat) <(awk -v bar=$threshold '{if ($1 < bar/10) sum1+=$2;};{if ($1 > bar/10) sum2+=$2;}; END{print "Ab4 (ttZ) = "(sum2-sum1)/(sum1+sum2);}' b4_$fname.dat)
	paste <(awk -v bar=$threshold '{if ($1 < bar/10) sum1+=$3;};{if ($1 > bar/10) sum2+=$3;}; END{print "Ab2 (lab) = "(sum2-sum1)/(sum1+sum2);}' b2_$fname.dat) <(awk -v bar=$threshold '{if ($1 < bar/10) sum1+=$3;};{if ($1 > bar/10) sum2+=$3;}; END{print "Ab4 (lab) = "(sum2-sum1)/(sum1+sum2);}' b4_$fname.dat)
	((threshold++))
done
