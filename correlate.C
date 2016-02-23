#define ztree_cxx
#include "ztree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"

void ztree::Loop(std::string outfname , std::string tag, int pfTypeSelection)
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(outfname.data(),"recreate");
  
  TH2D * hGammaSig = new TH2D(Form("hGammaSig"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  TH2D * hJetSig = new TH2D(Form("hJetSig"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(weight==0)                   weight=1;
    if(ientry % 10001 == 0 ) cout<<ientry<<"/"<<nentries<<endl;
    int ipho = 0 ;
    if(nPho==2 && phoEt[1]>phoEt[0]) ipho=1;
    // cout<<vz<<endl;
    float gammajetdphi = fabs(phoPhi[0]-jetphi[0]);
    if(gammajetdphi > pi) gammajetdphi = 2*pi - gammajetdphi;
    if(gammajetdphi < 5.0 * pi / 6.0) 
    {
      continue;
    }
    
    for(int itrk = 0 ; itrk < nTrk ; ++itrk)
    {
      double deta = fabs(phoEta[ipho]-trkEta[itrk]);
      double dphi = fabs(phoPhi[ipho]-trkPhi[itrk]);
      if( dphi > pi ) dphi = 2*pi - dphi;
      hGammaSig->Fill(deta,dphi,weight);
      hGammaSig->Fill(-deta,dphi,weight);
      hGammaSig->Fill(deta,-dphi,weight);
      hGammaSig->Fill(-deta,-dphi,weight);
      hGammaSig->Fill(deta,(2*pi)-dphi,weight);
      hGammaSig->Fill(-deta,(2*pi)-dphi,weight);
      
      deta = fabs(jeteta[ipho]-trkEta[itrk]);
      dphi = fabs(jetphi[ipho]-trkPhi[itrk]);
      if( dphi > pi ) dphi = 2*pi - dphi;
      hJetSig->Fill(deta,dphi,weight);
      hJetSig->Fill(-deta,dphi,weight);
      hJetSig->Fill(deta,-dphi,weight);
      hJetSig->Fill(-deta,-dphi,weight);
      hJetSig->Fill(deta,(2*pi)-dphi,weight);
      hJetSig->Fill(-deta,(2*pi)-dphi,weight);
      
      
    }
  }
  
  fout->Write();
  fout->Close();
}

void ztree::MixedEvent(std::string outfname)
{
  TFile *fmix = TFile::Open("/home/ursu/HIMinimumBiasJet30Skim/HIMinimumBiasJet30Skim-xaa.root");
  TTree * mixtree = (TTree*) fmix->Get("ztree");
  InitMix(mixtree);
  
  
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("mix_%s",outfname.data()),"recreate");
  TH2D * hGammaMix = new TH2D(Form("hGammaMix"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  Long64_t nbytes = 0, nb = 0;
  
  std::vector<int>    vhiBin;
  std::vector<float>  vvz;
  
  // Long64_t nentriesmix = mix_fChain->GetEntriesFast();
  Long64_t nentriesmix = 10002;
  for (Long64_t jentry=0; jentry<nentriesmix;jentry++) {
    Long64_t ientry = LoadTreeMix(jentry);
    if (ientry < 0) break;
    nb = mix_fChain->GetEntry(jentry);   nbytes += nb;
    if(weight==0)                   weight=1;
    if(ientry % 10001 == 0 ) cout<<ientry<<"/"<<nentries<<endl;
    vhiBin.push_back(mix_hiBin);
    vvz.push_back(mix_vz);
    // cout<<vvz[ientry]<<" "<<mix_vz<<endl;
  }
  // exit(1);
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(weight==0)                   weight=1;
    if(ientry % 10001 == 0 ) cout<<ientry<<"/"<<nentries<<endl;
    
    int ipho = 0 ;
    if(nPho==2 && phoEt[1]>phoEt[0]) ipho=1;
    
    int nmatched = 0;
    int imatched[5];
    for(int i = 0 ; i < nentriesmix ; ++i)
    {
      if(nmatched>4) break;
      if(fabs(vz-vvz[i])<0.5 && abs(hiBin-vhiBin[i])<5)
      {
        // cout<<i<<" "<<fabs(vz-vvz[i])<<" "<<abs(hiBin-vhiBin[i])<<endl;
        imatched[nmatched]=i;
        nmatched++;
      }
    }
    
    for(int i = 0 ; i < nmatched ; ++i)
    {
      Long64_t mixentry = LoadTreeMix(imatched[i]);
      if (mixentry < 0) break;
      nb = mix_fChain->GetEntry(imatched[i]);   nbytes += nb;
      
      for(int itrk = 0 ; itrk < mix_nTrk ; ++itrk)
      {
        double deta = fabs(phoEta[ipho]-mix_trkEta[itrk]);
        double dphi = fabs(phoPhi[ipho]-mix_trkPhi[itrk]);
        if( dphi > pi ) dphi = 2*pi - dphi;
        hGammaMix->Fill(deta,dphi,weight);
        hGammaMix->Fill(-deta,dphi,weight);
        hGammaMix->Fill(deta,-dphi,weight);
        hGammaMix->Fill(-deta,-dphi,weight);
        hGammaMix->Fill(deta,(2*pi)-dphi,weight);
        hGammaMix->Fill(-deta,(2*pi)-dphi,weight);
      }
      
    }
    
    
    hGammaMix->Fill(0.0,0.0,weight);
  }
  fout->Write();
  fout->Close();
}


 
int main(int argc, char *argv[])
{
  if(argc != 3 && argc != 4 && argc != 5)
  {    
    std::cout<<"usage: ./ztree.exe <infilename> <outfilename> [tag] [pfTypeSelection]"<<std::endl;
    exit(1);
  }
  ztree * t = new ztree(argv[1]);
  t->Loop(argv[2]);
  t->MixedEvent(argv[2]);
  // if(argc==3) t->Loop(argv[2]);
  // if(argc==4) t->Loop(argv[2],argv[3]);
  // if(argc==5) t->Loop(argv[2],argv[3],std::atoi(argv[4]));
  return 0;
}


