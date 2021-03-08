run_folders=`ls ~/ctG_runs` 
for run in $run_folders
do 
	echo $run
	./dataSilas.sh $run
done 
counter=-0.9
data_files=`ls ~/ctG_runs/*.dat`
until $counter==1 
do 
	for data in $data_files
	do 
	#implement the asymmetry analysis
	#need to extract the value for ctG somehow
	#look for value from param card?
	

