arglist="${@:6}"
nline=$(($1+1))
whichmbfile=$(($1%40))
whichmbfile=$(($whichmbfile+1))
tar -xzvf $4
mbfile=`head -n${whichmbfile} minbiasmixing.txt | tail -n1`

echo waiting for queue to clear up
while [ 4000 -lt `ls /mnt/hadoop/cms/store/user/velicanu/locks/ | wc -l` ]
do
  # will stay here until total job queue is less than the threshold
  sleep 10
done
echo done waiting starting job

echo 1 > /mnt/hadoop/cms/store/user/velicanu/locks/${1}.txt

echo ./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist} 1 ${mbfile}
./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist} 1 ${mbfile}
echo $@
if [[ `ls -trs *.root | tail -n1 | awk '{print $1}'` -gt 20 ]]; then # for files with more than 0 events inside
  mv `ls -tr *.root | tail -n1` $3
fi
ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf

rm /mnt/hadoop/cms/store/user/velicanu/locks/${1}.txt
