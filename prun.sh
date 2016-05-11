if [ $# -lt 4 ]
then
  echo "Usage: ./runskim.sh <input-list> <out-dir> <inputfile.tgz> <exe> [args]"
  exit 1
fi
now="job_${4}_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir -p $2
mkdir $now
njobs=`wc -l $1 | awk '{print $1}'`

cp tmp_run.sh $1 $3 $4 $now
arglist=`echo $@`
cat prun.condor | sed "s@log_flag@$now@g" | sed "s@arg_list@${arglist}@g" | sed "s@user_flag@$USER@g" | sed "s@dir_flag@$PWD/$now@g" | sed "s@njobs@${njobs}@g" | sed "s@exe_flag@$4@g" | sed "s@tar_flag@$3@g" > $now/pmerge.condor

cat $now/pmerge.condor
condor_submit $now/pmerge.condor

