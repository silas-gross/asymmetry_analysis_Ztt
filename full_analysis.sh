#!/bin/bash
run_folders=`ls ~/ctG_runs` 
held_runs=$run_folders
for run in $run_folders
do 
	echo $run
	./dataSilas.sh $run
done 
counter=-9
#cd ~/ctG_runs
#until $counter == 9
#do 
#	b2_tt_vals=(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 1,2,3,4,5,6,7,8,9,10)
#	b2_lab_vals=(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 1,2,3,4,5,6,7,8,9,10)
#	b4_tt_vals=(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 1,2,3,4,5,6,7,8,9,10)
#	b4_lab_vals=(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 1,2,3,4,5,6,7,8,9,10)


#	for data in $held_runs 
#	do
#		i=0
#		paste <(awk '{if ($1 < $4/10) sum1+=$2;};{if ($1 > $4/10) sum2+=$2;}; END{print "Ab2 (ttZ) = "(sum2-sum1)/(sum1+sum2);}' b2_$data.dat $counter) >> b2_tt_vals[$i] <(awk '{if ($1 < $4/10) sum1+=$2;};{if ($1 > $4/10) sum2+=$2;}; END{print "Ab4 (ttZ) = "(sum2-sum1)/(sum1+sum2);}' b4_$data.dat) >>b4_tt_vals[$i]
#		paste <(awk '{if ($1 < $4/10) sum1+=$3;};{if ($1 > $4/10) sum2+=$3;}; END{print "Ab2 (lab) = "(sum2-sum1)/(sum1+sum2);}' b2_$data.dat) <(awk '{if ($1 < $4/10) sum1+=$3;};{if ($1 > $4/10) sum2+=$3;}; END{print "Ab4 (lab) = "(sum2-sum1)/(sum1+sum2);}' b4_$data.dat $counter)>>b4_lab_vals[$i]
#		((i++)) 
#	done
#	echo $b2_tt_vals >> b2_ttZ_frame_asym_at_$counter.txt
#	echo $b4_tt_vals >> b4_ttZ_frame_asym_at_$counter.txt
#	echo $b2_lab_vals >> b2_lab_frame_asym_at_$counter.txt
#	echo $b4_lab_vals >> b4_lab_frame_asym_at_$counter.txt

#	((counter++))
#done
#sudo rm ~/ctG_runs/*.dat
	#implement the asymmetry analysis
	#need to extract the value for ctG somehow
	#look for value from param card?
#forget this, doing this part in the c++ file instead, way easier	

