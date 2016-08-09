#include "ggTree.h"
#include "jetTree.h"
#include "trackTree.h"
#include "SkimTree.h"
#include "L2L3ResidualWFits.h"
#include "getTrkCorr.h"

//! cuts defined here , {veto, loose, medium, tight}
float cuts_barrel_pbpb_eleSigmaIEtaIEta_2012[4] = {0.0111,0.0108,0.0106,0.0097};
float cuts_barrel_pbpb_eleEoverPInv[4] = {0.2805,0.1240,0.0148,0.0148};
float cuts_barrel_pbpb_eledEtaAtVtx[4] = {0.0158,0.0157,0.0149,0.0147};
float cuts_barrel_pbpb_eledPhiAtVtx[4] = {0.1572,0.0544,0.0340,0.0257};
float cuts_barrel_pbpb_eleHoverE[4]    = {0.0885,0.0359,0.0333,0.0325};
float cuts_barrel_pbpb_eleD0[4]        = {0.0522,0.0260,0.0160,0.0159};
float cuts_barrel_pbpb_eleDz[4]        = {0.1300,0.1267,0.0694,0.0653};
float cuts_barrel_pbpb_eleMissHits[4]  = {1,1,1,1};

float cuts_endcap_pbpb_eleSigmaIEtaIEta_2012[4] = {0.03488 , 0.0312 , 0.0299 , 0.0294};
float cuts_endcap_pbpb_eleEoverPInv[4] = {0.1867 , 0.1628 , 0.1262 , 0.0596};
float cuts_endcap_pbpb_eledEtaAtVtx[4] = {0.0171 , 0.0158 , 0.0086 , 0.0085};
float cuts_endcap_pbpb_eledPhiAtVtx[4] = {0.3554 , 0.1907 , 0.1224 , 0.0350};
float cuts_endcap_pbpb_eleHoverE[4]    = {0.1228 , 0.1014 , 0.0927 , 0.0377};
float cuts_endcap_pbpb_eleD0[4]        = {0.1909 , 0.1060 , 0.0872 , 0.0800};
float cuts_endcap_pbpb_eleDz[4]        = {0.2641 , 0.2238 , 0.2032 , 0.1852};
float cuts_endcap_pbpb_eleMissHits[4]  = {1,1,1,1};

float cuts_barrel_pp_eleSigmaIEtaIEta_2012[4] = {0.0114,0.0103,0.0101,0.0101};
float cuts_barrel_pp_eleEoverPInv[4] = {0.207,0.102,0.0174,0.012};
float cuts_barrel_pp_eledEtaAtVtx[4] = {0.0152,0.0105,0.0103,0.00926};
float cuts_barrel_pp_eledPhiAtVtx[4] = {0.216,0.115,0.0336,0.0336};
float cuts_barrel_pp_eleHoverE[4]    = {0.181,0.104,0.0876,0.0597};
float cuts_barrel_pp_eleD0[4]        = {0.0564,0.0261,0.0118,0.0111};
float cuts_barrel_pp_eleDz[4]        = {0.472,0.41,0.373,0.0466};
float cuts_barrel_pp_eleMissHits[4]  = {2,2,2,2};

float cuts_endcap_pp_eleSigmaIEtaIEta_2012[4] = {0.0352,0.0301,0.0283,0.0279};
float cuts_endcap_pp_eleEoverPInv[4] = {0.174,0.126,0.0898,0.00999};
float cuts_endcap_pp_eledEtaAtVtx[4] = {0.0113,0.00814,0.00733,0.00724};
float cuts_endcap_pp_eledPhiAtVtx[4] = {0.237,0.182,0.114,0.0918};
float cuts_endcap_pp_eleHoverE[4]    = {0.116,0.0897,0.0678,0.0615};
float cuts_endcap_pp_eleD0[4]        = {0.222,0.118,0.0739,0.0351};
float cuts_endcap_pp_eleDz[4]        = {0.921,0.822,0.602,0.417};
float cuts_endcap_pp_eleMissHits[4]  = {3,1,1,1};
int cut_type_pbpb = 1;
int cut_type_pp = 2;

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


bool goodMuon(int imu) {
  if(_muChi2NDF->at(imu)<10
      && _muMuonHits->at(imu)>0
      && _muStations->at(imu)>1
      && _muTrkLayers->at(imu)>5
      && _muPixelHits->at(imu)>0
      && fabs(_muInnerD0->at(imu))<0.2
      && fabs(_muInnerDz->at(imu))<0.5
      ) return true;
  else return false;
}

//! Electron can be pp or PbPb which have different cuts
bool goodElectron(int i, bool is_pp) {
  if(is_pp)
  {
    if(fabs(_eleSCEta->at(i))<1.479) {
      if(  fabs(_eledEtaAtVtx->at(i))<cuts_barrel_pp_eledEtaAtVtx[cut_type_pp]
          && fabs(_eledPhiAtVtx->at(i))<cuts_barrel_pp_eledPhiAtVtx[cut_type_pp]
          && _eleSigmaIEtaIEta->at(i)<cuts_barrel_pp_eleSigmaIEtaIEta_2012[cut_type_pp]
          && _eleHoverE->at(i)<cuts_barrel_pp_eleHoverE[cut_type_pp]
          && fabs(_eleD0->at(i))<cuts_barrel_pp_eleD0[cut_type_pp]
          && fabs(_eleDz->at(i))<cuts_barrel_pp_eleDz[cut_type_pp]
          && fabs(_eleEoverPInv->at(i))<cuts_barrel_pp_eleEoverPInv[cut_type_pp]
          && _eleMissHits->at(i) <= cuts_barrel_pp_eleMissHits[cut_type_pp]
          ) return true;
      else return false;
    }
    if(fabs(_eleSCEta->at(i))>1.479) {
      if(  fabs(_eledEtaAtVtx->at(i))<cuts_endcap_pp_eledEtaAtVtx[cut_type_pp]
          && fabs(_eledPhiAtVtx->at(i))<cuts_endcap_pp_eledPhiAtVtx[cut_type_pp]
          && _eleSigmaIEtaIEta->at(i)<cuts_endcap_pp_eleSigmaIEtaIEta_2012[cut_type_pp]
          && _eleHoverE->at(i)<cuts_endcap_pp_eleHoverE[cut_type_pp]
          && fabs(_eleD0->at(i))<cuts_endcap_pp_eleD0[cut_type_pp]
          && fabs(_eleDz->at(i))<cuts_endcap_pp_eleDz[cut_type_pp]
          && fabs(_eleEoverPInv->at(i))<cuts_endcap_pp_eleEoverPInv[cut_type_pp]
          && _eleMissHits->at(i) <= cuts_endcap_pp_eleMissHits[cut_type_pp]
          ) return true;
      else return false;
    }
  } else {
    if(fabs(_eleSCEta->at(i))<1.479) {
      if(  fabs(_eledEtaAtVtx->at(i))<cuts_barrel_pbpb_eledEtaAtVtx[cut_type_pp]
          && fabs(_eledPhiAtVtx->at(i))<cuts_barrel_pbpb_eledPhiAtVtx[cut_type_pp]
          && _eleSigmaIEtaIEta->at(i)<cuts_barrel_pbpb_eleSigmaIEtaIEta_2012[cut_type_pp]
          && _eleHoverE->at(i)<cuts_barrel_pbpb_eleHoverE[cut_type_pp]
          && fabs(_eleD0->at(i))<cuts_barrel_pbpb_eleD0[cut_type_pp]
          && fabs(_eleDz->at(i))<cuts_barrel_pbpb_eleDz[cut_type_pp]
          && fabs(_eleEoverPInv->at(i))<cuts_barrel_pbpb_eleEoverPInv[cut_type_pp]
          && _eleMissHits->at(i) <= cuts_barrel_pbpb_eleMissHits[cut_type_pp]
          ) return true;
      else return false;
    }
    if(fabs(_eleSCEta->at(i))>1.479) {
      if(  fabs(_eledEtaAtVtx->at(i))<cuts_endcap_pbpb_eledEtaAtVtx[cut_type_pp]
          && fabs(_eledPhiAtVtx->at(i))<cuts_endcap_pbpb_eledPhiAtVtx[cut_type_pp]
          && _eleSigmaIEtaIEta->at(i)<cuts_endcap_pbpb_eleSigmaIEtaIEta_2012[cut_type_pp]
          && _eleHoverE->at(i)<cuts_endcap_pbpb_eleHoverE[cut_type_pp]
          && fabs(_eleD0->at(i))<cuts_endcap_pbpb_eleD0[cut_type_pp]
          && fabs(_eleDz->at(i))<cuts_endcap_pbpb_eleDz[cut_type_pp]
          && fabs(_eleEoverPInv->at(i))<cuts_endcap_pbpb_eleEoverPInv[cut_type_pp]
          && _eleMissHits->at(i) <= cuts_endcap_pbpb_eleMissHits[cut_type_pp]
          ) return true;
      else return false;
    }
  }

  return false;
}


void gammajetSkim(TString infilename="HiForest.root", TString outfilename="Zevents.root", string jetname="ak4PFJetAnalyzer", int i_is_pp = 0 , float mcweight = 1, string minbias = "", int startindex = 0, int endindex = -1) {

  bool is_pp = (i_is_pp == 1) ;
  TrkCorr* trkCorr;
  // if(!is_pp) trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_PbPb/");
  if(!is_pp) trkCorr = new TrkCorr("TrkCorr_Jun7_Iterative_PbPb_etaLT2p4/");
  else trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_pp/");
  cout<<trkCorr<<endl;
  L2L3Residual * jetcorr = new L2L3Residual(3);
  cout<<jetcorr<<endl;
  TFile *fin = TFile::Open(infilename);

  TFile *fout = new TFile(outfilename,"recreate");

  TH1::SetDefaultSumw2();

  int minbiasstart = 0;


  int Ztype; //type 1 muon, type 2 electron
  float Zmass, Zpt, Zeta, Zrapidity, Zphi;
  float Zlepton1Pt, Zlepton2Pt, Zlepton1Eta, Zlepton2Eta, Zlepton1Phi, Zlepton2Phi;
  float weight = 0 , vz = -99;
  float vz_mix = -99;
  int hiBin = -99;
  int hiBin_mix = -99;
  int HLT_HISinglePhoton40_Eta1p5_v1 = -99;
  int HLT_HISinglePhoton40_Eta1p5_v2 = -99;
  int HLT_HISinglePhoton40_Eta1p5ForPPRef_v1 = -99;
  int Zcharge;
  float leptonptcut = 10;

  //mixvar decleration
  float dvz_mix[10];
  int dhiBin_mix[10];
  float dhiEvtPlanes_mix[10];

  int njet;
  float jetpt[200], jeteta[200], jetphi[200];
  float gjetpt[200], gjeteta[200], gjetphi[200];
  float chargedSum[200], neutralSum[200], eSum[200];
  int jetID[200], subid[200];

  int _mult;
  vector<float> *_pt;
  vector<float> *_eta;
  vector<float> *_phi;
  vector<int> *_pdg;
  vector<int> *_chg;
  vector<int> *_matchingID;
  vector<int> *_sube;
  int mult;
  float pt[10000];
  float eta[10000];
  float phi[10000];
  int pdg[10000];
  int chg[10000];
  int matchingID[10000];
  int sube[10000];

  const int nPtBins = 13;
  const double PtBins[nPtBins+1]={0,2.5,5.0,7.5,10.0,12.5,15.0,20,30,40,50,70,100,150};
  const int nYBins = 13;

  TH1F *mmMass = new TH1F("mmMass",";m^{#mu#mu} (GeV/c^{2});Events",30,60,120);
  TH1F *mmMassSS = new TH1F("mmMassSS",";m^{#mu#mu} (GeV/c^{2});Events",30,60,120);

  TH1F *mmPt = new TH1F("mmPt",";p_{T}^{#mu#mu} (GeV/c);dN/dp_{T}",nPtBins,PtBins);
  TH1F *mmY = new TH1F("mmY",";y^{#mu#mu};Events",nYBins,-2.6,2.6);
  TH1F *mmPhi = new TH1F("mmPhi",";#phi^{#mu#mu};Events",20,-pi,pi);

  TH1F *eeMass = new TH1F("eeMass",";m^{ee} (GeV/c^{2});Events",30,60,120);
  TH1F *eeMassSS = new TH1F("eeMassSS",";m^{ee} (GeV/c^{2});Events",30,60,120);

  TH1F *eePt = new TH1F("eePt",";p_{T}^{ee} (GeV/c);dN/dp_{T}",nPtBins,PtBins);
  TH1F *eeY = new TH1F("eeY",";y^{ee};Events",nYBins,-2.6,2.6);
  TH1F *eePhi = new TH1F("eePhi",";#phi^{ee};Events",20,-pi,pi);

  int nMuPair = 0;
  int nElPair = 0;

  Int_t           hiNevtPlane;
  Float_t         hiEvtPlanes[29];   //[hiNevtPlane]
  Float_t         hiEvtPlanes_mix[29];   //[hiNevtPlane]

  Int_t           nTrk;
  Int_t           nTrk_mix;
  Int_t           run;
  Int_t           event;
  Int_t           lumis;
  Float_t         trkPt[100000];   //[nTrk]
  Float_t         trkPt_mix[100000];   //[nTrk]
  Float_t         trkPtError[100000];   //[nTrk]
  UChar_t         trkNHit[100000];   //[nTrk]
  UChar_t         trkNlayer[100000];   //[nTrk]
  Float_t         trkEta[100000];   //[nTrk]
  Float_t         trkEta_mix[100000];   //[nTrk]
  Float_t         trkPhi[100000];   //[nTrk]
  Float_t         trkPhi_mix[100000];   //[nTrk]
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
  Float_t         trkWeight_mix[100000];   //[nTrk]
  Int_t    nPho;
  Float_t  phoE[100];   //_nPho
  Float_t  phoEt[100];   //_nPho
  Float_t  phoCorr[100];   //_nPho
  Float_t  phoEta[100];   //_nPho
  Float_t  phoPhi[100];   //_nPho
  Float_t  phoSCE[100];   //_nPho
  Float_t  phoSCRawE[100];   //_nPho
  Float_t  phoESEn[100];   //_nPho
  Float_t  phoSCEta[100];   //_nPho
  Float_t  phoSCPhi[100];   //_nPho
  Float_t  phoSCEtaWidth[100];   //_nPho
  Float_t  phoSCPhiWidth[100];   //_nPho
  Float_t  phoSCBrem[100];   //_nPho
  Int_t    phohasPixelSeed[100];   //_nPho
  Float_t  phoR9[100];   //_nPho
  Float_t  phoHoverE[100];   //_nPho
  Float_t  phoSigmaIEtaIEta[100];   //_nPho
  Float_t  pho_ecalClusterIsoR2[100];   //_nPho
  Float_t  pho_ecalClusterIsoR3[100];   //_nPho
  Float_t  pho_ecalClusterIsoR4[100];   //_nPho
  Float_t  pho_ecalClusterIsoR5[100];   //_nPho
  Float_t  pho_hcalRechitIsoR1[100];   //_nPho
  Float_t  pho_hcalRechitIsoR2[100];   //_nPho
  Float_t  pho_hcalRechitIsoR3[100];   //_nPho
  Float_t  pho_hcalRechitIsoR4[100];   //_nPho
  Float_t  pho_hcalRechitIsoR5[100];   //_nPho
  Float_t  pho_trackIsoR1PtCut20[100];   //_nPho
  Float_t  pho_trackIsoR2PtCut20[100];   //_nPho
  Float_t  pho_trackIsoR3PtCut20[100];   //_nPho
  Float_t  pho_trackIsoR4PtCut20[100];   //_nPho
  Float_t  pho_trackIsoR5PtCut20[100];   //_nPho
  Float_t  pho_swissCrx[100];   //_nPho
  Float_t  pho_seedTime[100];   //_nPho

  Float_t  phoE3x3[100];   //_nPho
  Float_t  phoE1x5[100];   //_nPho
  Float_t  phoE2x5[100];   //_nPho
  Float_t  phoE5x5[100];   //_nPho
  Float_t  phoSigmaIEtaIEta_2012[100];   //_nPho
  Int_t    phoNoise[100];   //_nPho
  Int_t    pho_genMatchedIndex[100];   //_nPho

  Float_t  pfcIso1[100];   //_nPho
  Float_t  pfcIso2[100];   //_nPho
  Float_t  pfcIso3[100];   //_nPho
  Float_t  pfcIso4[100];   //_nPho
  Float_t  pfcIso5[100];   //_nPho
  Float_t  pfpIso1[100];   //_nPho
  Float_t  pfpIso2[100];   //_nPho
  Float_t  pfpIso3[100];   //_nPho
  Float_t  pfpIso4[100];   //_nPho
  Float_t  pfpIso5[100];   //_nPho
  Float_t  pfnIso1[100];   //_nPho
  Float_t  pfnIso2[100];   //_nPho
  Float_t  pfnIso3[100];   //_nPho
  Float_t  pfnIso4[100];   //_nPho
  Float_t  pfnIso5[100];   //_nPho
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

  TTree *ztree = new TTree("ztree","Jet track tree");

  ztree->Branch("run",  &run, "run/I");
  ztree->Branch("event",  &event, "event/I");
  ztree->Branch("lumis",  &lumis, "lumis/I");
  ztree->Branch("hiBin", &hiBin, "hiBin/I");
  ztree->Branch("vz", &vz, "vz/F");

  ztree->Branch("nlooped", &nlooped, "nlooped/I");
  ztree->Branch("nmix", &nmix, "nmix/I");
  ztree->Branch("dvz_mix", dvz_mix, "dvz_mix[nmix]/F");
  ztree->Branch("dhiBin_mix", dhiBin_mix, "dhiBin_mix[nmix]/I");
  ztree->Branch("dhiEvtPlanes_mix", dhiEvtPlanes_mix, "dhiEvtPlanes_mix[nmix]/F");
  ztree->Branch("nTrk_mix",	&nTrk_mix,	"nTrk_mix/I");
  ztree->Branch("trkPt_mix",	&trkPt_mix,	"trkPt_mix[nTrk_mix]/F");
  ztree->Branch("trkPhi_mix", &trkPhi_mix,"trkPhi_mix[nTrk_mix]/F");
  ztree->Branch("trkEta_mix", &trkEta_mix,"trkEta_mix[nTrk_mix]/F");
  ztree->Branch("trkWeight_mix", &trkWeight_mix,"trkWeight_mix[nTrk_mix]/F");

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

  ztree->Branch("Ztype",	&Ztype,	"Ztype/I");
  ztree->Branch("Zmass",	&Zmass,	"Zmass/F");
  ztree->Branch("Zpt",	&Zpt,	"Zpt/F");
  ztree->Branch("Zeta",	&Zeta,	"Zeta/F");
  ztree->Branch("Zphi",	&Zphi,	"Zphi/F");
  ztree->Branch("Zrapidity",	&Zrapidity,	"Zrapidity/F");
  ztree->Branch("Zlepton1Pt",	&Zlepton1Pt,	"Zlepton1Pt/F");
  ztree->Branch("Zlepton2Pt",	&Zlepton2Pt,	"Zlepton2Pt/F");
  ztree->Branch("Zlepton1Eta",	&Zlepton1Eta,	"Zlepton1Eta/F");
  ztree->Branch("Zlepton2Eta",	&Zlepton2Eta,	"Zlepton2Eta/F");
  ztree->Branch("Zlepton1Phi",	&Zlepton1Phi,	"Zlepton1Phi/F");
  ztree->Branch("Zlepton2Phi",	&Zlepton2Phi,	"Zlepton2Phi/F");
  ztree->Branch("Zcharge",	&Zcharge,	"Zcharge/I");
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


  TTree *inggTree;
  if(is_pp) inggTree = (TTree*)fin->Get("ggHiNtuplizerGED/EventTree");
  else      inggTree = (TTree*)fin->Get("ggHiNtuplizer/EventTree");
  if(!inggTree){
    cout<<"Could not access gg tree!"<<endl;
    return;
  }
  initggTree(inggTree);
  // akPu4CaloJetAnalyzer
  TTree *injetTree = (TTree*)fin->Get(Form("%s/t",jetname.data()));
  // TTree *injetTree = (TTree*)fin->Get("ak3PFJetAnalyzer/t");
  // if(!injetTree) injetTree = (TTree*)fin->Get("akPu3PFJetAnalyzer/t");
  if(!injetTree){
    cout<<"Could not access jet tree!"<<endl;
    return;
  }
  initjetTree(injetTree);

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


  bool ismc = true;
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
  initTrackTree(tracktree_);

  TTree * skimTree                     = (TTree*) fin->Get("skimanalysis/HltTree");
  if( skimTree == 0 )
  {
    cout<<"Could not access skim tree!"<<endl;
    return;
  }
  initSkimTree(skimTree);

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
  // int nEv = inggTree->GetEntries();
  int nEv = evttree->GetEntries();
  TFile * fminbias = 0;
  TTree *evttree_mix = 0;
  TTree * tracktree_mix = 0;
  TTree * skimTree_mix = 0;
  TTree *injetTreeFORTRKCORR_mix = 0;
  vector<float> vmix_vz;
  vector<int> vmix_hiBin;
  vector<float> vmix_hiEvtPlanes;
  vector<int> vmix_pcollisionEventSelection;
  vector<int> vmix_HBHENoiseFilterResultRun2Loose;
  vector<int> vmix_pPAprimaryVertexFilter;
  vector<int> vmix_pBeamScrapingFilter;
  vector<int> vmix_index;

  if(!minbias.empty())
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
    if( tracktree_mix == 0 ) tracktree_        = (TTree*) fminbias->Get("ppTrack/trackTree");
    if(!tracktree_mix){
      cout<<"Could not access mix track tree!"<<endl;
      return;
    }
    initTrackTreeMix(tracktree_mix);

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


    const int nevmix = evttree_mix->GetEntries();
    cout<<"indexing minbias for mixing... ";
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


  for (int j=startindex; j<nEv; j++) {
    Zlepton1Pt=-99;
    Zlepton2Pt=-99;
    Zlepton1Eta=-99;
    Zlepton2Eta=-99;
    Zlepton1Phi=-99;
    Zlepton2Phi=-99;

    Zlepton1Pt=-99;
    Zlepton2Pt=-99;
    Zlepton1Eta=-99;
    Zlepton2Eta=-99;
    Zlepton1Phi=-99;
    Zlepton2Phi=-99;

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
    if(j%100 == 0) { cout << "Processing event: " << j << endl; }
    // if(j%1 == 0) { cout << "Processing event: " << j << endl; }
    // if(j%1000 == 0) { cout << "Processing event: " << j << endl; }
    if(j == endindex ) { cout << "stopping: " << j << endl; break; }
    if(fabs(vz)>15) continue;
    if( !( HLT_HISinglePhoton40_Eta1p5_v1 == 1 || HLT_HISinglePhoton40_Eta1p5_v2 == 1 || HLT_HISinglePhoton40_Eta1p5ForPPRef_v1 == 1 ) ) continue; // photon 40 trigger cut for pbpb+pp data, pbpb mc, pp mc
    // skimTree->GetEntry(j);
    // cout<<"here "<<pcollisionEventSelection<<endl;
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

    // cout<<"end of jet loop "<<njet<<endl;
    //cout<<"before: "<<jetpt[0]<<endl;

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
		// if(!(_nMC==0 || nmcphoton!=0)) continue;
    // cout<<"end mc loop "<<_nMC<<endl;

    int maxPhoIndex = -1;
    float maxPhoEt = -1;
		for(int ipho = 0 ; ipho < _nPho ; ++ipho)
    {
      if(_phoEt->at(ipho)<35 ) continue;
      if(fabs(_phoEta->at(ipho))>1.44) continue;
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
      float pho_sumIsoCorrected = sumIso - sumIsoCorrections->GetBinContent(sumIsoCorrections->FindBin(getAngleToEP(fabs( (*_phoPhi)[maxPhoIndex] - hiEvtPlanes[8]))));

      if(is_pp) //sumiso correction only in pbpb
      {
        if( sumIso>1 ) passed = false;
      } else {
        if( pho_sumIsoCorrected>1 ) passed = false;
      }
      if(_phoHoverE->at(maxPhoIndex)>0.1) passed = false;
      if(_phoSigmaIEtaIEta_2012->at(maxPhoIndex) > 0.0170 ) passed = false;
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
        nphoton = 1;
      }
    }
    nPho = nphoton;
    // cout<<"end photon loop "<<nphoton<<endl;
    if(nphoton==0) continue;

    injetTree->GetEntry(j);
    injetTreeFORTRKCORR->GetEntry(j);
    // if(j>10000 ) { cout << "Processing event: " << j << endl; break; }
    // cout<<"event: "<<j<<endl;
    njet = 0;

    float maxJetPt = -999;
    for(int k = 0; k<nref_corr; k++)
    {
      if(TMath::Abs(jteta_corr[k])>2) continue;
      if(jtpt_corr[k]>maxJetPt) maxJetPt=jtpt_corr[k];
    }

    for(int ij=0; ij<nref; ij++) {
      if(jtpt[ij]>40 && goodJet(ij) && fabs(jteta[ij])<1.6 && acos(cos(jtphi[ij] - phoPhi[0])) > 7 * pi / 8)
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
        njet++;
      }
    } //end of jet loop
    if(njet==0) continue;

    // if(false && !minbias.empty()) //mix things up
    // cout<<"start mixing: "<<vz<<" "<<hiBin<<" "<<hiEvtPlanes[8]<<" "<<njet<<endl;
    if(!minbias.empty()) //mix things up
    {
      int minbiasend = minbiasstart;
      nmix = 0;
      bool wraparound = false;
      nlooped = 0;
      int ntracks_mix = 0;
      for(int iminbias = minbiasstart ; iminbias <= (int)vmix_index.size() ; ++ iminbias )
      {
        if(iminbias == (int)vmix_index.size()) {
          wraparound = true;
          iminbias = 0;
        }
        if(wraparound && iminbias == minbiasstart) break; //came back to start, done mixing
        nlooped++;
        // skimTree_mix->GetEntry(iminbias);
        // evttree_mix->GetEntry(iminbias);

        if(abs(hiBin - vmix_hiBin[iminbias])>5) continue;
        if(fabs(vz - vmix_vz[iminbias])>5) continue;
        float dphi_evplane = fabs(hiEvtPlanes[8] - vmix_hiEvtPlanes[iminbias]);
        if(dphi_evplane > TMath::Pi()/2.0) dphi_evplane = TMath::Pi()-dphi_evplane;
        if(dphi_evplane > TMath::Pi()/16.0) continue;
        // now we are within 2.5% centrality, 5cm vz and pi/16 angle of the original event

        // skimTree_mix->GetEntry(j);
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
        // cout<<"getentry: "<<nmix<<" of "<<nlooped<<endl;
        injetTreeFORTRKCORR_mix->GetEntry(vmix_index[iminbias]);

        float maxJetPt_mix = -999;
        for(int k = 0; k<nref_corr_mix; k++)
        {
          if(TMath::Abs(jteta_corr_mix[k])>2) continue;
          if(jtpt_corr_mix[k]>maxJetPt_mix) maxJetPt_mix=jtpt_corr_mix[k];
        }

        tracktree_mix->GetEntry(vmix_index[iminbias]);
        // bool atleastonetrack = false;
        for (int ijet = 0; ijet < njet; ijet++) {
          // cout<<jetpt[ijet]<<" "<<jeteta[ijet]<<" "<< acos(cos(jetphi[ijet] - phoPhi[0]))<<endl;
          if( jetpt[ijet]<40 ) continue; //jet pt Cut
          if( fabs(jeteta[ijet]) > 1.6) continue; //jeteta Cut
          if( jetID[ijet]==0 ) continue; //redundant in this skim (all true)
          if( acos(cos(jetphi[ijet] - phoPhi[0])) < 7 * pi / 8 ) continue;

          // cout<<"foundajet: "<<jetpt[ijet]<<endl;
          for(int itrkmix = 0 ; itrkmix < nTrk_mix_ ; ++itrkmix)
          {
            if(trkPt_mix_[itrkmix]<1 || trkPt_mix_[itrkmix]>300 || fabs(trkEta_mix_[itrkmix])>2.4 ) continue;

            float dphi = acos( cos(jetphi[ijet] - trkPhi_mix_[itrkmix]));
            float deta = fabs( jeteta[ijet] - trkEta_mix_[itrkmix ]);
            float dr = sqrt((dphi*dphi)+(deta*deta));
            if(dr>0.3) continue; // only save mix tracks around jet cone

            if(highPurity_mix_[itrkmix]!=1) continue;
            if(trkPtError_mix_[itrkmix]/trkPt_mix_[itrkmix]>0.1 || TMath::Abs(trkDz1_mix_[itrkmix]/trkDzError1_mix_[itrkmix])>3 || TMath::Abs(trkDxy1_mix_[itrkmix]/trkDxyError1_mix_[itrkmix])>3) continue;
            if(trkChi2_mix_[itrkmix]/(float)trkNdof_mix_[itrkmix]/(float)trkNlayer_mix_[itrkmix]>0.15) continue;
            if(trkNHit_mix_[itrkmix]<11 && trkPt_mix_[itrkmix]>0.7) continue;
            if((maxJetPt_mix>50 && trkPt_mix_[itrkmix]>maxJetPt_mix) || (maxJetPt_mix<50 && trkPt_mix_[itrkmix]>50)) continue;

            float Et = (pfHcal_mix_[itrkmix]+pfEcal_mix_[itrkmix])/TMath::CosH(trkEta_mix_[itrkmix]);
            if(!(trkPt_mix_[itrkmix]<20 || (Et>0.5*trkPt_mix_[itrkmix]))) continue;


            float trkweight_mix = 0;
            if(is_pp) trkweight_mix = getTrkWeightMix(trkCorr,itrkmix,0);
            else trkweight_mix = getTrkWeightMix(trkCorr,itrkmix,vmix_hiBin[iminbias]);
            trkPt_mix[ntracks_mix] = trkPt_mix_[itrkmix];   //[nTrk_mix]
            trkEta_mix[ntracks_mix] = trkEta_mix_[itrkmix];   //[nTrk_mix]
            trkPhi_mix[ntracks_mix] = trkPhi_mix_[itrkmix];   //[nTrk_mix]
            trkWeight_mix[ntracks_mix] = trkweight_mix;
            ntracks_mix++;
            // atleastonetrack = true;
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
        if(nmix >= 10) break; // done mixing
      }
      minbiasstart = minbiasend;
      nTrk_mix = ntracks_mix;
    }
    cout<<nTrk_mix<<endl;
    if(nTrk_mix==0)
    {
      // cout<<"here"<<endl;
      // break;
    }
    //cout<<"after: "<<jetpt[0]<<endl;

    bool flagMu = 0; bool flagEle = 0;
    if(flagMu || flagEle) cout<<"nothing"<<endl;

    TLorentzVector muon1, muon2;
    TLorentzVector ele1, ele2;

    for(int i1 = 0; i1 < _nMu; i1++) {

      if(_muPt->at(i1)>leptonptcut && fabs(_muEta->at(i1))<2.4 && goodMuon(i1)) {

        for(int i2 = i1+1; i2 < _nMu; i2++) {

          if(_muPt->at(i2)>leptonptcut && fabs(_muEta->at(i2))<2.4 && goodMuon(i2)) {

            muon1.SetPtEtaPhiM(_muPt->at(i1), _muEta->at(i1), _muPhi->at(i1), 0.105658);
            muon2.SetPtEtaPhiM(_muPt->at(i2), _muEta->at(i2), _muPhi->at(i2), 0.105658);
            TLorentzVector pair = muon1 + muon2;

            if(pair.M()>60 && pair.M()<120) {

              Ztype = 1;
              Zmass = pair.M();
              Zpt = pair.Pt();
              Zrapidity = pair.Rapidity();
              Zeta = pair.Eta();
              Zphi = pair.Phi();
              Zcharge = _muCharge->at(i1) + _muCharge->at(i2);
              flagMu = 1;
              Zlepton1Pt = muon1.Pt();
              Zlepton2Pt = muon2.Pt();
              Zlepton1Eta = muon1.Eta();
              Zlepton2Eta = muon2.Eta();
              Zlepton1Phi = muon1.Phi();
              Zlepton2Phi = muon2.Phi();
              if(_muCharge->at(i1) != _muCharge->at(i2)) {
                mmMass->Fill(pair.M());
                mmPt->Fill(pair.Pt());
                mmY->Fill(pair.Rapidity());
                mmPhi->Fill(pair.Phi());
                nMuPair++;
              }
              else {
                mmMassSS->Fill(pair.M());
              }

            }
          }
        }
      }
    } //end of muon loop

    for(int i1 = 0; i1 < _nEle; i1++) {

      if(_elePt->at(i1)>leptonptcut && fabs(_eleSCEta->at(i1))<2.5 && goodElectron(i1,is_pp) && (fabs(_eleSCEta->at(i1))<1.4442 || fabs(_eleSCEta->at(i1))>1.566)) {

        for(int i2 = i1+1; i2 < _nEle; i2++) {

          if(_elePt->at(i2)>leptonptcut && fabs(_eleSCEta->at(i2))<2.5 && goodElectron(i2,is_pp) && (fabs(_eleSCEta->at(i2))<1.4442 || fabs(_eleSCEta->at(i2))>1.566)) {

            ele1.SetPtEtaPhiM(_elePt->at(i1), _eleEta->at(i1), _elePhi->at(i1), 0.000511);
            ele2.SetPtEtaPhiM(_elePt->at(i2), _eleEta->at(i2), _elePhi->at(i2), 0.000511);
            TLorentzVector pair = ele1 + ele2;

            if(pair.M()>60 && pair.M()<120) {

              Ztype = 2;
              Zmass = pair.M();
              Zpt = pair.Pt();
              Zrapidity = pair.Rapidity();
              Zeta = pair.Eta();
              Zphi = pair.Phi();
              Zcharge = _eleCharge->at(i1) + _eleCharge->at(i2);
              flagEle = 1;
              Zlepton1Pt = ele1.Pt();
              Zlepton2Pt = ele2.Pt();
              Zlepton1Eta = ele1.Eta();
              Zlepton2Eta = ele2.Eta();
              Zlepton1Phi = ele1.Phi();
              Zlepton2Phi = ele2.Phi();

              if(_eleCharge->at(i1) != _eleCharge->at(i2)) {
                eeMass->Fill(pair.M());
                eePt->Fill(pair.Pt());
                eeY->Fill(pair.Rapidity());
                eePhi->Fill(pair.Phi());
                nElPair++;
              }
              else {
                eeMassSS->Fill(pair.M());
              }

            }
          }
        }
      }
    } //end of electron loop
    // cout<<"end z loop "<<_nEle<<" "<<_nMu<<endl;
    // if( flagEle==0 && flagMu==0 ) continue;

    tracktree_->GetEntry(j);

    int ntracks = 0;
    // std::cout<<nTrk_<<std::endl;
    for(int itrk = 0 ; itrk < nTrk_ ; ++itrk)
    {
      // cout<<"itrk "<<itrk<<endl;
      // if((trkMVA_zzz[itrk]<0.5 && trkMVA_[itrk]!=-99) || (int)trkNHit_[itrk]<8 || trkPtError_[itrk]/trkPt_[itrk]>0.3 || fabs(trkDz1_[itrk])/trkDzError1_[itrk]>3 || fabs(trkDxy1_[itrk])/trkDxyError1_[itrk]>3) continue;
      // if((Zlepton1Pt!=-99&&sqrt(pow(Zlepton1Phi- trkPhi_[itrk],2) + pow(Zlepton1Eta- trkEta_[itrk],2))<0.006)) continue; // reject z leptons
      // if((Zlepton2Pt!=-99&&sqrt(pow(Zlepton2Phi- trkPhi_[itrk],2) + pow(Zlepton2Eta- trkEta_[itrk],2))<0.006)) continue; // reject z leptons
      // if(!highPurity_[itrk]) continue;
      // std::cout<<"here"<<std::endl;
      if(trkPt_[itrk]<1 || trkPt_[itrk]>300 || fabs(trkEta_[itrk])>2.4 ) continue;
      if(highPurity_[itrk]!=1) continue;
      if(trkPtError_[itrk]/trkPt_[itrk]>0.1 || TMath::Abs(trkDz1_[itrk]/trkDzError1_[itrk])>3 || TMath::Abs(trkDxy1_[itrk]/trkDxyError1_[itrk])>3) continue;
      if(trkChi2_[itrk]/(float)trkNdof_[itrk]/(float)trkNlayer_[itrk]>0.15) continue;
      if(trkNHit_[itrk]<11 && trkPt_[itrk]>0.7) continue;
      if((maxJetPt>50 && trkPt_[itrk]>maxJetPt) || (maxJetPt<50 && trkPt_[itrk]>50)) continue;

      float Et = (pfHcal_[itrk]+pfEcal_[itrk])/TMath::CosH(trkEta_[itrk]);
      if(!(trkPt_[itrk]<20 || (Et>0.5*trkPt_[itrk]))) continue;
      // cout<<"itrk "<<itrk<<endl;

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
      //if((trkPt[itrk]-2*trkPtError[itrk])*TMath::CosH(trkEta[itrk])>15 && (trkPt[itrk]-2*trkPtError[itrk])*TMath::CosH(trkEta[itrk])>pfHcal[itrk]+pfEcal[itrk]) continue;} //Calo Matching
    }
    // cout<<"end track loop "<<ntracks<<endl;
    nTrk=ntracks;
    ztree->Fill();

  } //end of loop over events


  fout->cd();
  ztree->Write();
  // injetTree->Write();
  // trackTree->Write();
  fout->Write();
  fout->Close();

}

int main(int argc, char *argv[])
{
  if((argc < 3))
  {
    std::cout << "Usage: ./gammajetSkim.exe <inputfile> <outputfile> [jetname] [is_pp] [mcweight] [startindex] [endindex]" << std::endl;
    return 1;
  }
  if(argc==3)  gammajetSkim(argv[1], argv[2]); //basic input output files
  if(argc==4)  gammajetSkim(argv[1], argv[2], argv[3]); //add jet name
  if(argc==5)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4])); //add is_pp
  if(argc==6)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5])); //add custom mcweight
  if(argc==7)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6]); //add minbias mix
  if(argc==8)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7])); //add startindex
  if(argc==9)  gammajetSkim(argv[1], argv[2], argv[3], std::atoi(argv[4]),std::atof(argv[5]),argv[6],std::atoi(argv[7]),std::atoi(argv[8])); //add endindex
  return 0;
}
