#include "getTrkCorr.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

Float_t         trkPt_[100000];   //[nTrk]
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
Float_t         jtpt[10000];   //[nTrk]
Float_t         jteta[10000];   //[nTrk]
Float_t         jtphi[10000];   //[nTrk]

Int_t           nTrk_;
Int_t           hiBin;
Int_t           ntracks;

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
  // float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  
  
  for (int j=3; j<10; j++) {
    for(int i = 0 ; i < nTrk_ ; ++i)
    {
      if(trkPt_[i]<0.5 || trkPt_[i]>300 || fabs(trkEta_[i])>2.4 ) continue;
      float trkweight = 0;
      if(is_pp) trkweight=getTrkWeight(trkCorr,i,0,j);
      else trkweight=getTrkWeight(trkCorr,i,hiBin,j);
      std::cout<<trkweight<<endl;
      ntracks++;
    }
  }
}

int main(int argc, char *argv[])
{
  if((argc < 3))
  {
    std::cout << "Usage: ./gammajetSkim.exe <inputfile> <outputfile> [jetname] [is_pp]" << std::endl;
    return 1;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(1, 2);
  for (int n = 0; n < 10; ++n) {
    std::cout << dis(gen) << ' ';
  }
  std::cout << '\n';
  return 0;
  if(argc==3)  simpleskim(argv[1], argv[2]);
  if(argc==4)  simpleskim(argv[1], argv[2], argv[3]);
  if(argc==5)  simpleskim(argv[1], argv[2], argv[3], std::atoi(argv[4]));
  return 0;
}

