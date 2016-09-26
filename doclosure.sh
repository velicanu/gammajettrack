echo running closure histograms
# pp mc
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 0 20 $1 $2 gengen &
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 20 60 $1 $2 gengen &
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 60 100 $1 $2 gengen &
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 100 140 $1 $2 gengen &
# ./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 140 200 $1 $2 gengen &
# wait
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 0 20 $1 $2 $3 reco &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 20 60 $1 $2 $3 reco &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 60 100 $1 $2 $3 reco &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 100 140 $1 $2 $3 reco &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 140 200 $1 $2 $3 reco &
wait
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 0 20 $1 $2 $3 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 20 60 $1 $2 $3 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 60 100 $1 $2 $3 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 100 140 $1 $2 $3 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 140 200 $1 $2 $3 gen &
wait
hadd -f closure_${1}_${2}_${3}.root pbpbmc_pbpbmc_*_*.root
rm pbpbmc_pbpbmc_*_*.root
