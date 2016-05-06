// #include "ggTree.h"
// #include "jetTree.h"
// #include "trackTree.h"
// #include "SkimTree.h"
// #include <iostream>
#include "getTrkCorr.h"

using namespace std;

// bool goodJet(int i) {
  // if(	_neutralSum[i]/rawpt[i] < 0.9
      // && _chargedSum[i]/rawpt[i] > 0.01
      // && chargedN[i]+photonN[i]+neutralN[i]+eN[i]+muN[i] > 0
      // && chargedMax[i]/rawpt[i] < 0.99
      // && photonSum[i]/rawpt[i] < 0.99
      // && _eSum[i]/rawpt[i] < 0.99
      // ) return true;
  // else return false;
// }
Float_t         * trkPt_ = (Float_t*) malloc(sizeof(Float_t)*100000);   //[nTrk]
Float_t         trkPtError_[100000];   //[nTrk]
UChar_t         trkNHit_[100000];   //[nTrk]
Float_t         trkEta_[100000];   //[nTrk]
Float_t         trkPhi_[100000];   //[nTrk]
Bool_t          highPurity_[100000];   //[nTrk]
Float_t         trkDxy1_[100000];   //[nTrk]
Float_t         trkDxyError1_[100000];   //[nTrk]
Float_t         trkDz1_[100000];   //[nTrk]
Float_t         trkDzError1_[100000];   //[nTrk]
Float_t         trkMVA_[100000];   //[nTrk]
Float_t         jtpt[1000];   //[nTrk]
Float_t         jteta[1000];   //[nTrk]
Float_t         jtphi[1000];   //[nTrk]

Int_t           nTrk_;

Int_t           nref;


float getTrkWeight(TrkCorr * trkCorr, int itrk, int hiBin, int nev)
{
  float rmin = 999;
  for(int k = 0; k<nref; k++)
  {
    if(jtpt[k]<50) break;
    // if(!goodJet(k)) continue;
    if(TMath::Abs(jteta[k]>2)) continue;//jet quality cut
    float R = TMath::Power(jteta[k]-trkEta_[itrk],2)+TMath::Power(TMath::ACos(TMath::Cos(jtphi[k]-trkPhi_[itrk])),2);
    if(rmin*rmin>R) rmin=TMath::Power(R,0.5);
  }
  return trkCorr->getTrkCorr(trkPt_[itrk],trkEta_[itrk],trkPhi_[itrk],hiBin,rmin, nev);
}


void simpleskim(TString infilename="HiForest.root", TString outfilename="Zevents.root", string jetname="ak4PFJetAnalyzer", int i_is_pp = 0 ) {

  bool is_pp = (i_is_pp == 1) ;
  TrkCorr* trkCorr;
  if(is_pp) trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_PbPb/");
  else trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_pp/");
  std::cout<<trkCorr<<std::endl;
  TFile *fin = TFile::Open(infilename);

  TTree *injetTree = (TTree*)fin->Get(Form("%s/t",jetname.data()));
  if(!injetTree){
    cout<<"Could not access jet tree!"<<endl;
    return;
  }
  
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
  tracktree_->SetBranchAddress("nTrk", &nTrk_);
  tracktree_->SetBranchAddress("trkPt", trkPt_);
  tracktree_->SetBranchAddress("trkPtError", trkPtError_);
  tracktree_->SetBranchAddress("trkNHit", trkNHit_);
  tracktree_->SetBranchAddress("trkEta", trkEta_);
  tracktree_->SetBranchAddress("trkPhi", trkPhi_);
  tracktree_->SetBranchAddress("highPurity", highPurity_);
  tracktree_->SetBranchAddress("trkDxy1", trkDxy1_);
  tracktree_->SetBranchAddress("trkDxyError1", trkDxyError1_);
  tracktree_->SetBranchAddress("trkDz1", trkDz1_);
  tracktree_->SetBranchAddress("trkDzError1", trkDzError1_);
  tracktree_->SetBranchAddress("trkMVA", trkMVA_);
  injetTree->SetBranchAddress("nref", &nref);
  injetTree->SetBranchAddress("jtpt", jtpt);
  injetTree->SetBranchAddress("jteta", jteta);
  injetTree->SetBranchAddress("jtphi", jtphi);


  // int nEv = inggTree->GetEntries();
  int nEv = evttree->GetEntries();
  float totaltrkeff = 0.0;
  for (int j=0; j<nEv; j++) {

    evttree->GetEntry(j);
    if(fabs(vz)>15) continue;
    injetTree->GetEntry(j);
    if(j%1000 == 0) { cout << "Processing event: " << j <<"/"<<nEv<< endl; }
    
    

    
    tracktree_->GetEntry(j);

    int ntracks = 0;
    if(nTrk_>100000) {
      std::cout<<"track error"<<std::endl;
      exit(1);
    }
    if(nref>10000) {
      std::cout<<"jet error"<<std::endl;
      exit(1);
    }
    for(int i = 0 ; i < nTrk_ ; ++i)
    {
      if((trkMVA_[i]<0.5 && trkMVA_[i]!=-99) || (int)trkNHit_[i]<8 || trkPtError_[i]/trkPt_[i]>0.3 || fabs(trkDz1_[i])/trkDzError1_[i]>3 || fabs(trkDxy1_[i])/trkDxyError1_[i]>3) continue;
      if(trkPt_[i]<0.5 || trkPt_[i]>300 || fabs(trkEta_[i])>2.4 ) continue;
      float trkweight = 0;
      if(is_pp) trkweight=getTrkWeight(trkCorr,i,0,j);
      else trkweight=getTrkWeight(trkCorr,i,hiBin,j);
      //std::cout<<trkweight<<endl;
      ntracks++;
      totaltrkeff += trkweight;
    }
  }
  std::cout<<totaltrkeff<<std::endl;
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

