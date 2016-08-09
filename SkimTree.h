//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr  7 14:17:12 2016 by ROOT version 6.02/13
// from TTree HltTree/
// found on file: /mnt/hadoop/cms/store/user/luck/2015-Data-promptRECO-photonSkims/pp-photonHLTFilter-v0-HiForest/0.root
//////////////////////////////////////////////////////////

#ifndef SkimTree_h
#define SkimTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

   // Declaration of leaf types
   Int_t           ana_step;
   Int_t           pHBHENoiseFilterResultProducer;
   Int_t           HBHENoiseFilterResult;
   Int_t           HBHENoiseFilterResultRun1;
   Int_t           HBHENoiseFilterResultRun2Loose;
   Int_t           HBHENoiseFilterResultRun2Tight;
   Int_t           HBHEIsoNoiseFilterResult;
   Int_t           pPAprimaryVertexFilter;
   Int_t           pBeamScrapingFilter;
   Int_t           pVertexFilterCutG;
   Int_t           pVertexFilterCutGloose;
   Int_t           pVertexFilterCutGtight;
   Int_t           pVertexFilterCutGplus;
   Int_t           pVertexFilterCutE;
   Int_t           pVertexFilterCutEandG;
   Int_t           superFilterPath;
   Int_t           pcollisionEventSelection;

   // List of branches
   TBranch        *b_ana_step;   //!
   TBranch        *b_pHBHENoiseFilterResultProducer;   //!
   TBranch        *b_HBHENoiseFilterResult;   //!
   TBranch        *b_HBHENoiseFilterResultRun1;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Tight;   //!
   TBranch        *b_HBHEIsoNoiseFilterResult;   //!
   TBranch        *b_pPAprimaryVertexFilter;   //!
   TBranch        *b_pBeamScrapingFilter;   //!
   TBranch        *b_pVertexFilterCutG;   //!
   TBranch        *b_pVertexFilterCutGloose;   //!
   TBranch        *b_pVertexFilterCutGtight;   //!
   TBranch        *b_pVertexFilterCutGplus;   //!
   TBranch        *b_pVertexFilterCutE;   //!
   TBranch        *b_pVertexFilterCutEandG;   //!
   TBranch        *b_superFilterPath;   //!
   TBranch        *b_pcollisionEventSelection;   //!

   Int_t           ana_step_mix;
   Int_t           pHBHENoiseFilterResultProducer_mix;
   Int_t           HBHENoiseFilterResult_mix;
   Int_t           HBHENoiseFilterResultRun1_mix;
   Int_t           HBHENoiseFilterResultRun2Loose_mix;
   Int_t           HBHENoiseFilterResultRun2Tight_mix;
   Int_t           HBHEIsoNoiseFilterResult_mix;
   Int_t           pPAprimaryVertexFilter_mix;
   Int_t           pBeamScrapingFilter_mix;
   Int_t           pVertexFilterCutG_mix;
   Int_t           pVertexFilterCutGloose_mix;
   Int_t           pVertexFilterCutGtight_mix;
   Int_t           pVertexFilterCutGplus_mix;
   Int_t           pVertexFilterCutE_mix;
   Int_t           pVertexFilterCutEandG_mix;
   Int_t           superFilterPath_mix;
   Int_t           pcollisionEventSelection_mix;

   // List of branches
   TBranch        *b_ana_step_mix;   //!
   TBranch        *b_pHBHENoiseFilterResultProducer_mix;   //!
   TBranch        *b_HBHENoiseFilterResult_mix;   //!
   TBranch        *b_HBHENoiseFilterResultRun1_mix;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Loose_mix;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Tight_mix;   //!
   TBranch        *b_HBHEIsoNoiseFilterResult_mix;   //!
   TBranch        *b_pPAprimaryVertexFilter_mix;   //!
   TBranch        *b_pBeamScrapingFilter_mix;   //!
   TBranch        *b_pVertexFilterCutG_mix;   //!
   TBranch        *b_pVertexFilterCutGloose_mix;   //!
   TBranch        *b_pVertexFilterCutGtight_mix;   //!
   TBranch        *b_pVertexFilterCutGplus_mix;   //!
   TBranch        *b_pVertexFilterCutE_mix;   //!
   TBranch        *b_pVertexFilterCutEandG_mix;   //!
   TBranch        *b_superFilterPath_mix;   //!
   TBranch        *b_pcollisionEventSelection_mix;   //!

#endif


void initSkimTree(TTree *tree)
{
   b_ana_step_mix = 0;
   b_pHBHENoiseFilterResultProducer = 0;
   b_HBHENoiseFilterResult = 0;
   b_HBHENoiseFilterResultRun1 = 0;
   b_HBHENoiseFilterResultRun2Loose = 0;
   b_HBHENoiseFilterResultRun2Tight = 0;
   b_HBHEIsoNoiseFilterResult = 0;
   b_pPAprimaryVertexFilter = 0;
   b_pBeamScrapingFilter = 0;
   b_pVertexFilterCutG = 0;
   b_pVertexFilterCutGloose = 0;
   b_pVertexFilterCutGtight = 0;
   b_pVertexFilterCutGplus = 0;
   b_pVertexFilterCutE = 0;
   b_pVertexFilterCutEandG = 0;
   b_superFilterPath = 0;
   b_pcollisionEventSelection = 0;
   tree->SetBranchAddress("ana_step", &ana_step, &b_ana_step);
   tree->SetBranchAddress("pHBHENoiseFilterResultProducer", &pHBHENoiseFilterResultProducer, &b_pHBHENoiseFilterResultProducer);
   tree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult, &b_HBHENoiseFilterResult);
   tree->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1, &b_HBHENoiseFilterResultRun1);
   tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
   tree->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight, &b_HBHENoiseFilterResultRun2Tight);
   tree->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult, &b_HBHEIsoNoiseFilterResult);
   tree->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter, &b_pPAprimaryVertexFilter);
   tree->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter, &b_pBeamScrapingFilter);
   tree->SetBranchAddress("pVertexFilterCutG", &pVertexFilterCutG, &b_pVertexFilterCutG);
   tree->SetBranchAddress("pVertexFilterCutGloose", &pVertexFilterCutGloose, &b_pVertexFilterCutGloose);
   tree->SetBranchAddress("pVertexFilterCutGtight", &pVertexFilterCutGtight, &b_pVertexFilterCutGtight);
   tree->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus, &b_pVertexFilterCutGplus);
   tree->SetBranchAddress("pVertexFilterCutE", &pVertexFilterCutE, &b_pVertexFilterCutE);
   tree->SetBranchAddress("pVertexFilterCutEandG", &pVertexFilterCutEandG, &b_pVertexFilterCutEandG);
   tree->SetBranchAddress("superFilterPath", &superFilterPath, &b_superFilterPath);
   tree->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection, &b_pcollisionEventSelection);
}

void initSkimTreeMix(TTree *tree)
{
   b_ana_step = 0;
   b_pHBHENoiseFilterResultProducer_mix = 0;
   b_HBHENoiseFilterResult_mix = 0;
   b_HBHENoiseFilterResultRun1_mix = 0;
   b_HBHENoiseFilterResultRun2Loose_mix = 0;
   b_HBHENoiseFilterResultRun2Tight_mix = 0;
   b_HBHEIsoNoiseFilterResult_mix = 0;
   b_pPAprimaryVertexFilter_mix = 0;
   b_pBeamScrapingFilter_mix = 0;
   b_pVertexFilterCutG_mix = 0;
   b_pVertexFilterCutGloose_mix = 0;
   b_pVertexFilterCutGtight_mix = 0;
   b_pVertexFilterCutGplus_mix = 0;
   b_pVertexFilterCutE_mix = 0;
   b_pVertexFilterCutEandG_mix = 0;
   b_superFilterPath_mix = 0;
   b_pcollisionEventSelection_mix = 0;
   tree->SetBranchAddress("ana_step", &ana_step_mix, &b_ana_step_mix);
   tree->SetBranchAddress("pHBHENoiseFilterResultProducer", &pHBHENoiseFilterResultProducer_mix, &b_pHBHENoiseFilterResultProducer_mix);
   tree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult_mix, &b_HBHENoiseFilterResult_mix);
   tree->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1_mix, &b_HBHENoiseFilterResultRun1_mix);
   tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose_mix, &b_HBHENoiseFilterResultRun2Loose_mix);
   tree->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight_mix, &b_HBHENoiseFilterResultRun2Tight_mix);
   tree->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult_mix, &b_HBHEIsoNoiseFilterResult_mix);
   tree->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter_mix, &b_pPAprimaryVertexFilter_mix);
   tree->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter_mix, &b_pBeamScrapingFilter_mix);
   tree->SetBranchAddress("pVertexFilterCutG", &pVertexFilterCutG_mix, &b_pVertexFilterCutG_mix);
   tree->SetBranchAddress("pVertexFilterCutGloose", &pVertexFilterCutGloose_mix, &b_pVertexFilterCutGloose_mix);
   tree->SetBranchAddress("pVertexFilterCutGtight", &pVertexFilterCutGtight_mix, &b_pVertexFilterCutGtight_mix);
   tree->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus_mix, &b_pVertexFilterCutGplus_mix);
   tree->SetBranchAddress("pVertexFilterCutE", &pVertexFilterCutE_mix, &b_pVertexFilterCutE_mix);
   tree->SetBranchAddress("pVertexFilterCutEandG", &pVertexFilterCutEandG_mix, &b_pVertexFilterCutEandG_mix);
   tree->SetBranchAddress("superFilterPath", &superFilterPath_mix, &b_superFilterPath_mix);
   tree->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection_mix, &b_pcollisionEventSelection_mix);
}
