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
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumis;
   Int_t           hiBin;
   Int_t           Ztype;
   Float_t         Zmass;
   Float_t         weight;
   Float_t         Zpt;
   Float_t         Zeta;
   Float_t         Zphi;
   Float_t         Zrapidity;
   Float_t         Zlepton1Pt;
   Float_t         Zlepton2Pt;
   Float_t         Zlepton1Eta;
   Float_t         Zlepton2Eta;
   Float_t         Zlepton1Phi;
   Float_t         Zlepton2Phi;
   Int_t           Zcharge;
   Int_t           njet;
   Float_t         jetpt[11];   //[njet]
   Float_t         jeteta[11];   //[njet]
   Float_t         jetphi[11];   //[njet]
   Int_t           jetID[11];   //[njet]
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
   vector<int>     *eleCharge;
   vector<int>     *eleChargeConsistent;
   vector<float>   *eleEn;
   vector<float>   *eleD0;
   vector<float>   *eleDz;
   vector<float>   *eleD0Err;
   vector<float>   *eleDzErr;
   vector<float>   *eleTrkPt;
   vector<float>   *eleTrkEta;
   vector<float>   *eleTrkPhi;
   vector<int>     *eleTrkCharge;
   vector<float>   *eleTrkChi2;
   vector<float>   *eleTrkNdof;
   vector<float>   *eleTrkNormalizedChi2;
   vector<int>     *eleTrkValidHits;
   vector<int>     *eleTrkLayers;
   vector<float>   *elePt;
   vector<float>   *eleEta;
   vector<float>   *elePhi;
   vector<float>   *eleSCEn;
   vector<float>   *eleESEn;
   vector<float>   *eleSCEta;
   vector<float>   *eleSCPhi;
   vector<float>   *eleSCRawEn;
   vector<float>   *eleSCEtaWidth;
   vector<float>   *eleSCPhiWidth;
   vector<float>   *eleHoverE;
   vector<float>   *eleEoverP;
   vector<float>   *eleEoverPInv;
   vector<float>   *eleBrem;
   vector<float>   *eledEtaAtVtx;
   vector<float>   *eledPhiAtVtx;
   vector<float>   *eleSigmaIEtaIEta;
   vector<float>   *eleSigmaIEtaIEta_2012;
   vector<float>   *eleSigmaIPhiIPhi;
   vector<int>     *eleMissHits;
   vector<float>   *eleESEffSigmaRR;
   vector<float>   *elePFChIso;
   vector<float>   *elePFPhoIso;
   vector<float>   *elePFNeuIso;
   vector<float>   *elePFPUIso;
   vector<float>   *elePFChIso03;
   vector<float>   *elePFPhoIso03;
   vector<float>   *elePFNeuIso03;
   vector<float>   *elePFChIso04;
   vector<float>   *elePFPhoIso04;
   vector<float>   *elePFNeuIso04;
   vector<float>   *eleBC1E;
   vector<float>   *eleBC1Eta;
   vector<float>   *eleBC2E;
   vector<float>   *eleBC2Eta;
   Int_t           nPho;
   vector<float>   *phoE;
   vector<float>   *phoEt;
   vector<float>   *phoEta;
   vector<float>   *phoPhi;
   vector<float>   *phoSCE;
   vector<float>   *phoSCRawE;
   vector<float>   *phoESEn;
   vector<float>   *phoSCEta;
   vector<float>   *phoSCPhi;
   vector<float>   *phoSCEtaWidth;
   vector<float>   *phoSCPhiWidth;
   vector<float>   *phoSCBrem;
   vector<int>     *phohasPixelSeed;
   vector<float>   *phoR9;
   vector<float>   *phoHoverE;
   vector<float>   *phoSigmaIEtaIEta;
   vector<float>   *phoE1x3;
   vector<float>   *phoE2x2;
   vector<float>   *phoE3x3;
   vector<float>   *phoE2x5Max;
   vector<float>   *phoE1x5;
   vector<float>   *phoE2x5;
   vector<float>   *phoE5x5;
   vector<float>   *phoMaxEnergyXtal;
   vector<float>   *phoSigmaEtaEta;
   vector<float>   *phoR1x5;
   vector<float>   *phoR2x5;
   vector<float>   *phoESEffSigmaRR;
   vector<float>   *phoSigmaIEtaIEta_2012;
   vector<float>   *phoSigmaIEtaIPhi_2012;
   vector<float>   *phoSigmaIPhiIPhi_2012;
   vector<float>   *phoE1x3_2012;
   vector<float>   *phoE2x2_2012;
   vector<float>   *phoE3x3_2012;
   vector<float>   *phoE2x5Max_2012;
   vector<float>   *phoE5x5_2012;
   vector<float>   *phoBC1E;
   vector<float>   *phoBC1Eta;
   vector<float>   *phoBC2E;
   vector<float>   *phoBC2Eta;
   vector<float>   *pho_ecalClusterIsoR2;
   vector<float>   *pho_ecalClusterIsoR3;
   vector<float>   *pho_ecalClusterIsoR4;
   vector<float>   *pho_ecalClusterIsoR5;
   vector<float>   *pho_hcalRechitIsoR1;
   vector<float>   *pho_hcalRechitIsoR2;
   vector<float>   *pho_hcalRechitIsoR3;
   vector<float>   *pho_hcalRechitIsoR4;
   vector<float>   *pho_hcalRechitIsoR5;
   vector<float>   *pho_trackIsoR1PtCut20;
   vector<float>   *pho_trackIsoR2PtCut20;
   vector<float>   *pho_trackIsoR3PtCut20;
   vector<float>   *pho_trackIsoR4PtCut20;
   vector<float>   *pho_trackIsoR5PtCut20;
   vector<float>   *pho_swissCrx;
   vector<float>   *pho_seedTime;
   vector<float>   *pfcIso1;
   vector<float>   *pfcIso2;
   vector<float>   *pfcIso3;
   vector<float>   *pfcIso4;
   vector<float>   *pfcIso5;
   vector<float>   *pfpIso1;
   vector<float>   *pfpIso2;
   vector<float>   *pfpIso3;
   vector<float>   *pfpIso4;
   vector<float>   *pfpIso5;
   vector<float>   *pfnIso1;
   vector<float>   *pfnIso2;
   vector<float>   *pfnIso3;
   vector<float>   *pfnIso4;
   vector<float>   *pfnIso5;
   Int_t           nMu;
   vector<float>   *muPt;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<int>     *muCharge;
   vector<int>     *muType;
   vector<int>     *muIsGood;
   vector<float>   *muD0;
   vector<float>   *muDz;
   vector<float>   *muChi2NDF;
   vector<float>   *muInnerD0;
   vector<float>   *muInnerDz;
   vector<int>     *muTrkLayers;
   vector<int>     *muPixelLayers;
   vector<int>     *muPixelHits;
   vector<int>     *muMuonHits;
   vector<int>     *muTrkQuality;
   vector<int>     *muStations;
   vector<float>   *muIsoTrk;
   vector<float>   *muPFChIso;
   vector<float>   *muPFPhoIso;
   vector<float>   *muPFNeuIso;
   vector<float>   *muPFPUIso;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_Ztype;   //!
   TBranch        *b_Zmass;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_Zpt;   //!
   TBranch        *b_Zeta;   //!
   TBranch        *b_Zphi;   //!
   TBranch        *b_Zrapidity;   //!
   TBranch        *b_Zlepton1Pt;   //!
   TBranch        *b_Zlepton2Pt;   //!
   TBranch        *b_Zlepton1Eta;   //!
   TBranch        *b_Zlepton2Eta;   //!
   TBranch        *b_Zlepton1Phi;   //!
   TBranch        *b_Zlepton2Phi;   //!
   TBranch        *b_Zcharge;   //!
   TBranch        *b_njet;   //!
   TBranch        *b_jetpt;   //!
   TBranch        *b_jeteta;   //!
   TBranch        *b_jetphi;   //!
   TBranch        *b_jetID;   //!
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
   
   
    TBranch   *b_eleCharge;
    TBranch   *b_eleChargeConsistent;
    TBranch   *b_eleEn;
    TBranch   *b_eleD0;
    TBranch   *b_eleDz;
    TBranch   *b_eleD0Err;
    TBranch   *b_eleDzErr;
    TBranch   *b_eleTrkPt;
    TBranch   *b_eleTrkEta;
    TBranch   *b_eleTrkPhi;
    TBranch   *b_eleTrkCharge;
    TBranch   *b_eleTrkChi2;
    TBranch   *b_eleTrkNdof;
    TBranch   *b_eleTrkNormalizedChi2;
    TBranch   *b_eleTrkValidHits;
    TBranch   *b_eleTrkLayers;
    TBranch   *b_elePt;
    TBranch   *b_eleEta;
    TBranch   *b_elePhi;
    TBranch   *b_eleSCEn;
    TBranch   *b_eleESEn;
    TBranch   *b_eleSCEta;
    TBranch   *b_eleSCPhi;
    TBranch   *b_eleSCRawEn;
    TBranch   *b_eleSCEtaWidth;
    TBranch   *b_eleSCPhiWidth;
    TBranch   *b_eleHoverE;
    TBranch   *b_eleEoverP;
    TBranch   *b_eleEoverPInv;
    TBranch   *b_eleBrem;
    TBranch   *b_eledEtaAtVtx;
    TBranch   *b_eledPhiAtVtx;
    TBranch   *b_eleSigmaIEtaIEta;
    TBranch   *b_eleSigmaIEtaIEta_2012;
    TBranch   *b_eleSigmaIPhiIPhi;
    TBranch   *b_eleMissHits;
    TBranch   *b_eleESEffSigmaRR;
    TBranch   *b_elePFChIso;
    TBranch   *b_elePFPhoIso;
    TBranch   *b_elePFNeuIso;
    TBranch   *b_elePFPUIso;
    TBranch   *b_elePFChIso03;
    TBranch   *b_elePFPhoIso03;
    TBranch   *b_elePFNeuIso03;
    TBranch   *b_elePFChIso04;
    TBranch   *b_elePFPhoIso04;
    TBranch   *b_elePFNeuIso04;
    TBranch   *b_eleBC1E;
    TBranch   *b_eleBC1Eta;
    TBranch   *b_eleBC2E;
    TBranch   *b_eleBC2Eta;
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
    TBranch   *b_phoE1x3;
    TBranch   *b_phoE2x2;
    TBranch   *b_phoE3x3;
    TBranch   *b_phoE2x5Max;
    TBranch   *b_phoE1x5;
    TBranch   *b_phoE2x5;
    TBranch   *b_phoE5x5;
    TBranch   *b_phoMaxEnergyXtal;
    TBranch   *b_phoSigmaEtaEta;
    TBranch   *b_phoR1x5;
    TBranch   *b_phoR2x5;
    TBranch   *b_phoESEffSigmaRR;
    TBranch   *b_phoSigmaIEtaIEta_2012;
    TBranch   *b_phoSigmaIEtaIPhi_2012;
    TBranch   *b_phoSigmaIPhiIPhi_2012;
    TBranch   *b_phoE1x3_2012;
    TBranch   *b_phoE2x2_2012;
    TBranch   *b_phoE3x3_2012;
    TBranch   *b_phoE2x5Max_2012;
    TBranch   *b_phoE5x5_2012;
    TBranch   *b_phoBC1E;
    TBranch   *b_phoBC1Eta;
    TBranch   *b_phoBC2E;
    TBranch   *b_phoBC2Eta;
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
    TBranch   *b_nMu;
    TBranch   *b_muPt;
    TBranch   *b_muEta;
    TBranch   *b_muPhi;
    TBranch   *b_muCharge;
    TBranch   *b_muType;
    TBranch   *b_muIsGood;
    TBranch   *b_muD0;
    TBranch   *b_muDz;
    TBranch   *b_muChi2NDF;
    TBranch   *b_muInnerD0;
    TBranch   *b_muInnerDz;
    TBranch   *b_muTrkLayers;
    TBranch   *b_muPixelLayers;
    TBranch   *b_muPixelHits;
    TBranch   *b_muMuonHits;
    TBranch   *b_muTrkQuality;
    TBranch   *b_muStations;
    TBranch   *b_muIsoTrk;
    TBranch   *b_muPFChIso;
    TBranch   *b_muPFPhoIso;
    TBranch   *b_muPFNeuIso;
    TBranch   *b_muPFPUIso;


   ztree(std::string thisfilename);
   virtual ~ztree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(std::string outfname, std::string tag="", int pfTypeSelection = -99);
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

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   fChain->SetBranchAddress("Ztype", &Ztype, &b_Ztype);
   fChain->SetBranchAddress("Zmass", &Zmass, &b_Zmass);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("Zpt", &Zpt, &b_Zpt);
   fChain->SetBranchAddress("Zeta", &Zeta, &b_Zeta);
   fChain->SetBranchAddress("Zphi", &Zphi, &b_Zphi);
   fChain->SetBranchAddress("Zrapidity", &Zrapidity, &b_Zrapidity);
   fChain->SetBranchAddress("Zlepton1Pt", &Zlepton1Pt, &b_Zlepton1Pt);
   fChain->SetBranchAddress("Zlepton2Pt", &Zlepton2Pt, &b_Zlepton2Pt);
   fChain->SetBranchAddress("Zlepton1Eta", &Zlepton1Eta, &b_Zlepton1Eta);
   fChain->SetBranchAddress("Zlepton2Eta", &Zlepton2Eta, &b_Zlepton2Eta);
   fChain->SetBranchAddress("Zlepton1Phi", &Zlepton1Phi, &b_Zlepton1Phi);
   fChain->SetBranchAddress("Zlepton2Phi", &Zlepton2Phi, &b_Zlepton2Phi);
   fChain->SetBranchAddress("Zcharge", &Zcharge, &b_Zcharge);
   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("jetpt", jetpt, &b_jetpt);
   fChain->SetBranchAddress("jeteta", jeteta, &b_jeteta);
   fChain->SetBranchAddress("jetphi", jetphi, &b_jetphi);
   fChain->SetBranchAddress("jetID", jetID, &b_jetID);
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
