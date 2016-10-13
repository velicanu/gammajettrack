#include "TRandom3.h"
#include "ggTree.h"
#include "jetTree.h"
#include "trackTree.h"
#include "SkimTree.h"
#include "L2L3ResidualWFits.h"
#include "getTrkCorr.h"
#include <stdlib.h>     /* srand, rand */
#include <functional>   /* hash */

/************************ code outline ********************************
(1) Setup                                                             *
  (1.1) Helper functions                                              *
    (1.11) pp smearing functions                                      *
  (1.2) List of variables                                             *
  (1.3) Output tree branches                                          *
  (1.4) Reading the input HiForest                                    *
  (1.5) Reading the mixed HiForest                                    *
    (1.51) Indexing of mixed event                                    *
  (1.6) Photon energy correction initialization                       *
                                                                      *
(2) Loop                                                              *
  (2.1) Event and trigger cuts                                        *
  (2.2) Photon selection                                              *
  (2.3) Jet selection                                                 *
  (2.4) Track selection                                               *
  (2.5) Minbias mixing                                                *
    (2.51) Mixing criteria                                            *
    (2.52) Mixed Jets                                                 *
    (2.53) Mixed Cones                                                *
    (2.54) Mixed Tracks from jet and cones                            *
    (2.55) Mixed gen particles from jet and cone                      *
                                                                      *
**********************************************************************/








//! Begin Setup

// these variables are used to get tracking efficiency correction
// they're not filled in the output tree
Int_t           nref_corr;
Float_t         chargedSum_corr[100];   //[nref_corr]
Float_t         rawpt_corr[100];   //[nref_corr]
Float_t         jtpt_corr[100];   //[nref_corr]
Float_t         jteta_corr[100];   //[nref_corr]
Float_t         jtphi_corr[100];   //[nref_corr]

Int_t           nref_corr_mix;
Float_t         chargedSum_corr_mix[100];   //[nref_corr_mix]
Float_t         rawpt_corr_mix[100];   //[nref_corr_mix]
Float_t         jtpt_corr_mix[100];   //[nref_corr_mix]
Float_t         jteta_corr_mix[100];   //[nref_corr_mix]
Float_t         jtphi_corr_mix[100];   //[nref_corr_mix]

//! (1.1) Begin helper functions

double getAngleToEP(double angle) {
    angle = (angle > TMath::Pi()) ? 2 * TMath::Pi() - angle : angle;
    return (angle > TMath::Pi()/2) ? TMath::Pi() - angle : angle;
}

int getCentBin(int hibin)
{
  if(hibin < 20)       return 0;
  else if(hibin < 60)  return 1;
  else if(hibin < 100) return 2;
  else if(hibin < 140) return 3;
  return 4;
}

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

bool goodJet_ak3pupf(int i) {
  if(	neutralSum_ak3pupf[i]/rawpt_ak3pupf[i] < 0.9
      && chargedSum_ak3pupf[i]/rawpt_ak3pupf[i] > 0.01
      && chargedN_ak3pupf[i]+photonN_ak3pupf[i]+neutralN_ak3pupf[i]+eN_ak3pupf[i]+muN_ak3pupf[i] > 0
      && chargedMax_ak3pupf[i]/rawpt_ak3pupf[i] < 0.99
      && photonSum_ak3pupf[i]/rawpt_ak3pupf[i] < 0.99
      && eSum_ak3pupf[i]/rawpt_ak3pupf[i] < 0.99
      ) return true;
  else return false;
}

float getTrkWeight(TrkCorr * trkCorr, int itrk, int hiBin)
{
  float rmin = 999;
  for(int k = 0; k<nref_corr; k++)
  {
    if(jtpt_corr[k]<50) break;
    // if(!goodJet(k)) continue;
    if((TMath::Abs(chargedSum_corr[k]/rawpt_corr[k])<0.01) || (TMath::Abs(jteta_corr[k]>2))) continue;//jet quality cut
    float R = TMath::Power(jteta_corr[k]-trkEta_[itrk],2)+TMath::Power(TMath::ACos(TMath::Cos(jtphi_corr[k]-trkPhi_[itrk])),2);
    if(rmin*rmin>R) rmin=TMath::Power(R,0.5);
  }
  return trkCorr->getTrkCorr(trkPt_[itrk],trkEta_[itrk],trkPhi_[itrk],hiBin,rmin);
}

float getTrkWeightMix(TrkCorr * trkCorr, int itrk, int hiBin)
{
  float rmin = 999;
  for(int k = 0; k<nref_corr_mix; k++)
  {
    if(jtpt_corr_mix[k]<50) break;
    // if(!goodJet(k)) continue;
    if((TMath::Abs(chargedSum_corr_mix[k]/rawpt_corr_mix[k])<0.01) || (TMath::Abs(jteta_corr_mix[k]>2))) continue;//jet quality cut
    float R = TMath::Power(jteta_corr_mix[k]-trkEta_mix_[itrk],2)+TMath::Power(TMath::ACos(TMath::Cos(jtphi_corr_mix[k]-trkPhi_mix_[itrk])),2);
    if(rmin*rmin>R) rmin=TMath::Power(R,0.5);
  }
  return trkCorr->getTrkCorr(trkPt_mix_[itrk],trkEta_mix_[itrk],trkPhi_mix_[itrk],hiBin,rmin);
}

//! (1.11) Begin pp smearing
TRandom3 randSmearing(12345);    // random number seed should be fixed or reproducible

// pp resolution
std::vector<double> CSN_PP = {0.06, 0.91, 0};
std::vector<double> CSN_phi_PP = {7.72/100000000, 0.1222, 0.5818};

// smear 0-30 %
std::vector<double> CSN_HI_cent0030 = {0.06, 1.23, 7.38};
std::vector<double> CSN_phi_HI_cent0030 = {-1.303/1000000, 0.1651, 1.864};
// smear 30-100 %
std::vector<double> CSN_HI_cent30100 = {0.06, 1.23, 2.1};
std::vector<double> CSN_phi_HI_cent30100 = {-2.013/100000000, 0.1646, 1.04};

// smear 0-10 %
std::vector<double> CSN_HI_cent0010 = {0.06, 1.23, 8.38};
std::vector<double> CSN_phi_HI_cent0010 = {-3.18781/10000000, 0.125911, 2.23898};
// smear 10-30 %
std::vector<double> CSN_HI_cent1030 = {0.06, 1.23, 5.88};
std::vector<double> CSN_phi_HI_cent1030 = {1.14344/100000, 0.179847, 1.56128};
// smear 30-50 %
std::vector<double> CSN_HI_cent3050 = {0.06, 1.23, 3.24};
std::vector<double> CSN_phi_HI_cent3050 = {0.0145775, 0.1222, 1.21751};
// smear 50-100 %
std::vector<double> CSN_HI_cent50100 = {0.06, 1.23, 0};
std::vector<double> CSN_phi_HI_cent50100 = {-0.0073078, 0.168879, 0.798885};

float getSigmaRelPt(int hiBin, float jetpt)
{
  if(hiBin<20)
    return TMath::Sqrt(
                  (CSN_HI_cent0010.at(0)*CSN_HI_cent0010.at(0) - CSN_PP.at(0)*CSN_PP.at(0)) +
                  (CSN_HI_cent0010.at(1)*CSN_HI_cent0010.at(1) - CSN_PP.at(1)*CSN_PP.at(1))/jetpt +
                  (CSN_HI_cent0010.at(2)*CSN_HI_cent0010.at(2) - CSN_PP.at(2)*CSN_PP.at(2))/(jetpt*jetpt)
                          );

  else if(20<=hiBin && hiBin<60)
    return TMath::Sqrt(
                  (CSN_HI_cent1030.at(0)*CSN_HI_cent1030.at(0) - CSN_PP.at(0)*CSN_PP.at(0)) +
                  (CSN_HI_cent1030.at(1)*CSN_HI_cent1030.at(1) - CSN_PP.at(1)*CSN_PP.at(1))/jetpt +
                  (CSN_HI_cent1030.at(2)*CSN_HI_cent1030.at(2) - CSN_PP.at(2)*CSN_PP.at(2))/(jetpt*jetpt)
                          );

  else if(60<=hiBin && hiBin<100)
    return TMath::Sqrt(
                  (CSN_HI_cent3050.at(0)*CSN_HI_cent3050.at(0) - CSN_PP.at(0)*CSN_PP.at(0)) +
                  (CSN_HI_cent3050.at(1)*CSN_HI_cent3050.at(1) - CSN_PP.at(1)*CSN_PP.at(1))/jetpt +
                  (CSN_HI_cent3050.at(2)*CSN_HI_cent3050.at(2) - CSN_PP.at(2)*CSN_PP.at(2))/(jetpt*jetpt)
                          );

  else
    return TMath::Sqrt(
                  (CSN_HI_cent50100.at(0)*CSN_HI_cent50100.at(0) - CSN_PP.at(0)*CSN_PP.at(0)) +
                  (CSN_HI_cent50100.at(1)*CSN_HI_cent50100.at(1) - CSN_PP.at(1)*CSN_PP.at(1))/jetpt +
                  (CSN_HI_cent50100.at(2)*CSN_HI_cent50100.at(2) - CSN_PP.at(2)*CSN_PP.at(2))/(jetpt*jetpt)
                          );
}

float getSigmaRelPhi(int hiBin, float jetpt)
{
  if(hiBin<20)
    return TMath::Sqrt(
                  (CSN_phi_HI_cent0010.at(0)*CSN_phi_HI_cent0010.at(0) - CSN_phi_PP.at(0)*CSN_phi_PP.at(0)) +
                  (CSN_phi_HI_cent0010.at(1)*CSN_phi_HI_cent0010.at(1) - CSN_phi_PP.at(1)*CSN_phi_PP.at(1))/jetpt +
                  (CSN_phi_HI_cent0010.at(2)*CSN_phi_HI_cent0010.at(2) - CSN_phi_PP.at(2)*CSN_phi_PP.at(2))/(jetpt*jetpt)
                          );

  else if(20<=hiBin && hiBin<60)
    return TMath::Sqrt(
                  (CSN_phi_HI_cent1030.at(0)*CSN_phi_HI_cent1030.at(0) - CSN_phi_PP.at(0)*CSN_phi_PP.at(0)) +
                  (CSN_phi_HI_cent1030.at(1)*CSN_phi_HI_cent1030.at(1) - CSN_phi_PP.at(1)*CSN_phi_PP.at(1))/jetpt +
                  (CSN_phi_HI_cent1030.at(2)*CSN_phi_HI_cent1030.at(2) - CSN_phi_PP.at(2)*CSN_phi_PP.at(2))/(jetpt*jetpt)
                          );

  else if(60<=hiBin && hiBin<100)
    return TMath::Sqrt(
                  (CSN_phi_HI_cent3050.at(0)*CSN_phi_HI_cent3050.at(0) - CSN_phi_PP.at(0)*CSN_phi_PP.at(0)) +
                  (CSN_phi_HI_cent3050.at(1)*CSN_phi_HI_cent3050.at(1) - CSN_phi_PP.at(1)*CSN_phi_PP.at(1))/jetpt +
                  (CSN_phi_HI_cent3050.at(2)*CSN_phi_HI_cent3050.at(2) - CSN_phi_PP.at(2)*CSN_phi_PP.at(2))/(jetpt*jetpt)
                          );

  else
    return TMath::Sqrt(
                  (CSN_phi_HI_cent50100.at(0)*CSN_phi_HI_cent50100.at(0) - CSN_phi_PP.at(0)*CSN_phi_PP.at(0)) +
                  (CSN_phi_HI_cent50100.at(1)*CSN_phi_HI_cent50100.at(1) - CSN_phi_PP.at(1)*CSN_phi_PP.at(1))/jetpt +
                  (CSN_phi_HI_cent50100.at(2)*CSN_phi_HI_cent50100.at(2) - CSN_phi_PP.at(2)*CSN_phi_PP.at(2))/(jetpt*jetpt)
                          );
}

//! End pp smearing

//! End helper functions

void gammajetSkim(TString infilename="HiForest.root", TString outfilename="Zevents.root", string jetname="ak4PFJetAnalyzer", int i_is_pp = 0 , float mcweight = 1, string minbias = "", int startindex = 0, int endindex = -1, int do_jet_skim = 1, int jetptmin = 30) {

  // next two lines are for event mixing for data with condor so each photon file starts
  // at a different index in the minbias mix tree that is random but deterministic
  unsigned int filehash = std::hash<std::string>()(infilename.Data()) % 2147483647;
  srand(filehash); // seed with filehash to always mix consistently and randomly
  int minbiasstart = 0;


  bool is_pp = (i_is_pp == 1) ;
  int isPP = i_is_pp;

  // tracking correction initialized here
  TrkCorr* trkCorr;
  if(!is_pp) trkCorr = new TrkCorr("TrkCorr_Jun7_Iterative_PbPb_etaLT2p4/");
  else trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_pp/");
  cout<<trkCorr<<endl;

  // the L2L3Residual correction is currently not being used, but can be turned on
  L2L3Residual * jetcorr = new L2L3Residual(3);
  cout<<jetcorr<<endl;


  TFile *fin = TFile::Open(infilename);
  TFile *fout = new TFile(outfilename,"recreate");


//! (1.2) Begin list of input/output variables

  float weight = 0 , vz = -99;
  float vz_mix = -99;
  int hiBin = -99;
  int hiBin_mix = -99;
  int HLT_HISinglePhoton40_Eta1p5_v1 = -99;
  int HLT_HISinglePhoton40_Eta1p5_v2 = -99;
  int HLT_HISinglePhoton40_Eta1p5ForPPRef_v1 = -99;


  //mixvar decleration
  float dvz_mix[10];
  int dhiBin_mix[10];
  float dhiEvtPlanes_mix[10];

  int njet_smeared;
  float jetpt_smeared0020[2000], jeteta_smeared0020[2000], jetphi_smeared0020[2000];
  float jetpt_smeared2060[2000], jeteta_smeared2060[2000], jetphi_smeared2060[2000];
  float jetpt_smeared60100[2000], jeteta_smeared60100[2000], jetphi_smeared60100[2000];
  float jetpt_smeared100200[2000], jeteta_smeared100200[2000], jetphi_smeared100200[2000];
  int njet;
  float jetpt[200], jeteta[200], jetphi[200];
  float gjetpt[200], gjeteta[200], gjetphi[200];
  float chargedSum[200], neutralSum[200], eSum[200];
  float jetptsigma0020[200], jetphisigma0020[200];
  float jetptsigma2060[200], jetphisigma2060[200];
  float jetptsigma60100[200], jetphisigma60100[200];
  float jetptsigma100200[200], jetphisigma100200[200];
  int jetID[200], subid[200];


  Int_t           ngen;
  Int_t           genmatchindex[500];   //[ngen]
  Float_t         genpt[500];   //[ngen]
  Float_t         geneta[500];   //[ngen]
  Float_t         genphi[500];   //[ngen]
  Int_t           gensubid[500];   //[ngen]

  int _mult;
  vector<float> *_pt;
  vector<float> *_eta;
  vector<float> *_phi;
  vector<int> *_pdg;
  vector<int> *_chg;
  vector<int> *_matchingID;
  vector<int> *_sube;

  int _mult_mix;
  vector<float> *_pt_mix;
  vector<float> *_eta_mix;
  vector<float> *_phi_mix;
  vector<int> *_pdg_mix;
  vector<int> *_chg_mix;
  int mult_mix;
  float pt_mix[10000];
  float eta_mix[10000];
  float phi_mix[10000];
  int pdg_mix[10000];
  int chg_mix[10000];
  int nev_mix[10000];
  int mult_cone;
  float pt_cone[10000];
  float eta_cone[10000];
  float phi_cone[10000];
  int pdg_cone[10000];
  int chg_cone[10000];
  int nev_cone[10000];


  int mult;
  float pt[10000];
  float eta[10000];
  float phi[10000];
  int pdg[10000];
  int chg[10000];
  int matchingID[10000];
  int sube[10000];



  Int_t           hiNevtPlane;
  Float_t         hiEvtPlanes[29];   //[hiNevtPlane]
  Float_t         hiEvtPlanes_mix[29];   //[hiNevtPlane]

  Int_t           nTrk_mix;
  Float_t         trkPt_mix[100000];   //[nTrk]
  Float_t         trkFromEv_mix[100000];   //[nTrk]
  Float_t         trkEta_mix[100000];   //[nTrk]
  Float_t         trkPhi_mix[100000];   //[nTrk]
  Float_t         trkWeight_mix[100000];   //[nTrk]

  Int_t           nTrk_cone;
  Float_t         trkPt_cone[100000];   //[nTrk]
  Float_t         trkFromEv_cone[100000];   //[nTrk]
  Float_t         trkEta_cone[100000];   //[nTrk]
  Float_t         trkPhi_cone[100000];   //[nTrk]
  Float_t         trkWeight_cone[100000];   //[nTrk]

  Int_t           nTrk;
  UInt_t          run;
  ULong64_t       evt;
  UInt_t          lumi;
  Float_t         trkPt[100000];   //[nTrk]
  Float_t         trkPtError[100000];   //[nTrk]
  UChar_t         trkNHit[100000];   //[nTrk]
  UChar_t         trkNlayer[100000];   //[nTrk]
  Float_t         trkEta[100000];   //[nTrk]
  Float_t         trkPhi[100000];   //[nTrk]
  Int_t           trkCharge[100000];   //[nTrk]
  UChar_t         trkNVtx[100000];   //[nTrk]
  Bool_t          highPurity[100000];   //[nTrk]
  Bool_t          tight[100000];   //[nTrk]
  Bool_t          loose[100000];   //[nTrk]
  Float_t         trkChi2[100000];   //[nTrk]
  UChar_t         trkNdof[100000];   //[nTrk]
  Float_t         trkDxy1[100000];   //[nTrk]
  Float_t         trkDxyError1[100000];   //[nTrk]
  Float_t         trkDz1[100000];   //[nTrk]
  Float_t         trkDzError1[100000];   //[nTrk]
  Bool_t          trkFake[100000];   //[nTrk]
  UChar_t         trkAlgo[100000];   //[nTrk]
  UChar_t         trkOriginalAlgo[100000];   //[nTrk]
  Float_t         trkMVA[100000];   //[nTrk]
  Int_t           pfType[100000];   //[nTrk]
  Float_t         pfCandPt[100000];   //[nTrk]
  Float_t         pfEcal[100000];   //[nTrk]
  Float_t         pfHcal[100000];   //[nTrk]
  Float_t         trkWeight[100000];   //[nTrk]
  Int_t    nPho;
  Float_t  phoE[1];   //_nPho
  Float_t  phoEt[1];   //_nPho
  Float_t  phoEtCorrected[1];   //_nPho
  Float_t  pho_sumIso[1];   //_nPho
  Float_t  pho_sumIsoCorrected[1];   //_nPho
  Float_t  phoCorr[1];   //_nPho
  Float_t  phoEta[1];   //_nPho
  Float_t  phoPhi[1];   //_nPho
  Float_t  phoSCE[1];   //_nPho
  Float_t  phoSCRawE[1];   //_nPho
  Float_t  phoESEn[1];   //_nPho
  Float_t  phoSCEta[1];   //_nPho
  Float_t  phoSCPhi[1];   //_nPho
  Float_t  phoSCEtaWidth[1];   //_nPho
  Float_t  phoSCPhiWidth[1];   //_nPho
  Float_t  phoSCBrem[1];   //_nPho
  Int_t    phohasPixelSeed[1];   //_nPho
  Float_t  phoR9[1];   //_nPho
  Float_t  phoHoverE[1];   //_nPho
  Float_t  phoSigmaIEtaIEta[1];   //_nPho
  Float_t  pho_ecalClusterIsoR2[1];   //_nPho
  Float_t  pho_ecalClusterIsoR3[1];   //_nPho
  Float_t  pho_ecalClusterIsoR4[1];   //_nPho
  Float_t  pho_ecalClusterIsoR5[1];   //_nPho
  Float_t  pho_hcalRechitIsoR1[1];   //_nPho
  Float_t  pho_hcalRechitIsoR2[1];   //_nPho
  Float_t  pho_hcalRechitIsoR3[1];   //_nPho
  Float_t  pho_hcalRechitIsoR4[1];   //_nPho
  Float_t  pho_hcalRechitIsoR5[1];   //_nPho
  Float_t  pho_trackIsoR1PtCut20[1];   //_nPho
  Float_t  pho_trackIsoR2PtCut20[1];   //_nPho
  Float_t  pho_trackIsoR3PtCut20[1];   //_nPho
  Float_t  pho_trackIsoR4PtCut20[1];   //_nPho
  Float_t  pho_trackIsoR5PtCut20[1];   //_nPho
  Float_t  pho_swissCrx[1];   //_nPho
  Float_t  pho_seedTime[1];   //_nPho

  Float_t  phoE3x3[1];   //_nPho
  Float_t  phoE1x5[1];   //_nPho
  Float_t  phoE2x5[1];   //_nPho
  Float_t  phoE5x5[1];   //_nPho
  Float_t  phoSigmaIEtaIEta_2012[1];   //_nPho
  Int_t    phoNoise[1];   //_nPho
  Int_t    pho_genMatchedIndex[1];   //_nPho

  Float_t  pfcIso1[1];   //_nPho
  Float_t  pfcIso2[1];   //_nPho
  Float_t  pfcIso3[1];   //_nPho
  Float_t  pfcIso4[1];   //_nPho
  Float_t  pfcIso5[1];   //_nPho
  Float_t  pfpIso1[1];   //_nPho
  Float_t  pfpIso2[1];   //_nPho
  Float_t  pfpIso3[1];   //_nPho
  Float_t  pfpIso4[1];   //_nPho
  Float_t  pfpIso5[1];   //_nPho
  Float_t  pfnIso1[1];   //_nPho
  Float_t  pfnIso2[1];   //_nPho
  Float_t  pfnIso3[1];   //_nPho
  Float_t  pfnIso4[1];   //_nPho
  Float_t  pfnIso5[1];   //_nPho
	Int_t    nMC;
	Int_t    mcPID[500];

	Int_t    mcStatus[500];
	Float_t  mcEt[500];
	Float_t  mcPt[500];
	Float_t  mcEta[500];
	Float_t  mcPhi[500];
	Float_t  mcMomPt[500];
	Float_t  mcMomEta[500];
	Float_t  mcMomPhi[500];
	Int_t    mcMomPID[500];
  int nmix = 0, nlooped = 0;

  Int_t           nref_ak3pupf_out;
  Float_t         * rawpt_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * jtpt_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * jteta_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * jtphi_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * neutralSum_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * chargedSum_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * nmixEv_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * jetID_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * chargedN_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * photonN_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * neutralN_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * eN_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Int_t         * muN_ak3pupf_out = (Int_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * chargedMax_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * photonSum_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
  Float_t         * eSum_ak3pupf_out = (Float_t*) malloc(sizeof(Float_t)*3000);   //[nref]
//! End list of input/output variables

//! (1.3) Begin output skim and branch definitions
  TTree *ztree = new TTree("ztree","Jet track tree");

  ztree->Branch("isPP",  &isPP, "isPP/I");
  ztree->Branch("run",  &run, "run/i");
  ztree->Branch("evt",  &evt, "evt/l");
  ztree->Branch("lumi",  &lumi, "lumi/i");
  ztree->Branch("hiBin", &hiBin, "hiBin/I");
  ztree->Branch("vz", &vz, "vz/F");
  ztree->Branch("pcollisionEventSelection", &pcollisionEventSelection, "pcollisionEventSelection/F");
  ztree->Branch("HLT_HISinglePhoton40_Eta1p5_v1", &HLT_HISinglePhoton40_Eta1p5_v1, "HLT_HISinglePhoton40_Eta1p5_v1/F");
  ztree->Branch("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, "HBHENoiseFilterResultRun2Loose/F");

  ztree->Branch("nlooped", &nlooped, "nlooped/I");
  ztree->Branch("nmix", &nmix, "nmix/I");
  ztree->Branch("dvz_mix", dvz_mix, "dvz_mix[nmix]/F");
  ztree->Branch("dhiBin_mix", dhiBin_mix, "dhiBin_mix[nmix]/I");
  ztree->Branch("dhiEvtPlanes_mix", dhiEvtPlanes_mix, "dhiEvtPlanes_mix[nmix]/F");
  ztree->Branch("nTrk_mix",	&nTrk_mix,	"nTrk_mix/I");
  ztree->Branch("trkFromEv_mix",	&trkFromEv_mix,	"trkFromEv_mix[nTrk_mix]/F");
  ztree->Branch("trkPt_mix",	&trkPt_mix,	"trkPt_mix[nTrk_mix]/F");
  ztree->Branch("trkPhi_mix", &trkPhi_mix,"trkPhi_mix[nTrk_mix]/F");
  ztree->Branch("trkEta_mix", &trkEta_mix,"trkEta_mix[nTrk_mix]/F");
  ztree->Branch("trkWeight_mix", &trkWeight_mix,"trkWeight_mix[nTrk_mix]/F");

  ztree->Branch("nTrk_cone",	&nTrk_cone,	"nTrk_cone/I");
  ztree->Branch("trkFromEv_cone",	&trkFromEv_cone,	"trkFromEv_cone[nTrk_cone]/F");
  ztree->Branch("trkPt_cone",	&trkPt_cone,	"trkPt_cone[nTrk_cone]/F");
  ztree->Branch("trkPhi_cone", &trkPhi_cone,"trkPhi_cone[nTrk_cone]/F");
  ztree->Branch("trkEta_cone", &trkEta_cone,"trkEta_cone[nTrk_cone]/F");
  ztree->Branch("trkWeight_cone", &trkWeight_cone,"trkWeight_cone[nTrk_cone]/F");

  ztree->Branch("hiNevtPlane", &hiNevtPlane, "hiNevtPlane/I");
  ztree->Branch("hiEvtPlanes", hiEvtPlanes, "hiEvtPlanes[hiNevtPlane]/F");

  ztree->Branch("mult", &mult, "mult/I");
  ztree->Branch("pt", pt, "pt[mult]/F");
  ztree->Branch("eta", eta, "eta[mult]/F");
  ztree->Branch("phi", phi, "phi[mult]/F");
  ztree->Branch("pdg", pdg, "pdg[mult]/I");
  ztree->Branch("chg", chg, "chg[mult]/I");
  ztree->Branch("matchingID", matchingID, "matchingID[mult]/I");
  ztree->Branch("sube", sube, "sube[mult]/I");

  ztree->Branch("mult_mix", &mult_mix, "mult_mix/I");
  ztree->Branch("pt_mix", pt_mix, "pt_mix[mult_mix]/F");
  ztree->Branch("eta_mix", eta_mix, "eta_mix[mult_mix]/F");
  ztree->Branch("phi_mix", phi_mix, "phi_mix[mult_mix]/F");
  ztree->Branch("pdg_mix", pdg_mix, "pdg_mix[mult_mix]/I");
  ztree->Branch("chg_mix", chg_mix, "chg_mix[mult_mix]/I");
  ztree->Branch("nev_mix", nev_mix, "nev_mix[mult_mix]/I");
  ztree->Branch("mult_cone", &mult_cone, "mult_cone/I");
  ztree->Branch("pt_cone", pt_cone, "pt_cone[mult_cone]/F");
  ztree->Branch("eta_cone", eta_cone, "eta_cone[mult_cone]/F");
  ztree->Branch("phi_cone", phi_cone, "phi_cone[mult_cone]/F");
  ztree->Branch("pdg_cone", pdg_cone, "pdg_cone[mult_cone]/I");
  ztree->Branch("chg_cone", chg_cone, "chg_cone[mult_cone]/I");
  ztree->Branch("nev_cone", nev_cone, "nev_cone[mult_cone]/I");

  ztree->Branch("njet_smeared",	&njet_smeared,	"njet_smeared/I");
  ztree->Branch("jetpt_smeared0020",	&jetpt_smeared0020,	"jetpt_smeared0020[njet_smeared]/F");
  ztree->Branch("jeteta_smeared0020",	&jeteta_smeared0020,	"jeteta_smeared0020[njet_smeared]/F");
  ztree->Branch("jetphi_smeared0020",	&jetphi_smeared0020,	"jetphi_smeared0020[njet_smeared]/F");
  ztree->Branch("jetpt_smeared2060",	&jetpt_smeared2060,	"jetpt_smeared2060[njet_smeared]/F");
  ztree->Branch("jeteta_smeared2060",	&jeteta_smeared2060,	"jeteta_smeared2060[njet_smeared]/F");
  ztree->Branch("jetphi_smeared2060",	&jetphi_smeared2060,	"jetphi_smeared2060[njet_smeared]/F");
  ztree->Branch("jetpt_smeared60100",	&jetpt_smeared60100,	"jetpt_smeared60100[njet_smeared]/F");
  ztree->Branch("jeteta_smeared60100",	&jeteta_smeared60100,	"jeteta_smeared60100[njet_smeared]/F");
  ztree->Branch("jetphi_smeared60100",	&jetphi_smeared60100,	"jetphi_smeared60100[njet_smeared]/F");
  ztree->Branch("jetpt_smeared100200",	&jetpt_smeared100200,	"jetpt_smeared100200[njet_smeared]/F");
  ztree->Branch("jeteta_smeared100200",	&jeteta_smeared100200,	"jeteta_smeared100200[njet_smeared]/F");
  ztree->Branch("jetphi_smeared100200",	&jetphi_smeared100200,	"jetphi_smeared100200[njet_smeared]/F");

  ztree->Branch("njet",	&njet,	"njet/I");
  ztree->Branch("jetpt",	&jetpt,	"jetpt[njet]/F");
  ztree->Branch("jeteta",	&jeteta,	"jeteta[njet]/F");
  ztree->Branch("jetphi",	&jetphi,	"jetphi[njet]/F");
  ztree->Branch("gjetpt",	&gjetpt,	"gjetpt[njet]/F");
  ztree->Branch("gjeteta",	&gjeteta,	"gjeteta[njet]/F");
  ztree->Branch("gjetphi",	&gjetphi,	"gjetphi[njet]/F");
  ztree->Branch("jetID",	&jetID,	"jetID[njet]/I");
  ztree->Branch("subid",	&subid,	"subid[njet]/I");
  ztree->Branch("chargedSum",	&chargedSum,	"chargedSum[njet]/F");
  ztree->Branch("neutralSum",	&neutralSum,	"neutralSum[njet]/F");
  ztree->Branch("eSum",	&eSum,	"eSum[njet]/F");
  ztree->Branch("jetptsigma0020",	&jetptsigma0020,	"jetptsigma0020[njet]/F");
  ztree->Branch("jetphisigma0020",	&jetphisigma0020,	"jetphisigma0020[njet]/F");
  ztree->Branch("jetptsigma2060",	&jetptsigma2060,	"jetptsigma2060[njet]/F");
  ztree->Branch("jetphisigma2060",	&jetphisigma2060,	"jetphisigma2060[njet]/F");
  ztree->Branch("jetptsigma60100",	&jetptsigma60100,	"jetptsigma60100[njet]/F");
  ztree->Branch("jetphisigma60100",	&jetphisigma60100,	"jetphisigma60100[njet]/F");
  ztree->Branch("jetptsigma100200",	&jetptsigma100200,	"jetptsigma100200[njet]/F");
  ztree->Branch("jetphisigma100200",	&jetphisigma100200,	"jetphisigma100200[njet]/F");

  ztree->Branch("ngen",	&ngen,	"ngen/I");
  ztree->Branch("genmatchindex",	&genmatchindex,	"genmatchindex[ngen]/I");
  ztree->Branch("genpt",	&genpt,	"genpt[ngen]/F");
  ztree->Branch("geneta",	&geneta,	"geneta[ngen]/F");
  ztree->Branch("genphi",	&genphi,	"genphi[ngen]/F");
  ztree->Branch("gensubid",	&gensubid,	"gensubid[ngen]/I");


  ztree->Branch("njet_mix", &nref_ak3pupf_out, "njet_mix/I");
  ztree->Branch("rawpt_mix", rawpt_ak3pupf_out, "rawpt_mix[njet_mix]/F");
  ztree->Branch("jetpt_mix", jtpt_ak3pupf_out, "jetpt_mix[njet_mix]/F");
  ztree->Branch("jeteta_mix", jteta_ak3pupf_out, "jeteta_mix[njet_mix]/F");
  ztree->Branch("jetphi_mix", jtphi_ak3pupf_out, "jetphi_mix[njet_mix]/F");
  ztree->Branch("nmixEv_mix", nmixEv_ak3pupf_out, "nmixEv_mix[njet_mix]/I");
  ztree->Branch("jetID_mix", jetID_ak3pupf_out, "jetID_mix[njet_mix]/I");
  ztree->Branch("neutralSum_mix", neutralSum_ak3pupf_out, "neutralSum_mix[njet_mix]/F");
  ztree->Branch("chargedSum_mix", chargedSum_ak3pupf_out, "chargedSum_mix[njet_mix]/F");
  ztree->Branch("chargedN_mix", chargedN_ak3pupf_out, "chargedN_mix[njet_mix]/I");
  ztree->Branch("photonN_mix", photonN_ak3pupf_out, "photonN_mix[njet_mix]/I");
  ztree->Branch("neutralN_mix", neutralN_ak3pupf_out, "neutralN_mix[njet_mix]/I");
  ztree->Branch("eN_mix", eN_ak3pupf_out, "eN_mix[njet_mix]/I");
  ztree->Branch("muN_mix", muN_ak3pupf_out, "muN_mix[njet_mix]/I");
  ztree->Branch("chargedMax_mix", chargedMax_ak3pupf_out, "chargedMax_mix[njet_mix]/F");
  ztree->Branch("photonSum_mix", photonSum_ak3pupf_out, "photonSum_mix[njet_mix]/F");
  ztree->Branch("eSum_mix", eSum_ak3pupf_out, "eSum_mix[njet_mix]/F");


  ztree->Branch("nTrk",	&nTrk,	"nTrk/I");
  ztree->Branch("trkPt",	&trkPt,	"trkPt[nTrk]/F");
  ztree->Branch("trkPtError", &trkPtError,"trkPtError[nTrk]/F");
  ztree->Branch("trkNHit", &trkNHit,"trkNHit[nTrk]/b");
  ztree->Branch("trkNlayer", &trkNlayer,"trkNlayer[nTrk]/b");
  ztree->Branch("trkEta", &trkEta,"trkEta[nTrk]/F");
  ztree->Branch("trkPhi", &trkPhi,"trkPhi[nTrk]/F");
  ztree->Branch("trkCharge", &trkCharge,"trkCharge[nTrk]/I");
  ztree->Branch("trkNVtx", &trkNVtx,"trkNVtx[nTrk]/b");
  ztree->Branch("highPurity", &highPurity,"highPurity[nTrk]/O");
  ztree->Branch("tight", &tight,"tight[nTrk]/O");
  ztree->Branch("loose", &loose,"loose[nTrk]/O");
  ztree->Branch("trkChi2", &trkChi2,"trkChi2[nTrk]/F");
  ztree->Branch("trkNdof", &trkNdof,"trkNdof[nTrk]/b");
  ztree->Branch("trkDxy1", &trkDxy1,"trkDxy1[nTrk]/F");
  ztree->Branch("trkDxyError1", &trkDxyError1,"trkDxyError1[nTrk]/F");
  ztree->Branch("trkDz1", &trkDz1,"trkDz1[nTrk]/F");
  ztree->Branch("trkDzError1", &trkDzError1,"trkDzError1[nTrk]/F");
  ztree->Branch("trkFake", &trkFake,"trkFake[nTrk]/O");
  ztree->Branch("trkAlgo", &trkAlgo,"trkAlgo[nTrk]/b");
  ztree->Branch("trkOriginalAlgo", &trkOriginalAlgo,"trkOriginalAlgo[nTrk]/b");
  ztree->Branch("trkMVA", &trkMVA,"trkMVA[nTrk]/F");
  ztree->Branch("pfType", &pfType,"pfType[nTrk]/I");
  ztree->Branch("pfCandPt", &pfCandPt,"pfCandPt[nTrk]/F");
  ztree->Branch("pfEcal", &pfEcal,"pfEcal[nTrk]/F");
  ztree->Branch("pfHcal", &pfHcal,"pfHcal[nTrk]/F");
  ztree->Branch("trkWeight", &trkWeight,"trkWeight[nTrk]/F");
  ztree->Branch("weight", &weight,"weight/F");

  ztree->Branch("nPho",&nPho,"nPho/I");
  ztree->Branch("phoE",&phoE,"phoE[nPho]/F");
  ztree->Branch("phoEt",&phoEt,"phoEt[nPho]/F");
  ztree->Branch("phoEtCorrected",&phoEtCorrected,"phoEtCorrected[nPho]/F");
  ztree->Branch("pho_sumIso",&pho_sumIso,"pho_sumIso[nPho]/F");
  ztree->Branch("pho_sumIsoCorrected",&pho_sumIsoCorrected,"pho_sumIsoCorrected[nPho]/F");
  ztree->Branch("phoCorr",&phoCorr,"phoCorr[nPho]/F");
  ztree->Branch("phoEta",&phoEta,"phoEta[nPho]/F");
  ztree->Branch("phoPhi",&phoPhi,"phoPhi[nPho]/F");
  ztree->Branch("phoSCE",&phoSCE,"phoSCE[nPho]/F");
  ztree->Branch("phoSCRawE",&phoSCRawE,"phoSCRawE[nPho]/F");
  ztree->Branch("phoESEn",&phoESEn,"phoESEn[nPho]/F");
  ztree->Branch("phoSCEta",&phoSCEta,"phoSCEta[nPho]/F");
  ztree->Branch("phoSCPhi",&phoSCPhi,"phoSCPhi[nPho]/F");
  ztree->Branch("phoSCEtaWidth",&phoSCEtaWidth,"phoSCEtaWidth[nPho]/F");
  ztree->Branch("phoSCPhiWidth",&phoSCPhiWidth,"phoSCPhiWidth[nPho]/F");
  ztree->Branch("phoSCBrem",&phoSCBrem,"phoSCBrem[nPho]/F");
  ztree->Branch("phohasPixelSeed",&phohasPixelSeed,"phohasPixelSeed[nPho]/I");
  ztree->Branch("phoR9",&phoR9,"phoR9[nPho]/F");
  ztree->Branch("phoHoverE",&phoHoverE,"phoHoverE[nPho]/F");
  ztree->Branch("phoSigmaIEtaIEta",&phoSigmaIEtaIEta,"phoSigmaIEtaIEta[nPho]/F");
  ztree->Branch("pho_ecalClusterIsoR2",&pho_ecalClusterIsoR2,"pho_ecalClusterIsoR2[nPho]/F");
  ztree->Branch("pho_ecalClusterIsoR3",&pho_ecalClusterIsoR3,"pho_ecalClusterIsoR3[nPho]/F");
  ztree->Branch("pho_ecalClusterIsoR4",&pho_ecalClusterIsoR4,"pho_ecalClusterIsoR4[nPho]/F");
  ztree->Branch("pho_ecalClusterIsoR5",&pho_ecalClusterIsoR5,"pho_ecalClusterIsoR5[nPho]/F");
  ztree->Branch("pho_hcalRechitIsoR1",&pho_hcalRechitIsoR1,"pho_hcalRechitIsoR1[nPho]/F");
  ztree->Branch("pho_hcalRechitIsoR2",&pho_hcalRechitIsoR2,"pho_hcalRechitIsoR2[nPho]/F");
  ztree->Branch("pho_hcalRechitIsoR3",&pho_hcalRechitIsoR3,"pho_hcalRechitIsoR3[nPho]/F");
  ztree->Branch("pho_hcalRechitIsoR4",&pho_hcalRechitIsoR4,"pho_hcalRechitIsoR4[nPho]/F");
  ztree->Branch("pho_hcalRechitIsoR5",&pho_hcalRechitIsoR5,"pho_hcalRechitIsoR5[nPho]/F");
  ztree->Branch("pho_trackIsoR1PtCut20",&pho_trackIsoR1PtCut20,"pho_trackIsoR1PtCut20[nPho]/F");
  ztree->Branch("pho_trackIsoR2PtCut20",&pho_trackIsoR2PtCut20,"pho_trackIsoR2PtCut20[nPho]/F");
  ztree->Branch("pho_trackIsoR3PtCut20",&pho_trackIsoR3PtCut20,"pho_trackIsoR3PtCut20[nPho]/F");
  ztree->Branch("pho_trackIsoR4PtCut20",&pho_trackIsoR4PtCut20,"pho_trackIsoR4PtCut20[nPho]/F");
  ztree->Branch("pho_trackIsoR5PtCut20",&pho_trackIsoR5PtCut20,"pho_trackIsoR5PtCut20[nPho]/F");
  ztree->Branch("pho_swissCrx",&pho_swissCrx,"pho_swissCrx[nPho]/F");
  ztree->Branch("pho_seedTime",&pho_seedTime,"pho_seedTime[nPho]/F");

  ztree->Branch("phoE3x3",&phoE3x3,"phoE3x3[nPho]/F");
  ztree->Branch("phoE1x5",&phoE1x5,"phoE1x5[nPho]/F");
  ztree->Branch("phoE2x5",&phoE2x5,"phoE2x5[nPho]/F");
  ztree->Branch("phoE5x5",&phoE5x5,"phoE5x5[nPho]/F");
  ztree->Branch("phoSigmaIEtaIEta_2012",&phoSigmaIEtaIEta_2012,"phoSigmaIEtaIEta_2012[nPho]/F");
  ztree->Branch("phoNoise",&phoNoise,"phoNoise[nPho]/I");
  ztree->Branch("pho_genMatchedIndex",&pho_genMatchedIndex,"pho_genMatchedIndex[nPho]/I");

  ztree->Branch("pfcIso1",&pfcIso1,"pfcIso1[nPho]/F");
  ztree->Branch("pfcIso2",&pfcIso2,"pfcIso2[nPho]/F");
  ztree->Branch("pfcIso3",&pfcIso3,"pfcIso3[nPho]/F");
  ztree->Branch("pfcIso4",&pfcIso4,"pfcIso4[nPho]/F");
  ztree->Branch("pfcIso5",&pfcIso5,"pfcIso5[nPho]/F");
  ztree->Branch("pfpIso1",&pfpIso1,"pfpIso1[nPho]/F");
  ztree->Branch("pfpIso2",&pfpIso2,"pfpIso2[nPho]/F");
  ztree->Branch("pfpIso3",&pfpIso3,"pfpIso3[nPho]/F");
  ztree->Branch("pfpIso4",&pfpIso4,"pfpIso4[nPho]/F");
  ztree->Branch("pfpIso5",&pfpIso5,"pfpIso5[nPho]/F");
  ztree->Branch("pfnIso1",&pfnIso1,"pfnIso1[nPho]/F");
  ztree->Branch("pfnIso2",&pfnIso2,"pfnIso2[nPho]/F");
  ztree->Branch("pfnIso3",&pfnIso3,"pfnIso3[nPho]/F");
  ztree->Branch("pfnIso4",&pfnIso4,"pfnIso4[nPho]/F");
  ztree->Branch("pfnIso5",&pfnIso5,"pfnIso5[nPho]/F");
	ztree->Branch("nMC", &nMC,"nMC/I");
	ztree->Branch("mcPID", &mcPID,"mcPID[nMC]/I");
	ztree->Branch("mcStatus", &mcStatus,"mcStatus[nMC]/I");
	ztree->Branch("mcPt", &mcPt,"mcPt[nMC]/F");
	ztree->Branch("mcEt", &mcEt,"mcEt[nMC]/F");
	ztree->Branch("mcEta", &mcEta,"mcEta[nMC]/F");
	ztree->Branch("mcPhi", &mcPhi,"mcPhi[nMC]/F");
	ztree->Branch("mcMomPt", &mcMomPt,"mcMomPt[nMC]/F");
	ztree->Branch("mcMomEta", &mcMomEta,"mcMomEta[nMC]/F");
	ztree->Branch("mcMomPhi", &mcMomPhi,"mcMomPhi[nMC]/F");
	ztree->Branch("mcMomPID", &mcMomPID,"mcMomPID[nMC]/I");
//! End skim tree definition and branches

//! (1.4) Begin reading the HiForest and setting the trees we use
  TTree *inggTree;
  if(is_pp) inggTree = (TTree*)fin->Get("ggHiNtuplizerGED/EventTree");
  else      inggTree = (TTree*)fin->Get("ggHiNtuplizer/EventTree");
  if(!inggTree){
    cout<<"Could not access gg tree!"<<endl;
    return;
  }
  initggTree(inggTree); // from ggTree.h

  TTree *injetTree = (TTree*)fin->Get(Form("%s/t",jetname.data())); // passed in input to easily change jet algo used
  if(!injetTree){
    cout<<"Could not access jet tree!"<<endl;
    return;
  }
  initjetTree(injetTree); // from jetTree.h
  injetTree->SetBranchAddress("ngen", &ngen);
  injetTree->SetBranchAddress("genmatchindex", &genmatchindex);
  injetTree->SetBranchAddress("genpt", &genpt);
  injetTree->SetBranchAddress("geneta", &geneta);
  injetTree->SetBranchAddress("genphi", &genphi);
  injetTree->SetBranchAddress("gensubid", &gensubid);

  // jet tree required by tracking efficiency calculation
  TTree *injetTreeFORTRKCORR;
  if(!is_pp) injetTreeFORTRKCORR = (TTree*)fin->Get(Form("akPu4CaloJetAnalyzer/t"));
  else       injetTreeFORTRKCORR = (TTree*)fin->Get(Form("ak4CaloJetAnalyzer/t"));
  if(!injetTreeFORTRKCORR){
    cout<<"Could not access akPu4Calo tree!"<<endl;
    return;
  }
  injetTreeFORTRKCORR->SetBranchAddress("nref", &nref_corr);
  injetTreeFORTRKCORR->SetBranchAddress("chargedSum", &chargedSum_corr);
  injetTreeFORTRKCORR->SetBranchAddress("rawpt", &rawpt_corr);
  injetTreeFORTRKCORR->SetBranchAddress("jtpt", &jtpt_corr);
  injetTreeFORTRKCORR->SetBranchAddress("jteta", &jteta_corr);
  injetTreeFORTRKCORR->SetBranchAddress("jtphi", &jtphi_corr);



  TTree *evttree = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
  if(!evttree){
    cout<<"Could not access event tree!"<<endl;
    return;
  }
  evttree->SetBranchAddress("weight", &weight);
  evttree->SetBranchAddress("hiBin", &hiBin);
  evttree->SetBranchAddress("vz", &vz);
  evttree->SetBranchAddress("hiNevtPlane", &hiNevtPlane);
  evttree->SetBranchAddress("hiEvtPlanes", &hiEvtPlanes);
  evttree->SetBranchAddress("evt", &evt);
  evttree->SetBranchAddress("lumi", &lumi);
  evttree->SetBranchAddress("run", &run);


  bool ismc = true; // ismc is defined by the existance of the genparticle tree
  TTree *genptree = (TTree*)fin->Get("HiGenParticleAna/hi");
  if(!genptree){
    cout<<"Could not access gen particle tree!"<<endl;
    ismc = false;
  }
  if(ismc)
  {
    genptree->SetBranchAddress("mult", &_mult);
    genptree->SetBranchAddress("pt", &_pt);
    genptree->SetBranchAddress("eta", &_eta);
    genptree->SetBranchAddress("phi", &_phi);
    genptree->SetBranchAddress("pdg", &_pdg);
    genptree->SetBranchAddress("chg", &_chg);
    genptree->SetBranchAddress("matchingID", &_matchingID);
    genptree->SetBranchAddress("sube", &_sube);
  }
  TTree *hlttree = (TTree*)fin->Get("hltanalysis/HltTree");
  if(!hlttree){
    cout<<"Could not access hlt tree!"<<endl;
    return;
  }
  hlttree->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v1", &HLT_HISinglePhoton40_Eta1p5_v1);
  hlttree->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5_v2", &HLT_HISinglePhoton40_Eta1p5_v2);
  hlttree->SetBranchAddress("HLT_HISinglePhoton40_Eta1p5ForPPRef_v1", &HLT_HISinglePhoton40_Eta1p5ForPPRef_v1);

  TTree * tracktree_                     = (TTree*) fin->Get("anaTrack/trackTree");
  if( tracktree_ == 0 ) tracktree_        = (TTree*) fin->Get("ppTrack/trackTree");
  if(!tracktree_){
    cout<<"Could not access track tree!"<<endl;
    return;
  }
  initTrackTree(tracktree_); // from trackTree.h

  TTree * skimTree                     = (TTree*) fin->Get("skimanalysis/HltTree");
  if( skimTree == 0 )
  {
    cout<<"Could not access skim tree!"<<endl;
    return;
  }
  initSkimTree(skimTree); // from SkimTree.h
//! End setting the input hiforest trees


//! (1.5) Begin setting up the trees from the mixed minbias HiForest
  TFile * fminbias = 0;
  TTree *evttree_mix = 0;
  TTree * tracktree_mix = 0;
  TTree *genptree_mix = 0;
  TTree * skimTree_mix = 0;
  TTree *injetTreeFORTRKCORR_mix = 0;
  TTree * jettree_ak3pupf   = 0;

  vector<float> vmix_vz;
  vector<int> vmix_hiBin;
  vector<float> vmix_hiEvtPlanes;
  vector<int> vmix_pcollisionEventSelection;
  vector<int> vmix_HBHENoiseFilterResultRun2Loose;
  vector<int> vmix_pPAprimaryVertexFilter;
  vector<int> vmix_pBeamScrapingFilter;
  vector<int> vmix_index;

  int nEventsToMix = 10;
  if(!minbias.empty() && minbias.compare("null")!=0 )
  {
    fminbias = TFile::Open(minbias.data());

    evttree_mix = (TTree*)fminbias->Get("hiEvtAnalyzer/HiTree");
    if(!evttree_mix){
      cout<<"Could not access mix event tree!"<<endl;
      return;
    }
    evttree_mix->SetBranchAddress("hiBin", &hiBin_mix);
    evttree_mix->SetBranchAddress("vz", &vz_mix);
    evttree_mix->SetBranchAddress("hiEvtPlanes", &hiEvtPlanes_mix);

    tracktree_mix                     = (TTree*) fminbias->Get("anaTrack/trackTree");
    if( tracktree_mix == 0 ) tracktree_mix        = (TTree*) fminbias->Get("ppTrack/trackTree");
    if(!tracktree_mix){
      cout<<"Could not access mix track tree!"<<endl;
      return;
    }
    initTrackTreeMix(tracktree_mix);

    jettree_ak3pupf   = (TTree*) fminbias->Get("akPu3PFJetAnalyzer/t");
    if(!jettree_ak3pupf){
      cout<<"Could not access mix jet tree!"<<endl;
      return;
    }
    initjetTree_ak3pupf(jettree_ak3pupf);


    skimTree_mix                     = (TTree*) fminbias->Get("skimanalysis/HltTree");
    if( skimTree_mix == 0 )
    {
      cout<<"Could not access mix skim tree!"<<endl;
      return;
    }
    initSkimTreeMix(skimTree_mix);

    if(!is_pp) injetTreeFORTRKCORR_mix = (TTree*)fminbias->Get(Form("akPu4CaloJetAnalyzer/t"));
    else       injetTreeFORTRKCORR_mix = (TTree*)fminbias->Get(Form("ak4CaloJetAnalyzer/t"));
    if(!injetTreeFORTRKCORR_mix){
      cout<<"Could not access mix akPu4Calo tree!"<<endl;
      return;
    }
    injetTreeFORTRKCORR_mix->SetBranchAddress("nref", &nref_corr_mix);
    injetTreeFORTRKCORR_mix->SetBranchAddress("chargedSum", &chargedSum_corr_mix);
    injetTreeFORTRKCORR_mix->SetBranchAddress("rawpt", &rawpt_corr_mix);
    injetTreeFORTRKCORR_mix->SetBranchAddress("jtpt", &jtpt_corr_mix);
    injetTreeFORTRKCORR_mix->SetBranchAddress("jteta", &jteta_corr_mix);
    injetTreeFORTRKCORR_mix->SetBranchAddress("jtphi", &jtphi_corr_mix);

    genptree_mix = (TTree*)fminbias->Get("HiGenParticleAna/hi");
    if(ismc)
    {
      genptree_mix->SetBranchAddress("mult", &_mult_mix);
      genptree_mix->SetBranchAddress("pt", &_pt_mix);
      genptree_mix->SetBranchAddress("eta", &_eta_mix);
      genptree_mix->SetBranchAddress("phi", &_phi_mix);
      genptree_mix->SetBranchAddress("pdg", &_pdg_mix);
      genptree_mix->SetBranchAddress("chg", &_chg_mix);
    }

    const int nevmix = evttree_mix->GetEntries();
    minbiasstart = rand() % nevmix; // here we pick a random start event to protect from condor jobs always starting at 0
    cout<<"indexing minbias for mixing... Start event is: "<<minbiasstart<<"  ";
    // First put everything we cut on for mixing in vectors for performance (not sure how much this helps)
    // same event cuts as signal
    // (1.51) Begin minbias mixing indexing
    for(int iminbias = 0 ; iminbias < nevmix ; ++ iminbias )
    {
      skimTree_mix->GetEntry(iminbias);
      evttree_mix->GetEntry(iminbias);
      if(fabs(vz_mix)>15) continue;
      skimTree_mix->GetEntry(iminbias);
      if (!is_pp) // HI event selection
      {
        if ((pcollisionEventSelection_mix < 1))  continue;
        if(!ismc)
        {
          if (HBHENoiseFilterResultRun2Loose_mix < 1) continue; // re-use config value...
        }
      }
      else // pp event selection
      {
        if (pPAprimaryVertexFilter_mix < 1 || pBeamScrapingFilter_mix < 1)  continue;
      }
      vmix_vz.push_back(vz_mix);
      vmix_hiBin.push_back(hiBin_mix);
      vmix_hiEvtPlanes.push_back(hiEvtPlanes_mix[8]);
      vmix_pcollisionEventSelection.push_back(pcollisionEventSelection_mix);
      vmix_HBHENoiseFilterResultRun2Loose.push_back(HBHENoiseFilterResultRun2Loose_mix);
      vmix_pPAprimaryVertexFilter.push_back(pPAprimaryVertexFilter_mix);
      vmix_pBeamScrapingFilter.push_back(pBeamScrapingFilter_mix);
      vmix_index.push_back(iminbias);
    }
    cout<<"done indexing minbias"<<endl;

  } else {
    cout<<"WARNING: Minbias file not provided, no mixing will be done"<<endl;
  }
//! End minbias mixing HiForest setup

//! (1.6) Begin photon energy correction setup
  int const nCentBins = 5;
  int const nEtaBins = 1;
  TH1D * photonEnergyCorrections[nCentBins][nEtaBins];

  TFile * energyCorrectionFile = TFile::Open("photonEnergyCorrections.root");
  TFile* sumIsoCorrectionFile;
  if(ismc) sumIsoCorrectionFile = TFile::Open("sumIsoCorrections_MC.root");
  else     sumIsoCorrectionFile = TFile::Open("sumIsoCorrections_Data.root");

  TH1D* sumIsoCorrections = (TH1D*)sumIsoCorrectionFile->Get("sumIsoCorrections");
  for (int icent=0; icent<nCentBins; ++icent)
  {
    for (int ieta=0; ieta<nEtaBins; ++ieta)
    {
      photonEnergyCorrections[icent][ieta] = (TH1D*)energyCorrectionFile->Get(Form("photonEnergyCorr_cent%i_eta%i", icent, ieta));
    }
  }

//! End photon energy correction setup

//! (2) Begin Loop
  int nEv = evttree->GetEntries();
  for (int j=startindex; j<nEv; j++) {
    skimTree->GetEntry(j);
    // if(!(HBHENoiseFilterResultRun2Loose && pPAprimaryVertexFilter && pBeamScrapingFilter)) continue;
    evttree->GetEntry(j);

    if(weight==1) weight = mcweight;

    if(ismc)
    {
      genptree->GetEntry(j);
      mult = _mult;
      for(int igenp = 0 ; igenp < _mult ; ++igenp)
      {
        pt[igenp] = _pt->at(igenp);
        eta[igenp] = _eta->at(igenp);
        phi[igenp] = _phi->at(igenp);
        pdg[igenp] = _pdg->at(igenp);
        chg[igenp] = _chg->at(igenp);
        matchingID[igenp] = _matchingID->at(igenp);
        sube[igenp] = _sube->at(igenp);
      }
    }
    hlttree->GetEntry(j);
    if(j%1000 == 0) { cout << "Processing event: " << j << "/" << endindex << endl; }

//! (2.1) Begin event and trigger cuts
    if(j == endindex ) { cout << "stopping: " << j << endl; break; }
    if(fabs(vz)>15) continue;
    if( !( HLT_HISinglePhoton40_Eta1p5_v1 == 1 || HLT_HISinglePhoton40_Eta1p5_v2 == 1 || HLT_HISinglePhoton40_Eta1p5ForPPRef_v1 == 1 ) ) continue; // photon 40 trigger cut for pbpb+pp data, pbpb mc, pp mc
    if (!is_pp) // HI event selection
    {
      if ((pcollisionEventSelection < 1))  continue;
      if(!ismc)
      {
        if (HBHENoiseFilterResultRun2Loose < 1) continue; // re-use config value...
      }
    }
    else // pp event selection
    {
      if (pPAprimaryVertexFilter < 1 || pBeamScrapingFilter < 1)  continue;
    }
//! End event and trigger cuts

//! (2.2) Begin photon cuts and selection
    inggTree->GetEntry(j);
		int nmcphoton = 0;
    for(int imc = 0 ; imc < _nMC ; ++imc)
		{
			// if(abs((*_mcMomPID)[imc])!=22) continue; //only signal photons if mc
			nmcphoton++;
			mcPID[imc] = (*_mcPID)[imc];
			mcStatus[imc] = (*_mcStatus)[imc];
			mcPt[imc] = (*_mcPt)[imc];
			mcEt[imc] = (*_mcEt)[imc];
			mcEta[imc] = (*_mcEta)[imc];
			mcPhi[imc] = (*_mcPhi)[imc];
			mcMomPt[imc] = (*_mcMomPt)[imc];
			mcMomEta[imc] = (*_mcMomEta)[imc];
			mcMomPhi[imc] = (*_mcMomPhi)[imc];
			mcMomPID[imc] = (*_mcMomPID)[imc];
		}
		nMC = nmcphoton;

    int maxPhoIndex = -1;
    float maxPhoEt = -1;
		for(int ipho = 0 ; ipho < _nPho ; ++ipho)
    {
      if(_phoEt->at(ipho)<35 ) continue;
      if(fabs(_phoEta->at(ipho))>1.44) continue;

      // spike rejection:
      if(_phoSigmaIEtaIEta->at(ipho) < 0.002) continue;
      if(fabs(_pho_seedTime->at(ipho)) > 3.0) continue;
      if(_pho_swissCrx->at(ipho) > 0.9) continue;

      if(_phoEt->at(ipho) > maxPhoEt)
      {
        maxPhoEt = _phoEt->at(ipho);
        maxPhoIndex = ipho;
      }
    }
    int nphoton = 0;
    bool passed = true;
    if(maxPhoIndex>-1)
    {
      bool failedNoiseCut =  ((_phoE3x3->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) > 2./3.-0.03 &&
                              _phoE3x3->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) < 2./3.+0.03) &&
                              (_phoE1x5->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) > 1./3.-0.03 &&
                              _phoE1x5->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) < 1./3.+0.03) &&
                              (_phoE2x5->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) > 2./3.-0.03 &&
                              _phoE2x5->at(maxPhoIndex)/_phoE5x5->at(maxPhoIndex) < 2./3.+0.03));
      // Isolation cone cut
      // if((*_pho_ecalClusterIsoR4)[maxPhoIndex]+(*_pho_hcalRechitIsoR4)[maxPhoIndex]+(*_pho_trackIsoR4PtCut20)[maxPhoIndex]>1) passed = false;

      float sumIso = (*_pho_ecalClusterIsoR4)[maxPhoIndex]+(*_pho_hcalRechitIsoR4)[maxPhoIndex]+(*_pho_trackIsoR4PtCut20)[maxPhoIndex] ;
      float sumIsoCorrected = sumIso - sumIsoCorrections->GetBinContent(sumIsoCorrections->FindBin(getAngleToEP(fabs( (*_phoPhi)[maxPhoIndex] - hiEvtPlanes[8]))));

      if(is_pp) //sumiso correction only in pbpb
      {
        if( sumIso>1 ) passed = false;
      } else {
        if( sumIsoCorrected>1 ) passed = false;
      }
      if(_phoHoverE->at(maxPhoIndex)>0.1) passed = false;
      if(_phoSigmaIEtaIEta_2012->at(maxPhoIndex) > 0.0170 ) passed = false;

      float eleEpTemp = 100.0;
      for (int ie=0; ie<_nEle; ++ie) {
        if (_elePt->at(ie) < 10)
          continue;
        if (abs(_eleEta->at(ie) - _phoEta->at(maxPhoIndex)) > 0.03) // deta
          continue;
        if (abs(acos(cos(_eleEta->at(ie) - _phoEta->at(maxPhoIndex)))) > 0.03) // dphi
          continue;
        if (eleEpTemp < _eleEoverP->at(ie))
          continue;

        passed = false;
        break;
      }

      if(passed)
      {
        phoE3x3[0] = _phoE3x3->at(maxPhoIndex);
        phoE1x5[0] = _phoE1x5->at(maxPhoIndex);
        phoE2x5[0] = _phoE2x5->at(maxPhoIndex);
        phoE5x5[0] = _phoE5x5->at(maxPhoIndex);
        phoSigmaIEtaIEta_2012[0] = _phoSigmaIEtaIEta_2012->at(maxPhoIndex);
        if(failedNoiseCut)   phoNoise[0] = 0;
        else                 phoNoise[0] = 1;
        if(ismc)             pho_genMatchedIndex[0] = _pho_genMatchedIndex->at(maxPhoIndex);
        phoE[0] = (*_phoE)[maxPhoIndex];
        phoEt[0] = (*_phoEt)[maxPhoIndex];
        phoEta[0] = (*_phoEta)[maxPhoIndex];
        phoPhi[0] = (*_phoPhi)[maxPhoIndex];
        phoSCE[0] = (*_phoSCE)[maxPhoIndex];
        phoSCRawE[0] = (*_phoSCRawE)[maxPhoIndex];
        phoESEn[0] = (*_phoESEn)[maxPhoIndex];
        phoSCEta[0] = (*_phoSCEta)[maxPhoIndex];
        phoSCPhi[0] = (*_phoSCPhi)[maxPhoIndex];
        phoSCEtaWidth[0] = (*_phoSCEtaWidth)[maxPhoIndex];
        phoSCPhiWidth[0] = (*_phoSCPhiWidth)[maxPhoIndex];
        phoSCBrem[0] = (*_phoSCBrem)[maxPhoIndex];
        phohasPixelSeed[0] = (*_phohasPixelSeed)[maxPhoIndex];
        phoR9[0] = (*_phoR9)[maxPhoIndex];
        phoHoverE[0] = (*_phoHoverE)[maxPhoIndex];
        phoSigmaIEtaIEta[0] = (*_phoSigmaIEtaIEta)[maxPhoIndex];
        pho_ecalClusterIsoR2[0] = (*_pho_ecalClusterIsoR2)[maxPhoIndex];
        pho_ecalClusterIsoR3[0] = (*_pho_ecalClusterIsoR3)[maxPhoIndex];
        pho_ecalClusterIsoR4[0] = (*_pho_ecalClusterIsoR4)[maxPhoIndex];
        pho_ecalClusterIsoR5[0] = (*_pho_ecalClusterIsoR5)[maxPhoIndex];
        pho_hcalRechitIsoR1[0] = (*_pho_hcalRechitIsoR1)[maxPhoIndex];
        pho_hcalRechitIsoR2[0] = (*_pho_hcalRechitIsoR2)[maxPhoIndex];
        pho_hcalRechitIsoR3[0] = (*_pho_hcalRechitIsoR3)[maxPhoIndex];
        pho_hcalRechitIsoR4[0] = (*_pho_hcalRechitIsoR4)[maxPhoIndex];
        pho_hcalRechitIsoR5[0] = (*_pho_hcalRechitIsoR5)[maxPhoIndex];
        pho_trackIsoR1PtCut20[0] = (*_pho_trackIsoR1PtCut20)[maxPhoIndex];
        pho_trackIsoR2PtCut20[0] = (*_pho_trackIsoR2PtCut20)[maxPhoIndex];
        pho_trackIsoR3PtCut20[0] = (*_pho_trackIsoR3PtCut20)[maxPhoIndex];
        pho_trackIsoR4PtCut20[0] = (*_pho_trackIsoR4PtCut20)[maxPhoIndex];
        pho_trackIsoR5PtCut20[0] = (*_pho_trackIsoR5PtCut20)[maxPhoIndex];
        pho_swissCrx[0] = (*_pho_swissCrx)[maxPhoIndex];
        pho_seedTime[0] = (*_pho_seedTime)[maxPhoIndex];
        pfcIso1[0] = (*_pfcIso1)[maxPhoIndex];
        pfcIso2[0] = (*_pfcIso2)[maxPhoIndex];
        pfcIso3[0] = (*_pfcIso3)[maxPhoIndex];
        pfcIso4[0] = (*_pfcIso4)[maxPhoIndex];
        pfcIso5[0] = (*_pfcIso5)[maxPhoIndex];
        pfpIso1[0] = (*_pfpIso1)[maxPhoIndex];
        pfpIso2[0] = (*_pfpIso2)[maxPhoIndex];
        pfpIso3[0] = (*_pfpIso3)[maxPhoIndex];
        pfpIso4[0] = (*_pfpIso4)[maxPhoIndex];
        pfpIso5[0] = (*_pfpIso5)[maxPhoIndex];
        pfnIso1[0] = (*_pfnIso1)[maxPhoIndex];
        pfnIso2[0] = (*_pfnIso2)[maxPhoIndex];
        pfnIso3[0] = (*_pfnIso3)[maxPhoIndex];
        pfnIso4[0] = (*_pfnIso4)[maxPhoIndex];
        pfnIso5[0] = (*_pfnIso5)[maxPhoIndex];

        phoCorr[0] = photonEnergyCorrections[getCentBin(hiBin)][0]->GetBinContent(photonEnergyCorrections[getCentBin(hiBin)][0]->FindBin((*_phoEt)[maxPhoIndex]));
        phoEtCorrected[0] = (*_phoEt)[maxPhoIndex]/phoCorr[0];
        pho_sumIso[0] = sumIso;
        pho_sumIsoCorrected[0] = sumIsoCorrected;

        nphoton = 1;
      }
    }
    nPho = nphoton;
    if(nphoton==0) continue;
//! End photon cuts and selection

//! (2.3) Begin jet cuts and selection
    injetTree->GetEntry(j);
    injetTreeFORTRKCORR->GetEntry(j);
    njet = 0;

    float maxJetPt = -999;
    for(int k = 0; k<nref_corr; k++)
    {
      if(TMath::Abs(jteta_corr[k])>2) continue;
      if(jtpt_corr[k]>maxJetPt) maxJetPt=jtpt_corr[k];
    }
    njet_smeared = 0;
    for(int ij=0; ij<nref; ij++) {
      // if(jtpt[ij]>40 && goodJet(ij) && fabs(jteta[ij])<1.6 && acos(cos(jtphi[ij] - phoPhi[0])) > 7 * pi / 8)
      // if(jtpt[ij]>30 && fabs(jteta[ij])<1.6)
      if(jtpt[ij]>jetptmin && fabs(jteta[ij])<1.6 && acos(cos(jtphi[ij] - phoPhi[0])) > 7 * pi / 8)
      {
        //jetpt[njet] = jetcorr->get_corrected_pt(jtpt[ij],jteta[ij]);
        //        cout<<jetpt[njet]<<endl;
       	jetpt[njet] = jtpt[ij];
        jeteta[njet] = jteta[ij];
        jetphi[njet] = jtphi[ij];
       	gjetpt[njet] = refpt[ij];
        gjeteta[njet] = refeta[ij];
        gjetphi[njet] = refphi[ij];
        jetID[njet] = goodJet(ij);
        subid[njet] = _subid[ij];
        chargedSum[njet] = _chargedSum[ij];
        neutralSum[njet] = _neutralSum[ij];
        eSum[njet] = _eSum[ij];
        if(njet>19) {
          cout<<"need bigger smearing arrays"<<endl;
          exit(1);
        }
        if(is_pp) //do smearing
        {
          int smearcents[] = {5,25,65,105};
          for(int ismearcent = 0 ; ismearcent < 4 ; ++ismearcent)
          {
            float sigmapt = getSigmaRelPt(smearcents[ismearcent],jtpt[ij]);
            float sigmaphi = getSigmaRelPhi(smearcents[ismearcent],jtpt[ij]);

            if(ismearcent==0)
            {
              jetptsigma0020[njet] = sigmapt;
              jetphisigma0020[njet] = sigmaphi;
              for (int ijetsmear = 0; ijetsmear < 100; ijetsmear++) {
                jetpt_smeared0020[njet*100+ijetsmear]=jetpt[njet]*randSmearing.Gaus(1,sigmapt);
                jeteta_smeared0020[njet*100+ijetsmear]=jeteta[njet];
                jetphi_smeared0020[njet*100+ijetsmear]=jetphi[njet]+randSmearing.Gaus(0,sigmaphi);
              }
            } else if(ismearcent==1) {
              jetptsigma2060[njet] = sigmapt;
              jetphisigma2060[njet] = sigmaphi;
              for (int ijetsmear = 0; ijetsmear < 100; ijetsmear++) {
                jetpt_smeared2060[njet*100+ijetsmear]=jetpt[njet]*randSmearing.Gaus(1,sigmapt);
                jeteta_smeared2060[njet*100+ijetsmear]=jeteta[njet];
                jetphi_smeared2060[njet*100+ijetsmear]=jetphi[njet]+randSmearing.Gaus(0,sigmaphi);
              }
            } else if(ismearcent==2) {
              jetptsigma60100[njet] = sigmapt;
              jetphisigma60100[njet] = sigmaphi;
              for (int ijetsmear = 0; ijetsmear < 100; ijetsmear++) {
                jetpt_smeared60100[njet*100+ijetsmear]=jetpt[njet]*randSmearing.Gaus(1,sigmapt);
                jeteta_smeared60100[njet*100+ijetsmear]=jeteta[njet];
                jetphi_smeared60100[njet*100+ijetsmear]=jetphi[njet]+randSmearing.Gaus(0,sigmaphi);
              }
            } else if(ismearcent==3) {
              jetptsigma100200[njet] = sigmapt;
              jetphisigma100200[njet] = sigmaphi;
              for (int ijetsmear = 0; ijetsmear < 100; ijetsmear++) {
                jetpt_smeared100200[njet*100+ijetsmear]=jetpt[njet]*randSmearing.Gaus(1,sigmapt);
                jeteta_smeared100200[njet*100+ijetsmear]=jeteta[njet];
                jetphi_smeared100200[njet*100+ijetsmear]=jetphi[njet]+randSmearing.Gaus(0,sigmaphi);
              }
            }
          }
          njet_smeared=(njet+1)*100;
        }
        njet++;
      }
    } //end of jet loop
    // if(do_jet_skim && njet==0) continue;
//! End jet selection

    float maxTrkPt = -999;
//! (2.4) Begin track cuts and selection
    tracktree_->GetEntry(j);

    int ntracks = 0;
    // std::cout<<nTrk_<<std::endl;
    for(int itrk = 0 ; itrk < nTrk_ ; ++itrk)
    {
      // cout<<"itrk "<<itrk<<endl;
      // if((trkMVA_zzz[itrk]<0.5 && trkMVA_[itrk]!=-99) || (int)trkNHit_[itrk]<8 || trkPtError_[itrk]/trkPt_[itrk]>0.3 || fabs(trkDz1_[itrk])/trkDzError1_[itrk]>3 || fabs(trkDxy1_[itrk])/trkDxyError1_[itrk]>3) continue;
      // if(!highPurity_[itrk]) continue;
      // std::cout<<"here"<<std::endl;
      if(trkPt_[itrk]<1 || trkPt_[itrk]>300 || fabs(trkEta_[itrk])>2.4 ) continue;
      if(highPurity_[itrk]!=1) continue;
      if(trkPtError_[itrk]/trkPt_[itrk]>0.1 || TMath::Abs(trkDz1_[itrk]/trkDzError1_[itrk])>3 || TMath::Abs(trkDxy1_[itrk]/trkDxyError1_[itrk])>3) continue;
      if(!is_pp && trkChi2_[itrk]/(float)trkNdof_[itrk]/(float)trkNlayer_[itrk]>0.15) continue;
      if(!is_pp && trkNHit_[itrk]<11) continue;

      //if((maxJetPt>50 && trkPt_[itrk]>maxJetPt) || (maxJetPt<50 && trkPt_[itrk]>50)) continue;

      float Et = (pfHcal_[itrk]+pfEcal_[itrk])/TMath::CosH(trkEta_[itrk]);
      if(!(trkPt_[itrk]<20 || (Et>0.5*trkPt_[itrk]))) continue;
      // cout<<"itrk "<<itrk<<endl;
      if(trkPt_[itrk] > maxTrkPt) maxTrkPt = trkPt_[itrk];
      float trkweight = 0;
      if(is_pp) trkweight = getTrkWeight(trkCorr,itrk,0);
      else trkweight = getTrkWeight(trkCorr,itrk,hiBin);
      trkPt[ntracks] = trkPt_[itrk];   //[nTrk]
      trkPtError[ntracks] = trkPtError_[itrk];   //[nTrk]
      trkNHit[ntracks] = trkNHit_[itrk];   //[nTrk]
      trkNlayer[ntracks] = trkNlayer_[itrk];   //[nTrk]
      trkEta[ntracks] = trkEta_[itrk];   //[nTrk]
      trkPhi[ntracks] = trkPhi_[itrk];   //[nTrk]
      trkCharge[ntracks] = trkCharge_[itrk];   //[nTrk]
      trkNVtx[ntracks] = trkNVtx_[itrk];   //[nTrk]
      highPurity[ntracks] = highPurity_[itrk];   //[nTrk]
      tight[ntracks] = tight_[itrk];   //[nTrk]
      loose[ntracks] = loose_[itrk];   //[nTrk]
      trkChi2[ntracks] = trkChi2_[itrk];   //[nTrk]
      trkNdof[ntracks] = trkNdof_[itrk];   //[nTrk]
      trkDxy1[ntracks] = trkDxy1_[itrk];   //[nTrk]
      trkDxyError1[ntracks] = trkDxyError1_[itrk];   //[nTrk]
      trkDz1[ntracks] = trkDz1_[itrk];   //[nTrk]
      trkDzError1[ntracks] = trkDzError1_[itrk];   //[nTrk]
      trkFake[ntracks] = trkFake_[itrk];   //[nTrk]
      trkAlgo[ntracks] = trkAlgo_[itrk];   //[nTrk]
      trkOriginalAlgo[ntracks] = trkOriginalAlgo_[itrk];   //[nTrk]
      trkMVA[ntracks] = trkMVA_[itrk];   //[nTrk]
      pfType[ntracks] = pfType_[itrk];   //[nTrk]
      pfCandPt[ntracks] = pfCandPt_[itrk];   //[nTrk]
      pfEcal[ntracks] = pfEcal_[itrk];   //[nTrk]
      pfHcal[ntracks] = pfHcal_[itrk];   //[nTrk]
      trkWeight[ntracks] = trkweight;
      ntracks++;
    }
    nTrk=ntracks;
//! End track selection
    if(!do_jet_skim && maxTrkPt < 8) continue;
//! (2.5) Begin minbias mixing criteria machinery
    if(!minbias.empty() && minbias.compare("null")!=0 ) //mix things up
    // if(false) //mix things up
    {
      int minbiasend = minbiasstart;
      mult_mix = 0;
      nmix = 0;
      bool wraparound = false;
      nlooped = 0;
      int ntracks_mix = 0;
      int ntracks_cone = 0;
      int njets_mix = 0;
      // Start looping through the mixed event starting where we left off, so we don't always mix same events`
      for(int iminbias = minbiasstart ; iminbias <= (int)vmix_index.size() ; ++ iminbias )
      {
        // this part lets us wrap around to the beginning if we reach the last event
        if(iminbias == (int)vmix_index.size()) {
          wraparound = true;
          iminbias = 0;
        }
        if(wraparound && iminbias == minbiasstart) break; //came back to start, done mixing
        nlooped++;
//! (2.51) HiBin, vz, eventplane selection
        // vmix_ vectors are set in 1.51
        if(abs(hiBin - vmix_hiBin[iminbias])>0) continue;
        if(fabs(vz - vmix_vz[iminbias])>1) continue;
        float dphi_evplane = fabs(hiEvtPlanes[8] - vmix_hiEvtPlanes[iminbias]);
        if(dphi_evplane > TMath::Pi()/2.0) dphi_evplane = TMath::Pi()-dphi_evplane;
        if(dphi_evplane > TMath::Pi()/16.0) continue;
        // now we are within 2.5% centrality, 5cm vz and pi/16 angle of the original event
        if (!is_pp) // HI event selection
        {
          if ((vmix_pcollisionEventSelection[iminbias] < 1))  continue;
          if(!ismc)
          {
            if (vmix_HBHENoiseFilterResultRun2Loose[iminbias] < 1) continue; // re-use config value...
          }
        }
        else // pp event selection
        {
          if (vmix_pPAprimaryVertexFilter[iminbias] < 1 || vmix_pBeamScrapingFilter[iminbias] < 1)  continue;
        }
        injetTreeFORTRKCORR_mix->GetEntry(vmix_index[iminbias]);

        float maxJetPt_mix = -999;
        for(int k = 0; k<nref_corr_mix; k++)
        {
          if(TMath::Abs(jteta_corr_mix[k])>2) continue;
          if(jtpt_corr_mix[k]>maxJetPt_mix) maxJetPt_mix=jtpt_corr_mix[k];
        }

        vector<int> uejet_idx;

//! (2.52) Jets from mixed events

        vector<int> mixjet_idx;
        jettree_ak3pupf->GetEntry(vmix_index[iminbias]);
        for(int ijetmix = 0 ; ijetmix < nref_ak3pupf ; ++ijetmix)
        {
          if( jtpt_ak3pupf[ijetmix]<30 ) continue; //jet pt Cut
          if( fabs(jteta_ak3pupf[ijetmix]) > 1.6) continue; //jeteta Cut
          if( acos(cos(jtphi_ak3pupf[ijetmix] - phoPhi[0])) < 7 * pi / 8 ) continue;
          // cout<<jtpt_ak3pupf[ijetmix]<<" "<<fabs(jteta_ak3pupf[ijetmix])<<endl;
          // if( jetID[ijet]==0 ) continue;
          rawpt_ak3pupf_out[njets_mix] = rawpt_ak3pupf[ijetmix];
          jtpt_ak3pupf_out[njets_mix] = jtpt_ak3pupf[ijetmix];
          jteta_ak3pupf_out[njets_mix] = jteta_ak3pupf[ijetmix];
          jtphi_ak3pupf_out[njets_mix] = jtphi_ak3pupf[ijetmix];
          neutralSum_ak3pupf_out[njets_mix] = neutralSum_ak3pupf[ijetmix];
          chargedSum_ak3pupf_out[njets_mix] = chargedSum_ak3pupf[ijetmix];
          nmixEv_ak3pupf_out[njets_mix] = nmix;
          jetID_ak3pupf_out[njets_mix] = goodJet_ak3pupf(ijetmix);
          chargedN_ak3pupf_out[njets_mix] = chargedN_ak3pupf[ijetmix];
          photonN_ak3pupf_out[njets_mix] = photonN_ak3pupf[ijetmix];
          neutralN_ak3pupf_out[njets_mix] = neutralN_ak3pupf[ijetmix];
          eN_ak3pupf_out[njets_mix] = eN_ak3pupf[ijetmix];
          muN_ak3pupf_out[njets_mix] = muN_ak3pupf[ijetmix];
          chargedMax_ak3pupf_out[njets_mix] = chargedMax_ak3pupf[ijetmix];
          photonSum_ak3pupf_out[njets_mix] = photonSum_ak3pupf[ijetmix];
          eSum_ak3pupf_out[njets_mix] = eSum_ak3pupf[ijetmix];
          njets_mix++;
          mixjet_idx.push_back(ijetmix);
        }
        // return;
        tracktree_mix->GetEntry(vmix_index[iminbias]);

//! (2.53) Cones in mixed events (i.e. real jets in signal event)
        for (int ijet = 0; ijet < njet; ijet++) {
          if( jetpt[ijet]<30 ) continue; //jet pt Cut
          if( fabs(jeteta[ijet]) > 1.6) continue; //jeteta Cut
          if( acos(cos(jetphi[ijet] - phoPhi[0])) < 7 * pi / 8 ) continue;
          uejet_idx.push_back(ijet);
        }

//! (2.54) Tracks from jet and cones in mixed events
        int nuejets = uejet_idx.size();
        int nmixjets = mixjet_idx.size();
        for(int itrkmix = 0 ; itrkmix < nTrk_mix_ ; ++itrkmix)
        {
          if(trkPt_mix_[itrkmix]<1 || trkPt_mix_[itrkmix]>300 || fabs(trkEta_mix_[itrkmix])>2.4 ) continue;


          if(highPurity_mix_[itrkmix]!=1) continue;
          if(trkPtError_mix_[itrkmix]/trkPt_mix_[itrkmix]>0.1 || TMath::Abs(trkDz1_mix_[itrkmix]/trkDzError1_mix_[itrkmix])>3 || TMath::Abs(trkDxy1_mix_[itrkmix]/trkDxyError1_mix_[itrkmix])>3) continue;
          if(trkChi2_mix_[itrkmix]/(float)trkNdof_mix_[itrkmix]/(float)trkNlayer_mix_[itrkmix]>0.15) continue;
          if(trkNHit_mix_[itrkmix]<11 && trkPt_mix_[itrkmix]>0.7) continue;
          if((maxJetPt_mix>50 && trkPt_mix_[itrkmix]>maxJetPt_mix) || (maxJetPt_mix<50 && trkPt_mix_[itrkmix]>50)) continue;

          float Et = (pfHcal_mix_[itrkmix]+pfEcal_mix_[itrkmix])/TMath::CosH(trkEta_mix_[itrkmix]);
          if(!(trkPt_mix_[itrkmix]<20 || (Et>0.5*trkPt_mix_[itrkmix]))) continue;

          bool inacone = false;
          if(nmix<nEventsToMix/2) // use first half of mixed events for ue mixing and the second for jet mixing
          {
            for(int ijetcand = 0 ; ijetcand < nuejets ; ijetcand++)
            {
              float dphi = acos( cos(jetphi[uejet_idx[ijetcand]] - trkPhi_mix_[itrkmix]));
              float deta = fabs( jeteta[uejet_idx[ijetcand]] - trkEta_mix_[itrkmix]);
              float dr = sqrt((dphi*dphi)+(deta*deta));
              if(dr<0.3)
              {
                inacone = true;
                break;
              }
            }
          } else {
            for(int ijetcand = 0 ; ijetcand < nmixjets ; ijetcand++)
            {
              float dphi = acos( cos(jtphi_ak3pupf[mixjet_idx[ijetcand]] - trkPhi_mix_[itrkmix]));
              float deta = fabs( jteta_ak3pupf[mixjet_idx[ijetcand]] - trkEta_mix_[itrkmix]);
              float dr = sqrt((dphi*dphi)+(deta*deta));
              if(dr<0.3)
              {
                inacone = true;
                break;
              }
            }
          }

          if(!inacone) continue;
          float trkweight_mix = 0;
          if(is_pp) trkweight_mix = getTrkWeightMix(trkCorr,itrkmix,0);
          else trkweight_mix = getTrkWeightMix(trkCorr,itrkmix,vmix_hiBin[iminbias]);
          if(nmix<nEventsToMix/2) // use first half of mixed events for ue mixing and the second for jet mixing
          {
            trkFromEv_cone[ntracks_cone] = nmix;   //[nTrk_mix]
            trkPt_cone[ntracks_cone] = trkPt_mix_[itrkmix];   //[nTrk_mix]
            trkEta_cone[ntracks_cone] = trkEta_mix_[itrkmix];   //[nTrk_mix]
            trkPhi_cone[ntracks_cone] = trkPhi_mix_[itrkmix];   //[nTrk_mix]
            trkWeight_cone[ntracks_cone] = trkweight_mix;
            ntracks_cone++;
          } else {
            trkFromEv_mix[ntracks_mix] = nmix;   //[nTrk_mix]
            trkPt_mix[ntracks_mix] = trkPt_mix_[itrkmix];   //[nTrk_mix]
            trkEta_mix[ntracks_mix] = trkEta_mix_[itrkmix];   //[nTrk_mix]
            trkPhi_mix[ntracks_mix] = trkPhi_mix_[itrkmix];   //[nTrk_mix]
            trkWeight_mix[ntracks_mix] = trkweight_mix;
            ntracks_mix++;
          }
          // atleastonetrack = true;
        }
        if(ismc)
        {
          genptree_mix->GetEntry(vmix_index[iminbias]);
//! (2.55) Gen particles from jet and cones in mixed events
          for(int igenp = 0 ; igenp < _mult_mix ; ++igenp)
          {
            if(_pt_mix->at(igenp)<1 || _pt_mix->at(igenp)>300 || fabs(_eta_mix->at(igenp))>2.4 ) continue;

            bool inacone = false;

            if(nmix<nEventsToMix/2) // use first half of mixed events for ue mixing and the second for jet mixing
            {
              for(int ijetcand = 0 ; ijetcand < nuejets ; ijetcand++)
              {
                float dphi = acos( cos(jetphi[uejet_idx[ijetcand]] - _phi_mix->at(igenp)));
                float deta = fabs( jeteta[uejet_idx[ijetcand]] - _eta_mix->at(igenp));
                float dr = sqrt((dphi*dphi)+(deta*deta));
                if(dr<0.3)
                {
                  inacone = true;
                  break;
                }
              }
            } else {
              for(int ijetcand = 0 ; ijetcand < nmixjets ; ijetcand++)
              {
                float dphi = acos( cos(jtphi_ak3pupf[mixjet_idx[ijetcand]] - _phi_mix->at(igenp)));
                float deta = fabs( jteta_ak3pupf[mixjet_idx[ijetcand]] - _eta_mix->at(igenp));
                float dr = sqrt((dphi*dphi)+(deta*deta));
                if(dr<0.3)
                {
                  inacone = true;
                  break;
                }
              }
            }

            if(!inacone) continue;
            if(nmix<nEventsToMix/2) // use first half of mixed events for ue mixing and the second for jet mixing
            {
              pt_mix[mult_mix] = _pt_mix->at(igenp);
              eta_mix[mult_mix] = _eta_mix->at(igenp);
              phi_mix[mult_mix] = _phi_mix->at(igenp);
              pdg_mix[mult_mix] = _pdg_mix->at(igenp);
              chg_mix[mult_mix] = _chg_mix->at(igenp);
              // cout<<mult<<" "<<_mult_mix<<" "<<mult_mix<<" "<<nmix<<endl;
              nev_mix[mult_mix] = nmix;
              // cout<<mult_mix<<" "<<nmix<<" "<<mult_mix<<" "<<nev_mix[mult_mix]<<endl;
              mult_mix++;
            } else {
              pt_cone[mult_cone] = _pt_mix->at(igenp);
              eta_cone[mult_cone] = _eta_mix->at(igenp);
              phi_cone[mult_cone] = _phi_mix->at(igenp);
              pdg_cone[mult_cone] = _pdg_mix->at(igenp);
              chg_cone[mult_cone] = _chg_mix->at(igenp);
              nev_cone[mult_cone] = nmix;
              mult_cone++;
            }
          }
        }

        evttree_mix->GetEntry(vmix_index[iminbias]);
        dvz_mix[nmix] = fabs(vz - vz_mix);
        dhiBin_mix[nmix] = abs(hiBin - hiBin_mix);
        dhiEvtPlanes_mix[nmix] = dphi_evplane;
        // if(atleastonetrack)
        nmix++;
        // if(atleastonetrack) nmix++;
       minbiasend = iminbias;
        if(nmix >= nEventsToMix) break; // done mixing
      }
      minbiasstart = minbiasend;
      nTrk_mix = ntracks_mix;
      nTrk_cone = ntracks_cone;
      nref_ak3pupf_out = njets_mix;
      if(nTrk_mix==0)
      {
        cout<<nTrk_mix<<" "<<j<<endl;
        // cout<<"here"<<endl;
       // break;
      }
    }
//! End minbias mixing
    // cout<<j<<" before fill"<<endl;
    ztree->Fill();
    // cout<<j<<" after fill"<<endl;

  } //end of loop over events


  fout->cd();
  ztree->Write();
  fout->Write();
  fout->Close();

}

int main(int argc, char *argv[])
{
  if((argc < 3))
  {
    std::cout << "Usage: ./gammajetSkim.exe <inputfile> <outputfile> [jetname] [is_pp] [mcweight] [startindex] [endindex] [dojetskim] [jetptmin]" << std::endl;
    return 1;
  }
  if(argc==3)  gammajetSkim(argv[1], argv[2]); //basic input output files
  if(argc==4)  gammajetSkim(argv[1], argv[2], argv[3]); //add jet name
  if(argc==5)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4])); //add is_pp
  if(argc==6)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5])); //add custom mcweight
  if(argc==7)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6]); //add minbias mix
  if(argc==8)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7])); //add startindex
  if(argc==9)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7]),std::atoi(argv[8])); //add endindex
  if(argc==10) gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7]),std::atoi(argv[8]),std::atoi(argv[9])); //add do_jet_skim
  if(argc==11) gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7]),std::atoi(argv[8]),std::atoi(argv[9]),std::atoi(argv[10])); // add jetptmin
  return 0;
}
