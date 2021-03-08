cd ~/ctG_runs
file=$1"/MADatNLO.top"
grep -A41 "(  b4 " $file > tmp1.txt
awk 'NR > 2 { print }' < tmp1.txt > tmp2.txt
sed 's/D/e/g' tmp2.txt > b4ttzC.dat
rm tmp1.txt tmp2.txt
grep -A41 "(  b4l " $file > tmp1.txt
awk 'NR > 2 { print }' < tmp1.txt > tmp2.txt
sed 's/D/e/g' tmp2.txt > b4labC.dat
rm tmp1.txt tmp2.txt
grep -A41 "(  b2 " $file > tmp1.txt
awk 'NR > 2 { print }' < tmp1.txt > tmp2.txt
sed 's/D/e/g' tmp2.txt > b2ttzC.dat
rm tmp1.txt tmp2.txt
grep -A41 "(  b2l " $file > tmp1.txt
awk 'NR > 2 { print }' < tmp1.txt > tmp2.txt
sed 's/D/e/g' tmp2.txt > b2labC.dat
rm tmp1.txt tmp2.txt
paste b2ttzC.dat b2labC.dat > output.dat
awk '{print $1,$2,$5}' output.dat > b2_$1.dat
rm output.dat b2ttzC.dat b2labC.dat
paste b4ttzC.dat b4labC.dat > output.dat
awk '{print $1,$2,$5}' output.dat > b4_$1.dat
rm output.dat b4ttzC.dat b4labC.dat
