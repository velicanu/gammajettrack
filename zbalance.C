#define ztree_cxx
#include "zbalance.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"
#include <algorithm>

void ztree::Loop(std::string outfname , std::string tag, std::string probe, std::string alpha)
{
  // float f_alpha = std::atof(alpha.data());
  std::string s_alpha = alpha;
  s_alpha.erase(std::remove_copy(alpha.begin(), alpha.end(), s_alpha.begin(), '.'), s_alpha.end());
  
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s.root",outfname.data(),tag.data(),s_alpha.data()),"recreate");
  // TH1D * hzjetratio = new TH1D(Form("hzjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";#alpha=%s  %s-jet balance;",alpha.data(),probe.data()),14,0.1,2);
  TH1D * hzjetratio = new TH1D(Form("hzjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";Z-jet balance;"),14,0.1,2);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(Zpt<30 || Zpt>60) continue ; //Zpt cut
    if(Zmass<70 || Zmass>110) continue;
    // if (Cut(ientry) < 0) continue;
    if(weight==0)                   weight=1;
    // bool has_alpha = false;
    int njetsincone = 0;
    // int maxjeti = -1;
    float maxjetpt = -1;
    for(int ijet = 0 ; ijet < njet ; ++ijet)
    {
      if(fabs(jeteta[ijet])>1.3) continue;
      float zjetdphi = Zphi - jetphi[ijet];
      if( zjetdphi > pi ) zjetdphi = 2 * TMath::Pi() - zjetdphi;
      if( zjetdphi < 2.7 ) continue;
      if(jetpt[ijet]>maxjetpt)
      {
        maxjetpt = jetpt[ijet];
        // maxjeti = ijet;
      }
      njetsincone++;
    }
    if(maxjetpt>10 )
    {
      hzjetratio->Fill( maxjetpt / Zpt );
    }
  }
  
  fout->Write();
  fout->Close();
}

void ztree::gammajetBalance(std::string outfname , std::string tag, std::string probe, std::string alpha)
{
  float f_alpha = std::atof(alpha.data());
  std::string s_alpha = alpha;
  s_alpha.erase(std::remove_copy(alpha.begin(), alpha.end(), s_alpha.begin(), '.'), s_alpha.end());
  
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("%s_%s_%s.root",outfname.data(),tag.data(),s_alpha.data()),"recreate");
  // TH1D * hgjetratio = new TH1D(Form("hgjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";#alpha=%s  %s-jet balance;",alpha.data(),probe.data()),14,0.1,2);
  TH1D * hgjetratio = new TH1D(Form("hgjetratio_%s_%s",tag.data(),s_alpha.data()),Form(";#gamma-jet balance;"),14,0.1,2);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(nPho!=1) continue;
    if(phoEt[0]<45 || phoEt[0]>60) continue;
    // if (Cut(ientry) < 0) continue;
    if(weight==0)                   weight=1;
    int njetsincone = 0;
    int maxjeti = -1;
    float maxjetpt = -1;
    for(int ijet = 0 ; ijet < njet ; ++ijet)
    {
      if(jetID[ijet]!=1) continue;
      if(fabs(jeteta[ijet])>1.3) continue;
      float gjetdphi = phoPhi[0] - jetphi[ijet];
      if( gjetdphi > pi ) gjetdphi = 2 * TMath::Pi() - gjetdphi;
      if( gjetdphi < 2.7 ) continue;
      if(jetpt[ijet]>maxjetpt)
      {
        maxjetpt = jetpt[ijet];
        maxjeti = ijet;
      }
      njetsincone++;
    }
    bool has_alpha = false;
    for(int ijet = 0 ; ijet < njet ; ++ijet)
    {
      if(jetID[ijet]!=1) continue;
      if(fabs(jeteta[ijet])>1.3) continue;
      float gjetdphi = phoPhi[0] - jetphi[ijet];
      if( gjetdphi > pi ) gjetdphi = 2 * TMath::Pi() - gjetdphi;
      float gjetdeta = phoEta[0] - jeteta[ijet];
      float dr = sqrt((gjetdeta*gjetdeta)+(gjetdphi*gjetdphi));
      if( ijet != maxjeti && dr > 0.25 && jetpt[ijet]>f_alpha*phoEt[0] ) has_alpha=true; 
    }
    
    if(maxjetpt>10 && !has_alpha)
    {
      hgjetratio->Fill( maxjetpt / phoEt[0] );
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
  // if(argc==3) t->Loop(argv[2]);
  // if(argc==4) t->Loop(argv[2],argv[3]);
  // if(argc==5) t->Loop(argv[2],argv[3],argv[4]);
  // if(argc==6) t->Loop(argv[2],argv[3],argv[4],argv[5]);
  if(argc==3) t->gammajetBalance(argv[2]);
  if(argc==4) t->gammajetBalance(argv[2],argv[3]);
  if(argc==5) t->gammajetBalance(argv[2],argv[3],argv[4]);
  if(argc==6) t->gammajetBalance(argv[2],argv[3],argv[4],argv[5]);
  return 0;
}


