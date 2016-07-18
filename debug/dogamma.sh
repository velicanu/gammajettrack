# ./zbalance.exe /export/d00/scratch/dav2105/ztrees/g.pp-photonHLTFilter-v0-HiForest-40GeV.root g ppdata g 0.2 &
# ./zbalance.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon50_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1-40GeV.root g ppmc g 0.2 &
./zbalance.exe /export/d00/scratch/dav2105/ztrees/ppdata.root g ppdata g 0.2 &
./zbalance.exe /export/d00/scratch/dav2105/ztrees/ppmc.root g ppmc g 0.2 &
wait
hadd -f gall.root g_ppmc_*.root g_ppdata_*.root
