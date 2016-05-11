arglist="${@:6}"
nline=$(($1+1))
tar -xzvf $4
echo ./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist}
./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist}
echo $@
if [[ `ls -trs *.root | tail -n1 | awk '{print $1}'` -gt 20 ]]; then # for files with more than 0 events inside
  mv `ls -tr *.root | tail -n1` $3
fi
ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf
