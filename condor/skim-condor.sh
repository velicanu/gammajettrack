#!/bin/bash

if [[ $# -ne 5 ]]; then
    echo "usage: ./skim-condor.sh [0/1/2/3] [input list] [output dir] [residuals] [mixing]"
    echo "[0: PbPb Data, 1: PbPb MC, 2: pp Data, 3: pp MC]"
    exit 1
fi

mkdir -p $3

JOBS=$(cat $2 | wc -l)

cat > skim.condor <<EOF
Universe     = vanilla
Initialdir   = $PWD/
Notification = Error
Executable   = $PWD/skim.sh
Arguments    = \$(Process) $1 $2 $3 $4 $5
GetEnv       = True
Output       = $PWD/logs/\$(Process).out
Error        = $PWD/logs/\$(Process).err
Log          = $PWD/logs/\$(Process).log
Rank         = Mips
+AccountingGroup = "group_cmshi.$(whoami)"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = gammajetSkim.exe,residuals.tgz,$2
#noop_job = !( stringListMember("\$(Process)","") )

Queue $JOBS
EOF

condor_submit skim.condor
