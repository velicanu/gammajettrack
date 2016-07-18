
# zjet pp data
./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/PromptReco-AOD-DielectronSkim-262274-262328_ppFOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.PromptReco-AOD-DielectronSkim-262274-262328_ppFOREST_v24_5z.root ak4PFJetAnalyzer 1 &
./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/PromptReco-AOD-DimuonSkim-Mass40-262274-262328_ppFOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.PromptReco-AOD-DimuonSkim-Mass40-262274-262328_ppFOREST_v24_5z.root ak4PFJetAnalyzer 1 &

# zjet pp mc
./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/pp_Pythia8_Ze10e10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.pp_Pythia8_Ze10e10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24_5z.root ak3PFJetAnalyzer 1 &
./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/pp_Pythia8_Zmu10mu10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.pp_Pythia8_Zmu10mu10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24_5z.root ak3PFJetAnalyzer 1 &



# zjet PbPb data

./zjetSkim.exe /mnt/hadoop/cms/store/user/rbi/azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_3/0.root /export/d00/scratch/dav2105/ztrees/z.azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_5z.root akCs4PFJetAnalyzer 0 &
./zjetSkim.exe /mnt/hadoop/cms/store/user/rbi/merged/azsigmon-HIRun2015E-PromptReco-AOD-DimuonSkim-Mass40-v3_forest_csjet_v1_2/0.root /export/d00/scratch/dav2105/ztrees/z.azsigmon-HIRun2015E-PromptReco-AOD-DimuonSkim-Mass40-v3_forest_csjet_v1_5z.root akCs4PFJetAnalyzer 0 &

# zjet PbPb mc
  
# ./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/pp_Pythia8_Ze10e10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.pp_Pythia8_Ze10e10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24.root ak3PFJetAnalyzer 0 &
# ./zjetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/pp_Pythia8_Zmu10mu10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24/0.root /export/d00/scratch/dav2105/ztrees/z.pp_Pythia8_Zmu10mu10Jet_m60120_pthat0_TuneCUETP8M1_5020GeV_GEN_SIM_20160110_FOREST_v24.root ak3PFJetAnalyzer 0 &


wait 
echo done
