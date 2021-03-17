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
	cd ~/ctG_runs 
	file1=$data'/summary.txt'
	grep -A0 "section:"  $file1 >~/mtG_data_runs_bash_script/temp1.txt
	file1=`ls ~/ctG_runs/$data/run_*`
	grep -A0 "ctG" $file1 >~/mtG_data_runs_bash_script/temp2.txt 
	cd ~/mtG_data_runs_bash_script
	./asymmetrySilas.sh -9 9 $data > tresults.txt
	paste temp1.txt temp2.txt tresults.txt > results_$data.txt 
	rm temp1.txt temp2.txt tresults.txt
done
sudo rm ~/ctG_runs/*.dat
ls *.txt > fnames.txt
./ra
	#implement the asymmetry analysis
	#need to extract the value for ctG somehow
	#look for value from param card?
#forget this, doing this part in the c++ file instead, way easier	

