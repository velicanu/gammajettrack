# pp MC

./gammajetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/Pythia8_Photon15_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon15_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ak3PFJetAnalyzer 1 0.999456 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/Pythia8_Photon30_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon30_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ak3PFJetAnalyzer 1 0.186121 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/Pythia8_Photon50_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon50_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ak3PFJetAnalyzer 1 0.0422225 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/Pythia8_Photon80_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon80_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ak3PFJetAnalyzer 1 0.00931044 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/Pythia8_Photon120_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon120_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root ak3PFJetAnalyzer 1 0.00194072 &

# PbPb MC

./gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon15_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon15_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root akPu3PFJetAnalyzer 0 0.999565 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon30_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon30_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root akPu3PFJetAnalyzer 0 0.187379 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon50_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon50_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root akPu3PFJetAnalyzer 0 0.0434138 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon80_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon80_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root akPu3PFJetAnalyzer 0 0.0094069 &
./gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon120_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon120_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root akPu3PFJetAnalyzer 0 0.00211448 &


wait
# pp data
./gammajetSkim.exe /mnt/hadoop/cms/store/user/luck/2015-Data-promptRECO-photonSkims/pp-photonHLTFilter-v0-HiForest/0.root /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root ak3PFJetAnalyzer 1 &

# PbPb data
# done via condor

hadd -f /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v10.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon*_pp502_*
hadd -f /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v10.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon*_Hydjet_*


wait
echo
echo done
