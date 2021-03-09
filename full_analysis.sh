#!/bin/bash
run_folders=`ls ~/ctG_runs` 
held_runs=$run_folders
for run in $run_folders
do 
	echo $run
	./dataSilas.sh $run
done 


for data in $held_runs 
do
	./asymmetrySilas.sh -9 9 $data > results_$data.txt
done
sudo rm ~/ctG_runs/*.dat
	#implement the asymmetry analysis
	#need to extract the value for ctG somehow
	#look for value from param card?
#forget this, doing this part in the c++ file instead, way easier	

