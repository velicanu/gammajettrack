
if [ $# -lt 6 ]
then
  echo "Usage: ./doff.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi> <whichsys> <sysscalefactor> <inputfile>"
  exit 1
fi

# ./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/PbPb-Data-skim-170407.root pbpbdata 0 20 60 1000 recoreco 30 0 1 1 

./ffgamma.exe $9 pbpbdata 0 20 $1 $2 $3 recoreco $4 $5 $6 $7 $8 &
./ffgamma.exe $9 pbpbdata 20 60 $1 $2 $3 recoreco $4 $5 $6 $7 $8 &
#wait
./ffgamma.exe $9 pbpbdata 60 100 $1 $2 $3 recoreco $4 $5 $6 $7 $8 &
# ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v9.root pbpbdata 100 140 $1 $2 $3 recoreco $4 $5 $6 &
./ffgamma.exe $9 pbpbdata 100 200 $1 $2 $3 recoreco $4 $5 $6 $7 $8 &
#wait

#./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170406.root ppdata 0 20 $1 $2 $3 recoreco $4 $5 $6 &
#./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170406.root ppdata 20 60 $1 $2 $3 recoreco $4 $5 $6 &
#wait
#./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170406.root ppdata 60 100 $1 $2 $3 recoreco $4 $5 $6 &
# ./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170406.root ppdata 100 140 $1 $2 $3 recoreco $4 $5 $6 &
#./ffgamma.exe /export/d00/scratch/biran/photon-jet-track/pp-Data-skim-170406.root ppdata 100 200 $1 $2 $3 recoreco $4 $5 $6 &
wait

hadd -f all_${1}_${2}_${3}_gammaxi${6}.root pbpbdata_pbpbdata_*_*.root
# ppdata_ppdata_*_*.root 
#rm pbpbdata_pbpbdata_*_*.root ppdata_ppdata_*_*.root 
