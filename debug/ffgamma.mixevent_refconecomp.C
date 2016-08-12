#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>

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
  TH1D * hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  // TH1D * hjetgendphi = new TH1D(Form("hjetgendphi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#DeltaR_{gen,reco};"),20,0,0.1);
  TH1D * hgammaff = new TH1D(Form("hgammaff_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";z;"),20,0,1);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaffxi_refcone = new TH1D(Form("hgammaffxi_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaffxisideband_refcone = new TH1D(Form("hgammaffxisideband_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaphoffxi = new TH1D(Form("hgammaphoffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaphoffxi_refcone = new TH1D(Form("hgammaphoffxi_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);

  TH1D * hntrkincone = new TH1D(Form("hntrkincone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),101,-0.5,100.5);
  TH1D * hntrkinrefcone = new TH1D(Form("hntrkinrefcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),101,-0.5,100.5);


  int ntottrk = 0;
  int ntotmix = 0;
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

    for (int ijet = 0; ijet < njet; ijet++) {
      if( nPho==2 ) continue;
      if( phoEt[0]*phoCorr[0]<phoetmin || phoEt[0]*phoCorr[0]>phoetmax) continue;
      if( jetpt[ijet]<40 ) continue; //jet pt Cut
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

      if(gen.compare("gen")==0)
      {
        int ntrkmixcone = 0;
        int ntrkcone = 0;
        // cout<<nTrk_mix<<" "<<nTrk<<endl;
        for(int imix = 0 ; imix < nTrk_mix ; ++imix)
        {
          float dphi = acos( cos(jetphi[ijet] - trkPhi_mix[imix]));
          float deta = fabs( jeteta[ijet] - trkEta_mix[imix]);
          float dr = sqrt((dphi*dphi)+(deta*deta));
          if(dr<0.3)
          {
            TLorentzVector vtrackmix;
            vtrackmix.SetPtEtaPhiM(trkPt_mix[imix],trkEta_mix[imix],trkPhi_mix[imix],0);
            float angle = vjet.Angle(vtrackmix.Vect());
            // cout<<"            "<<cos(angle)<<endl;
            float z = trkPt_mix[imix]*cos(angle)/jetpt[ijet];
            float zpho = trkPt_mix[imix]/phoEt[0];
            float xi = log(1.0/z);
            // cout<<"ximix "<<xi<<endl;
            float xipho = log(1.0/zpho);

            if(signal) {
              // hgammaffxi_refcone->Fill(xi,trkWeight_mix[imix]/(float)nmix);
              // hgammaffxi_refcone->Fill(xi);
              hgammaffxi_refcone->Fill(xi,trkWeight_mix[imix]/(float)nmix);
              ntrkmixcone++;
              ntotmix++;
            }
            if(sideband) {
              hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[imix]/(float)nmix);
              // hgammaffxisideband_refcone->Fill(xi,trkWeight_mix[imix]);
            }
            hgammaphoffxi_refcone->Fill(xipho,trkWeight_mix[imix]/(float)nmix);
          }
        }

        for (int itrk = 0; itrk < nTrk; itrk++) {
          float dr = jettrk_dr(itrk,ijet);
          if(dr<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = trkPt[itrk]*cos(angle)/jetpt[ijet];
            float zpho = trkPt[itrk]/phoEt[0];
            float xi = log(1.0/z);
            float xipho = log(1.0/zpho);
            // cout<<"xi    "<<xi<<endl;

            hgammaff->Fill(z,trkWeight[itrk]);
            if(signal) {
              ntrkcone++;
              ntottrk++;
              hgammaffxi->Fill(xi,trkWeight[itrk]);
              // hgammaffxi->Fill(xi);
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]);
            }
            hgammaphoffxi->Fill(xipho,trkWeight[itrk]);
          }
        }
        // cout<<ntrkcone<<" "<<ntrkmixcone/float(nmix)<<endl;
        hntrkincone->Fill(ntrkcone);
        hntrkinrefcone->Fill(ntrkmixcone/float(nmix));
      }
      else
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
            float zpho = trkPt[itrk]/phoEt[0];
            float xi = log(1.0/z);
            float xipho = log(1.0/zpho);

            hgammaff->Fill(z,trkWeight[itrk]);
            if(signal) {
              hgammaffxi->Fill(xi,trkWeight[itrk]);
            }
            if(sideband) {
              hgammaffxisideband->Fill(xi,trkWeight[itrk]);
            }
            hgammaphoffxi->Fill(xipho,trkWeight[itrk]);
            // hgammaff->Fill(z);
            // hgammaffxi->Fill(xi);
            // hgammaphoffxi->Fill(xipho);
            // cout<<jetpt[ijet]<<endl;
          }
          float dr_refcone = refconetrk_dr(itrk,ijet);
          if(dr_refcone<0.3)
          {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM(trkPt[itrk],-trkEta[itrk],trkPhi[itrk],0);
            float angle = vjet.Angle(vtrack.Vect());
            // cout<<"            "<<cos(angle)<<endl;
            float z = trkPt[itrk]*cos(angle)/jetpt[ijet];
            float zpho = trkPt[itrk]/phoEt[0];
            float xi = log(1.0/z);
            float xipho = log(1.0/zpho);

            if(signal) {
              hgammaffxi_refcone->Fill(xi,trkWeight[itrk]);
            }
            if(sideband) {
              hgammaffxisideband_refcone->Fill(xi,trkWeight[itrk]);
            }
            hgammaphoffxi_refcone->Fill(xipho,trkWeight[itrk]);
            // hgammaffxi_refcone->Fill(xi);
            // hgammaphoffxi_refcone->Fill(xipho);
          }
          /*
          */
        }
          // photons: normal mode power mode
          // pho 40 trigger
          // photon spike cuts etc
          // phoet > 35
          // phoet > 40 after correction // haven't made it yet
          // phoeta < 1.44
          // sumiso < 1 GeV
          // h/em < 0.1
          // sigmaetaeta < 0.01

          // jets:
          // some pt
          // jeteta < 1.6
          // some id cuts // none yet but we'll add some
          // ak3pupf jets

          // delphi > 7 pi / 8


      }
    }

    /*
    */


  }

  fout->Write();
  fout->Close();
  cout<<ntottrk<<" "<<ntotmix<<endl;
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
