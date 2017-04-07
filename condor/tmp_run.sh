arglist="${@:6}"
nline=$(($1+1))
whichmbfile=$(($1%40))
whichmbfile=$(($whichmbfile+1))
tar -xzvf $4
mbfile=`head -n${whichmbfile} minbiasmixing.txt | tail -n1`


echo ./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist} 1 ${mbfile}
./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist} 1 ${mbfile}
echo $@
rm L2L3VsPtEtaBinned_ak3PF.root
if [[ `ls -trs *.root | tail -n1 | awk '{print $1}'` -gt 20 ]]; then # for files with more than 0 events inside
  mv `ls -tr *.root | tail -n1` $3
else
  ls -trsh *.root 
fi
ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf

