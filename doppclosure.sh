if [ $# -lt 7 ]
then
  echo "Usage: ./doclosure.sh <phoetmin> <phoetmax> <jetptmin> <checkjetid> <trkptmin> <gammaxi> <types...>"
  echo "Example: ./doclosure.sh 60 1000 30 0 1 gen reco"
  exit 1
fi

echo running closure histograms
for i in ${@:7}
do
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_minjet.root ppmc 0 20 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_minjet.root ppmc 20 60 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_minjet.root ppmc 60 100 $1 $2 $3 $i $4 $5 $6 &
  ./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_minjet.root ppmc 100 200 $1 $2 $3 $i $4 $5 $6 &
done
wait


hadd -f closure_pp_${1}_${2}_${3}_gammaxi${6}.root ppmc_ppmc_*_*.root
rm ppmc_ppmc_*_*.root
