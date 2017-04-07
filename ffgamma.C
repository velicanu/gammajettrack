#include "photonjettrack.h"

#include <TRandom3.h>
#include <TH1.h>
#include "TLorentzVector.h"

#include <iostream>
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

TRandom3 randSmearing(12345);    // random number seed should be fixed or reproducible

float getTrkWeight(int trkindex, float * trkweight, std::string gen) {
  if(gen.compare("gengen")==0 || gen.compare("gengen0")==0 || gen.compare("recogen")==0) return 1;
  return trkweight[trkindex];
}

float getTrkWeight(int trkindex, std::vector<float>* trkweight, std::string gen) {
  if(gen.compare("gengen")==0 || gen.compare("gengen0")==0 || gen.compare("recogen")==0) return 1;
  return (*trkweight)[trkindex];
}

void photonjettrack::jetshape(std::string label, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string jet_part, float trkptmin, int gammaxi) { return; }

// this function does the raw FF analysis and writes histograms to output file
void photonjettrack::ffgammajet(std::string outfname, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string gen, int checkjetid, float trkptmin, int gammaxi, int doJERsys)
{
  bool ismc;
  TFile * fvzweight = TFile::Open("fvzweight.root");
  TH1D * hvzweight = (TH1D*) fvzweight->Get("hvzdata");
  TFile * fcentweight = TFile::Open("fcentweight.root");
  TH1D * hcentweight = (TH1D*) fcentweight->Get(Form("hcentdata_%d_%d",centmin,centmax));

  std::string tag = outfname;
  std::string s_alpha = gen;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s_%d_%d.root",outfname.data(),tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),"recreate");

//! (1.2) List of histograms
  TH1D * hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),40,0,0.02);
  TH1D * hgenjetpt = new TH1D(Form("hgenjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet p_{T};"),20,0,500);
  // TH1D * hgenjetpt_mix = new TH1D(Form("hgenjetpt_mix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet_mix p_{T};"),20,0,500);
  TH1D * hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmixsideband = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband Raw FF after cuts (1.1)
  TH1D * hgammaffxijetmix = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixsideband = new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxijetmixue = new TH1D(Form("hgammaffxijetmixue_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixuesideband = new TH1D(Form("hgammaffxijetmixuesideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxiuemix = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sub mix jet ff (3.0)
  TH1D * hgammaffxiuemixsideband = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband sub mix jet ff (3.1)
  // TH1D * hgammaffxiuesiggen = new TH1D(Form("hgammaffxiuesiggen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  // TH1D * hgammaffxiuemixgen = new TH1D(Form("hgammaffxiuemixgen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
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
  std::vector<int> j_ev_mix;
  std::vector<int> p_ev_mix;

  std::vector<float> j_pt;
  std::vector<float> p_pt;
  std::vector<float> p_pt_mix;
  std::vector<float> j_pt_mix;
  std::vector<float> j_eta;
  std::vector<float> j_eta_mix;
  std::vector<float> p_eta;
  std::vector<float> p_eta_mix;
  std::vector<float> j_phi;
  std::vector<float> j_phi_mix;
  std::vector<float> p_phi;
  std::vector<float> p_phi_mix;

  int isPP = 0;

//! (2) Loop
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) { std::cout<<jentry<<"/"<<nentries<<std::endl; }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain->GetEntry(jentry);   nbytes += nb;
//! (2.1) Event selections
    if(!isPP)
    {
      if(hiBin < centmin || hiBin >= centmax) continue; //centrality cut
    }
    // if(nPho!=1) continue;
    if(phoNoise==0) continue;
    // if( gen.compare("gengen")==0 && mcMomPID!=-999 ) continue ; // prompt gen photon cut
    bool signal = (phoSigmaIEtaIEta_2012<0.010);
    bool sideband = (phoSigmaIEtaIEta_2012>0.011 && phoSigmaIEtaIEta_2012<0.017);
    if( phoEt/phoCorr<phoetmin || phoEt/phoCorr>phoetmax) continue;
    if(signal) {
      phoetsignal->Fill(phoEtCorrected);
    }
    if(sideband) {
      phoetsideband->Fill(phoEtCorrected);
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
      j_pt = *jetptCorr;
      j_eta = *jeteta;
      j_phi = *jetphi;
      nij_mix = njet_mix;
      j_pt_mix = *jetpt_mix;
      j_eta_mix = *jeteta_mix;
      j_phi_mix = *jetphi_mix;
      j_ev_mix = *nmixEv_mix;
    }
    else if(gen.compare("genreco")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
      nij = ngen;
      j_pt = *genpt;
      j_eta = *geneta;
      j_phi = *genphi;
      nij_mix = ngen_mix;
      j_pt_mix = *genpt_mix;
      j_eta_mix = *geneta_mix;
      j_phi_mix = *genphi_mix;
      j_ev_mix = *genev_mix;
    }
    if(gen.compare("recoreco")==0 || gen.compare("genreco")==0) {
      nip = nTrk;
      p_pt = *trkPt;
      p_eta = *trkEta;
      p_phi = *trkPhi;
      nip_mix = nTrk_mix;
      p_pt_mix = *trkPt_mix;
      p_eta_mix = *trkEta_mix;
      p_phi_mix = *trkPhi_mix;
      p_ev_mix = *trkFromEv_mix;
    }
    else if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
      nip = mult;
      p_pt = *pt;
      p_eta = *eta;
      p_phi = *phi;
      nip_mix = mult_mix;
      p_pt_mix = *pt_mix;
      p_eta_mix = *eta_mix;
      p_phi_mix = *phi_mix;
      p_ev_mix = *nev_mix;
    }

    //! Jet loop
    for (ij = 0; ij < nij; ij++) {
      if( gen.compare("gengen0")==0 && (*gensubid)[ij]!=0 ) continue;
      float tmpjetpt = j_pt[ij];
      // float tmpjetpt = gjetpt[ijet];
      float tmpjeteta = j_eta[ij];
      float tmpjetphi = j_phi[ij];
      if( gen.compare("gengen")==0  || gen.compare("genreco")==0 || gen.compare("gengen0")==0) {
        // tmpjetpt *= smeargenpt(isPP,hiBin);
        // tmpjeteta *= smeargeneta(isPP,hiBin);
        // tmpjetphi *= smeargenphi(isPP,hiBin);
      }

//! apply smearing if pp
      if(isPP)
      {
        // tmpjetpt = getSmearedPt(ij*100,centmin);
        // tmpjeteta = getSmearedEta(ijet*100,centmin);
        // tmpjetphi = getSmearedPhi(ij*100,centmin);
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
      bool dogensmearing = ( gen.compare("gengen")==0  || gen.compare("genreco")==0 || gen.compare("gengen0")==0 );
      // dogensmearing = false;
      if (dogensmearing) {
        int resolutionBin = getResolutionBin(centmin);
        float initialResolution = getResolutionHI(tmpjetpt, resolutionBin);
        smearFactor = randSmearing.Gaus(1, initialResolution);
        tmpjetpt *= smearFactor;
      }
//! jet selections
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta Cut
      if( acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8 ) continue;
      // cout<<jentry<<" "<<tmpjetpt<<" "<<tmpjeteta<<" "<<tmpjetphi<<endl;
      // exit(1);
      if(signal) {
        // cout<<ijet<<" "<<jetphi[ijet]<<","<<jeteta[ijet]<<endl;
        hjetpt->Fill(tmpjetpt);
        hgenjetpt->Fill(tmpjetpt);
        njets_perevent++;
        xjgsignal->Fill(tmpjetpt/phoEtCorrected);
      }
      if(sideband) {
        hjetptsideband->Fill(tmpjetpt);
        xjgsideband->Fill(tmpjetpt/phoEtCorrected);
      }
      hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012);
      TLorentzVector vjet;
      if(isPP)  vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);
      else      vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);

      if(gen.compare("recogen")==0) {}
      for(ip = 0 ; ip < nip ; ++ip)
      {
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if((*chg)[ip]==0) continue;
        }
        if(gen.compare("gengen0")==0) {
          if((*sube)[ip]!=0) continue;
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
          if(gammaxi==1) z = p_pt[ip]*cos(angle)/phoEtCorrected;
          float xi = log(1.0/z);
          if(signal) { hgammaffxi->Fill(xi,weight*getTrkWeight(ip,trkWeight,gen)); }
          if(sideband) { hgammaffxisideband->Fill(xi,weight*getTrkWeight(ip,trkWeight,gen)); }
        }
      }
      float nmixedUEevents = (nmix+1)/2;
      for(ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
      {
        if(p_pt_mix[ip_mix]<trkptmin) continue;
        if((p_ev_mix[ip_mix])%2!=0) continue;
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if((*chg_mix)[ip_mix]==0) continue;
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
          if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected;
          float xi = log(1.0/z);
          if(signal) {
            hgammaffxiuemix->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedUEevents);
          }
          if(sideband) { hgammaffxiuemixsideband->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedUEevents); }
        }
      }
    }

//! (2.4) Mix jet loop
    float nmixedjetevents = nmix/2;
    // nmixedjetevents = 1;
    for (ij_mix = 0; ij_mix < nij_mix; ij_mix++) {
      float tmpjetpt = j_pt_mix[ij_mix];
      float tmpjeteta = j_eta_mix[ij_mix];
      float tmpjetphi = j_phi_mix[ij_mix];
      if( gen.compare("gengen")==0  || gen.compare("genreco")==0  || gen.compare("gengen0")==0) {
        // tmpjetpt *= smeargenpt(isPP,hiBin);
        // tmpjeteta *= smeargeneta(isPP,hiBin);
        // tmpjetphi *= smeargenphi(isPP,hiBin);
      }
      float smearFactor = 1;
      bool dogensmearing = ( gen.compare("gengen")==0  || gen.compare("genreco")==0 || gen.compare("gengen0")==0 );
      // dogensmearing = false;
      if (dogensmearing) {
        int resolutionBin = getResolutionBin(centmin);
        float initialResolution = getResolutionHI(tmpjetpt, resolutionBin);
        smearFactor = randSmearing.Gaus(1, initialResolution);
        tmpjetpt *= smearFactor;
      }

      if( j_ev_mix[ij_mix]%2!= 1) continue;
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta_mix Cut
      if( acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8 ) continue;
      if(signal) {
        hjetptjetmix->Fill(tmpjetpt,1./nmixedjetevents); // TODO: double check this
        njets_permixevent++;
        hnmixsignal->Fill(1);
        xjgmixsignal->Fill(tmpjetpt/phoEtCorrected,1/nmixedjetevents);
      }
      if(sideband) {
        hjetptjetmixsideband->Fill(tmpjetpt,1./nmixedjetevents);
        hnmixsideband->Fill(1);
        xjgmixsideband->Fill(tmpjetpt/phoEtCorrected,1/nmixedjetevents);
      }
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(tmpjetpt,tmpjeteta,tmpjetphi,0);
      // jetmix
      for(int ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
      { // mix reco jet mix reco track
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if((*chg_mix)[ip_mix]==0) continue;
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
          if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected;
          float xi = log(1.0/z);
//! 1-2: rjet_mix rtrk_mix
          if(signal) {
            hgammaffxijetmix->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
          }
          if(sideband) {
            hgammaffxijetmixsideband->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
          }
        }
      }
      // jetmixue
      for(int ip_mix = 0 ; ip_mix < nip_mix ; ++ip_mix)
      { // mix reco jet mix reco track
        if(gen.compare("recogen")==0 || gen.compare("gengen")==0 || gen.compare("gengen0")==0) {
          if((*chg_mix)[ip_mix]==0) continue;
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
          if(gammaxi==1) z = p_pt_mix[ip_mix]*cos(angle)/phoEtCorrected;
          float xi = log(1.0/z);
//! 1-4: rjet_mix rtrk_mix
          if(signal) {
            hgammaffxijetmixue->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
          }
          if(sideband) {
            hgammaffxijetmixuesideband->Fill(xi,weight*getTrkWeight(ip_mix,trkWeight_mix,gen)/nmixedjetevents);
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
  photonjettrack* t = new photonjettrack(argv[1]);
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
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atof(argv[10]));
  }
  if (argc==12) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atof(argv[10]),std::atoi(argv[11]));
  }
  if (argc==13) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),std::atoi(argv[7]),argv[8],std::atoi(argv[9]),std::atof(argv[10]),std::atoi(argv[11]),std::atoi(argv[12]));
  }
  // cout<<argc<<endl;
  return 0;
}