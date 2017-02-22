#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>
#include <typeinfo>

/************************ code outline ********************************
(1) Setup                                                             *
  (1.1) Smearing functions for pp                                     *
  (1.2) List of histograms                                            *
                                                                      *
(2) Loop                                                              *
  (2.1) Event selections                                              *
  (2.2) Reco jet loop                                                 *
  (2.3) Gen jet loop                                                  *
  (2.4) Mix reco jet loop                                             *
  (2.5) Mix gen jet loop                                              *
                                                                      *
**********************************************************************/

/************************ analysis objects ****************************
Reco Jet Reco Trk: (recoreco)
 1-1: rjet rtrk           raw FF
 1-2: rjet_mix rtrk_mix   mix jet bk
 1-3: rjet rtrk_mix      ue cone bk
 1-4: rjet rtrk_mix      jetmix ue cone bk

Gen Jet Gen Trk sube==0: (gengen)
 2-1: gjet gtrk sube==0   truth FF

Gen Jet Gen Trk inclusive: (mixgen)
 3-1: gjet gtrk           raw FF gen
 3-2: gjet_mix gtrk_mix   mix jet bk gen
 3-3: gjet gtrk           ue cone gen
**********************************************************************/

TFile * fgensmear = TFile::Open("gensmearhists.root");
TH2D * hpbpbrpt = (TH2D*) fgensmear->Get("hpbpbrpt");
TH2D * hpbpbreta = (TH2D*) fgensmear->Get("hpbpbreta");
TH2D * hpbpbrphi = (TH2D*) fgensmear->Get("hpbpbrphi");
TH2D * hpprpt = (TH2D*) fgensmear->Get("hpprpt");
TH2D * hppreta = (TH2D*) fgensmear->Get("hppreta");
TH2D * hpprphi = (TH2D*) fgensmear->Get("hpprphi");

float smeargenpt(int ispp, int hibin)
{
  if(ispp==0) {
    if(hibin < 20)
      return hpbpbrpt->ProjectionY("",1,2)->GetRandom();
    else if(hibin >= 20 && hibin < 60)
      return hpbpbrpt->ProjectionY("",3,6)->GetRandom();
    else if(hibin >= 60 && hibin < 100)
      return hpbpbrpt->ProjectionY("",7,10)->GetRandom();
    else
      return hpbpbrpt->ProjectionY("",11,20)->GetRandom();
  }
  else return hpprpt->ProjectionY()->GetRandom();
}

float smeargeneta(int ispp, int hibin)
{
  if(ispp==0) {
    if(hibin < 20)
      return hpbpbreta->ProjectionY("",1,2)->GetRandom();
    else if(hibin >= 20 && hibin < 60)
      return hpbpbreta->ProjectionY("",3,6)->GetRandom();
    else if(hibin >= 60 && hibin < 100)
      return hpbpbreta->ProjectionY("",7,10)->GetRandom();
    else
      return hpbpbreta->ProjectionY("",11,20)->GetRandom();
  }
  else return hppreta->ProjectionY()->GetRandom();
}

float smeargenphi(int ispp, int hibin)
{
  if(ispp==0) {
    if(hibin < 20)
      return hpbpbrphi->ProjectionY("",1,2)->GetRandom();
    else if(hibin >= 20 && hibin < 60)
      return hpbpbrphi->ProjectionY("",3,6)->GetRandom();
    else if(hibin >= 60 && hibin < 100)
      return hpbpbrphi->ProjectionY("",7,10)->GetRandom();
    else
      return hpbpbrphi->ProjectionY("",11,20)->GetRandom();
  }
  else return hpprphi->ProjectionY()->GetRandom();
}

//! (1.11) Begin pp smearing
TRandom3 randSmearing(12345);    // random number seed should be fixed or reproducible
int smearcents[] = {5,25,65,105};
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

std::vector<double>* CSN_vector[4] = {&CSN_HI_cent0010, &CSN_HI_cent1030, &CSN_HI_cent3050, &CSN_HI_cent50100};

int getResolutionBin(int centmin) {
  if (centmin == 0)
    return 0;
  else if (centmin == 20)
    return 1;
  else if (centmin == 60)
    return 2;
  else if (centmin == 100)
    return 3;
  else
    return 0;
}

double getResolutionHI(float jtpt, int resolutionBin)
{
  std::vector<double>* CSN_HI = CSN_vector[resolutionBin];
  double sigma = TMath::Sqrt(
    (CSN_HI->at(0)*CSN_HI->at(0)) +
    (CSN_HI->at(1)*CSN_HI->at(1))/jtpt +
    (CSN_HI->at(2)*CSN_HI->at(2))/(jtpt*jtpt)
  );

  return sigma;
}

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

//! (1) Setup
//! (1.1) Smearing functions for pp
float ztree::getSmearedPt(int jetindex,int centindex)
{
  if(centindex == 0)
    return jetpt_smeared0020[jetindex];
  else if(centindex == 20)
    return jetpt_smeared2060[jetindex];
  else if(centindex == 60)
    return jetpt_smeared60100[jetindex];
  else if(centindex == 100)
    return jetpt_smeared100200[jetindex];
  else
  {
    cout<<"centbin not supported"<<endl;
    exit(1);
  }
}

float ztree::getSmearedEta(int jetindex,int centindex)
{
  if(centindex == 0)
    return jeteta_smeared0020[jetindex];
  else if(centindex == 20)
    return jeteta_smeared2060[jetindex];
  else if(centindex == 60)
    return jeteta_smeared60100[jetindex];
  else if(centindex == 100)
    return jeteta_smeared100200[jetindex];
  else
  {
    cout<<"centbin not supported"<<endl;
    exit(1);
  }
}

float ztree::getSmearedPhi(int jetindex,int centindex)
{
  if(centindex == 0)
    return jetphi_smeared0020[jetindex];
  else if(centindex == 20)
    return jetphi_smeared2060[jetindex];
  else if(centindex == 60)
    return jetphi_smeared60100[jetindex];
  else if(centindex == 100)
    return jetphi_smeared100200[jetindex];
  else
  {
    cout<<"centbin not supported"<<endl;
    exit(1);
  }

}

float getTrkWeight(int trkindex, float * trkweight , string gen) {
  if(gen.compare("gengen")==0 || gen.compare("gengen0")==0 || gen.compare("recogen")==0) return 1;
  return trkweight[trkindex];
}

// this function does the raw FF analysis and writes histograms to output file
void ztree::ffgammajet(std::string outfname, int centmin, int centmax, float phoetmin, float phoetmax, int jetptcut, std::string gen, int checkjetid, int trkptmin, int gammaxi, int doJERsys)
{
  cout<<checkjetid<<endl; // doesn't do anything
  bool ismc;
  TFile * fvzweight = TFile::Open("fvzweight.root");
  TH1D * hvzweight = (TH1D*) fvzweight->Get("hvzdata");
  TFile * fcentweight = TFile::Open("fcentweight.root");
  TH1D * hcentweight = (TH1D*) fcentweight->Get(Form("hcentdata_%d_%d",centmin,centmax));

  string tag = outfname;
  string s_alpha = gen;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s_%d_%d.root",outfname.data(),tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),"recreate");

//! (1.2) List of histograms

//! (1.2) List of histograms
  TH1D * hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),40,0,0.02);
  TH1D * hgenjetpt = new TH1D(Form("hgenjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet p_{T};"),20,0,500);
  // TH1D * hgenjetpt_mix = new TH1D(Form("hgenjetpt_mix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet_mix p_{T};"),20,0,500);
  TH1D * hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmixsideband = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // Raw FF after cuts (1.0)
  TH1D * hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sideband Raw FF after cuts (1.1)
  TH1D * hgammaffxijetmix = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixsideband = new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxijetmixue = new TH1D(Form("hgammaffxijetmixue_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixuesideband = new TH1D(Form("hgammaffxijetmixuesideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxiuemix = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sub mix jet ff (3.0)
  TH1D * hgammaffxiuemixsideband = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // sideband sub mix jet ff (3.1)
  // TH1D * hgammaffxiuesiggen = new TH1D(Form("hgammaffxiuesiggen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // Raw FF after cuts (1.0)
  // TH1D * hgammaffxiuemixgen = new TH1D(Form("hgammaffxiuemixgen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,0,50); // Raw FF after cuts (1.0)
  // TH1D * hnjetperevt = new TH1D(Form("hnjetperevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  // TH1D * hnjetpermixevt = new TH1D(Form("hnjetpermixevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per mixed event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  TH1D * hnmixsignal = new TH1D(Form("hnmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * hnmixsideband = new TH1D(Form("hnmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * xjgsignal = new TH1D(Form("xjgsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgmixsignal = new TH1D(Form("xjgmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgsideband = new TH1D(Form("xjgsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgmixsideband = new TH1D(Form("xjgmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * phoetsignal = new TH1D(Form("phoetsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#gamma E_{T};"),50,0,500); // xjg crosscheck
  TH1D * phoetsideband = new TH1D(Form("phoetsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#gamma E_{T};"),50,0,500); // xjg crosscheck

  TH1D * hvz = new TH1D(Form("hvz_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";vz;"),30,-15,15); // vz weighting check
  TH1D * hcent = new TH1D(Form("hcent_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";cent;"),200,0,200); // vz weighting check

  // iterators
  int ij=-1, ij_mix=-1, ip=-1, ip_mix=-1;
  int nij=-1, nij_mix=-1, nip=-1, nip_mix=-1;
  Int_t * j_ev_mix=0;
  Int_t * p_ev_mix=0;

  Float_t * j_pt=0;
  Float_t * p_pt=0;
  Float_t * p_pt_mix=0;
  Float_t * j_pt_mix=0;
  Float_t * j_eta=0;
  Float_t * j_eta_mix=0;
  Float_t * p_eta=0;
  Float_t * p_eta_mix=0;
  Float_t * j_phi=0;
  Float_t * j_phi_mix=0;
  Float_t * p_phi=0;
  Float_t * p_phi_mix=0;
  // bool something = false;
//! (2) Loop
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) { cout<<jentry<<"/"<<nentries<<endl; }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain->GetEntry(jentry);   nbytes += nb;
    float_to_int(trkFromEv_mix,trkFromEv_mix_int,nTrk_mix);
//! (2.1) Event selections
    if(!isPP)
    {
      if(hiBin < centmin || hiBin >= centmax) continue; //centrality cut
    }
    if(nPho!=1) continue;
    if(phoNoise[0]==0) continue;
    // if( gen.compare("gengen")==0 && mcMomPID[0]!=-999 ) continue ; // prompt gen photon cut
    bool signal = (phoSigmaIEtaIEta_2012[0]<0.010);
    bool sideband = (phoSigmaIEtaIEta_2012[0]>0.011 && phoSigmaIEtaIEta_2012[0]<0.017);
    if( phoEt[0]/phoCorr[0]<phoetmin || phoEt[0]/phoCorr[0]>phoetmax) continue;
    if(signal) {
      phoetsignal->Fill(phoEtCorrected[0]);
    }
    if(sideband) {
      phoetsideband->Fill(phoEtCorrected[0]);
    }

    ismc = (weight!=0);
    weight=1;
    if(ismc) weight = weight * hvzweight->GetBinContent(hvzweight->FindBin(vz));
    if(ismc && !isPP) weight = weight * hcentweight->GetBinContent(hcentweight->FindBin(hiBin));
//! now we'll loop through the different jet collections first, reco, gen, recomix, and genmix

    hvz->Fill(vz,weight);
    hcent->Fill(hiBin,weight);

    int njets_perevent = 0;
    int njets_permixevent = 0;

    if(gen.compare("recoreco")==0 || gen.compare("recogen")==0) {
      nij = njet;
      j_pt = jetptCorr;
      j_eta = jeteta;
      j_phi = jetphi;
      nij_mix = njet_mix;
      j_pt_mix = jetpt_mix;
      j_eta_mix = jeteta_mix;
      j_phi_mix = jetphi_mix;
      j_ev_mix = nmixEv_mix;
    }
    else if(gen.compare("genreco")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
      nij = ngen;
      j_pt = genpt;
      j_eta = geneta;
      j_phi = genphi;
      nij_mix = ngen_mix;
      j_pt_mix = genpt_mix;
      j_eta_mix = geneta_mix;
      j_phi_mix = genphi_mix;
      j_ev_mix = genev_mix;
    }
    if(gen.compare("recoreco")==0 || gen.compare("genreco")==0) {
      nip = nTrk;
      p_pt = trkPt;
      p_eta = trkEta;
      p_phi = trkPhi;
      nip_mix = nTrk_mix;
      p_pt_mix = trkPt_mix;
      p_eta_mix = trkEta_mix;
      p_phi_mix = trkPhi_mix;
      p_ev_mix = trkFromEv_mix_int;
    }
    else if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
      nip = mult;
      p_pt = pt;
      p_eta = eta;
      p_phi = phi;
      nip_mix = mult_mix;
      p_pt_mix = pt_mix;
      p_eta_mix = eta_mix;
      p_phi_mix = phi_mix;
      p_ev_mix = nev_mix;
    }

    //! Jet loop
    for (ij = 0; ij < nij; ij++) {
      if( gen.compare("gengen0")==0 && gensubid[ij]!=0 ) continue;
      float tmpjetpt = j_pt[ij];
      // float tmpjetpt = gjetpt[ijet];
      float tmpjeteta = j_eta[ij];
      float tmpjetphi = j_phi[ij];
      if( gen.compare("gengen")==0  || gen.compare("genreco")==0 || gen.compare("gengen0")==0) {
        tmpjetpt *= smeargenpt(isPP,hiBin);
        tmpjeteta *= smeargeneta(isPP,hiBin);
        tmpjetphi *= smeargenphi(isPP,hiBin);
      }

//! apply smearing if pp
      if(isPP)
      {
        tmpjetpt = getSmearedPt(ij*100,centmin);
        // tmpjeteta = getSmearedEta(ijet*100,centmin);
        tmpjetphi = getSmearedPhi(ij*100,centmin);
      }
      // apply JER systematic uncertainty for PbPb
      float smearFactor = 1;
      if (doJERsys) {
        float SF = 1 + 0.15;
        int resolutionBin = getResolutionBin(centmin);
        float initialResolution = getResolutionHI(tmpjetpt, resolutionBin);
        smearFactor = randSmearing.Gaus(1, SF* initialResolution * sqrt(SF*SF - 1));
        tmpjetpt *= smearFactor;
      }
//! jet selections
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta Cut
      if( acos(cos(tmpjetphi - phoPhi[0])) < 7 * pi / 8 ) continue;
      // cout<<jentry<<" "<<tmpjetpt<<" "<<tmpjeteta<<" "<<tmpjetphi<<endl;
      // exit(1);
      if(signal) {
        // cout<<ijet<<" "<<jetphi[ijet]<<","<<jeteta[ijet]<<endl;
        hjetpt->Fill(tmpjetpt);
        hgenjetpt->Fill(tmpjetpt);
        njets_perevent++;
        xjgsignal->Fill(tmpjetpt/phoEtCorrected[0]);
      }
      if(sideband) {
        hjetptsideband->Fill(tmpjetpt);
        xjgsideband->Fill(tmpjetpt/phoEtCorrected[0]);
      }
      hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012[0]);
      TLorentzVector vjet;
      if(isPP)  vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);
      else      vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);

      if(gen.compare("recogen")==0) {}
      for(ip = 0 ; ip < nip ; ++ip)
      {
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if(chg[ip]==0) continue;
        }
        if(gen.compare("gengen0")==0) {
          if(sube[ip]!=0) continue;
        }

        if(p_pt[ip]<trkptmin) continue;
        float dphi = acos( cos(tmpjetphi - p_phi[ip]));
        float deta = fabs( tmpjeteta - p_eta[ip]);
        float dr = sqrt((dphi*dphi)+(deta*deta));
        if(dr<0.3)
        {
          TLorentzVector vtrack;
          vtrack.SetPtEtaPhiM(p_pt[ip],p_eta[ip],p_phi[ip],0);
          float angle = vjet.Angle(vtrack.Vect());
          float z = p_pt[ip]*cos(angle)/tmpjetpt;
          if(gammaxi==1) z = p_pt[ip]*cos(angle)/phoEtCorrected[0];
          float xi = log(1.0/z);
          if(signal) { hgammaffxi->Fill(p_pt[ip],weight*getTrkWeight(ip,trkWeight,gen)); }
          if(sideband) { hgammaffxisideband->Fill(p_pt[ip],weight*getTrkWeight(ip,trkWeight,gen)); }
        }
      }
      float nmixedUEevents = (nmix+2)/3;
      for(ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
      {
        if(p_pt_mix[ip_mix]<trkptmin) continue;
        if((p_ev_mix[ip_mix])%3!=0) continue;
        if(((int)p_ev_mix[ip_mix])%3!=0) continue;
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if(chg_mix[ip_mix]==0) continue;
        }
        float dphi = acos( cos(tmpjetphi - p_phi_mix[ip_mix]));
        float deta = fabs( tmpjeteta - p_eta_mix[ip_mix]);
        float dr = sqrt((dphi*dphi)+(deta*deta));
        if(dr<0.3)
        {
          TLorentzVector vtrack;
          vtrack.SetPtEtaPhiM(p_pt_mix[ip_mix],p_eta_mix[ip_mix],p_phi_mix[ip_mix],0);
          float angle = vjet.Angle(vtrack.Vect());
          float z = p_pt_mix[ip_mix]*cos(angle)/tmpjetpt;
          if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected[0];
          float xi = log(1.0/z);
          if(signal) {
            hgammaffxiuemix->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedUEevents);
          }
          if(sideband) { hgammaffxiuemixsideband->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedUEevents); }
        }
      }
    }

//! (2.4) Mix jet loop
    float nmixedjetevents = (nmix+1)/3;
    // nmixedjetevents = 1;
    for (ij_mix = 0; ij_mix < nij_mix; ij_mix++) {
      float tmpjetpt = j_pt_mix[ij_mix];
      float tmpjeteta = j_eta_mix[ij_mix];
      float tmpjetphi = j_phi_mix[ij_mix];
      if( gen.compare("gengen")==0  || gen.compare("genreco")==0  || gen.compare("gengen0")==0) {
        tmpjetpt *= smeargenpt(isPP,hiBin);
        tmpjeteta *= smeargeneta(isPP,hiBin);
        tmpjetphi *= smeargenphi(isPP,hiBin);
      }
      if( j_ev_mix[ij_mix]%3!= 1) continue;
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta_mix Cut
      if( acos(cos(tmpjetphi - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal) {
        hjetptjetmix->Fill(tmpjetpt,1./nmixedjetevents); // TODO: double check this
        njets_permixevent++;
        hnmixsignal->Fill(1);
        xjgmixsignal->Fill(tmpjetpt/phoEtCorrected[0],1/nmixedjetevents);
      }
      if(sideband) {
        hjetptjetmixsideband->Fill(tmpjetpt,1./nmixedjetevents);
        hnmixsideband->Fill(1);
        xjgmixsideband->Fill(tmpjetpt/phoEtCorrected[0],1/nmixedjetevents);
      }
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);
      if(gen.compare("recoreco")==0 || gen.compare("recogen")==0) {
        // jetmix
        for(int ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
        { // mix reco jet mix reco track
          if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
            if(chg_mix[ip_mix]==0) continue;
          }
          if(p_pt_mix[ip_mix]<trkptmin) continue;
          if(j_ev_mix[ij_mix]!=p_ev_mix[ip_mix]) continue; // tracks and jet come from same mixed event
          float dphi = acos( cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs( tmpjeteta - p_eta_mix[ip_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(p_pt_mix[ip_mix],p_eta_mix[ip_mix],p_phi_mix[ip_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = p_pt_mix[ip_mix]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected[0];
            float xi = log(1.0/z);
//! 1-2: rjet_mix rtrk_mix
            if(signal) {
              hgammaffxijetmix->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
            }
            if(sideband) {
              hgammaffxijetmixsideband->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
            }
          }
        }
        // jetmixue
        for(int ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
        { // mix reco jet mix reco track
          if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
            if(chg_mix[ip_mix]==0) continue;
          }
          if(p_pt_mix[ip_mix]<trkptmin) continue;
          if(j_ev_mix[ij_mix]!=(p_ev_mix[ip_mix]+1)) continue;
          float dphi = acos( cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs( tmpjeteta - p_eta_mix[ip_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(p_pt_mix[ip_mix],p_eta_mix[ip_mix],p_phi_mix[ip_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = p_pt_mix[ip_mix]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected[0];
            float xi = log(1.0/z);
//! 1-4: rjet_mix rtrk_mix
            if(signal) {
              hgammaffxijetmixue->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
            }
            if(sideband) {
              hgammaffxijetmixuesideband->Fill(p_pt_mix[ip_mix],weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
            }
          }
        }
      }
    }
    // if(something) break;
  }
  fout->Write();
  fout->Close();
}

int main(int argc, char *argv[])
{
  if(argc > 12 || argc < 3 )
  {
    std::cout<<"usage: ./ffgamma.exe <infilename> <outfilename> [centmin centmax] [phoetmin] [phoetmax] [gen] [checkjetid] [trkptmin]"<<std::endl;
    exit(1);
  }
  ztree * t = new ztree(argv[1]);
  if (argc==3) {
    t->ffgammajet(argv[2]);
  }
  if (argc==5) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]));
  }
  if (argc==6) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]));
  }
  if (argc==7) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]));
  }
  if (argc==8) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]));
  }
  if (argc==9) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8]);
  }
  if (argc==10) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]));
  }
  if (argc==11) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atoi(argv[10]));
  }
  if (argc==12) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atoi(argv[10]),std::atoi(argv[11]));
  }
  if (argc==13) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atoi(argv[10]),std::atoi(argv[11]),std::atoi(argv[12]));
  }
  // cout<<argc<<endl;
  return 0;
}
