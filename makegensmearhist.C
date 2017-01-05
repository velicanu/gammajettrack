{
  TFile *fpp = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_pp502_TuneCUETP8M1-HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_forest_v1.root");
  TFile *fpbpb = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root");
  
  TTree * zpp = (TTree*) fpp->Get("ztree");
  TTree * zpbpb = (TTree*) fpbpb->Get("ztree");
  
  TFile * outf = new TFile("gensmearhists.root","recreate");
  TH2D * hpbpbrpt = new TH2D("hpbpbrpt",";hiBin;jetpt/gjetpt",20,0,200,20,0,2);
  TH2D * hpbpbreta = new TH2D("hpbpbreta",";hiBin;jeteta/gjeteta",20,0,200,20,0,2);
  TH2D * hpbpbrphi = new TH2D("hpbpbrphi",";hiBin;jetphi/gjetphi",20,0,200,20,0,2);
  TH2D * hpprpt = new TH2D("hpprpt",";hiBin;jetpt/gjetpt",20,0,200,20,0,2);
  TH2D * hppreta = new TH2D("hppreta",";hiBin;jeteta/gjeteta",20,0,200,20,0,2);
  TH2D * hpprphi = new TH2D("hpprphi",";hiBin;jetphi/gjetphi",20,0,200,20,0,2);
  zpbpb->Draw("jetpt/gjetpt:hiBin>>hpbpbrpt","gjetpt>0","goff");
  zpbpb->Draw("jeteta/gjeteta:hiBin>>hpbpbreta","gjetpt>0","goff");
  zpbpb->Draw("jetphi/gjetphi:hiBin>>hpbpbrphi","gjetpt>0","goff");
  zpp->Draw("jetpt/gjetpt:(hiBin+1)>>hpprpt","gjetpt>0","goff");
  zpp->Draw("jeteta/gjeteta:(hiBin+1)>>hppreta","gjetpt>0","goff");
  zpp->Draw("jetphi/gjetphi:(hiBin+1)>>hpprphi","gjetpt>0","goff");
  outf->Write();
  outf->Close();
}