#!/bin/bash

RESUBMIT=""

for FILE in logs/*.out
do
    if [ -s $FILE ]; then
        if [ "$(tail -n1 $FILE | grep done)" != "done" ]; then
            PROCESS=$(basename $FILE .out)
            if [ "$RESUBMIT" = "" ]; then
                RESUBMIT=$PROCESS
            else
                RESUBMIT="${RESUBMIT},${PROCESS}"
            fi
        fi
    else
        PROCESS=$(basename $FILE .out)
        if [ "$RESUBMIT" = "" ]; then
            RESUBMIT=$PROCESS
        else
            RESUBMIT="${RESUBMIT},${PROCESS}"
        fi
    fi
done

echo $RESUBMIT
sed -i "s/\#noop/noop/g" skim.condor
sed -i "s/__FAILED__/$RESUBMIT/g" skim.condor

condor_submit skim.condor

# reset skim.condor
sed -i 's/.*noop_job.*/#noop_job = !( stringListMember("\$(Process)","__FAILED__") )/' skim.condor
