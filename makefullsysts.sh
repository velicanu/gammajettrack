#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo "Usage: ./makefullsysts.sh [phoetmin] [jetptmin]"
    echo "Example: ./makefullsysts.sh 60 30"
    echo "Example: ./makefullsysts.sh 80 40"
    exit 1
fi

mkdir -p v3syst

# nominal jet & gamma xi
echo "Making nominal histograms"
mkdir -p v3syst/nominal
./doff.sh $1 1000 $2 0 1 0 0 0 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 0 0 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/nominal/

# jer jet & gamma xi
echo "Making jer histograms"
mkdir -p v3syst/jer10
./doff.sh $1 1000 $2 0 1 0 1 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 1 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jer10/
mkdir -p v3syst/jer06
./doff.sh $1 1000 $2 0 1 0 1 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 1 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jer06/
mkdir -p v3syst/jer03
./doff.sh $1 1000 $2 0 1 0 1 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 1 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jer03/

# jes jet & gamma xi
echo "Making jes histograms"
mkdir -p v3syst/jes10
./doff.sh $1 1000 $2 0 1 0 2 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 2 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jes10/
mkdir -p v3syst/jes06
./doff.sh $1 1000 $2 0 1 0 2 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 2 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jes06/
mkdir -p v3syst/jes03
./doff.sh $1 1000 $2 0 1 0 2 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 2 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jes03/

mkdir -p v3syst/jesm10
./doff.sh $1 1000 $2 0 1 0 3 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 3 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jesm10/
mkdir -p v3syst/jesm06
./doff.sh $1 1000 $2 0 1 0 3 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 3 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jesm06/
mkdir -p v3syst/jesm03
./doff.sh $1 1000 $2 0 1 0 3 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 3 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/jesm03/

# pes jet & gamma xi
echo "Making pes histograms"
mkdir -p v3syst/pes10
./doff.sh $1 1000 $2 0 1 0 4 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 4 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pes10/
mkdir -p v3syst/pes06
./doff.sh $1 1000 $2 0 1 0 4 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 4 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pes06/
mkdir -p v3syst/pes03
./doff.sh $1 1000 $2 0 1 0 4 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 4 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pes03/

mkdir -p v3syst/pesm10
./doff.sh $1 1000 $2 0 1 0 5 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 5 1 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pesm10/
mkdir -p v3syst/pesm06
./doff.sh $1 1000 $2 0 1 0 5 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 5 0.66 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pesm06/
mkdir -p v3syst/pesm03
./doff.sh $1 1000 $2 0 1 0 5 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
./doff.sh $1 1000 $2 0 1 1 5 0.33 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/pesm03/

# track jet & gamma xi
echo "Making nominal histograms"
mkdir -p v3syst/trk
./doff.sh $1 1000 $2 0 1 0 0 0 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170413-UIC.root
./doff.sh $1 1000 $2 0 1 1 0 0 /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170413-UIC.root
mv all_${1}_1000_${2}_gammaxi*.root v3syst/trk/



