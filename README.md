# gammajettrack

Code base for gamma-jet-track analysis. Primary component is gammajetSkim.C which reads a HiForest and outputs a single tree containing photon, jets, and tracks passing multiple selection criteria.

## compiling
```bash
g++ gammajetSkim.C $(root-config --cflags --libs)  -Werror -Wall -O2 -o gammajetSkim.exe
g++ ffgamma.C $(root-config --cflags --libs)  -Werror -Wall -O2 -o ffgamma.exe
```
## running skim

How to get this to run out of the box:
```bash
git clone git@github.com:velicanu/gammajettrack.git
cd gammajettrack/
tar -xvf condor/residuals.tgz
g++ gammajetSkim.C $(root-config --cflags --libs)  -Werror -Wall -O2 -o gammajetSkim.exe
./gammajetSkim.exe /mnt/hadoop/cms/store/user/richard/2015-Data-promptRECO-photonSkims/HIPhoton40AndZ/PbPb-photonHLTFilter-v3/160202_145715/0000/HiForestAOD_5.root test2.root akPu3PFJetAnalyzer 0 1
```

## running ff analysis
```bash
# ./ffgamma.exe <infilename> <outfilename> [centmin centmax] [phoetmin] [phoetmax] [jetptmin] [gen]
./ffgamma.exe /export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root.mix pbpbmc 140 200  100 300 40 reco
```
