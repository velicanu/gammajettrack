#!/bin/bash

if [[ $# -lt 4 ]]; then
    echo "usage: ./skim-pbpbmc.sh [n] [input list] [output dir] [residuals]"
    exit 1
fi

WEIGHTS=(0.999328 0.447420 0.153135 0.042342 0.012907)

tar -xzvf $4

FILE=$(head -n$(($1+1)) $2 | tail -n1)
if [[ $FILE =~ [0-9]*Flt30 ]]; then
    PTHAT=${BASH_REMATCH[0]}
    PTHAT=${PTHAT/%Flt30/}
    case $PTHAT in
        15)
            WEIGHT=${WEIGHTS[0]}
            ;;
        30)
            WEIGHT=${WEIGHTS[1]}
            ;;
        50)
            WEIGHT=${WEIGHTS[2]}
            ;;
        80)
            WEIGHT=${WEIGHTS[3]}
            ;;
        120)
            WEIGHT=${WEIGHTS[4]}
            ;;
        *)
            echo "bad match"
            exit 1
            ;;
    esac
    echo "pthat: $PTHAT, weight: ${WEIGHT}"
    echo ./gammajetSkim.exe $FILE ${1}.root akPu3PFJetAnalyzer 0 $WEIGHT /mnt/hadoop/cms/store/user/velicanu/Merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root
    ./gammajetSkim.exe $FILE ${1}.root akPu3PFJetAnalyzer 0 $WEIGHT /mnt/hadoop/cms/store/user/velicanu/Merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root
    mv ${1}.root ${3}

    ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf
fi
