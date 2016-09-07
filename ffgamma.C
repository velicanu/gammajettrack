#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>

const int jetptcut = 40;

float ztree::jettrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(jetphi[ijet] - trkPhi[itrk]));
  float deta = fabs( jeteta[ijet] - trkEta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::refconetrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(jetphi[ijet] - trkPhi[itrk]));
  float deta = fabs( jeteta[ijet] + trkEta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::genjettrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(gjetphi[ijet] - phi[itrk]));
  float deta = fabs( gjeteta[ijet] - eta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::genrefconetrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(gjetphi[ijet] - phi[itrk]));
  float deta = fabs( gjeteta[ijet] + eta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::genjetrecotrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(gjetphi[ijet] - trkPhi[itrk]));
  float deta = fabs( gjeteta[ijet] - trkEta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::genrefconerecotrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(gjetphi[ijet] - trkPhi[itrk]));
  float deta = fabs( gjeteta[ijet] + trkEta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::recojetgentrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(jetphi[ijet] - phi[itrk]));
  float deta = fabs( jeteta[ijet] - eta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

float ztree::recorefconegentrk_dr(int itrk, int ijet)
{
  float dphi = acos( cos(jetphi[ijet] - phi[itrk]));
  float deta = fabs( jeteta[ijet] + eta[itrk]);
  return sqrt((dphi*dphi)+(deta*deta));
}

void ztree::ffgammajet(std::string outfname, int centmin, int centmax, float phoetmin, float phoetmax, std::string gen)
{
  string tag = outfname;
  string s_alpha = gen;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s_%d_%d.root",outfname.data(),tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),"recreate");

  // TH2D * hsubept = new TH2D(Form("hsubept_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,-0.5,99.5,100,0,100);
  // TH2D * hsubept_refcone = new TH2D(Form("hsubept_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,-0.5,99.5,100,0,100);

  TH1D * hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),40,0,0.02);
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
  // TH1D * hnmix = new TH1D(Form("hnmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";mixevents;"),1,0,2); // sideband sub mix jet ff (3.1)
  TH1D * hgammaffxiuesiggen = new TH1D(Form("hgammaffxiuesiggen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hgammaffxiuemixgen = new TH1D(Form("hgammaffxiuemixgen_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5); // Raw FF after cuts (1.0)
  TH1D * hnmixsignal = new TH1D(Form("hnmixsignal_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * hnmixsideband = new TH1D(Form("hnmixsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),1,0,2); // Raw FF after cuts (1.0)
  TH1D * hmultinmix = new TH1D(Form("hmultinmix_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),100,-50,50); // Raw FF after cuts (1.0)


  // TH1D * hntrkincone = new TH1D(Form("hntrkincone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),101,-0.5,100.5);
  // TH1D * hntrkinrefcone = new TH1D(Form("hntrkinrefcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),101,-0.5,100.5);
  int nin = 0 , nmix_in = 0;


  // int ntottrk = 0;
  // int ntotmix = 0;
  // int ntotmultijet = 0;
  // int ntotsinglejet = 0;
  Long64_t nbytes = 0, nb = 0;
  cout<<phoetmin<<" "<<phoetmax<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) { cout<<jentry<<"/"<<nentries<<endl; }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    // cout<<njet<<endl;
    // if(jentry > 10000) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(hiBin < centmin || hiBin >= centmax) continue; //centrality cut
    if(nPho!=1) continue;
    if(phoNoise==0) continue;
    if(weight==0)                   weight=1;
    bool signal = (phoSigmaIEtaIEta_2012[0]<0.010);
    bool sideband = (phoSigmaIEtaIEta_2012[0]>0.011 && phoSigmaIEtaIEta_2012[0]<0.017);


    // for(int imix = 0 ; imix < nmix ; ++imix)
    // {
      // hnmix->Fill(1);
    // }

      // int npassingjets = 0;
    for (int ijet = 0; ijet < njet; ijet++) {

      if( nPho==2 ) continue;
      if( phoEt[0]*phoCorr[0]<phoetmin || phoEt[0]*phoCorr[0]>phoetmax) continue;
      if( jetpt[ijet]<jetptcut ) continue; //jet pt Cut
      if( fabs(jeteta[ijet]) > 1.6) continue; //jeteta Cut
      if( fabs(jeteta[ijet]) < 0.3) continue; //jeteta Cut for reflected cone
      if( jetID[ijet]==0 ) continue; //redundant in this skim (all true)
      if( acos(cos(jetphi[ijet] - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal) {
        hjetpt->Fill(jetpt[ijet]);
      }
      if(sideband) {
        hjetptsideband->Fill(jetpt[ijet]);
      }
      hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012[0]);
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(jetpt[ijet],jeteta[ijet],jetphi[ijet],0);
      // npassingjets++;
      // if(npassingjets>1) {ntotmultijet++;}
      // else {ntotsinglejet++;}
      // if(npassingjets>1) {continue;}
      if(gen.compare("gen")==0)
      {
        // int ntrkmixcone = 0;
        // int ntrkcone = 0;
        // cout<<nTrk_mix<<" "<<nTrk<<endl;

        int mult_in = 0;
        for(int igen = 0 ; igen < mult ; ++igen)
        {
          if(!(abs(pdg[igen])==11 || abs(pdg[igen])==13 || abs(pdg[igen])==211 || abs(pdg[igen])==2212 || abs(pdg[igen])==321) || pt[igen]<1) continue;
          float dphi = acos( cos(jetphi[ijet] - phi[igen]));
          float deta = fabs( jeteta[ijet] - eta[igen]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt[igen],eta[igen],phi[igen],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt[igen]*cos(angle)/gjetpt[ijet];
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
              nin++;
              mult_in++;
            }
            // hsubept->Fill(sube[igen],pt[igen]);
            // if(signal) {
              // ntottrk++;
            // }
            // if(sideband) {
              // hgammaffxisideband->Fill(xi);
            // }
          }
        }
        int mult_mix_in = 0;
        for(int igen_mix = 0 ; igen_mix < mult_mix ; ++igen_mix)
        {
          if(!(abs(pdg_mix[igen_mix])==11 || abs(pdg_mix[igen_mix])==13 || abs(pdg_mix[igen_mix])==211 || abs(pdg_mix[igen_mix])==2212 || abs(pdg_mix[igen_mix])==321) || pt_mix[igen_mix]<1) continue;
          float dphi = acos( cos(jetphi[ijet] - phi_mix[igen_mix]));
          float deta = fabs( jeteta[ijet] - eta_mix[igen_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(pt_mix[igen_mix],eta_mix[igen_mix],phi_mix[igen_mix],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = pt_mix[igen_mix]*cos(angle)/gjetpt[ijet];
            float xi = log(1.0/z);
            hgammaffxiuemixgen->Fill(xi,1.0/(float)nmix);
            nmix_in++;
            mult_mix_in++;
            // hsubept->Fill(sube[igen_mix],pt[igen_mix]);
            // if(signal) {
              // ntottrk++;
            // }
            // if(sideband) {
              // hgammaffxisideband->Fill(xi);
            // }
          }
        }
        hmultinmix->Fill(mult_in-mult_mix_in);
        // cout<<mult_in<<" "<<mult_mix_in<<endl;


        // cout<<ntrkcone<<" "<<ntrkmixcone/float(nmix)<<endl;
        // hntrkincone->Fill(ntrkcone);
        // hntrkinrefcone->Fill(ntrkmixcone/float(nmix));
      }
      else if(gen.compare("reco")==0)
      {
        for (int itrk = 0; itrk < nTrk; itrk++) {
          float dr = jettrk_dr(itrk,ijet);
          // float dr = genjetrecotrk_dr(itrk,ijet);
          // float dr_refcone = genrefconerecotrk_dr(itrk,ijet);
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            // cout<<cos(angle)<<endl;
            float z = trkPt[itrk]*cos(angle)/jetpt[ijet];
            // float zpho = trkPt[itrk]/phoEt[0];
            float xi = log(1.0/z);
            // float xipho = log(1.0/zpho);

            if(signal) {
              hgammaffxi->Fill(xi,trkWeight[itrk]); //Raw FF after cuts (1.0)
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]); // Raw FF after cuts sideband (1.1)
            }
            // cout<<jetpt[ijet]<<endl;
          }
        }
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        {
          float dphi = acos( cos(jetphi[ijet] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta[ijet] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt[ijet];
            float xi = log(1.0/z);

            if(signal) {
              hgammaffxiuemix->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
              // ntotmix++;
            }
            if(sideband) {
              hgammaffxiuemixsideband->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
            }
          }
        }
      }
    }
    for (int ijet_mix = 0; ijet_mix < njet_mix; ijet_mix++) {
      if( nPho==2 ) continue;
      if( phoEt[0]*phoCorr[0]<phoetmin || phoEt[0]*phoCorr[0]>phoetmax) continue;
      if( jetpt_mix[ijet_mix]<jetptcut ) continue; //jet pt Cut
      if( fabs(jeteta_mix[ijet_mix]) > 1.6) continue; //jeteta_mix Cut
      if( fabs(jeteta_mix[ijet_mix]) < 0.3) continue; //jeteta_mix Cut for reflected cone
      if( jetID_mix[ijet_mix]==0 ) continue; //redundant in this skim (all true)
      if( acos(cos(jetphi_mix[ijet_mix] - phoPhi[0])) < 7 * pi / 8 ) continue;
      if(signal) {
        hjetptjetmix->Fill(jetpt_mix[ijet_mix]/(float)nmix);
        hnmixsignal->Fill(1,nmix);
      }
      if(sideband) {
        hjetptjetmixsideband->Fill(jetpt_mix[ijet_mix]/(float)nmix);
        hnmixsideband->Fill(1,nmix);
      }
      // hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012[0]);
      TLorentzVector vjet;
      vjet.SetPtEtaPhiM(jetpt_mix[ijet_mix],jeteta_mix[ijet_mix],jetphi_mix[ijet_mix],0);
      if(gen.compare("gen")==0)
      {
        // int ntrkmixcone = 0;
        // int ntrkcone = 0;
        // cout<<nTrk_mix<<" "<<nTrk<<endl;
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        {
          float dphi = acos( cos(jetphi_mix[ijet_mix] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta_mix[ijet_mix] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            // TLorentzVector vtrackmix;
            // vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            // float angle = vjet.Angle(vtrackmix.Vect());
            // cout<<"            "<<cos(angle)<<endl;
            // float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt_mix[ijet_mix];
            // float xi = log(1.0/z);
            // cout<<"xitrk_mix "<<xi<<endl;

            if(signal) {
              // hgammaffxigenmix->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
              // hgammaffxi_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // hgammaffxi_refcone->Fill(xi);
              // hgammaffxi_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // ntrkmixcone++;
              // ntotmix++;

            }
            if(sideband) {
              // hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[itrk_mix]);
            }
          }
        }
      } else if(gen.compare("reco")==0) {
        for(int itrk_mix = 0 ; itrk_mix < nTrk_mix ; ++itrk_mix)
        {
          float dphi = acos( cos(jetphi_mix[ijet_mix] - trkPhi_mix[itrk_mix]));
          float deta = fabs( jeteta_mix[ijet_mix] - trkEta_mix[itrk_mix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[itrk_mix],trkEta_mix[itrk_mix],trkPhi_mix[itrk_mix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            // cout<<"            "<<cos(angle)<<endl;
            float z = trkPt_mix[itrk_mix]*cos(angle)/jetpt_mix[ijet_mix];
            float xi = log(1.0/z);
            // cout<<"xitrk_mix "<<xi<<endl;

            if(signal) {
              hgammaffxijetmix->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
              // hgammaffxi_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // hgammaffxi_refcone->Fill(xi);
              // hgammaffxi_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // ntrkmixcone++;
              // ntotmix++;

            }
            if(sideband) {
              hgammaffxijetmixsideband->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
              // hgammaffximixsideband->Fill(xi,trkWeight[itrk_mix]/(float)nmix);
              // hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[itrk_mix]/(float)nmix);
              // hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[itrk_mix]);
            }
          }
        }
      }
    }


    /*
    */


  }
  cout<<nin<<" "<<nmix_in<<endl;

  fout->Write();
  fout->Close();
  // cout<<ntottrk<<" "<<ntotmix<<endl;
  // cout<<ntotmultijet<<"/"<<(ntotsinglejet+ntotmultijet)<<" = "<<ntotmultijet/(float)(ntotsinglejet+ntotmultijet)<<endl;
}



int main(int argc, char *argv[])
{
  if(argc != 3 && argc != 5 && argc != 6 && argc != 7 && argc != 8 )
  {
    std::cout<<"usage: ./ffgamma.exe <infilename> <outfilename> [centmin centmax] [phoetmin] [phoetmax] [gen]"<<std::endl;
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
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]),std::atof(argv[5]),std::atof(argv[6]),argv[7]);
  }

  return 0;
}
