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

void ztree::ffgammajet(std::string outfname, int centmin, int centmax)
{
  string tag = outfname;
  string s_alpha = "";
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s_%d_%d.root",outfname.data(),tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),"recreate");
  TH1D * hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";jet p_{T};"),20,0,500);
  TH1D * hgammaff = new TH1D(Form("hgammaff_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";z;"),20,0,1);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaffxi_refcone = new TH1D(Form("hgammaffxi_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaphoffxi = new TH1D(Form("hgammaphoffxi_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  TH1D * hgammaphoffxi_refcone = new TH1D(Form("hgammaphoffxi_refcone_%s_%s_%d_%d",tag.data(),s_alpha.data(),abs(centmin),abs(centmax)),Form(";#xi=ln(1/z);"),10,0,5);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if(jentry%10000==0) { cout<<jentry<<"/"<<nentries<<endl; }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    // cout<<njet<<endl;
    // if(jentry > 10000) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(hiBin < centmin || hiBin >= centmax) continue; //centrality cut
    if(nPho!=1) continue;
    if(phoEt[0]<100 || phoEt[0]>300) continue;
    if(weight==0)                   weight=1;
    // cout<<njet<<endl;

    for (int ijet = 0; ijet < njet; ijet++) {
      if( nPho==2 ) continue;
      if( jetpt[ijet]<40 ) continue; //jet pt Cut
      if( fabs(jeteta[ijet]) > 1.6) continue; //jeteta Cut
      if( fabs(jeteta[ijet]) < 0.3) continue; //jeteta Cut for reflected cone
      if( jetID[ijet]==0 ) continue; //redundant in this skim (all true)
      if( acos(cos(jetphi[ijet] - phoPhi[0])) < 7 * pi / 8 ) continue;
      hjetpt->Fill(jetpt[ijet]);

      for (int itrk = 0; itrk < nTrk; itrk++) {
        float dr = jettrk_dr(itrk,ijet);
        float dr_refcone = refconetrk_dr(itrk,ijet);
        if(dr<0.3)
        {
          float z = trkPt[itrk]/jetpt[ijet];
          float zpho = trkPt[itrk]/phoEt[0];
          float xi = log(1.0/z);
          float xipho = log(1.0/zpho);

          hgammaff->Fill(z,trkWeight[itrk]);
          hgammaffxi->Fill(xi,trkWeight[itrk]);
          hgammaphoffxi->Fill(xipho,trkWeight[itrk]);
          // cout<<jetpt[ijet]<<endl;
        }
        if(dr_refcone<0.3)
        {
          float z = trkPt[itrk]/jetpt[ijet];
          float zpho = trkPt[itrk]/phoEt[0];
          float xi = log(1.0/z);
          float xipho = log(1.0/zpho);

          hgammaffxi_refcone->Fill(xi,trkWeight[itrk]);
          hgammaphoffxi_refcone->Fill(xipho,trkWeight[itrk]);
        }

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

  fout->Write();
  fout->Close();
}



int main(int argc, char *argv[])
{
  if(argc != 3 && argc != 5 && argc != 6)
  {
    std::cout<<"usage: ./ffgamma.exe <infilename> <outfilename> [centmin centmax]"<<std::endl;
    exit(1);
  }
  ztree * t = new ztree(argv[1]);
  if (argc==3) {
    t->ffgammajet(argv[2]);
  }
  if (argc==5) {
    t->ffgammajet(argv[2],std::atoi(argv[3]),std::atoi(argv[4]));
  }
  return 0;
}
