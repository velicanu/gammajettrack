echo running closure histograms
# pp mc
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 0 20 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 20 60 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 60 100 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 100 140 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 140 200 100 300 &
wait
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 0 20 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 20 60 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 60 100 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 100 140 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix10events pbpbmc 140 200 100 300 gen &

wait
hadd -f closure.root pbpbmc_pbpbmc_*_*.root
rm pbpbmc_pbpbmc_*_*.root
