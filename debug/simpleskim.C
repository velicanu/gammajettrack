#include "ggTree.h"
#include "jetTree.h"
#include "trackTree.h"
#include "SkimTree.h"
#include "getTrkCorr.h"


bool goodJet(int i) {
  if(	_neutralSum[i]/rawpt[i] < 0.9
      && _chargedSum[i]/rawpt[i] > 0.01
      && chargedN[i]+photonN[i]+neutralN[i]+eN[i]+muN[i] > 0
      && chargedMax[i]/rawpt[i] < 0.99
      && photonSum[i]/rawpt[i] < 0.99
      && _eSum[i]/rawpt[i] < 0.99
      ) return true;
  else return false;
}


float getTrkWeight(TrkCorr * trkCorr, int itrk, int hiBin)
{
  float rmin = 999;
  for(int k = 0; k<nref; k++)
  {
    if(jtpt[k]<50) break;
    if(!goodJet(k)) continue;
    if(TMath::Abs(jteta[k]>2)) continue;//jet quality cut
    float R = TMath::Power(jteta[k]-trkEta_[itrk],2)+TMath::Power(TMath::ACos(TMath::Cos(jtphi[k]-trkPhi_[itrk])),2);
    if(rmin*rmin>R) rmin=TMath::Power(R,0.5);
  }
  return trkCorr->getTrkCorr(trkPt_[itrk],trkEta_[itrk],trkPhi_[itrk],hiBin,rmin);
}


void simpleskim(TString infilename="HiForest.root", TString outfilename="Zevents.root", string jetname="ak4PFJetAnalyzer", int i_is_pp = 0 ) {

  bool is_pp = (i_is_pp == 1) ;
  TrkCorr* trkCorr;
  if(is_pp) trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_PbPb/");
  else trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_pp/");
  TFile *fin = TFile::Open(infilename);

  // TFile *fout = new TFile(outfilename,"recreate");

  TH1::SetDefaultSumw2();

  TTree *injetTree = (TTree*)fin->Get(Form("%s/t",jetname.data()));
  if(!injetTree){
    cout<<"Could not access jet tree!"<<endl;
    return;
  }
  initjetTree(injetTree);
  
  TTree *evttree = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
  if(!evttree){
    cout<<"Could not access event tree!"<<endl;
    return;
  }
  float weight = 0 , vz = -99;
  int hiBin = -99;
  evttree->SetBranchAddress("weight", &weight);
  evttree->SetBranchAddress("hiBin", &hiBin);
  evttree->SetBranchAddress("vz", &vz);
  
  TTree * tracktree_                     = (TTree*) fin->Get("anaTrack/trackTree");
  if( tracktree_ == 0 ) tracktree_        = (TTree*) fin->Get("ppTrack/trackTree");
  if(!tracktree_){
    cout<<"Could not access track tree!"<<endl;
    return;
  }
  initTrackTree(tracktree_);
  
  TTree * skimTree                     = (TTree*) fin->Get("skimanalysis/HltTree");
  if( skimTree == 0 )
  {
    cout<<"Could not access skim tree!"<<endl;
    return;
  }
  initSkimTree(skimTree);
  


  // int nEv = inggTree->GetEntries();
  int nEv = evttree->GetEntries();

  for (int j=0; j<nEv; j++) {

    skimTree->GetEntry(j);
    // if(!(HBHENoiseFilterResultRun2Loose && pPAprimaryVertexFilter && pBeamScrapingFilter)) continue;
    evttree->GetEntry(j);
    if(fabs(vz)>15) continue;
    injetTree->GetEntry(j);
    if(j%10000 == 0) { cout << "Processing event: " << j << endl; }
    
    

    
    tracktree_->GetEntry(j);

    int ntracks = 0;
    for(int i = 0 ; i < nTrk_ ; ++i)
    {
      if((trkMVA_[i]<0.5 && trkMVA_[i]!=-99) || (int)trkNHit_[i]<8 || trkPtError_[i]/trkPt_[i]>0.3 || fabs(trkDz1_[i])/trkDzError1_[i]>3 || fabs(trkDxy1_[i])/trkDxyError1_[i]>3) continue;
      if(trkPt_[i]<0.5 || trkPt_[i]>300 || fabs(trkEta_[i])>2.4 ) continue;
      float trkweight = 0;
      if(is_pp) trkweight=getTrkWeight(trkCorr,i,0);
      else trkweight=getTrkWeight(trkCorr,i,hiBin);
      std::cout<<trkweight<<endl;
      ntracks++;
      //if((trkPt[i]-2*trkPtError[i])*TMath::CosH(trkEta[i])>15 && (trkPt[i]-2*trkPtError[i])*TMath::CosH(trkEta[i])>pfHcal[i]+pfEcal[i]) continue;} //Calo Matching
    }
    // nTrk=ntracks;
    

  } //end of loop over events


  // fout->cd();
  // ztree->Write();
  // injetTree->Write();
  // trackTree->Write();
  // fout->Write();
  // fout->Close();

}

int main(int argc, char *argv[])
{
  if((argc < 3))
  {
    std::cout << "Usage: ./gammajetSkim.exe <inputfile> <outputfile> [jetname] [is_pp]" << std::endl;
    return 1;
  }
  if(argc==3)  simpleskim(argv[1], argv[2]);
  if(argc==4)  simpleskim(argv[1], argv[2], argv[3]);
  if(argc==5)  simpleskim(argv[1], argv[2], argv[3], std::atoi(argv[4]));
  return 0;
}

