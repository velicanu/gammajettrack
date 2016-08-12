arglist="${@:6}"
nline=$(($1+1))
whichmbfile=$(($1/1080))
if [ $whichmbfile -eq 0 ]; then
  mbfile="/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/0.root"
fi
if [ $whichmbfile -eq 1 ]; then
  mbfile="/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/1.root"
fi
if [ $whichmbfile -eq 2 ]; then
  mbfile="/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/2.root"
fi
if [ $whichmbfile -eq 3 ]; then
  mbfile="/mnt/hadoop/cms/store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/3.root"
fi

tar -xzvf $4
echo ./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist} 1 ${mbfile}
./$5 `head -n${nline} $2 | tail -n1` ${nline}.root ${arglist}
echo $@
if [[ `ls -trs *.root | tail -n1 | awk '{print $1}'` -gt 20 ]]; then # for files with more than 0 events inside
  mv `ls -tr *.root | tail -n1` $3
fi
ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf
