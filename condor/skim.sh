#!/bin/bash

if [[ $# -lt 5 ]]; then
    echo "don't run this locally! run ./skim-condor.sh instead!"
    echo "usage: ./skim.sh [n] [0/1] [input list] [output dir] [residuals] [[mixing list]]"
    exit 1
fi

PBPB_WEIGHTS=(0.999328 0.447420 0.153135 0.042342 0.012907)
PP_WEIGHTS=(0.999456 0.186121 0.0422225 0.00931044 0.00194072)

JETALGO=akPu3PFJetAnalyzer
ISPP=0
WEIGHT=1
MIXFILE=""

tar -xzvf $5

FILE=$(head -n$(($1+1)) $3 | tail -n1)
case $2 in
    0)
        if [[ $# -lt 6 ]]; then
            echo "no mixing file list provided"
            exit 1
        fi

        NMIX=$(($1%40))
        NMIX=$(($NMIX+1))
        MIXFILE=$(head -n${NMIX} $6 | tail -n1)
        ;;
    1)
        if [[ $FILE =~ [0-9]*Flt30 ]]; then
            PTHAT=${BASH_REMATCH[0]}
            PTHAT=${PTHAT/%Flt30/}
            case $PTHAT in
                15)
                    WEIGHT=${PBPB_WEIGHTS[0]}
                    ;;
                30)
                    WEIGHT=${PBPB_WEIGHTS[1]}
                    ;;
                50)
                    WEIGHT=${PBPB_WEIGHTS[2]}
                    ;;
                80)
                    WEIGHT=${PBPB_WEIGHTS[3]}
                    ;;
                120)
                    WEIGHT=${PBPB_WEIGHTS[4]}
                    ;;
                *)
                    echo "bad match"
                    exit 1
                    ;;
            esac
            echo "pthat: $PTHAT, weight: ${WEIGHT}"
        fi
        MIXFILE=/mnt/hadoop/cms/store/user/biran/photon-jet-track/PbPb-MB-Hydjet-Cymbal-170331.root
        ;;
    2)
        JETALGO=ak3PFJetAnalyzer
        ISPP=1
        ;;
    3)
        JETALGO=ak3PFJetAnalyzer
        ISPP=1
        if [[ $FILE =~ [0-9]*_pp502 ]]; then
            PTHAT=${BASH_REMATCH[0]}
            PTHAT=${PTHAT/%_pp502/}
            case $PTHAT in
                15)
                    WEIGHT=${PP_WEIGHTS[0]}
                    ;;
                30)
                    WEIGHT=${PP_WEIGHTS[1]}
                    ;;
                50)
                    WEIGHT=${PP_WEIGHTS[2]}
                    ;;
                80)
                    WEIGHT=${PP_WEIGHTS[3]}
                    ;;
                120)
                    WEIGHT=${PP_WEIGHTS[4]}
                    ;;
                *)
                    echo "bad match"
                    exit 1
                    ;;
            esac
            echo "pthat: $PTHAT, weight: ${WEIGHT}"
        fi
        ;;
    *)
        echo "bad option"
        exit 1
        ;;
esac

echo ./gammajetSkim.exe $FILE ${1}.root $JETALGO $ISPP $WEIGHT $MIXFILE
./gammajetSkim.exe $FILE ${1}.root $JETALGO $ISPP $WEIGHT $MIXFILE

mv ${1}.root ${4}

ls | grep -v .out | grep -v .err | grep -v .log | grep -v _condor_stdout | grep -v _condor_stderr | xargs rm -rf
