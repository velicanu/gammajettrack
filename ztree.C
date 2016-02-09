#define ztree_cxx
#include "ztree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"

void ztree::Loop(std::string outfname , std::string tag)
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(outfname.data(),"recreate");
  int jetptbins[] = {30,40,60,100,1000};
  const int njetbins = 4;
  TH1D * hfragFunctIn[njetbins];
  TH1D * hfragFunctOut[njetbins];
  TH1D * hnTrkincone[njetbins];
  TH1D * hnTrkoutcone[njetbins];
  TH1D * htrkPtincone[njetbins];
  TH1D * htrkPtoutcone[njetbins];
  TH1D * hnjets[njetbins];
  TH1D * hjetpt[njetbins];
  TH1D * hjeteta[njetbins];
  TH1D * hjetphi[njetbins];
  for(int k = 0 ; k < njetbins ; ++k)
  {
    hfragFunctIn[k] = new TH1D(Form("hfragFunctIn_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";trkPt/jetPt #DeltaR<0.4;",100,0,2);
    hfragFunctOut[k] = new TH1D(Form("hfragFunctOut_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";trkPt/jetPt reflected;",100,0,2);
    hnTrkincone[k] = new TH1D(Form("hnTrkincone_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";nTrk #DeltaR<0.4;",100,0,50);
    hnTrkoutcone[k] = new TH1D(Form("hnTrkoutcone_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";nTrk #DeltaR<0.4;",100,0,50);
    htrkPtincone[k] = new TH1D(Form("htrkPtincone_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";p_{T} #DeltaR<0.4;",100,0,50);
    htrkPtoutcone[k] = new TH1D(Form("htrkPtoutcone_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),";p_{T} #DeltaR>0.4;",100,0,50);
    hnjets[k] = new TH1D(Form("hnjets_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),"",1,0,2);
    hjetpt[k] = new TH1D(Form("hjetpt_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),"",25,0,100);
    hjeteta[k] = new TH1D(Form("hjeteta_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),"",100,-2.5,2.5);
    hjetphi[k] = new TH1D(Form("hjetphi_%s_jt%d_%d",tag.data(),jetptbins[k],jetptbins[k+1]),"",100,-TMath::Pi(),TMath::Pi());
  }
  float jetradius = 0.4;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(weight==0)                   weight=1;
    if(ientry % 9999 == 0 ) cout<<ientry<<"/"<<nentries<<endl;
    
    
    for(int k = 0 ; k < njetbins ; ++k)
    {
      int njetinptbin = 0;
      for(int jidx = 0 ; jidx < njet ; ++jidx)
      {
        if(jeteta[jidx]<jetradius) continue;
        if(jetID==0) continue;
        if(jetpt[jidx] < jetptbins[k] || jetpt[jidx] > jetptbins[k+1]) continue;
        njetinptbin++;
        hjetpt[k]->Fill(jetpt[jidx]);
        hjeteta[k]->Fill(jeteta[jidx]);
        hjetphi[k]->Fill(jetphi[jidx]);
        int ntrkincone = 0 , ntrkoutcone = 0;
        float totalptincone = 0.0 , totalptoutcone = 0.0;
        for(int trkidx = 0 ; trkidx < nTrk ; ++trkidx)
        {
          float dRjet = sqrt( (jeteta[jidx]-trkEta[trkidx])*(jeteta[jidx]-trkEta[trkidx]) + getDphi(jetphi[jidx],trkPhi[trkidx])*getDphi(jetphi[jidx],trkPhi[trkidx]) );
          float dRcone = sqrt( (-jeteta[jidx]-trkEta[trkidx])*(-jeteta[jidx]-trkEta[trkidx]) + getDphi(jetphi[jidx],trkPhi[trkidx])*getDphi(jetphi[jidx],trkPhi[trkidx]) );
          if(dRjet<jetradius)
          {
            hfragFunctIn[k]->Fill(trkPt[trkidx]/jetpt[jidx]);
            ntrkincone++;
            totalptincone+=trkPt[trkidx];
          }
          if(dRcone<jetradius)
          {
            hfragFunctOut[k]->Fill(trkPt[trkidx]/jetpt[jidx]);
            ntrkoutcone++;
            totalptoutcone+=trkPt[trkidx];
          }
        }
        hnTrkincone[k]->Fill(ntrkincone);
        hnTrkoutcone[k]->Fill(ntrkoutcone);
        htrkPtincone[k]->Fill(totalptincone);
        htrkPtoutcone[k]->Fill(totalptoutcone);
      }
      hnjets[k]->Fill(njetinptbin);
    }
  }
  
  fout->Write();
  fout->Close();
}


int main(int argc, char *argv[])
{
  if(argc != 3 && argc != 4)
  {    
    std::cout<<"usage: ./ztree.exe <infilename> <outfilename>"<<std::endl;
    exit(1);
  }
  ztree * t = new ztree(argv[1]);
  if(argc==3) t->Loop(argv[2]);
  if(argc==4) t->Loop(argv[2],argv[3]);
  return 0;
}


