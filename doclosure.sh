if [ $# -lt 7 ]
then
  echo "Usage: ./doclosure.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./doclosure.sh 60 1000 30 0 1 0 gengen recoreco"
  exit 1
fi

echo running closure histograms
for i in ${@:7}
do
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 0 20 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 20 60 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 60 100 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root pbpbmc 100 200 $1 $2 $3 $i $4 $5 $6 &
done
wait


hadd -f closure_pbpb_${1}_${2}_${3}_gammaxi${6}.root pbpbmc_pbpbmc_*_*.root
rm pbpbmc_pbpbmc_*_*.root
