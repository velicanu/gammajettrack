
if [ $# -lt 2 ]
then
  echo "Usage: ./doff.sh <phoetmin> <phoetmax> "
  exit 1
fi

# echo running mc mc
# pp mc
./ffgamma.exe ../g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v10.root ppmc -1 200 $1 $2 &
# pbpb mc
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 0 20 $1 $2 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 20 60 $1 $2 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 60 100 $1 $2 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 100 200 $1 $2 &
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 140 200 $1 $2 &
# wait
# echo ============
# echo finished running mc, now running data
# pp data
./ffgamma.exe ../g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata -1 200 $1 $2 &
# pbpb data
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root pbpbdata 0 20 $1 $2  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root pbpbdata 20 60 $1 $2  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root pbpbdata 60 100 $1 $2  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root pbpbdata 100 200 $1 $2  &
# ./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root pbpbdata 140 200 $1 $2  &
wait
hadd -f all_${1}_${2}.root p*data_p*data__*_*.root p*mc_p*mc__*_*.root
rm p*data_p*data__*_*.root p*mc_p*mc__*_*.root
