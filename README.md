# gammajettrack

Code base for gamma-jet-track analysis. Primary component is gammajetSkim.C which reads a HiForest and outputs a single tree containing photon, jets, and tracks passing multiple selection criteria.

## compiling
```bash
g++ gammajetSkim.C $(root-config --cflags --libs)  -Werror -Wall -O2 -o gammajetSkim.exe
```
## running
The skim code can be run with several parameters listed below, and as an example.
```bash
# /gammajetSkim.exe <inputfile> <outfile> [jetname] [is_pp] [mcweight] [startindex] [endindex] /mnt/hadoop/cms/store/user/velicanu/Merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root 147000 147010
/gammajetSkim.exe /mnt/hadoop/cms/store/user/velicanu/Merged/Pythia8_Photon120_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1/0.root /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon120_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.test akPu3PFJetAnalyzer 0 0.0434138 /mnt/hadoop/cms/store/user/velicanu/Merged/Hydjet_Quenched_MinBias_5020GeV_750-HINPbPbWinter16DR-NoPU_75X_mcRun2_HeavyIon_forest_v2/0.root 147000 147010
```
