rm g.Pythia8_Dijet30-*.root
echo running pF FF histos...
./ztree.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Dijet30_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_FOREST_758_PrivMC_vstest_v1.root g.Pythia8_Dijet30-all.root pbpbmc30 -99 &
./ztree.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Dijet30_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_FOREST_758_PrivMC_vstest_v1.root g.Pythia8_Dijet30-m1.root pbpbmc30 -1 &
./ztree.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Dijet30_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_FOREST_758_PrivMC_vstest_v1.root g.Pythia8_Dijet30-1.root pbpbmc30 1 &
./ztree.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Dijet30_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_FOREST_758_PrivMC_vstest_v1.root g.Pythia8_Dijet30-2.root pbpbmc30 2 &
./ztree.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Dijet30_pp_TuneCUETP8M1_Hydjet_MinBias_5020GeV_FOREST_758_PrivMC_vstest_v1.root g.Pythia8_Dijet30-3.root pbpbmc30 3 &
wait
echo done, merging output...
hadd -f allmc.root g.Pythia8_Dijet30-*.root
echo done
