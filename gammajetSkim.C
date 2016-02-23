#include "ggTree.h"
#include "jetTree.h"
#include "trackTree.h"

bool goodJet(int i) {
  if(	neutralSum[i]/rawpt[i] < 0.9
      && chargedSum[i]/rawpt[i] > 0.01
      && chargedN[i]+photonN[i]+neutralN[i]+eN[i]+muN[i] > 0
      && chargedMax[i]/rawpt[i] < 0.99
      && photonSum[i]/rawpt[i] < 0.99
      && eSum[i]/rawpt[i] < 0.99
      ) return true;
  else return false;
}

// bool goodPho(int i) {
// if(	neutralSum[i]/rawpt[i] < 0.9
// && chargedSum[i]/rawpt[i] > 0.01
// && chargedN[i]+photonN[i]+neutralN[i]+eN[i]+muN[i] > 0
// && chargedMax[i]/rawpt[i] < 0.99
// && photonSum[i]/rawpt[i] < 0.99
// && eSum[i]/rawpt[i] < 0.99
// ) return true;
// else return false;
// }



void gammajetSkim(TString infilename="HiForest.root", TString outfilename="Zevents.root", string jetname="ak4PFJetAnalyzer") {

  TH1::SetDefaultSumw2();


  int Ztype; //type 1 muon, type 2 electron
  float Zmass, Zpt, Zeta, Zrapidity, Zphi;
  float Zlepton1Pt, Zlepton2Pt, Zlepton1Eta, Zlepton2Eta, Zlepton1Phi, Zlepton2Phi;
  float weight = 0 , vz = -99;
  int hiBin = -99;
  int Zcharge;


  int njet;
  float jetpt[200], jeteta[200], jetphi[200]; 
  int jetID[200];
  
  Int_t           nTrk;
  Int_t           run;
  Int_t           event;
  Int_t           lumis;
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
  // Int_t    nEle;
  // Int_t    eleCharge[100];   //_nEle
  // Int_t    eleChargeConsistent[100];   //_nEle
  // Float_t  eleEn[100];   //_nEle
  // Float_t  eleD0[100];   //_nEle
  // Float_t  eleDz[100];   //_nEle
  // Float_t  eleD0Err[100];   //_nEle
  // Float_t  eleDzErr[100];   //_nEle
  // Float_t  eleTrkPt[100];   //_nEle
  // Float_t  eleTrkEta[100];   //_nEle
  // Float_t  eleTrkPhi[100];   //_nEle
  // Int_t    eleTrkCharge[100];   //_nEle
  // Float_t  eleTrkChi2[100];   //_nEle
  // Float_t  eleTrkNdof[100];   //_nEle
  // Float_t  eleTrkNormalizedChi2[100];   //_nEle
  // Int_t    eleTrkValidHits[100];   //_nEle
  // Int_t    eleTrkLayers[100];   //_nEle
  // Float_t  elePt[100];   //_nEle
  // Float_t  eleEta[100];   //_nEle
  // Float_t  elePhi[100];   //_nEle
  // Float_t  eleSCEn[100];   //_nEle
  // Float_t  eleESEn[100];   //_nEle
  // Float_t  eleSCEta[100];   //_nEle
  // Float_t  eleSCPhi[100];   //_nEle
  // Float_t  eleSCRawEn[100];   //_nEle
  // Float_t  eleSCEtaWidth[100];   //_nEle
  // Float_t  eleSCPhiWidth[100];   //_nEle
  // Float_t  eleHoverE[100];   //_nEle
  // Float_t  eleEoverP[100];   //_nEle
  // Float_t  eleEoverPInv[100];   //_nEle
  // Float_t  eleBrem[100];   //_nEle
  // Float_t  eledEtaAtVtx[100];   //_nEle
  // Float_t  eledPhiAtVtx[100];   //_nEle
  // Float_t  eleSigmaIEtaIEta[100];   //_nEle
  // Float_t  eleSigmaIEtaIEta_2012[100];   //_nEle
  // Float_t  eleSigmaIPhiIPhi[100];   //_nEle
  // Int_t    eleMissHits[100];   //_nEle
  // Float_t  eleESEffSigmaRR[100];   //_nEle
  // Float_t  elePFChIso[100];   //_nEle
  // Float_t  elePFPhoIso[100];   //_nEle
  // Float_t  elePFNeuIso[100];   //_nEle
  // Float_t  elePFPUIso[100];   //_nEle
  // Float_t  elePFChIso03[100];   //_nEle
  // Float_t  elePFPhoIso03[100];   //_nEle
  // Float_t  elePFNeuIso03[100];   //_nEle
  // Float_t  elePFChIso04[100];   //_nEle
  // Float_t  elePFPhoIso04[100];   //_nEle
  // Float_t  elePFNeuIso04[100];   //_nEle
  // Float_t  eleBC1E[100];   //_nEle
  // Float_t  eleBC1Eta[100];   //_nEle
  // Float_t  eleBC2E[100];   //_nEle
  // Float_t  eleBC2Eta[100];   //_nEle
  Int_t    nPho;
  Float_t  phoE[100];   //_nPho
  Float_t  phoEt[100];   //_nPho
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
  // Float_t  phoE1x3[100];   //_nPho
  // Float_t  phoE2x2[100];   //_nPho
  // Float_t  phoE3x3[100];   //_nPho
  // Float_t  phoE2x5Max[100];   //_nPho
  // Float_t  phoE1x5[100];   //_nPho
  // Float_t  phoE2x5[100];   //_nPho
  // Float_t  phoE5x5[100];   //_nPho
  // Float_t  phoMaxEnergyXtal[100];   //_nPho
  // Float_t  phoSigmaEtaEta[100];   //_nPho
  // Float_t  phoR1x5[100];   //_nPho
  // Float_t  phoR2x5[100];   //_nPho
  // Float_t  phoESEffSigmaRR[100];   //_nPho
  // Float_t  phoSigmaIEtaIEta_2012[100];   //_nPho
  // Float_t  phoSigmaIEtaIPhi_2012[100];   //_nPho
  // Float_t  phoSigmaIPhiIPhi_2012[100];   //_nPho
  // Float_t  phoE1x3_2012[100];   //_nPho
  // Float_t  phoE2x2_2012[100];   //_nPho
  // Float_t  phoE3x3_2012[100];   //_nPho
  // Float_t  phoE2x5Max_2012[100];   //_nPho
  // Float_t  phoE5x5_2012[100];   //_nPho
  // Float_t  phoBC1E[100];   //_nPho
  // Float_t  phoBC1Eta[100];   //_nPho
  // Float_t  phoBC2E[100];   //_nPho
  // Float_t  phoBC2Eta[100];   //_nPho
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
  // Int_t     nMu;
  // Float_t  muPt[100];   //_nMu
  // Float_t  muEta[100];   //_nMu
  // Float_t  muPhi[100];   //_nMu
  // Int_t    muCharge[100];   //_nMu
  // Int_t    muType[100];   //_nMu
  // Int_t    muIsGood[100];   //_nMu
  // Float_t  muD0[100];   //_nMu
  // Float_t  muDz[100];   //_nMu
  // Float_t  muChi2NDF[100];   //_nMu
  // Float_t  muInnerD0[100];   //_nMu
  // Float_t  muInnerDz[100];   //_nMu
  // Int_t    muTrkLayers[100];   //_nMu
  // Int_t    muPixelLayers[100];   //_nMu
  // Int_t    muPixelHits[100];   //_nMu
  // Int_t    muMuonHits[100];   //_nMu
  // Int_t    muTrkQuality[100];   //_nMu
  // Int_t    muStations[100];   //_nMu
  // Float_t  muIsoTrk[100];   //_nMu
  // Float_t  muPFChIso[100];   //_nMu
  // Float_t  muPFPhoIso[100];   //_nMu
  // Float_t  muPFNeuIso[100];   //_nMu
  // Float_t  muPFPUIso[100000];   //_nMu
  
  TTree *ztree = new TTree("ztree","Jet track tree");
  ztree->Branch("run",	&run,	"run/I");
  ztree->Branch("event",	&event,	"event/I");
  ztree->Branch("lumis",	&lumis,	"lumis/I");
  ztree->Branch("hiBin", &hiBin, "hiBin/I");
  ztree->Branch("vz", &vz, "vz/F");
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
  ztree->Branch("jetID",	&jetID,	"jetID[njet]/I");
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
  ztree->Branch("weight", &weight,"weight/F");
  // ztree->Branch("nEle",&nEle,"nEle/I");
  // ztree->Branch("eleCharge",&eleCharge,"eleCharge[nEle]/I");    
  // ztree->Branch("eleChargeConsistent",&eleChargeConsistent,"eleChargeConsistent[nEle]/I");    
  // ztree->Branch("eleEn",&eleEn,"eleEn[nEle]/F");    
  // ztree->Branch("eleD0",&eleD0,"eleD0[nEle]/F");    
  // ztree->Branch("eleDz",&eleDz,"eleDz[nEle]/F");    
  // ztree->Branch("eleD0Err",&eleD0Err,"eleD0Err[nEle]/F");    
  // ztree->Branch("eleDzErr",&eleDzErr,"eleDzErr[nEle]/F");    
  // ztree->Branch("eleTrkPt",&eleTrkPt,"eleTrkPt[nEle]/F");    
  // ztree->Branch("eleTrkEta",&eleTrkEta,"eleTrkEta[nEle]/F");    
  // ztree->Branch("eleTrkPhi",&eleTrkPhi,"eleTrkPhi[nEle]/F");    
  // ztree->Branch("eleTrkCharge",&eleTrkCharge,"eleTrkCharge[nEle]/I");    

  // ztree->Branch("eleTrkChi2",&eleTrkChi2,"eleTrkChi2[nEle]/F"); 
  // ztree->Branch("eleTrkNdof",&eleTrkNdof,"eleTrkNdof[nEle]/F");    
  // ztree->Branch("eleTrkNormalizedChi2",&eleTrkNormalizedChi2,"eleTrkNormalizedChi2[nEle]/F");
  
  // ztree->Branch("eleTrkValidHits",&eleTrkValidHits,"eleTrkValidHits[nEle]/I");    
  // ztree->Branch("eleTrkLayers",&eleTrkLayers,"eleTrkLayers[nEle]/I");    
  // ztree->Branch("elePt",&elePt,"elePt[nEle]/F");    

  // ztree->Branch("eleEta",&eleEta,"eleEta[nEle]/F");    
  // ztree->Branch("elePhi",&elePhi,"elePhi[nEle]/F");    
  // ztree->Branch("eleSCEn",&eleSCEn,"eleSCEn[nEle]/F");    
  // ztree->Branch("eleESEn",&eleESEn,"eleESEn[nEle]/F");    
  // ztree->Branch("eleSCEta",&eleSCEta,"eleSCEta[nEle]/F");    

  // ztree->Branch("eleSCPhi",&eleSCPhi,"eleSCPhi[nEle]/F");    
  // ztree->Branch("eleSCRawEn",&eleSCRawEn,"eleSCRawEn[nEle]/F");    
  // ztree->Branch("eleSCEtaWidth",&eleSCEtaWidth,"eleSCEtaWidth[nEle]/F");    
  // ztree->Branch("eleSCPhiWidth",&eleSCPhiWidth,"eleSCPhiWidth[nEle]/F");    
  // ztree->Branch("eleHoverE",&eleHoverE,"eleHoverE[nEle]/F");    
  // ztree->Branch("eleEoverP",&eleEoverP,"eleEoverP[nEle]/F");    
  // ztree->Branch("eleEoverPInv",&eleEoverPInv,"eleEoverPInv[nEle]/F");    
  // ztree->Branch("eleBrem",&eleBrem,"eleBrem[nEle]/F");    
  // ztree->Branch("eledEtaAtVtx",&eledEtaAtVtx,"eledEtaAtVtx[nEle]/F");    
  // ztree->Branch("eledPhiAtVtx",&eledPhiAtVtx,"eledPhiAtVtx[nEle]/F");    
  // ztree->Branch("eleSigmaIEtaIEta",&eleSigmaIEtaIEta,"eleSigmaIEtaIEta[nEle]/F");    
  // ztree->Branch("eleSigmaIEtaIEta_2012",&eleSigmaIEtaIEta_2012,"eleSigmaIEtaIEta_2012[nEle]/F");    
  // ztree->Branch("eleSigmaIPhiIPhi",&eleSigmaIPhiIPhi,"eleSigmaIPhiIPhi[nEle]/F"); 

  // ztree->Branch("eleMissHits",&eleMissHits,"eleMissHits[nEle]/I");    
  // ztree->Branch("eleESEffSigmaRR",&eleESEffSigmaRR,"eleESEffSigmaRR[nEle]/F");    
  // ztree->Branch("elePFChIso",&elePFChIso,"elePFChIso[nEle]/F");    
  // ztree->Branch("elePFPhoIso",&elePFPhoIso,"elePFPhoIso[nEle]/F");    
  // ztree->Branch("elePFNeuIso",&elePFNeuIso,"elePFNeuIso[nEle]/F");    
  // ztree->Branch("elePFPUIso",&elePFPUIso,"elePFPUIso[nEle]/F");    
  // ztree->Branch("elePFChIso03",&elePFChIso03,"elePFChIso03[nEle]/F");    
  // ztree->Branch("elePFPhoIso03",&elePFPhoIso03,"elePFPhoIso03[nEle]/F");    
  // ztree->Branch("elePFNeuIso03",&elePFNeuIso03,"elePFNeuIso03[nEle]/F");    
  // ztree->Branch("elePFChIso04",&elePFChIso04,"elePFChIso04[nEle]/F");    
  // ztree->Branch("elePFPhoIso04",&elePFPhoIso04,"elePFPhoIso04[nEle]/F");    
  // ztree->Branch("elePFNeuIso04",&elePFNeuIso04,"elePFNeuIso04[nEle]/F");    
  // ztree->Branch("eleBC1E",&eleBC1E,"eleBC1E[nEle]/F");    
  // ztree->Branch("eleBC1Eta",&eleBC1Eta,"eleBC1Eta[nEle]/F");    
  // ztree->Branch("eleBC2E",&eleBC2E,"eleBC2E[nEle]/F");    
  // ztree->Branch("eleBC2Eta",&eleBC2Eta,"eleBC2Eta[nEle]/F");    

  ztree->Branch("nPho",&nPho,"nPho/I");
  ztree->Branch("phoE",&phoE,"phoE[nPho]/F");    
  ztree->Branch("phoEt",&phoEt,"phoEt[nPho]/F");    
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
  // ztree->Branch("phoE1x3",&phoE1x3,"phoE1x3[nPho]/F");    
  // ztree->Branch("phoE2x2",&phoE2x2,"phoE2x2[nPho]/F");    
  // ztree->Branch("phoE3x3",&phoE3x3,"phoE3x3[nPho]/F");    
  // ztree->Branch("phoE2x5Max",&phoE2x5Max,"phoE2x5Max[nPho]/F");    
  // ztree->Branch("phoE1x5",&phoE1x5,"phoE1x5[nPho]/F");    
  // ztree->Branch("phoE2x5",&phoE2x5,"phoE2x5[nPho]/F");    
  // ztree->Branch("phoE5x5",&phoE5x5,"phoE5x5[nPho]/F");    
  // ztree->Branch("phoMaxEnergyXtal",&phoMaxEnergyXtal,"phoMaxEnergyXtal[nPho]/F");    
  // ztree->Branch("phoSigmaEtaEta",&phoSigmaEtaEta,"phoSigmaEtaEta[nPho]/F");    
  // ztree->Branch("phoR1x5",&phoR1x5,"phoR1x5[nPho]/F");    
  // ztree->Branch("phoR2x5",&phoR2x5,"phoR2x5[nPho]/F");    
  // ztree->Branch("phoESEffSigmaRR",&phoESEffSigmaRR,"phoESEffSigmaRR[nPho]/F");    
  // ztree->Branch("phoSigmaIEtaIEta_2012",&phoSigmaIEtaIEta_2012,"phoSigmaIEtaIEta_2012[nPho]/F");    
  // ztree->Branch("phoSigmaIEtaIPhi_2012",&phoSigmaIEtaIPhi_2012,"phoSigmaIEtaIPhi_2012[nPho]/F");    
  // ztree->Branch("phoSigmaIPhiIPhi_2012",&phoSigmaIPhiIPhi_2012,"phoSigmaIPhiIPhi_2012[nPho]/F");    
  // ztree->Branch("phoE1x3_2012",&phoE1x3_2012,"phoE1x3_2012[nPho]/F");    
  // ztree->Branch("phoE2x2_2012",&phoE2x2_2012,"phoE2x2_2012[nPho]/F");    
  // ztree->Branch("phoE3x3_2012",&phoE3x3_2012,"phoE3x3_2012[nPho]/F");    
  // ztree->Branch("phoE2x5Max_2012",&phoE2x5Max_2012,"phoE2x5Max_2012[nPho]/F");    
  // ztree->Branch("phoE5x5_2012",&phoE5x5_2012,"phoE5x5_2012[nPho]/F");    
  // ztree->Branch("phoBC1E",&phoBC1E,"phoBC1E[nPho]/F");    
  // ztree->Branch("phoBC1Eta",&phoBC1Eta,"phoBC1Eta[nPho]/F");    
  // ztree->Branch("phoBC2E",&phoBC2E,"phoBC2E[nPho]/F");    
  // ztree->Branch("phoBC2Eta",&phoBC2Eta,"phoBC2Eta[nPho]/F");    
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
  // ztree->Branch("nMu",&nMu,"nMu/I");   
  // ztree->Branch("muPt",&muPt,"muPt[nMu]/F");    
  // ztree->Branch("muEta",&muEta,"[nMu]/F");    
  // ztree->Branch("muPhi",&muPhi,"muPhi[nMu]/F");    
  // ztree->Branch("muCharge",&muCharge,"muCharge[nMu]/I");    
  // ztree->Branch("muType",&muType,"muType[nMu]/I");    
  // ztree->Branch("muIsGood",&muIsGood,"muIsGood[nMu]/I");    
  // ztree->Branch("muD0",&muD0,"muD0[nMu]/F");    
  // ztree->Branch("muDz",&muDz,"muDz[nMu]/F");    
  // ztree->Branch("muChi2NDF",&muChi2NDF,"muChi2NDF[nMu]/F");    
  // ztree->Branch("muInnerD0",&muInnerD0,"muInnerD0[nMu]/F");    
  // ztree->Branch("muInnerDz",&muInnerDz,"muInnerDz[nMu]/F");    
  // ztree->Branch("muTrkLayers",&muTrkLayers,"muTrkLayers[nMu]/I");    
  // ztree->Branch("muPixelLayers",&muPixelLayers,"muPixelLayers[nMu]/I");    
  // ztree->Branch("muPixelHits",&muPixelHits,"muPixelHits[nMu]/I");    
  // ztree->Branch("muMuonHits",&muMuonHits,"muMuonHits[nMu]/I");    
  // ztree->Branch("muTrkQuality",&muTrkQuality,"muTrkQuality[nMu]/I");    
  // ztree->Branch("muStations",&muStations,"muStations[nMu]/I");    
  // ztree->Branch("muIsoTrk",&muIsoTrk,"muIsoTrk[nMu]/F");    
  // ztree->Branch("muPFChIso",&muPFChIso,"muPFChIso[nMu]/F");    
  // ztree->Branch("muPFPhoIso",&muPFPhoIso,"muPFPhoIso[nMu]/F");    
  // ztree->Branch("muPFNeuIso",&muPFNeuIso,"muPFNeuIso[nMu]/F");    
  // ztree->Branch("muPFPUIso",&muPFPUIso,"muPFPUIso[nMu]/F");    


  // const int nPtBins = 13;
  // const double PtBins[nPtBins+1]={0,2.5,5.0,7.5,10.0,12.5,15.0,20,30,40,50,70,100,150};
  // const int nYBins = 13;

  // TH1F *mmMass = new TH1F("mmMass",";m^{#mu#mu} (GeV/c^{2});Events",30,60,120);
  // TH1F *mmMassSS = new TH1F("mmMassSS",";m^{#mu#mu} (GeV/c^{2});Events",30,60,120);

  // TH1F *mmPt = new TH1F("mmPt",";p_{T}^{#mu#mu} (GeV/c);dN/dp_{T}",nPtBins,PtBins);
  // TH1F *mmY = new TH1F("mmY",";y^{#mu#mu};Events",nYBins,-2.6,2.6);
  // TH1F *mmPhi = new TH1F("mmPhi",";#phi^{#mu#mu};Events",20,-pi,pi);

  // TH1F *eeMass = new TH1F("eeMass",";m^{ee} (GeV/c^{2});Events",30,60,120);
  // TH1F *eeMassSS = new TH1F("eeMassSS",";m^{ee} (GeV/c^{2});Events",30,60,120);

  // TH1F *eePt = new TH1F("eePt",";p_{T}^{ee} (GeV/c);dN/dp_{T}",nPtBins,PtBins);
  // TH1F *eeY = new TH1F("eeY",";y^{ee};Events",nYBins,-2.6,2.6);
  // TH1F *eePhi = new TH1F("eePhi",";#phi^{ee};Events",20,-pi,pi);

  // int nMuPair = 0;
  // int nElPair = 0;


  TFile *fin = TFile::Open(infilename);

  TFile *fout = new TFile(outfilename,"recreate");

  TTree *inggTree = (TTree*)fin->Get("ggHiNtuplizer/EventTree");
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
  
  TTree *evttree = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
  if(!evttree){
    cout<<"Could not access event tree!"<<endl;
    return;
  }
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
  


  // int nEv = inggTree->GetEntries();
  int nEv = evttree->GetEntries();

  for (int j=0; j<nEv; j++) {

    injetTree->GetEntry(j);
    if(j%20000 == 0) cout << "Processing event: " << j << endl;
    
    njet = 0;
    for(int ij=0; ij<nref; ij++) {
      if(jtpt[ij]>30 && goodJet(ij))
      {
        jetpt[njet] = jtpt[ij];
        jeteta[njet] = jteta[ij];
        jetphi[njet] = jtphi[ij];
        jetID[njet] = goodJet(ij);
        njet++;
      }
    } //end of jet loop
    if(njet==0) continue;
    
    inggTree->GetEntry(j);
    int nphoton = 0;
    for(int ipho = 0 ; ipho < _nPho ; ++ipho)
    {
      
      if((*_phoHoverE)[ipho]<0.1 && (*_pho_swissCrx)[ipho]<0.9 && abs((*_pho_seedTime)[ipho])<3.0 && ((*_pho_ecalClusterIsoR4)[ipho] + (*_pho_hcalRechitIsoR4)[ipho] + (*_pho_trackIsoR4PtCut20)[ipho]) < 1.0 && (*_phoSigmaIEtaIEta_2012)[ipho]<0.01 && (*_phoR9)[ipho]>0.3 ) //photon selection
      {
        phoE[nphoton] = (*_phoE)[ipho];   
        phoEt[nphoton] = (*_phoEt)[ipho];   
        phoEta[nphoton] = (*_phoEta)[ipho];   
        phoPhi[nphoton] = (*_phoPhi)[ipho];   
        phoSCE[nphoton] = (*_phoSCE)[ipho];   
        phoSCRawE[nphoton] = (*_phoSCRawE)[ipho];   
        phoESEn[nphoton] = (*_phoESEn)[ipho];   
        phoSCEta[nphoton] = (*_phoSCEta)[ipho];   
        phoSCPhi[nphoton] = (*_phoSCPhi)[ipho];   
        phoSCEtaWidth[nphoton] = (*_phoSCEtaWidth)[ipho];   
        phoSCPhiWidth[nphoton] = (*_phoSCPhiWidth)[ipho];   
        phoSCBrem[nphoton] = (*_phoSCBrem)[ipho];   
        phohasPixelSeed[nphoton] = (*_phohasPixelSeed)[ipho];   
        phoR9[nphoton] = (*_phoR9)[ipho];   
        phoHoverE[nphoton] = (*_phoHoverE)[ipho];   
        phoSigmaIEtaIEta[nphoton] = (*_phoSigmaIEtaIEta)[ipho];   
        pho_ecalClusterIsoR2[nphoton] = (*_pho_ecalClusterIsoR2)[ipho];   
        pho_ecalClusterIsoR3[nphoton] = (*_pho_ecalClusterIsoR3)[ipho];   
        pho_ecalClusterIsoR4[nphoton] = (*_pho_ecalClusterIsoR4)[ipho];   
        pho_ecalClusterIsoR5[nphoton] = (*_pho_ecalClusterIsoR5)[ipho];   
        pho_hcalRechitIsoR1[nphoton] = (*_pho_hcalRechitIsoR1)[ipho];   
        pho_hcalRechitIsoR2[nphoton] = (*_pho_hcalRechitIsoR2)[ipho];   
        pho_hcalRechitIsoR3[nphoton] = (*_pho_hcalRechitIsoR3)[ipho];   
        pho_hcalRechitIsoR4[nphoton] = (*_pho_hcalRechitIsoR4)[ipho];   
        pho_hcalRechitIsoR5[nphoton] = (*_pho_hcalRechitIsoR5)[ipho];   
        pho_trackIsoR1PtCut20[nphoton] = (*_pho_trackIsoR1PtCut20)[ipho];   
        pho_trackIsoR2PtCut20[nphoton] = (*_pho_trackIsoR2PtCut20)[ipho];   
        pho_trackIsoR3PtCut20[nphoton] = (*_pho_trackIsoR3PtCut20)[ipho];   
        pho_trackIsoR4PtCut20[nphoton] = (*_pho_trackIsoR4PtCut20)[ipho];   
        pho_trackIsoR5PtCut20[nphoton] = (*_pho_trackIsoR5PtCut20)[ipho];   
        pho_swissCrx[nphoton] = (*_pho_swissCrx)[ipho];   
        pho_seedTime[nphoton] = (*_pho_seedTime)[ipho];   
        pfcIso1[nphoton] = (*_pfcIso1)[ipho];   
        pfcIso2[nphoton] = (*_pfcIso2)[ipho];   
        pfcIso3[nphoton] = (*_pfcIso3)[ipho];   
        pfcIso4[nphoton] = (*_pfcIso4)[ipho];   
        pfcIso5[nphoton] = (*_pfcIso5)[ipho];   
        pfpIso1[nphoton] = (*_pfpIso1)[ipho];   
        pfpIso2[nphoton] = (*_pfpIso2)[ipho];   
        pfpIso3[nphoton] = (*_pfpIso3)[ipho];   
        pfpIso4[nphoton] = (*_pfpIso4)[ipho];   
        pfpIso5[nphoton] = (*_pfpIso5)[ipho];   
        pfnIso1[nphoton] = (*_pfnIso1)[ipho];   
        pfnIso2[nphoton] = (*_pfnIso2)[ipho];   
        pfnIso3[nphoton] = (*_pfnIso3)[ipho];   
        pfnIso4[nphoton] = (*_pfnIso4)[ipho];   
        pfnIso5[nphoton] = (*_pfnIso5)[ipho];   
        nphoton++;
      }
    }
    nPho = nphoton;
    if(nphoton==0) continue;
    
    tracktree_->GetEntry(j);
    evttree->GetEntry(j);

    int ntracks = 0;
    for(int i = 0 ; i < nTrk_ ; ++i)
    {
      if((trkMVA_[i]<0.5 && trkMVA_[i]!=-99) || (int)trkNHit_[i]<8 || trkPtError_[i]/trkPt_[i]>0.3 || fabs(trkDz1_[i])/trkDzError1_[i]>3 || fabs(trkDxy1_[i])/trkDxyError1_[i]>3) continue;
      trkPt[ntracks] = trkPt_[i];   //[nTrk]
      trkPtError[ntracks] = trkPtError_[i];   //[nTrk]
      trkNHit[ntracks] = trkNHit_[i];   //[nTrk]
      trkNlayer[ntracks] = trkNlayer_[i];   //[nTrk]
      trkEta[ntracks] = trkEta_[i];   //[nTrk]
      trkPhi[ntracks] = trkPhi_[i];   //[nTrk]
      trkCharge[ntracks] = trkCharge_[i];   //[nTrk]
      trkNVtx[ntracks] = trkNVtx_[i];   //[nTrk]
      highPurity[ntracks] = highPurity_[i];   //[nTrk]
      tight[ntracks] = tight_[i];   //[nTrk]
      loose[ntracks] = loose_[i];   //[nTrk]
      trkChi2[ntracks] = trkChi2_[i];   //[nTrk]
      trkNdof[ntracks] = trkNdof_[i];   //[nTrk]
      trkDxy1[ntracks] = trkDxy1_[i];   //[nTrk]
      trkDxyError1[ntracks] = trkDxyError1_[i];   //[nTrk]
      trkDz1[ntracks] = trkDz1_[i];   //[nTrk]
      trkDzError1[ntracks] = trkDzError1_[i];   //[nTrk]
      trkFake[ntracks] = trkFake_[i];   //[nTrk]
      trkAlgo[ntracks] = trkAlgo_[i];   //[nTrk]
      trkOriginalAlgo[ntracks] = trkOriginalAlgo_[i];   //[nTrk]
      trkMVA[ntracks] = trkMVA_[i];   //[nTrk]
      pfType[ntracks] = pfType_[i];   //[nTrk]
      pfCandPt[ntracks] = pfCandPt_[i];   //[nTrk]
      pfEcal[ntracks] = pfEcal_[i];   //[nTrk]
      pfHcal[ntracks] = pfHcal_[i];   //[nTrk]
      ntracks++;
      //if((trkPt[i]-2*trkPtError[i])*TMath::CosH(trkEta[i])>15 && (trkPt[i]-2*trkPtError[i])*TMath::CosH(trkEta[i])>pfHcal[i]+pfEcal[i]) continue;} //Calo Matching
    }
    nTrk=ntracks;
    
    
    ztree->Fill();

  } //end of loop over events


  fout->cd();
  ztree->Write();
  // injetTree->Write();
  // trackTree->Write();
  fout->Write();

}

int main(int argc, char *argv[])
{
  if((argc < 3))
  {
    std::cout << "Usage: ./gammajetSkim.exe <inputfile> <outputfile> [jetname]" << std::endl;
    return 1;
  }
  if(argc==3)  gammajetSkim(argv[1], argv[2]);
  if(argc==4)  gammajetSkim(argv[1], argv[2], argv[3]);
  return 0;
}

