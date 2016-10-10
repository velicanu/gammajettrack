
if [ $# -lt 5 ]
then
  echo "Usage: ./doff.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> "
  exit 1
fi


./ffgamma.exe /export/d00/scratch/dav2105/ztrees/HIPhoton40AndZ-PbPb-photonHLTFilter-v4.root pbpbdata 0 20 $1 $2 $3 reco $4 $5 &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/HIPhoton40AndZ-PbPb-photonHLTFilter-v4.root pbpbdata 20 60 $1 $2 $3 reco $4 $5  &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/HIPhoton40AndZ-PbPb-photonHLTFilter-v4.root pbpbdata 60 100 $1 $2 $3 reco $4 $5  &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/HIPhoton40AndZ-PbPb-photonHLTFilter-v4.root pbpbdata 100 140 $1 $2 $3 reco $4 $5  &
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/HIPhoton40AndZ-PbPb-photonHLTFilter-v4.root pbpbdata 140 200 $1 $2 $3 reco $4 $5  &
wait

hadd -f all_${1}_${2}_${3}.root pbpbdata_pbpbdata_*_*.root
rm pbpbdata_pbpbdata_*_*.root
