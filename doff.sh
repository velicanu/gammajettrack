echo running pp mc
# pp mc
./ffgamma.exe ../g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ppmc &
# pbpb mc
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_forest_v1.root pbpbmc 0 20 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_forest_v1.root pbpbmc 20 60 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_forest_v1.root pbpbmc 60 100 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_forest_v1.root pbpbmc 100 140 &
./ffgamma.exe ../g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_forest_v1.root pbpbmc 140 200 &
wait
echo ============
echo finished running mc, now running data
# pp data
./ffgamma.exe ../g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ppdata &
# pp mc
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3-fixedtrksel.root pbpbdata 0 20  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3-fixedtrksel.root pbpbdata 20 60  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3-fixedtrksel.root pbpbdata 60 100  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3-fixedtrksel.root pbpbdata 100 140  &
./ffgamma.exe ../g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3-fixedtrksel.root pbpbdata 140 200  &
wait
