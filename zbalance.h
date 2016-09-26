//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 16 11:49:15 2015 by ROOT version 6.02/10
// from TTree ztree/Z boson candidate events
// found on file: test.root
//////////////////////////////////////////////////////////

#ifndef ztree_h
#define ztree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ztree {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  TTree          *mix_fChain;
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
   Int_t           nlooped;
   Int_t           nmix;
   Float_t         dvz_mix[10];   //[nmix]
   Int_t           dhiBin_mix[10];   //[nmix]
   Float_t         dhiEvtPlanes_mix[10];   //[nmix]
   Int_t           nTrk_mix;
   Float_t         trkPt_mix[1000];   //[nTrk_mix]
   Float_t         trkPhi_mix[1000];   //[nTrk_mix]
   Float_t         trkEta_mix[1000];   //[nTrk_mix]
   Float_t         trkWeight_mix[1000];   //[nTrk_mix]
   Float_t         trkFromEv_mix[1000];   //[nTrk_mix]

   Float_t         trkWeight[5000];   //[nTrk]
  Int_t           run;
  Int_t           event;
  Int_t           lumis;
  Int_t           hiBin;
  Float_t         vz;
  // Int_t           Ztype;
  // Float_t         Zmass;
  Float_t         weight;
  // Float_t         Zpt;
  // Float_t         Zeta;
  // Float_t         Zphi;
  // Float_t         Zrapidity;
  // Float_t         Zlepton1Pt;
  // Float_t         Zlepton2Pt;
  // Float_t         Zlepton1Eta;
  // Float_t         Zlepton2Eta;
  // Float_t         Zlepton1Phi;
  // Float_t         Zlepton2Phi;
  // Int_t           Zcharge;

  Int_t           mult;
  Float_t         pt[10000];   //[mult]
  Float_t         eta[10000];   //[mult]
  Float_t         phi[10000];   //[mult]
  Int_t           pdg[10000];   //[mult]
  Int_t           chg[10000];   //[mult]
  Int_t           matchingID[10000];   //[mult]
  Int_t           sube[10000];   //[mult]

  Int_t           mult_mix;
  Float_t         pt_mix[10000];   //[mult]
  Float_t         eta_mix[10000];   //[mult]
  Float_t         phi_mix[10000];   //[mult]
  Int_t           pdg_mix[10000];   //[mult]
  Int_t           chg_mix[10000];   //[mult]

  Int_t           nMC;
  Int_t           mcPID[392];   //[nMC]
  Int_t           mcStatus[392];   //[nMC]
  Float_t         mcPt[392];   //[nMC]
  Float_t         mcEt[392];   //[nMC]
  Float_t         mcEta[392];   //[nMC]
  Float_t         mcPhi[392];   //[nMC]
  Float_t         mcMomPt[392];   //[nMC]
  Float_t         mcMomEta[392];   //[nMC]
  Float_t         mcMomPhi[392];   //[nMC]
  Int_t           mcMomPID[392];   //[nMC]

  Int_t           njet;
  Float_t         jetpt[40];   //[njet]
  Float_t         jeteta[40];   //[njet]
  Float_t         jetphi[40];   //[njet]
  Int_t           jetID[40];   //[njet]
  Float_t         gjetpt[40];   //[njet]
  Float_t         gjeteta[40];   //[njet]
  Float_t         gjetphi[40];   //[njet]

  Int_t           njet_mix;
  Float_t         rawpt_mix[41];   //[njet_mix]
  Float_t         jetpt_mix[41];   //[njet_mix]
  Float_t         jeteta_mix[41];   //[njet_mix]
  Float_t         jetphi_mix[41];   //[njet_mix]
  Int_t           nmixEv_mix[41];   //[njet_mix]
  Int_t           jetID_mix[41];   //[njet_mix]
  Float_t         neutralSum_mix[41];   //[njet_mix]
  Float_t         chargedSum_mix[41];   //[njet_mix]
  Int_t           chargedN_mix[41];   //[njet_mix]
  Int_t           photonN_mix[41];   //[njet_mix]
  Int_t           neutralN_mix[41];   //[njet_mix]
  Int_t           eN_mix[41];   //[njet_mix]
  Int_t           muN_mix[41];   //[njet_mix]
  Float_t         chargedMax_mix[41];   //[njet_mix]
  Float_t         photonSum_mix[41];   //[njet_mix]
  Float_t         eSum_mix[41];   //[njet_mix]

  Int_t           nTrk;
  Float_t         trkPt[5000];   //[nTrk]
  Float_t         trkPtError[5000];   //[nTrk]
  UChar_t         trkNHit[5000];   //[nTrk]
  UChar_t         trkNlayer[5000];   //[nTrk]
  Float_t         trkEta[5000];   //[nTrk]
  Float_t         trkPhi[5000];   //[nTrk]
  Int_t           trkCharge[5000];   //[nTrk]
  UChar_t         trkNVtx[5000];   //[nTrk]
  Bool_t          highPurity[5000];   //[nTrk]
  Bool_t          tight[5000];   //[nTrk]
  Bool_t          loose[5000];   //[nTrk]
  Float_t         trkChi2[5000];   //[nTrk]
  UChar_t         trkNdof[5000];   //[nTrk]
  Float_t         trkDxy1[5000];   //[nTrk]
  Float_t         trkDxyError1[5000];   //[nTrk]
  Float_t         trkDz1[5000];   //[nTrk]
  Float_t         trkDzError1[5000];   //[nTrk]
  Bool_t          trkFake[5000];   //[nTrk]
  UChar_t         trkAlgo[5000];   //[nTrk]
  UChar_t         trkOriginalAlgo[5000];   //[nTrk]
  Float_t         trkMVA[5000];   //[nTrk]
  Int_t           pfType[5000];   //[nTrk]
  Float_t         pfCandPt[5000];   //[nTrk]
  Float_t         pfEcal[5000];   //[nTrk]
  Float_t         pfHcal[5000];   //[nTrk]
  Int_t    nPho;
  Float_t  phoE[1];   //_nPho
  Float_t  phoEt[1];   //_nPho
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
  Float_t  phoCorr[1];   //_nPho
  Int_t    pho_genMatchedIndex[1];   //[nPho]
  Float_t  phoSigmaIEtaIEta_2012[1];   //[nPho]
   Int_t           phoNoise[1];   //[nPho]

  // List of branches
   TBranch        *b_nlooped;   //!
   TBranch        *b_nmix;   //!
   TBranch        *b_dvz_mix;   //!
   TBranch        *b_dhiBin_mix;   //!
   TBranch        *b_dhiEvtPlanes_mix;   //!
   TBranch        *b_nTrk_mix;   //!
   TBranch        *b_trkPt_mix;   //!
   TBranch        *b_trkPhi_mix;   //!
   TBranch        *b_trkEta_mix;   //!
   TBranch        *b_trkWeight_mix;   //!
   TBranch        *b_trkFromEv_mix;   //!
  TBranch        *b_trkWeight;   //!
  TBranch        *b_run;   //!
  TBranch        *b_event;   //!
  TBranch        *b_lumis;   //!
  TBranch        *b_hiBin;   //!
  TBranch        *b_vz;   //!
  // TBranch        *b_Ztype;   //!
  // TBranch        *b_Zmass;   //!
  TBranch        *b_weight;   //!
  // TBranch        *b_Zpt;   //!
  // TBranch        *b_Zeta;   //!
  // TBranch        *b_Zphi;   //!
  // TBranch        *b_Zrapidity;   //!
  // TBranch        *b_Zlepton1Pt;   //!
  // TBranch        *b_Zlepton2Pt;   //!
  // TBranch        *b_Zlepton1Eta;   //!
  // TBranch        *b_Zlepton2Eta;   //!
  // TBranch        *b_Zlepton1Phi;   //!
  // TBranch        *b_Zlepton2Phi;   //!
  // TBranch        *b_Zcharge;   //!
  TBranch        *b_mult;   //!
  TBranch        *b_pt;   //!
  TBranch        *b_eta;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_chg;   //!
  TBranch        *b_matchingID;   //!
  TBranch        *b_sube;   //!
  TBranch        *b_mult_mix;   //!
  TBranch        *b_pt_mix;   //!
  TBranch        *b_eta_mix;   //!
  TBranch        *b_phi_mix;   //!
  TBranch        *b_pdg_mix;   //!
  TBranch        *b_chg_mix;   //!

  TBranch        *b_njet;   //!
  TBranch        *b_jetpt;   //!
  TBranch        *b_jeteta;   //!
  TBranch        *b_jetphi;   //!
  TBranch        *b_gjetpt;   //!
  TBranch        *b_gjeteta;   //!
  TBranch        *b_gjetphi;   //!
  TBranch        *b_jetID;   //!

  TBranch        *b_njet_mix;   //!
  TBranch        *b_rawpt_mix;   //!
  TBranch        *b_jetpt_mix;   //!
  TBranch        *b_jeteta_mix;   //!
  TBranch        *b_jetphi_mix;   //!
  TBranch        *b_nmixEv_mix;   //!
  TBranch        *b_jetID_mix;   //!
  TBranch        *b_neutralSum_mix;   //!
  TBranch        *b_chargedSum_mix;   //!
  TBranch        *b_chargedN_mix;   //!
  TBranch        *b_photonN_mix;   //!
  TBranch        *b_neutralN_mix;   //!
  TBranch        *b_eN_mix;   //!
  TBranch        *b_muN_mix;   //!
  TBranch        *b_chargedMax_mix;   //!
  TBranch        *b_photonSum_mix;   //!
  TBranch        *b_eSum_mix;   //!

  TBranch        *b_nTrk;   //!
  TBranch        *b_trkPt;   //!
  TBranch        *b_trkPtError;   //!
  TBranch        *b_trkNHit;   //!
  TBranch        *b_trkNlayer;   //!
  TBranch        *b_trkEta;   //!
  TBranch        *b_trkPhi;   //!
  TBranch        *b_trkCharge;   //!
  TBranch        *b_trkNVtx;   //!
  TBranch        *b_highPurity;   //!
  TBranch        *b_tight;   //!
  TBranch        *b_loose;   //!
  TBranch        *b_trkChi2;   //!
  TBranch        *b_trkNdof;   //!
  TBranch        *b_trkDxy1;   //!
  TBranch        *b_trkDxyError1;   //!
  TBranch        *b_trkDz1;   //!
  TBranch        *b_trkDzError1;   //!
  TBranch        *b_trkFake;   //!
  TBranch        *b_trkAlgo;   //!
  TBranch        *b_trkOriginalAlgo;   //!
  TBranch        *b_trkMVA;   //!
  TBranch        *b_pfType;   //!
  TBranch        *b_pfCandPt;   //!
  TBranch        *b_pfEcal;   //!
  TBranch        *b_pfHcal;   //!
   TBranch        *b_phoSigmaIEtaIEta_2012;   //!
   TBranch        *b_phoNoise;   //!


  TBranch   *b_nPho;
  TBranch   *b_phoE;
  TBranch   *b_phoEt;
  TBranch   *b_phoEta;
  TBranch   *b_phoPhi;
  TBranch   *b_phoSCE;
  TBranch   *b_phoSCRawE;
  TBranch   *b_phoESEn;
  TBranch   *b_phoSCEta;
  TBranch   *b_phoSCPhi;
  TBranch   *b_phoSCEtaWidth;
  TBranch   *b_phoSCPhiWidth;
  TBranch   *b_phoSCBrem;
  TBranch   *b_phohasPixelSeed;
  TBranch   *b_phoR9;
  TBranch   *b_phoHoverE;
  TBranch   *b_phoSigmaIEtaIEta;
  TBranch   *b_pho_ecalClusterIsoR2;
  TBranch   *b_pho_ecalClusterIsoR3;
  TBranch   *b_pho_ecalClusterIsoR4;
  TBranch   *b_pho_ecalClusterIsoR5;
  TBranch   *b_pho_hcalRechitIsoR1;
  TBranch   *b_pho_hcalRechitIsoR2;
  TBranch   *b_pho_hcalRechitIsoR3;
  TBranch   *b_pho_hcalRechitIsoR4;
  TBranch   *b_pho_hcalRechitIsoR5;
  TBranch   *b_pho_trackIsoR1PtCut20;
  TBranch   *b_pho_trackIsoR2PtCut20;
  TBranch   *b_pho_trackIsoR3PtCut20;
  TBranch   *b_pho_trackIsoR4PtCut20;
  TBranch   *b_pho_trackIsoR5PtCut20;
  TBranch   *b_pho_swissCrx;
  TBranch   *b_pho_seedTime;
  TBranch   *b_pho_genMatchedIndex;   //!
  TBranch   *b_pfcIso1;
  TBranch   *b_pfcIso2;
  TBranch   *b_pfcIso3;
  TBranch   *b_pfcIso4;
  TBranch   *b_pfcIso5;
  TBranch   *b_pfpIso1;
  TBranch   *b_pfpIso2;
  TBranch   *b_pfpIso3;
  TBranch   *b_pfpIso4;
  TBranch   *b_pfpIso5;
  TBranch   *b_pfnIso1;
  TBranch   *b_pfnIso2;
  TBranch   *b_pfnIso3;
  TBranch   *b_pfnIso4;
  TBranch   *b_pfnIso5;
  TBranch   *b_phoCorr;
  TBranch        *b_nMC;   //!
  TBranch        *b_mcPID;   //!
  TBranch        *b_mcStatus;   //!
  TBranch        *b_mcPt;   //!
  TBranch        *b_mcEt;   //!
  TBranch        *b_mcEta;   //!
  TBranch        *b_mcPhi;   //!
  TBranch        *b_mcMomPt;   //!
  TBranch        *b_mcMomEta;   //!
  TBranch        *b_mcMomPhi;   //!
  TBranch        *b_mcMomPID;   //!



  ztree(std::string thisfilename);
  virtual ~ztree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual Long64_t LoadTreeMix(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     ffgammajet(std::string outfname, int centmin = -1, int centmax = 200, float phoetmin = 100, float phoetmax = 300, int jetptcut=30, std::string gen="");
  virtual float    jettrk_dr(int itrk, int ijet);
  virtual float    refconetrk_dr(int itrk, int ijet);
  virtual float    genjettrk_dr(int itrk, int ijet);
  virtual float    genrefconetrk_dr(int itrk, int ijet);
  virtual float    genjetrecotrk_dr(int itrk, int ijet);
  virtual float    genrefconerecotrk_dr(int itrk, int ijet);
  virtual float    recojetgentrk_dr(int itrk, int ijet);
  virtual float    recorefconegentrk_dr(int itrk, int ijet);
  // virtual void     MixedEvent(std::string outfname);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ztree_cxx
ztree::ztree(std::string thisfilename) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  TFile *f = TFile::Open(thisfilename.data());
  TTree * tree = (TTree*) f->Get("ztree");
  Init(tree);
}

ztree::~ztree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ztree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ztree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

Long64_t ztree::LoadTreeMix(Long64_t entry)
{
  // Set the environment to read one entry
  if (!mix_fChain) return -5;
  Long64_t centry = mix_fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (mix_fChain->GetTreeNumber() != fCurrent) {
    fCurrent = mix_fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ztree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nlooped", &nlooped, &b_nlooped);
   fChain->SetBranchAddress("nmix", &nmix, &b_nmix);
   fChain->SetBranchAddress("dvz_mix", dvz_mix, &b_dvz_mix);
   fChain->SetBranchAddress("dhiBin_mix", dhiBin_mix, &b_dhiBin_mix);
   fChain->SetBranchAddress("dhiEvtPlanes_mix", dhiEvtPlanes_mix, &b_dhiEvtPlanes_mix);
   fChain->SetBranchAddress("nTrk_mix", &nTrk_mix, &b_nTrk_mix);
   fChain->SetBranchAddress("trkPt_mix", trkPt_mix, &b_trkPt_mix);
   fChain->SetBranchAddress("trkPhi_mix", trkPhi_mix, &b_trkPhi_mix);
   fChain->SetBranchAddress("trkEta_mix", trkEta_mix, &b_trkEta_mix);
   fChain->SetBranchAddress("trkWeight_mix", trkWeight_mix, &b_trkWeight_mix);
   fChain->SetBranchAddress("trkFromEv_mix", trkFromEv_mix, &b_trkFromEv_mix);
  fChain->SetBranchAddress("trkWeight", trkWeight, &b_trkWeight);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
  fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
  fChain->SetBranchAddress("vz", &vz, &b_vz);
  // fChain->SetBranchAddress("Ztype", &Ztype, &b_Ztype);
  // fChain->SetBranchAddress("Zmass", &Zmass, &b_Zmass);
  fChain->SetBranchAddress("weight", &weight, &b_weight);
  // fChain->SetBranchAddress("Zpt", &Zpt, &b_Zpt);
  // fChain->SetBranchAddress("Zeta", &Zeta, &b_Zeta);
  // fChain->SetBranchAddress("Zphi", &Zphi, &b_Zphi);
  // fChain->SetBranchAddress("Zrapidity", &Zrapidity, &b_Zrapidity);
  // fChain->SetBranchAddress("Zlepton1Pt", &Zlepton1Pt, &b_Zlepton1Pt);
  // fChain->SetBranchAddress("Zlepton2Pt", &Zlepton2Pt, &b_Zlepton2Pt);
  // fChain->SetBranchAddress("Zlepton1Eta", &Zlepton1Eta, &b_Zlepton1Eta);
  // fChain->SetBranchAddress("Zlepton2Eta", &Zlepton2Eta, &b_Zlepton2Eta);
  // fChain->SetBranchAddress("Zlepton1Phi", &Zlepton1Phi, &b_Zlepton1Phi);
  // fChain->SetBranchAddress("Zlepton2Phi", &Zlepton2Phi, &b_Zlepton2Phi);
  // fChain->SetBranchAddress("Zcharge", &Zcharge, &b_Zcharge);
  fChain->SetBranchAddress("mult", &mult, &b_mult);
  fChain->SetBranchAddress("pt", pt, &b_pt);
  fChain->SetBranchAddress("eta", eta, &b_eta);
  fChain->SetBranchAddress("phi", phi, &b_phi);
  fChain->SetBranchAddress("pdg", pdg, &b_pdg);
  fChain->SetBranchAddress("chg", chg, &b_chg);
  fChain->SetBranchAddress("matchingID", matchingID, &b_matchingID);
  fChain->SetBranchAddress("sube", sube, &b_sube);
  fChain->SetBranchAddress("mult_mix", &mult_mix, &b_mult_mix);
  fChain->SetBranchAddress("pt_mix", pt_mix, &b_pt_mix);
  fChain->SetBranchAddress("eta_mix", eta_mix, &b_eta_mix);
  fChain->SetBranchAddress("phi_mix", phi_mix, &b_phi_mix);
  fChain->SetBranchAddress("pdg_mix", pdg_mix, &b_pdg_mix);
  fChain->SetBranchAddress("chg_mix", chg_mix, &b_chg_mix);

  fChain->SetBranchAddress("njet", &njet, &b_njet);
  fChain->SetBranchAddress("jetpt", jetpt, &b_jetpt);
  fChain->SetBranchAddress("jeteta", jeteta, &b_jeteta);
  fChain->SetBranchAddress("jetphi", jetphi, &b_jetphi);
  fChain->SetBranchAddress("jetID", jetID, &b_jetID);
  fChain->SetBranchAddress("gjetpt", gjetpt, &b_gjetpt);
  fChain->SetBranchAddress("gjeteta", gjeteta, &b_gjeteta);
  fChain->SetBranchAddress("gjetphi", gjetphi, &b_gjetphi);

  fChain->SetBranchAddress("njet_mix", &njet_mix, &b_njet_mix);
  fChain->SetBranchAddress("rawpt_mix", rawpt_mix, &b_rawpt_mix);
  fChain->SetBranchAddress("jetpt_mix", jetpt_mix, &b_jetpt_mix);
  fChain->SetBranchAddress("jeteta_mix", jeteta_mix, &b_jeteta_mix);
  fChain->SetBranchAddress("jetphi_mix", jetphi_mix, &b_jetphi_mix);
  fChain->SetBranchAddress("nmixEv_mix", nmixEv_mix, &b_nmixEv_mix);
  fChain->SetBranchAddress("jetID_mix", jetID_mix, &b_jetID_mix);
  fChain->SetBranchAddress("neutralSum_mix", neutralSum_mix, &b_neutralSum_mix);
  fChain->SetBranchAddress("chargedSum_mix", chargedSum_mix, &b_chargedSum_mix);
  fChain->SetBranchAddress("chargedN_mix", chargedN_mix, &b_chargedN_mix);
  fChain->SetBranchAddress("photonN_mix", photonN_mix, &b_photonN_mix);
  fChain->SetBranchAddress("neutralN_mix", neutralN_mix, &b_neutralN_mix);
  fChain->SetBranchAddress("eN_mix", eN_mix, &b_eN_mix);
  fChain->SetBranchAddress("muN_mix", muN_mix, &b_muN_mix);
  fChain->SetBranchAddress("chargedMax_mix", chargedMax_mix, &b_chargedMax_mix);
  fChain->SetBranchAddress("photonSum_mix", photonSum_mix, &b_photonSum_mix);
  fChain->SetBranchAddress("eSum_mix", eSum_mix, &b_eSum_mix);

  fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
  fChain->SetBranchAddress("trkPt", trkPt, &b_trkPt);
  fChain->SetBranchAddress("trkPtError", trkPtError, &b_trkPtError);
  fChain->SetBranchAddress("trkNHit", trkNHit, &b_trkNHit);
  fChain->SetBranchAddress("trkNlayer", trkNlayer, &b_trkNlayer);
  fChain->SetBranchAddress("trkEta", trkEta, &b_trkEta);
  fChain->SetBranchAddress("trkPhi", trkPhi, &b_trkPhi);
  fChain->SetBranchAddress("trkCharge", trkCharge, &b_trkCharge);
  fChain->SetBranchAddress("trkNVtx", trkNVtx, &b_trkNVtx);
  fChain->SetBranchAddress("highPurity", highPurity, &b_highPurity);
  fChain->SetBranchAddress("tight", tight, &b_tight);
  fChain->SetBranchAddress("loose", loose, &b_loose);
  fChain->SetBranchAddress("trkChi2", trkChi2, &b_trkChi2);
  fChain->SetBranchAddress("trkNdof", trkNdof, &b_trkNdof);
  fChain->SetBranchAddress("trkDxy1", trkDxy1, &b_trkDxy1);
  fChain->SetBranchAddress("trkDxyError1", trkDxyError1, &b_trkDxyError1);
  fChain->SetBranchAddress("trkDz1", trkDz1, &b_trkDz1);
  fChain->SetBranchAddress("trkDzError1", trkDzError1, &b_trkDzError1);
  fChain->SetBranchAddress("trkFake", trkFake, &b_trkFake);
  fChain->SetBranchAddress("trkAlgo", trkAlgo, &b_trkAlgo);
  fChain->SetBranchAddress("trkOriginalAlgo", trkOriginalAlgo, &b_trkOriginalAlgo);
  fChain->SetBranchAddress("trkMVA", trkMVA, &b_trkMVA);
  fChain->SetBranchAddress("pfType", pfType, &b_pfType);
  fChain->SetBranchAddress("pfCandPt", pfCandPt, &b_pfCandPt);
  fChain->SetBranchAddress("pfEcal", pfEcal, &b_pfEcal);
  fChain->SetBranchAddress("pfHcal", pfHcal, &b_pfHcal);

  fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
  fChain->SetBranchAddress("phoE", phoE, &b_phoE);
  fChain->SetBranchAddress("phoEt", phoEt, &b_phoEt);
  fChain->SetBranchAddress("phoEta", phoEta, &b_phoEta);
  fChain->SetBranchAddress("phoPhi", phoPhi, &b_phoPhi);
  fChain->SetBranchAddress("phoSCE", phoSCE, &b_phoSCE);
  fChain->SetBranchAddress("phoSCRawE", phoSCRawE, &b_phoSCRawE);
  fChain->SetBranchAddress("phoESEn", phoESEn, &b_phoESEn);
  fChain->SetBranchAddress("phoSCEta", phoSCEta, &b_phoSCEta);
  fChain->SetBranchAddress("phoSCPhi", phoSCPhi, &b_phoSCPhi);
  fChain->SetBranchAddress("phoSCEtaWidth", phoSCEtaWidth, &b_phoSCEtaWidth);
  fChain->SetBranchAddress("phoSCPhiWidth", phoSCPhiWidth, &b_phoSCPhiWidth);
  fChain->SetBranchAddress("phoSCBrem", phoSCBrem, &b_phoSCBrem);
  fChain->SetBranchAddress("phohasPixelSeed", phohasPixelSeed, &b_phohasPixelSeed);
  fChain->SetBranchAddress("phoR9", phoR9, &b_phoR9);
  fChain->SetBranchAddress("phoHoverE", phoHoverE, &b_phoHoverE);
  fChain->SetBranchAddress("phoSigmaIEtaIEta", phoSigmaIEtaIEta, &b_phoSigmaIEtaIEta);
  fChain->SetBranchAddress("phoSigmaIEtaIEta_2012", phoSigmaIEtaIEta_2012, &b_phoSigmaIEtaIEta_2012);
  fChain->SetBranchAddress("phoNoise", phoNoise, &b_phoNoise);

  fChain->SetBranchAddress("pho_ecalClusterIsoR2", pho_ecalClusterIsoR2, &b_pho_ecalClusterIsoR2);
  fChain->SetBranchAddress("pho_ecalClusterIsoR3", pho_ecalClusterIsoR3, &b_pho_ecalClusterIsoR3);
  fChain->SetBranchAddress("pho_ecalClusterIsoR4", pho_ecalClusterIsoR4, &b_pho_ecalClusterIsoR4);
  fChain->SetBranchAddress("pho_ecalClusterIsoR5", pho_ecalClusterIsoR5, &b_pho_ecalClusterIsoR5);
  fChain->SetBranchAddress("pho_hcalRechitIsoR1", pho_hcalRechitIsoR1, &b_pho_hcalRechitIsoR1);
  fChain->SetBranchAddress("pho_hcalRechitIsoR2", pho_hcalRechitIsoR2, &b_pho_hcalRechitIsoR2);
  fChain->SetBranchAddress("pho_hcalRechitIsoR3", pho_hcalRechitIsoR3, &b_pho_hcalRechitIsoR3);
  fChain->SetBranchAddress("pho_hcalRechitIsoR4", pho_hcalRechitIsoR4, &b_pho_hcalRechitIsoR4);
  fChain->SetBranchAddress("pho_hcalRechitIsoR5", pho_hcalRechitIsoR5, &b_pho_hcalRechitIsoR5);
  fChain->SetBranchAddress("pho_trackIsoR1PtCut20", pho_trackIsoR1PtCut20, &b_pho_trackIsoR1PtCut20);
  fChain->SetBranchAddress("pho_trackIsoR2PtCut20", pho_trackIsoR2PtCut20, &b_pho_trackIsoR2PtCut20);
  fChain->SetBranchAddress("pho_trackIsoR3PtCut20", pho_trackIsoR3PtCut20, &b_pho_trackIsoR3PtCut20);
  fChain->SetBranchAddress("pho_trackIsoR4PtCut20", pho_trackIsoR4PtCut20, &b_pho_trackIsoR4PtCut20);
  fChain->SetBranchAddress("pho_trackIsoR5PtCut20", pho_trackIsoR5PtCut20, &b_pho_trackIsoR5PtCut20);
  fChain->SetBranchAddress("pho_swissCrx", pho_swissCrx, &b_pho_swissCrx);
  fChain->SetBranchAddress("pho_seedTime", pho_seedTime, &b_pho_seedTime);
  fChain->SetBranchAddress("pho_genMatchedIndex", pho_genMatchedIndex, &b_pho_genMatchedIndex);
  fChain->SetBranchAddress("pfcIso1", pfcIso1, &b_pfcIso1);
  fChain->SetBranchAddress("pfcIso2", pfcIso2, &b_pfcIso2);
  fChain->SetBranchAddress("pfcIso3", pfcIso3, &b_pfcIso3);
  fChain->SetBranchAddress("pfcIso4", pfcIso4, &b_pfcIso4);
  fChain->SetBranchAddress("pfcIso5", pfcIso5, &b_pfcIso5);
  fChain->SetBranchAddress("pfpIso1", pfpIso1, &b_pfpIso1);
  fChain->SetBranchAddress("pfpIso2", pfpIso2, &b_pfpIso2);
  fChain->SetBranchAddress("pfpIso3", pfpIso3, &b_pfpIso3);
  fChain->SetBranchAddress("pfpIso4", pfpIso4, &b_pfpIso4);
  fChain->SetBranchAddress("pfpIso5", pfpIso5, &b_pfpIso5);
  fChain->SetBranchAddress("pfnIso1", pfnIso1, &b_pfnIso1);
  fChain->SetBranchAddress("pfnIso2", pfnIso2, &b_pfnIso2);
  fChain->SetBranchAddress("pfnIso3", pfnIso3, &b_pfnIso3);
  fChain->SetBranchAddress("pfnIso4", pfnIso4, &b_pfnIso4);
  fChain->SetBranchAddress("pfnIso5", pfnIso5, &b_pfnIso5);
  fChain->SetBranchAddress("phoCorr", phoCorr, &b_phoCorr);
  fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
  fChain->SetBranchAddress("mcPID", mcPID, &b_mcPID);
  fChain->SetBranchAddress("mcStatus", mcStatus, &b_mcStatus);
  fChain->SetBranchAddress("mcPt", mcPt, &b_mcPt);
  fChain->SetBranchAddress("mcEt", mcEt, &b_mcEt);
  fChain->SetBranchAddress("mcEta", mcEta, &b_mcEta);
  fChain->SetBranchAddress("mcPhi", mcPhi, &b_mcPhi);
  fChain->SetBranchAddress("mcMomPt", mcMomPt, &b_mcMomPt);
  fChain->SetBranchAddress("mcMomEta", mcMomEta, &b_mcMomEta);
  fChain->SetBranchAddress("mcMomPhi", mcMomPhi, &b_mcMomPhi);
  fChain->SetBranchAddress("mcMomPID", mcMomPID, &b_mcMomPID);

  Notify();
}


Bool_t ztree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ztree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t ztree::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef ztree_cxx
