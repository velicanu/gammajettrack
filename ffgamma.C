#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>


void ztree::ffgammajet(std::string outfname)
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s.root",outfname.data(),tag.data(),s_alpha.data()),"recreate");
  // TH1D * hgjetratio = new TH1D(Form("hgjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";#alpha=%s  %s-jet balance;",alpha.data(),probe.data()),14,0.1,2);
  TH1D * hgjetratio = new TH1D(Form("hgjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";#gamma-jet balance;"),14,0.1,2);
  TH1D * hgammajetff = new TH1D(Form("hgammajetff_%s_%s",tag.data(),s_alpha.data()),Form(";p_{T}(>1 GeV)/p_{T-jet};"),20,0,1);
  TH1D * hgammaff = new TH1D(Form("hgammaff_%s_%s",tag.data(),s_alpha.data()),Form(";z;"),20,0,1);
  TH1D * hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s",tag.data(),s_alpha.data()),Form(";#xi=ln(1/z);"),10,0,5);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(nPho!=1) continue;
    if(phoEt[0]<45 || phoEt[0]>60) continue;
    if(weight==0)                   weight=1;
    for (size_t ijet = 0; ijet < njet; ijet++) {
      if( jetpt[ijet]<50 ) continue; //jet pt Cut
      if( fabs(jeteta[ijet]) > 1.6) continue; //jeteta Cut
      if( jetID[ijet]==0 ) continue; //redundant in this skim (all true)
      if( acos(cos(jetphi[ijet] - phoPhi[0])) < 7 * pi / 8 ) continue;

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
      ak3pupf jets

      // delphi > 7 pi / 8


    }


  }

  fout->Write();
  fout->Close();
}



int main(int argc, char *argv[])
{
  if(argc != 3 && argc != 4 && argc != 5 && argc != 6)
  {
    std::cout<<"usage: ./ztree.exe <infilename> <outfilename> [tag] [pfTypeSelection]"<<std::endl;
    exit(1);
  }
  ztree * t = new ztree(argv[1]);
  if (argc==3) {
    t->ffgammajet(argv[2]);
  }
  return 0;
}
