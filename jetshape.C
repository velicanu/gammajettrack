#define ztree_cxx
#include "jetshape.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>

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

float getdr(float eta1, float phi1, float eta2 , float phi2) {
  float dphi = acos(cos(phi1 - phi2));
  float deta = eta1-eta2;
  return sqrt((deta*deta)+(dphi*dphi));
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

// this function does the raw FF analysis and writes histograms to output file
void ztree::ffgammajet(std::string outfname, int centmin, int centmax, float phoetmin, float phoetmax, int jetptcut, std::string gen, int checkjetid, int trkptmin, int gammaxi, int trkptmax)
{
  string tag = outfname;
  string s_alpha = gen;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%d_%d_%d.root",tag.data(),s_alpha.data(),(int)phoetmin,abs(centmin),abs(centmax)),"recreate");

//! (1.2) List of histograms
  TH1D * hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),40,0,0.02);
  TH1D * hgenjetpt = new TH1D(Form("hgenjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet p_{T};"),20,0,500);
  TH1D * hgenjetpt_mix = new TH1D(Form("hgenjetpt_mix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet_mix p_{T};"),20,0,500);
  TH1D * hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmixsideband = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // Raw FF after cuts (1.0)
  TH1D * hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sideband Raw FF after cuts (1.1)
  TH1D * hgammaffxijetmix = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixsideband = new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxijetmixue = new TH1D(Form("hgammaffxijetmixue_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixuesideband = new TH1D(Form("hgammaffxijetmixuesideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxiuemix = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sub mix jet ff (3.0)
  TH1D * hgammaffxiuemixsideband = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // sideband sub mix jet ff (3.1)
  TH1D * hgammaffxiuesiggen = new TH1D(Form("hgammaffxiuesiggen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // Raw FF after cuts (1.0)
  TH1D * hgammaffxiuemixgen = new TH1D(Form("hgammaffxiuemixgen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";r;#rho"),20,0,1); // Raw FF after cuts (1.0)
  TH1D * hnjetperevt = new TH1D(Form("hnjetperevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  TH1D * hnjetpermixevt = new TH1D(Form("hnjetpermixevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per mixed event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  TH1D * hnmixsignal = new TH1D(Form("hnmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";;"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * hnmixsideband = new TH1D(Form("hnmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";;"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * xjgsignal = new TH1D(Form("xjgsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgmixsignal = new TH1D(Form("xjgmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgsideband = new TH1D(Form("xjgsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * xjgmixsideband = new TH1D(Form("xjgmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";xjg;"),16,0,2); // xjg crosscheck
  TH1D * phoetsignal = new TH1D(Form("phoetsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#gamma E_{T};"),50,0,500); // xjg crosscheck
  TH1D * phoetsideband = new TH1D(Form("phoetsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#gamma E_{T};"),50,0,500); // xjg crosscheck





//! (2) Loop
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) { cout<<jentry<<"/"<<nentries<<endl; }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain->GetEntry(jentry);   nbytes += nb;
//! (2.1) Event selections
    if(!isPP)
    {
      if(hiBin < centmin || hiBin >= centmax) continue; //centrality cut
    }
    if(nPho!=1) continue;
    if(phoNoise[0]==0) continue;
    if(weight==0)                   weight=1;
    bool signal = (phoSigmaIEtaIEta_2012[0]<0.010);
    bool sideband = (phoSigmaIEtaIEta_2012[0]>0.011 && phoSigmaIEtaIEta_2012[0]<0.017);
    if( phoEt[0]/phoCorr[0]<phoetmin || phoEt[0]/phoCorr[0]>phoetmax) continue;
    if(signal) {
      phoetsignal->Fill(phoEt[0]/phoCorr[0]);
    }
    if(sideband) {
      phoetsideband->Fill(phoEt[0]/phoCorr[0]);
    }

//! now we'll loop through the different jet collections first, reco, gen, recomix, and genmix

    int njets_perevent = 0;
    int njets_permixevent = 0;
    bool something = false;

//! (2.2) Reco jet loop
    int njetloop = njet;
    for (int ijet = 0; ijet < njetloop; ijet++) {
      float tmpjetpt = jetptCorr[ijet];
      // float tmpjetpt = gjetpt[ijet];
      float tmpjeteta = jeteta[ijet];
      float tmpjetphi = jetphi[ijet];
//! apply smearing if pp
      if(isPP)
      {
        tmpjetpt = getSmearedPt(ijet*100,centmin);
        // tmpjeteta = getSmearedEta(ijet*100,centmin);
        tmpjeteta = getSmearedPhi(ijet*100,centmin);
      }
//! jet selections
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta Cut
      if(checkjetid==1)
      {
        if( jetID[ijet]==0 ) continue;
      }
      if( acos(cos(tmpjetphi - phoPhi[0])) < 7 * pi / 8 ) continue;

      if(signal) {
        // cout<<ijet<<" "<<jetphi[ijet]<<","<<jeteta[ijet]<<endl;
        hjetpt->Fill(tmpjetpt);
        njets_perevent++;
        if(jetptCorr[ijet]!=-1) { xjgsignal->Fill(jetptCorr[ijet]/phoEt[0]*phoCorr[0]); }
        else                    { xjgsignal->Fill(jetpt[ijet]/phoEt[0]*phoCorr[0]); }
      }
      if(sideband) {
        hjetptsideband->Fill(tmpjetpt);
        if(jetptCorr[ijet]!=-1) { xjgsideband->Fill(jetptCorr[ijet]/phoEt[0]*phoCorr[0]); }
        else                    { xjgsideband->Fill(jetpt[ijet]/phoEt[0]*phoCorr[0]); }
      }
      hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012[0]);
      TLorentzVector vjet;
      if(isPP)  vjet.SetPtEtaPhiM(jetptCorr[ijet],tmpjeteta,tmpjetphi,0);
      else      vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);

      if(gen.compare("recogen")==0)
      {
        for(int igen = 0 ; igen < mult ; ++igen)
        {
          if(chg[igen]==0) continue;
          if(pt[igen]<trkptmin) continue;
          float dphi = acos( cos(tmpjetphi - phi[igen]));
          float deta = fabs( tmpjeteta - eta[igen]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt[igen],eta[igen],phi[igen],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt[igen]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = pt[igen]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);

            if(sube[igen] == 0) { // signal particles
              if(signal) { hgammaffxi->Fill(xi); } //recoj genp
              if(sideband) { hgammaffxisideband->Fill(xi); }
            } else { // underlying event
              if(signal) { hgammaffxiuesiggen->Fill(xi); }
              if(sideband) { } // so far nothing
            }
          }
        }
        for(int igen_mix = 0 ; igen_mix < mult_mix ; ++igen_mix)
        {
          if(chg_mix[igen_mix]==0) continue;
          float dphi = acos( cos(tmpjetphi - phi_mix[igen_mix]));
          float deta = fabs( tmpjeteta - eta_mix[igen_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt_mix[igen_mix],eta_mix[igen_mix],phi_mix[igen_mix],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt_mix[igen_mix]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = pt_mix[igen_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            hgammaffxiuemixgen->Fill(xi,2.0/(float)nmix);
          }
        }
      }
      else if(gen.compare("recoreco")==0)
      {
        for (int itrk = 0; itrk < nTrk; itrk++) { // reco jet reco track
          if(trkPt[itrk]<trkptmin) continue;
          float dphi = acos( cos(jetphi[ijet] - trkPhi[itrk]));
          float deta = fabs( jeteta[ijet] - trkEta[itrk]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = trkPt[itrk]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = trkPt[itrk]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta[itrk],trkPhi[itrk],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-1: rjet rtrk
            if(signal) {
              something = true;
              // cout<<"sig: "<<jentry<<" "<<trkEta[itrk]<<" "<<trkPhi[itrk]<<" "<<trkPt[itrk]<<" "<<trkWeight[itrk]<<" "<<endl;
              hgammaffxi->Fill(xi,trkWeight[itrk]*trkPt[itrk]/(tmpjetpt)); //Raw FF after cuts (1.0)
              // hgammaffxi->Fill(xi); //Raw FF after cuts (1.0)
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]*trkPt[itrk]/(tmpjetpt)); // Raw FF after cuts sideband (1.1)
              // hgammaffxisideband->Fill(xi); // Raw FF after cuts sideband (1.1)
            }
          }
        }
      }
      if(gen.compare("recoreco")==0) {
        float nmixedUEevents = (nmix+2)/3; //
        // nmixedUEevents = 1;
        // cout<<jentry<<" "<<nTrk_mix<<endl;
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix) { // reco jet UE track
          // cout<<itrk_mix<<" "<<trkPt_mix[itrk_mix]<<" "<<trkFromEv_mix[itrk_mix]<<endl;
          if(trkPt_mix[itrk_mix]<trkptmin) continue;
          if(((int)trkFromEv_mix[itrk_mix])%3!=0) continue;
          float dphi = acos( cos(tmpjetphi - trkPhi_mix[itrk_mix]));
          float deta = fabs( tmpjeteta - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          // cout<<itrk_mix<<" "<<trkPhi_mix[itrk_mix]<<" "<<tmpjetphi<<" , "<<trkEta_mix[itrk_mix]<<" "<<tmpjeteta<<" , "<<dr<<endl;
          if(dr<1)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = trkPt_mix[itrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-3: rjet rtrk_mix
            if(signal) {
              // cout<<"bak: "<<jentry<<" "<<trkEta_mix[itrk_mix]<<" "<<trkPhi_mix[itrk_mix]<<" "<<trkPt_mix[itrk_mix]<<" "<<trkWeight_mix[itrk_mix]<<" "<<endl;
              something = true;
              hgammaffxiuemix->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedUEevents);
              // ntotmix++;
            }
            if(sideband) {
              hgammaffxiuemixsideband->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedUEevents);
            }
          }
        }
      }
    }
    if(something)
    {
      // int step = 0;
      // cin >> step;
    }
//! (2.3) Gen jet loop
    for (int igenjet = 0; igenjet < ngen; igenjet++) {
      if( gen.compare("gengen")==0 && gensubid[igenjet]!=0) continue;
      if( genpt[igenjet]<jetptcut ) continue; //jet pt Cut
      if( fabs(geneta[igenjet]) > 1.6) continue; //jeteta Cut
      if( acos(cos(genphi[igenjet] - phoPhi[0])) < 7 * pi / 8 ) continue;
      // float sigmapt = getSigmaRelPt(hiBin,genpt[igenjet]);
      // float tmpjetpt = genpt[igenjet]*randSmearing.Gaus(1,sigmapt);
      float tmpjetpt = genpt[igenjet];
      float tmpjeteta = geneta[igenjet];
      float tmpjetphi = genphi[igenjet];

      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(tmpjetpt,geneta[igenjet],genphi[igenjet],0);
      if(signal) { hgenjetpt->Fill(tmpjetpt); }

      if(gen.compare("genreco")==0)
      {
        for (int itrk = 0; itrk < nTrk; itrk++) { // reco jet reco track
          if(trkPt[itrk]<trkptmin) continue;
          if(trkPt[itrk]>trkptmax) continue;
          float dphi = acos( cos(genphi[igenjet] - trkPhi[itrk]));
          float deta = fabs( geneta[igenjet] - trkEta[itrk]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = trkPt[itrk]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = trkPt[itrk]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta[itrk],trkPhi[itrk],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-1: gjet rtrk
            if(signal) {
              something = true;
              // cout<<"sig: "<<jentry<<" "<<trkEta[itrk]<<" "<<trkPhi[itrk]<<" "<<trkPt[itrk]<<" "<<trkWeight[itrk]<<" "<<endl;
              hgammaffxi->Fill(xi,trkWeight[itrk]*trkPt[itrk]/(tmpjetpt)); //Raw FF after cuts (1.0)
              // hgammaffxi->Fill(xi); //Raw FF after cuts (1.0)
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]*trkPt[itrk]/(tmpjetpt)); // Raw FF after cuts sideband (1.1)
              // hgammaffxisideband->Fill(xi); // Raw FF after cuts sideband (1.1)
            }
          }
        }
        float nmixedUEevents = (nmix+2)/3; //
        // nmixedUEevents = 1;
        // cout<<jentry<<" "<<nTrk_mix<<endl;
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix) { // reco jet UE track
          // cout<<itrk_mix<<" "<<trkPt_mix[itrk_mix]<<" "<<trkFromEv_mix[itrk_mix]<<endl;
          if(trkPt_mix[itrk_mix]<trkptmin) continue;
          if(trkPt_mix[itrk_mix]>trkptmax) continue;
          if(((int)trkFromEv_mix[itrk_mix])%3!=0) continue;
          float dphi = acos( cos(genphi[igenjet] - trkPhi_mix[itrk_mix]));
          float deta = fabs( geneta[igenjet] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          // cout<<itrk_mix<<" "<<trkPhi_mix[itrk_mix]<<" "<<tmpjetphi<<" , "<<trkEta_mix[itrk_mix]<<" "<<tmpjeteta<<" , "<<dr<<endl;
          if(dr<1)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/genpt[igenjet];
            if(gammaxi==1) z = trkPt_mix[itrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-3: gjet rtrk_mix
            if(signal) {
              // cout<<"bak: "<<jentry<<" "<<trkEta_mix[itrk_mix]<<" "<<trkPhi_mix[itrk_mix]<<" "<<trkPt_mix[itrk_mix]<<" "<<trkWeight_mix[itrk_mix]<<" "<<endl;
              something = true;
              hgammaffxiuemix->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedUEevents);
              // ntotmix++;
            }
            if(sideband) {
              hgammaffxiuemixsideband->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedUEevents);
            }
          }
        }
      }
      if(gen.compare("gengen")==0 || gen.compare("mixgen")==0)
      {
        for(int igentrk = 0 ; igentrk < mult ; ++igentrk)
        {
          if(gen.compare("gengen")==0 && sube[igentrk]!=0) continue;
          if(chg[igentrk]==0) continue;
          if(pt[igentrk]<trkptmin) continue;
          if(pt[igentrk]>trkptmax) continue;

          float dphi = acos( cos(genphi[igenjet] - phi[igentrk]));
          float deta = fabs( geneta[igenjet] - eta[igentrk]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt[igentrk],eta[igentrk],phi[igentrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt[igentrk]*cos(angle)/tmpjetpt;
            if(gammaxi==1) z = pt[igentrk]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(eta[igentrk],phi[igentrk],tmpjeteta,tmpjetphi);
            xi = deltar;
  //! 2-1: gjet gtrk sube==0
  //! 3-1: gjet gtrk
            if(signal) { hgammaffxi->Fill(xi,pt[igentrk]/(tmpjetpt)); } //recoj genp
            if(sideband) { hgammaffxisideband->Fill(xi,pt[igentrk]/(tmpjetpt)); }
          }
        }
      }
//! 3-3: gjet gtrk
      if(gen.compare("mixgen")==0)
      {
        for(int igentrk_mix = 0 ; igentrk_mix < mult_mix ; ++igentrk_mix)
        {
          if(chg[igentrk_mix]==0) continue;
          if(pt[igentrk_mix]<trkptmin) continue;
          if(pt[igentrk_mix]>trkptmax) continue;

          float dphi = acos( cos(genphi[igenjet] - phi_mix[igentrk_mix]));
          float deta = fabs( geneta[igenjet] - eta_mix[igentrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt_mix[igentrk_mix],eta_mix[igentrk_mix],phi_mix[igentrk_mix],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt_mix[igentrk_mix]*cos(angle)/genpt[igenjet];
            if(gammaxi==1) z = pt_mix[igentrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
  //! 3-2: gjet_mix gtrk_mix
            if(signal) { hgammaffxiuemix->Fill(xi); }
            if(sideband) { hgammaffxiuemixsideband->Fill(xi); }
          }
        }
      }
    }

//! (2.4) Mix reco jet loop
    float nmixedjetevents = (nmix+1)/3;
    // nmixedjetevents = 1;
    for (int ijet_mix = 0; ijet_mix < njet_mix; ijet_mix++) {
      if( nmixEv_mix[ijet_mix]%3!= 1) continue;
      if( jetpt_mix[ijet_mix]<jetptcut ) continue; //jet pt Cut
      if( fabs(jeteta_mix[ijet_mix]) > 1.6) continue; //jeteta_mix Cut
      if(checkjetid==1)
      {
        if( jetID_mix[ijet_mix]==0 ) continue;
      }
      if( acos(cos(jetphi_mix[ijet_mix] - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal && nmixEv_mix[ijet_mix]%3==1) {
        hjetptjetmix->Fill(jetpt_mix[ijet_mix],1./nmixedjetevents); // TODO: double check this
        njets_permixevent++;
        hnmixsignal->Fill(1);
        xjgmixsignal->Fill(jetpt_mix[ijet_mix]/phoEt[0]*phoCorr[0],1/nmixedjetevents);
      }
      if(sideband && nmixEv_mix[ijet_mix]%3==1) {
        hjetptjetmixsideband->Fill(jetpt_mix[ijet_mix],1./nmixedjetevents);
        hnmixsideband->Fill(1);
        xjgmixsideband->Fill(jetpt_mix[ijet_mix]/phoEt[0]*phoCorr[0],1/nmixedjetevents);
      }
      float tmpjetpt = jetpt_mix[ijet_mix];
      float tmpjeteta = jeteta_mix[ijet_mix];
      float tmpjetphi = jetphi_mix[ijet_mix];
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(jetpt_mix[ijet_mix],jeteta_mix[ijet_mix],jetphi_mix[ijet_mix],0);
      if(gen.compare("gen")==0)
      {
        // no jet mixing in gen ff
      } else if(gen.compare("recoreco")==0 || gen.compare("genreco")==0) {
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        { // mix reco jet mix reco track
          if(trkPt_mix[itrk_mix]<trkptmin) continue;
          if(trkPt_mix[itrk_mix]>trkptmax) continue;
          if(nmixEv_mix[ijet_mix]!=trkFromEv_mix[itrk_mix]) continue; // 1 mod 3
          float dphi = acos( cos(jetphi_mix[ijet_mix] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta_mix[ijet_mix] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt_mix[ijet_mix];
            if(gammaxi==1) z = trkPt_mix[itrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-2: rjet_mix rtrk_mix
            if(signal) {
              // cout<<"bak: "<<jentry<<" "<<trkEta_mix[itrk_mix]<<" "<<trkPhi_mix[itrk_mix]<<" "<<trkPt_mix[itrk_mix]<<" "<<trkWeight_mix[itrk_mix]<<" "<<endl;
              something = true;
              hgammaffxijetmix->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedjetevents);
              // ntotmix++;
            }
            if(sideband) {
              hgammaffxijetmixsideband->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedjetevents);
            }
          }
        }

        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        { // mix reco jet mix reco track
          if(trkPt_mix[itrk_mix]<trkptmin) continue;
          if(trkPt_mix[itrk_mix]>trkptmax) continue;
          if(nmixEv_mix[ijet_mix]!=(trkFromEv_mix[itrk_mix]+1)) continue;
          float dphi = acos( cos(jetphi_mix[ijet_mix] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta_mix[ijet_mix] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt_mix[ijet_mix];
            if(gammaxi==1) z = trkPt_mix[itrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],tmpjeteta,tmpjetphi);
            xi = deltar;
//! 1-4: rjet_mix rtrk_mix
            if(signal) {
              hgammaffxijetmixue->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedjetevents);
            }
            if(sideband) {
              hgammaffxijetmixuesideband->Fill(xi,trkWeight_mix[itrk_mix]*trkPt_mix[itrk_mix]/(tmpjetpt)/nmixedjetevents);
            }
          }
        }
      }
    }

//! (2.5) Mix gen jet loop
    if(gen.compare("mixgen")==0)
    {
      for (int igenjet_mix = 0; igenjet_mix < ngen_mix; igenjet_mix++) {
        if( genpt_mix[igenjet_mix]<jetptcut ) continue; //jet pt Cut
        if( fabs(geneta_mix[igenjet_mix]) > 1.6) continue; //jeteta Cut
        if( acos(cos(genphi_mix[igenjet_mix] - phoPhi[0])) < 7 * pi / 8 ) continue;
        float tmpjetpt = genpt_mix[igenjet_mix];
        float tmpjeteta = geneta_mix[igenjet_mix];
        float tmpjetphi = genphi_mix[igenjet_mix];
        TLorentzVector vjet;
        vjet.SetPtEtaPhiM(genpt_mix[igenjet_mix],geneta_mix[igenjet_mix],genphi_mix[igenjet_mix],0);
        if(signal) { hgenjetpt_mix->Fill(genpt[igenjet_mix]); }
        for(int igentrk_mix = 0 ; igentrk_mix < mult_mix ; ++igentrk_mix)
        {
          if(chg[igentrk_mix]==0) continue;
          if(pt[igentrk_mix]<trkptmin) continue;
          if(pt[igentrk_mix]>trkptmax) continue;

          float dphi = acos( cos(genphi_mix[igenjet_mix] - phi_mix[igentrk_mix]));
          float deta = fabs( geneta_mix[igenjet_mix] - eta_mix[igentrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<1)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt_mix[igentrk_mix],eta_mix[igentrk_mix],phi_mix[igentrk_mix],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt_mix[igentrk_mix]*cos(angle)/genpt_mix[igenjet_mix];
            if(gammaxi==1) z = pt_mix[igentrk_mix]*cos(angle)/(phoEt[0]*phoCorr[0]);
            float xi = log(1.0/z);
            float deltar = getdr(eta_mix[igentrk_mix],phi_mix[igentrk_mix],tmpjeteta,tmpjetphi);
            xi = deltar;
  //! 3-2: gjet_mix gtrk_mix
            if(signal) { hgammaffxijetmix->Fill(xi,pt_mix[igentrk_mix]/(tmpjetpt)); }
            if(sideband) { hgammaffxijetmixsideband->Fill(xi,pt_mix[igentrk_mix]/(tmpjetpt)); }
          }
        }
      }
    }
    hnjetperevt->Fill(njets_perevent);
    hnjetpermixevt->Fill(njets_permixevent);

  }
  fout->Write();
  fout->Close();
}



int main(int argc, char *argv[])
{
  if(argc > 13 || argc < 3 )
  {
    std::cout<<"usage: ./ffgamma.exe <infilename> <outfilename> [centmin centmax] [phoetmin] [phoetmax] [gen] [checkjetid] [trkptmin] [gammaxi] [trkptmax]"<<std::endl;
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
