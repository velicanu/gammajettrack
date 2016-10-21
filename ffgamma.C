#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
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
void ztree::ffgammajet(std::string outfname, int centmin, int centmax, float phoetmin, float phoetmax, int jetptcut, std::string gen, int checkjetid, int trkptmin)
{
  string tag = outfname;
  string s_alpha = gen;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s_%d_%d.root",outfname.data(),tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),"recreate");

//! (1.2) List of histograms
  TH1D * hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),40,0,0.02);
  TH1D * hgenjetpt = new TH1D(Form("hgenjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";genjet p_{T};"),20,0,500);
  TH1D * hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hjetptjetmixsideband = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband Raw FF after cuts (1.1)
  TH1D * hgammaffxijetmix = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sub mix jet ff (2.0)
  TH1D * hgammaffxijetmixsideband = new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband sub mix jet ff (2.1)
  TH1D * hgammaffxiuemix = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sub mix jet ff (3.0)
  TH1D * hgammaffxiuemixsideband = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // sideband sub mix jet ff (3.1)
  TH1D * hgammaffxiuesiggen = new TH1D(Form("hgammaffxiuesiggen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hgammaffxiuemixgen = new TH1D(Form("hgammaffxiuemixgen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hnjetperevt = new TH1D(Form("hnjetperevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  TH1D * hnjetpermixevt = new TH1D(Form("hnjetpermixevt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";nJets per mixed event;"),20,0.5,20.5); // Raw FF after cuts (1.0)
  TH1D * hnmixsignal = new TH1D(Form("hnmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * hnmixsideband = new TH1D(Form("hnmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
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
    if(phoNoise==0) continue;
    if(weight==0)                   weight=1;
    bool signal = (phoSigmaIEtaIEta_2012[0]<0.010);
    bool sideband = (phoSigmaIEtaIEta_2012[0]>0.011 && phoSigmaIEtaIEta_2012[0]<0.017);
    if( phoEt[0]/phoCorr[0]<phoetmin || phoEt[0]/phoCorr[0]>phoetmax) continue;
    if(signal) {
      phoetsignal->Fill(phoEt[0]);
    }
    if(sideband) {
      phoetsideband->Fill(phoEt[0]);
    }

//! now we'll loop through the different jet collections first, reco, gen, recomix, and genmix

    int njets_perevent = 0;
    int njets_permixevent = 0;
    
//! (2.2) Reco jet loop
    int njetloop = njet;
    for (int ijet = 0; ijet < njetloop; ijet++) {
      float tmpjetpt = jetpt[ijet];
      float tmpjeteta = jeteta[ijet];
      float tmpjetphi = jetphi[ijet];
      if(isPP)
      {
        tmpjetpt = getSmearedPt(ijet*100,centmin);
        tmpjeteta = getSmearedEta(ijet,centmin);  
      }
      if( tmpjetpt<jetptcut ) continue; //jet pt Cut
      if( fabs(tmpjeteta) > 1.6) continue; //jeteta Cut

      if(checkjetid==1)
      {
        if( jetID[ijet]==0 ) continue;
      }
      if( acos(cos(tmpjetphi - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal) {
        hjetpt->Fill(tmpjetpt);
        njets_perevent++;
        xjgsignal->Fill(jetptCorr[ijet]/phoEt[0]);
      }
      if(sideband) {
        hjetptsideband->Fill(tmpjetpt);
        xjgsideband->Fill(jetptCorr[ijet]/phoEt[0]);
      }
      hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012[0]);
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(jetptCorr[ijet],tmpjeteta,tmpjetphi,0);

      if(gen.compare("gen")==0)
      {
        for(int igen = 0 ; igen < mult ; ++igen)
        {
          if(!(abs(pdg[igen])==11 || abs(pdg[igen])==13 || abs(pdg[igen])==211 || abs(pdg[igen])==2212 || abs(pdg[igen])==321) || pt[igen]<trkptmin) continue;
          float dphi = acos( cos(tmpjetphi - phi[igen]));
          float deta = fabs( tmpjeteta - eta[igen]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt[igen],eta[igen],phi[igen],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt[igen]*cos(angle)/tmpjetpt;
            float xi = log(1.0/z);

            if(sube[igen] == 0)
            {
              if(signal)
              {
                hgammaffxi->Fill(xi);
              }
              if(sideband)
              {
                hgammaffxisideband->Fill(xi);
              }
            }
            else
            {
              if(signal)
              {
                hgammaffxiuesiggen->Fill(xi);
              }
              if(sideband)
              {

              }
            }
          }
        }
        for(int igen_mix = 0 ; igen_mix < mult_mix ; ++igen_mix)
        {
          if(!(abs(pdg_mix[igen_mix])==11 || abs(pdg_mix[igen_mix])==13 || abs(pdg_mix[igen_mix])==211 || abs(pdg_mix[igen_mix])==2212 || abs(pdg_mix[igen_mix])==321) || pt_mix[igen_mix]<trkptmin) continue;
          float dphi = acos( cos(tmpjetphi - phi_mix[igen_mix]));
          float deta = fabs( tmpjeteta - eta_mix[igen_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt_mix[igen_mix],eta_mix[igen_mix],phi_mix[igen_mix],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt_mix[igen_mix]*cos(angle)/tmpjetpt;
            float xi = log(1.0/z);
            hgammaffxiuemixgen->Fill(xi,2.0/(float)nmix);
          }
        }
      }
      else if(gen.compare("reco")==0)
      {
        
        for (int itrk = 0; itrk < nTrk; itrk++) {
          if(trkPt[itrk]<trkptmin) continue;
          float dphi = acos( cos(jetphi[ijet] - trkPhi[itrk]));
          float deta = fabs( jeteta[ijet] - trkEta[itrk]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          
          // float dr = genjetrecotrk_dr(itrk,ijet);
          // float dr_refcone = genrefconerecotrk_dr(itrk,ijet);
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            // cout<<cos(angle)<<endl;
            float z = trkPt[itrk]*cos(angle)/tmpjetpt;
            // float zpho = trkPt[itrk]/phoEt[0];
            float xi = log(1.0/z);
            // float xipho = log(1.0/zpho);

            if(signal) {
              hgammaffxi->Fill(xi,trkWeight[itrk]); //Raw FF after cuts (1.0)
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]); // Raw FF after cuts sideband (1.1)
            }
            // cout<<tmpjetpt<<endl;
          }
        }
        for(int itrk_cone = 0 ; itrk_cone < nTrk_cone ; ++itrk_cone)
        {
          if(trkPt_cone[itrk_cone]<trkptmin) continue;
          float dphi = acos( cos(tmpjetphi - trkPhi_cone[itrk_cone]));
          float deta = fabs( tmpjeteta - trkEta_cone[itrk_cone]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_cone[itrk_cone],trkEta_cone[itrk_cone],trkPhi_cone[itrk_cone],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_cone[itrk_cone]*cos(angle)/tmpjetpt;
            float xi = log(1.0/z);

            if(signal) {
              hgammaffxiuemix->Fill(xi,2*trkWeight[itrk_cone]/(float)nmix);
              // ntotmix++;
            }
            if(sideband) {
              hgammaffxiuemixsideband->Fill(xi,2*trkWeight[itrk_cone]/(float)nmix);
            }
          }
        }
      }
    }

//! (2.3) Gen jet loop
    for (int igenjet = 0; igenjet < ngen; igenjet++) {
      if( gensubid[igenjet]!=0) continue;
      if( genpt[igenjet]<jetptcut ) continue; //jet pt Cut
      if( fabs(geneta[igenjet]) > 1.6) continue; //jeteta Cut
      if( acos(cos(genphi[igenjet] - phoPhi[0])) < 7 * pi / 8 ) continue;
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(genpt[igenjet],geneta[igenjet],genphi[igenjet],0);
      hgenjetpt->Fill(genpt[igenjet]);
// if(gen.compare("gengen")==0)
      for(int igentrk = 0 ; igentrk < mult ; ++igentrk)
      {
        if(subid[igentrk]!=0) continue;
        if(!(abs(pdg[igentrk])==11 || abs(pdg[igentrk])==13 || abs(pdg[igentrk])==211 || abs(pdg[igentrk])==2212 || abs(pdg[igentrk])==321) ) continue;
        if(pt[igentrk]<trkptmin) continue;
        float dphi = acos( cos(genphi[igenjet] - phi[igentrk]));
        float deta = fabs( geneta[igenjet] - eta[igentrk]);
        float dr = sqrt((dphi*dphi)+(deta*deta));
        if(dr<0.3)
        {
          TLorentzVector vtrack;
          vtrack.SetPtEtaPhiM(pt[igentrk],eta[igentrk],phi[igentrk],0);
          float angle = vjet.Angle(vtrack.Vect());
          float z = pt[igentrk]*cos(angle)/genpt[igenjet];
          float xi = log(1.0/z);

          hgammaffxi->Fill(xi);
        }
      }
    }
    

    if(gen.compare("mixgen")==0)
    {
      for (int igenjet = 0; igenjet < ngen; igenjet++) {
        // if( gensubid[igenjet]!=0) continue;
        if( genpt[igenjet]<jetptcut ) continue; //jet pt Cut
        if( fabs(geneta[igenjet]) > 1.6) continue; //jeteta Cut
        if( acos(cos(genphi[igenjet] - phoPhi[0])) < 7 * pi / 8 ) continue;
        TLorentzVector vjet;
        vjet.SetPtEtaPhiM(genpt[igenjet],geneta[igenjet],genphi[igenjet],0);
        hgenjetpt->Fill(genpt[igenjet]);
        for(int igentrk = 0 ; igentrk < mult ; ++igentrk)
        {
          // if(subid[igentrk]!=0) continue;
          if(!(abs(pdg[igentrk])==11 || abs(pdg[igentrk])==13 || abs(pdg[igentrk])==211 || abs(pdg[igentrk])==2212 || abs(pdg[igentrk])==321) ) continue;
          if(pt[igentrk]<trkptmin) continue;
          float dphi = acos( cos(genphi[igenjet] - phi[igentrk]));
          float deta = fabs( geneta[igenjet] - eta[igentrk]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt[igentrk],eta[igentrk],phi[igentrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt[igentrk]*cos(angle)/genpt[igenjet];
            float xi = log(1.0/z);

            hgammaffxi->Fill(xi);
          }
        }
      }
    }

//! (2.4) Mix reco jet loop
    for (int ijet_mix = 0; ijet_mix < njet_mix; ijet_mix++) {
      if( jetpt_mix[ijet_mix]<jetptcut ) continue; //jet pt Cut
      if( fabs(jeteta_mix[ijet_mix]) > 1.6) continue; //jeteta_mix Cut
      // if( fabs(jeteta_mix[ijet_mix]) < 0.3) continue; //jeteta_mix Cut for reflected cone
      if(checkjetid==1)
      {
        if( jetID_mix[ijet_mix]==0 ) continue;
      }
      if( acos(cos(jetphi_mix[ijet_mix] - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal && nmixEv_mix[ijet_mix]<5) {
        hjetptjetmix->Fill(jetpt_mix[ijet_mix]); // TODO: double check this
        njets_permixevent++;
        hnmixsignal->Fill(1,nmix/2.);
        xjgmixsignal->Fill(jetpt_mix[ijet_mix]/phoEt[0],2./(float)nmix);
      }
      if(sideband && nmixEv_mix[ijet_mix]<5) {
        hjetptjetmixsideband->Fill(jetpt_mix[ijet_mix]);
        hnmixsideband->Fill(1,nmix/2.);
        xjgmixsideband->Fill(jetpt_mix[ijet_mix]/phoEt[0],2./(float)nmix);
      }
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(jetpt_mix[ijet_mix],jeteta_mix[ijet_mix],jetphi_mix[ijet_mix],0);
      if(gen.compare("gen")==0)
      {
        // no jet mixing in gen ff
      } else if(gen.compare("reco")==0) {
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        {
          if(trkPt_mix[itrk_mix]<trkptmin) continue;
          if(nmixEv_mix[ijet_mix]!=trkFromEv_mix[itrk_mix]) continue;
          float dphi = acos( cos(jetphi_mix[ijet_mix] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta_mix[ijet_mix] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt_mix[ijet_mix];
            float xi = log(1.0/z);

            if(signal) {
              hgammaffxijetmix->Fill(xi,2*trkWeight[itrk_mix]/(float)nmix);
            }
            if(sideband) {
              hgammaffxijetmixsideband->Fill(xi,2*trkWeight[itrk_mix]/(float)nmix);
            }
          }
        }
      }
    }

//! (2.5) Mix gen jet loop

    hnjetperevt->Fill(njets_perevent);
    hnjetpermixevt->Fill(njets_permixevent);
    
  }
  fout->Write();
  fout->Close();
}



int main(int argc, char *argv[])
{
  if(argc > 11 || argc < 3 )
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
  // cout<<argc<<endl;
  return 0;
}
