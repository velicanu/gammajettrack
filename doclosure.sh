echo running closure histograms
rm pbpbmc_pbpbmc_*_*.root
# pp mc
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 0 20 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 20 60 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 60 100 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 100 140 100 300 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 140 200 100 300 &
wait
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 0 20 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 20 60 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 60 100 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 100 140 100 300 gen &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root pbpbmc 140 200 100 300 gen &

wait
hadd -f closure.root pbpbmc_pbpbmc_*_*.root
