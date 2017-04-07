#!/bin/bash

if [[ $# -ne 3 ]]; then
    echo "usage: ./skim-pbpbmc-condor.sh [input list] [output dir] [residuals]"
    exit 1
fi

mkdir -p $2

JOBS=$(cat $1 | wc -l)

cat > skim-pbpbmc.condor <<EOF
Universe     = vanilla
Initialdir   = $PWD/
Notification = Error
Executable   = $PWD/skim-pbpbmc.sh
Arguments    = \$(Process) $1 $2 $3
GetEnv       = True
Output       = $PWD/logs/\$(Process).out
Error        = $PWD/logs/\$(Process).err
Log          = $PWD/logs/\$(Process).log
Rank         = Mips
+AccountingGroup = "group_cmshi.$(whoami)"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_input_files = gammajetSkim.exe,residuals.tgz
#noop_job = !( stringListMember("\$(Process)","") )

Queue $JOBS
EOF

condor_submit skim-pbpbmc.condor
