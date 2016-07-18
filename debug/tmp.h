//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  1 15:03:19 2016 by ROOT version 6.00/02
// from TTree ztree/Jet track tree
// found on file: ../g.Pythia8_Photon80_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root
//////////////////////////////////////////////////////////

#ifndef tmp_h
#define tmp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class tmp {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           lumis;
   Int_t           hiBin;
   Float_t         vz;
   Int_t           hiNevtPlane;
   Float_t         hiEvtPlanes[29];   //[hiNevtPlane]
   Int_t           Ztype;
   Float_t         Zmass;
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
   Float_t         jetpt[12];   //[njet]
   Float_t         jeteta[12];   //[njet]
   Float_t         jetphi[12];   //[njet]
   Int_t           jetID[12];   //[njet]
   Int_t           subid[12];   //[njet]
   Float_t         chargedSum[12];   //[njet]
   Float_t         neutralSum[12];   //[njet]
   Float_t         eSum[12];   //[njet]
   Int_t           nTrk;
   Float_t         trkPt[1708];   //[nTrk]
   Float_t         trkPtError[1708];   //[nTrk]
   UChar_t         trkNHit[1708];   //[nTrk]
   UChar_t         trkNlayer[1708];   //[nTrk]
   Float_t         trkEta[1708];   //[nTrk]
   Float_t         trkPhi[1708];   //[nTrk]
   Int_t           trkCharge[1708];   //[nTrk]
   UChar_t         trkNVtx[1708];   //[nTrk]
   Bool_t          highPurity[1708];   //[nTrk]
   Bool_t          tight[1708];   //[nTrk]
   Bool_t          loose[1708];   //[nTrk]
   Float_t         trkChi2[1708];   //[nTrk]
   UChar_t         trkNdof[1708];   //[nTrk]
   Float_t         trkDxy1[1708];   //[nTrk]
   Float_t         trkDxyError1[1708];   //[nTrk]
   Float_t         trkDz1[1708];   //[nTrk]
   Float_t         trkDzError1[1708];   //[nTrk]
   Bool_t          trkFake[1708];   //[nTrk]
   UChar_t         trkAlgo[1708];   //[nTrk]
   UChar_t         trkOriginalAlgo[1708];   //[nTrk]
   Float_t         trkMVA[1708];   //[nTrk]
   Int_t           pfType[1708];   //[nTrk]
   Float_t         pfCandPt[1708];   //[nTrk]
   Float_t         pfEcal[1708];   //[nTrk]
   Float_t         pfHcal[1708];   //[nTrk]
   Float_t         trkWeight[1708];   //[nTrk]
   Float_t         weight;
   Int_t           nPho;
   Float_t         phoE[3];   //[nPho]
   Float_t         phoEt[3];   //[nPho]
   Float_t         phoEta[3];   //[nPho]
   Float_t         phoPhi[3];   //[nPho]
   Float_t         phoSCE[3];   //[nPho]
   Float_t         phoSCRawE[3];   //[nPho]
   Float_t         phoESEn[3];   //[nPho]
   Float_t         phoSCEta[3];   //[nPho]
   Float_t         phoSCPhi[3];   //[nPho]
   Float_t         phoSCEtaWidth[3];   //[nPho]
   Float_t         phoSCPhiWidth[3];   //[nPho]
   Float_t         phoSCBrem[3];   //[nPho]
   Int_t           phohasPixelSeed[3];   //[nPho]
   Float_t         phoR9[3];   //[nPho]
   Float_t         phoHoverE[3];   //[nPho]
   Float_t         phoSigmaIEtaIEta[3];   //[nPho]
   Float_t         pho_ecalClusterIsoR2[3];   //[nPho]
   Float_t         pho_ecalClusterIsoR3[3];   //[nPho]
   Float_t         pho_ecalClusterIsoR4[3];   //[nPho]
   Float_t         pho_ecalClusterIsoR5[3];   //[nPho]
   Float_t         pho_hcalRechitIsoR1[3];   //[nPho]
   Float_t         pho_hcalRechitIsoR2[3];   //[nPho]
   Float_t         pho_hcalRechitIsoR3[3];   //[nPho]
   Float_t         pho_hcalRechitIsoR4[3];   //[nPho]
   Float_t         pho_hcalRechitIsoR5[3];   //[nPho]
   Float_t         pho_trackIsoR1PtCut20[3];   //[nPho]
   Float_t         pho_trackIsoR2PtCut20[3];   //[nPho]
   Float_t         pho_trackIsoR3PtCut20[3];   //[nPho]
   Float_t         pho_trackIsoR4PtCut20[3];   //[nPho]
   Float_t         pho_trackIsoR5PtCut20[3];   //[nPho]
   Float_t         pho_swissCrx[3];   //[nPho]
   Float_t         pho_seedTime[3];   //[nPho]
   Float_t         pfcIso1[3];   //[nPho]
   Float_t         pfcIso2[3];   //[nPho]
   Float_t         pfcIso3[3];   //[nPho]
   Float_t         pfcIso4[3];   //[nPho]
   Float_t         pfcIso5[3];   //[nPho]
   Float_t         pfpIso1[3];   //[nPho]
   Float_t         pfpIso2[3];   //[nPho]
   Float_t         pfpIso3[3];   //[nPho]
   Float_t         pfpIso4[3];   //[nPho]
   Float_t         pfpIso5[3];   //[nPho]
   Float_t         pfnIso1[3];   //[nPho]
   Float_t         pfnIso2[3];   //[nPho]
   Float_t         pfnIso3[3];   //[nPho]
   Float_t         pfnIso4[3];   //[nPho]
   Float_t         pfnIso5[3];   //[nPho]
   Int_t           nMC;
   Int_t           mcPID[381];   //[nMC]
   Int_t           mcStatus[381];   //[nMC]
   Float_t         mcPt[381];   //[nMC]
   Float_t         mcEta[381];   //[nMC]
   Float_t         mcPhi[381];   //[nMC]
   Float_t         mcMomPt[381];   //[nMC]
   Float_t         mcMomEta[381];   //[nMC]
   Float_t         mcMomPhi[381];   //[nMC]
   Int_t           mcMomPID[381];   //[nMC]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_hiNevtPlane;   //!
   TBranch        *b_hiEvtPlanes;   //!
   TBranch        *b_Ztype;   //!
   TBranch        *b_Zmass;   //!
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
   TBranch        *b_subid;   //!
   TBranch        *b_chargedSum;   //!
   TBranch        *b_neutralSum;   //!
   TBranch        *b_eSum;   //!
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
   TBranch        *b_trkWeight;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoSigmaIEtaIEta;   //!
   TBranch        *b_pho_ecalClusterIsoR2;   //!
   TBranch        *b_pho_ecalClusterIsoR3;   //!
   TBranch        *b_pho_ecalClusterIsoR4;   //!
   TBranch        *b_pho_ecalClusterIsoR5;   //!
   TBranch        *b_pho_hcalRechitIsoR1;   //!
   TBranch        *b_pho_hcalRechitIsoR2;   //!
   TBranch        *b_pho_hcalRechitIsoR3;   //!
   TBranch        *b_pho_hcalRechitIsoR4;   //!
   TBranch        *b_pho_hcalRechitIsoR5;   //!
   TBranch        *b_pho_trackIsoR1PtCut20;   //!
   TBranch        *b_pho_trackIsoR2PtCut20;   //!
   TBranch        *b_pho_trackIsoR3PtCut20;   //!
   TBranch        *b_pho_trackIsoR4PtCut20;   //!
   TBranch        *b_pho_trackIsoR5PtCut20;   //!
   TBranch        *b_pho_swissCrx;   //!
   TBranch        *b_pho_seedTime;   //!
   TBranch        *b_pfcIso1;   //!
   TBranch        *b_pfcIso2;   //!
   TBranch        *b_pfcIso3;   //!
   TBranch        *b_pfcIso4;   //!
   TBranch        *b_pfcIso5;   //!
   TBranch        *b_pfpIso1;   //!
   TBranch        *b_pfpIso2;   //!
   TBranch        *b_pfpIso3;   //!
   TBranch        *b_pfpIso4;   //!
   TBranch        *b_pfpIso5;   //!
   TBranch        *b_pfnIso1;   //!
   TBranch        *b_pfnIso2;   //!
   TBranch        *b_pfnIso3;   //!
   TBranch        *b_pfnIso4;   //!
   TBranch        *b_pfnIso5;   //!
   TBranch        *b_nMC;   //!
   TBranch        *b_mcPID;   //!
   TBranch        *b_mcStatus;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_mcMomPt;   //!
   TBranch        *b_mcMomEta;   //!
   TBranch        *b_mcMomPhi;   //!
   TBranch        *b_mcMomPID;   //!

   tmp(TTree *tree=0);
   virtual ~tmp();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tmp_cxx
tmp::tmp(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../g.Pythia8_Photon80_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../g.Pythia8_Photon80_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root");
      }
      f->GetObject("ztree",tree);

   }
   Init(tree);
}

tmp::~tmp()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tmp::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tmp::LoadTree(Long64_t entry)
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

void tmp::Init(TTree *tree)
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
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("hiNevtPlane", &hiNevtPlane, &b_hiNevtPlane);
   fChain->SetBranchAddress("hiEvtPlanes", hiEvtPlanes, &b_hiEvtPlanes);
   fChain->SetBranchAddress("Ztype", &Ztype, &b_Ztype);
   fChain->SetBranchAddress("Zmass", &Zmass, &b_Zmass);
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
   fChain->SetBranchAddress("subid", subid, &b_subid);
   fChain->SetBranchAddress("chargedSum", chargedSum, &b_chargedSum);
   fChain->SetBranchAddress("neutralSum", neutralSum, &b_neutralSum);
   fChain->SetBranchAddress("eSum", eSum, &b_eSum);
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
   fChain->SetBranchAddress("trkWeight", trkWeight, &b_trkWeight);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
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
   fChain->SetBranchAddress("nMC", &nMC, &b_nMC);
   fChain->SetBranchAddress("mcPID", mcPID, &b_mcPID);
   fChain->SetBranchAddress("mcStatus", mcStatus, &b_mcStatus);
   fChain->SetBranchAddress("mcPt", mcPt, &b_mcPt);
   fChain->SetBranchAddress("mcEta", mcEta, &b_mcEta);
   fChain->SetBranchAddress("mcPhi", mcPhi, &b_mcPhi);
   fChain->SetBranchAddress("mcMomPt", mcMomPt, &b_mcMomPt);
   fChain->SetBranchAddress("mcMomEta", mcMomEta, &b_mcMomEta);
   fChain->SetBranchAddress("mcMomPhi", mcMomPhi, &b_mcMomPhi);
   fChain->SetBranchAddress("mcMomPID", mcMomPID, &b_mcMomPID);
   Notify();
}

Bool_t tmp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tmp::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tmp::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tmp_cxx
