
if [ $# -lt 6 ]
then
  echo "Usage: ./doff.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi>"
  exit 1
fi


./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root pbpbdata 0 20 $1 $2 $3 recoreco $4 $5 $6 &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root pbpbdata 20 60 $1 $2 $3 recoreco $4 $5 $6 &
#wait
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root pbpbdata 60 100 $1 $2 $3 recoreco $4 $5 $6 &
# ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v9.root pbpbdata 100 140 $1 $2 $3 recoreco $4 $5 $6 &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root pbpbdata 100 200 $1 $2 $3 recoreco $4 $5 $6 &
#wait

./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata 0 20 $1 $2 $3 recoreco $4 $5 $6 &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata 20 60 $1 $2 $3 recoreco $4 $5 $6 &
#wait
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata 60 100 $1 $2 $3 recoreco $4 $5 $6 &
# ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata 100 140 $1 $2 $3 recoreco $4 $5 $6 &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata 100 200 $1 $2 $3 recoreco $4 $5 $6 &
wait

hadd -f all_${1}_${2}_${3}_gammaxi${6}.root pbpbdata_pbpbdata_*_*.root ppdata_ppdata_*_*.root 
rm pbpbdata_pbpbdata_*_*.root ppdata_ppdata_*_*.root 
