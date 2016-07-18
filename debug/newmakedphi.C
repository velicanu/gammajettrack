#define ztree_cxx
#include "ztree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include "ggTree.h"

float ztree::getTrkWeight(TrkCorr * trkCorr, int itrk)
{
	float rmin = 999;
	for(int k = 0; k<njet; k++)
	{
		if(jetpt[k]<50) break;
		if(TMath::Abs(jeteta[k]>2)) continue;//jet quality cut
		float R = TMath::Power(jeteta[k]-trkEta[itrk],2)+TMath::Power(TMath::ACos(TMath::Cos(jetphi[k]-trkPhi[itrk])),2);
		if(rmin*rmin>R) rmin=TMath::Power(R,0.5);
	}
	return trkCorr->getTrkCorr(trkPt[itrk],trkEta[itrk],trkPhi[itrk],hiBin,rmin);
}

void ztree::Loop(std::string outfname , std::string tag, int pfTypeSelection)
{
	TrkCorr* trkCorr = new TrkCorr("TrkCorr_Feb16_Iterative_PbPb/");
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(outfname.data(),"recreate");
  
  TH2D * hGammaSig = new TH2D(Form("hGammaSig"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  TH2D * hJetSig = new TH2D(Form("hJetSig"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
	string rockettypes[2] = {"pho","jet"};
	string rocketpts[4] = {"12","24","48","8p"};
	float ptbinsrocket[5] = {1,2,4,8,1000};
	TH1D * hrocket[2][4];
	TH1D * hrocone[2][4];
	for(int i = 0 ; i < 2 ; ++i)
	{
		for(int j = 0 ; j < 4 ; ++j)
		{
			hrocket[i][j] = new TH1D(Form("hrocketsig_%s_%s",rockettypes[i].data(),rocketpts[j].data()),";#DeltaR jet;",30,-1.5,1.5); 
			hrocone[i][j] = new TH1D(Form("hroconesig_%s_%s",rockettypes[i].data(),rocketpts[j].data()),";#DeltaR jet;",30,-1.5,1.5); 
		}
	}
	string hascorr[2] = {"corr","nocorr"};
	string trktype[3] = {"pt","eta","phi"};
	double trkbins[6] = {0,100,-2.5,2.5,-pi,pi};
	TH1D * htrkptetaphi[2][3];
	TH2D * htrkptetaphivcorr[1][3];
	for(int i = 0 ; i < 2 ; ++i)
	{
		for(int j = 0 ; j < 3 ; ++j)
		{
			htrkptetaphi[i][j] = new TH1D(Form("htrksig_%s_%s",hascorr[i].data(),trktype[j].data()),Form(";trk %s ;",trktype[j].data()),24,trkbins[2*j],trkbins[2*j+1]); 
			if(i==0) {
				htrkptetaphivcorr[0][j] = new TH2D(Form("htrksig_%s_vcorr",trktype[j].data()),Form(";trk %s;correction",trktype[j].data()),24,trkbins[2*j],trkbins[2*j+1],50,0,10); 
			}
		}
	}
	
	
	TH1D * hjetpt = new TH1D(Form("hjetptsig"),";p_{T} pho;",30,0,300); 
	TH1D * hphoet = new TH1D(Form("hphoetsig"),";p_{T} jet;",30,0,300); 
	TH1D * hphoconeeta = new TH1D(Form("hphoconeetasig"),";#eta reflected cone pho;",50,-2.5,2.5); 
	TH1D * hjetconeeta = new TH1D(Form("hjetconeetasig"),";#eta reflected cone jet;",50,-2.5,2.5); 
  
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
    if(phoEt[ipho]<50) continue;
    // cout<<vz<<endl;
    float gammajetdphi = fabs(phoPhi[0]-jetphi[0]);
    if(gammajetdphi > pi) gammajetdphi = 2*pi - gammajetdphi;
    if(gammajetdphi < 5.0 * pi / 6.0) 
    {
      continue;
    }
		hjetpt->Fill(jetpt[0]);
		hphoet->Fill(phoEt[ipho]);
		bool valid_phocone = fabs(phoEta[ipho])>0.5;
		bool valid_jetcone = fabs(jeteta[0])>0.5;
		if(valid_phocone) hphoconeeta->Fill(phoEta[ipho]);
		if(valid_jetcone) hjetconeeta->Fill(jeteta[0]);
    
    for(int itrk = 0 ; itrk < nTrk ; ++itrk)
    {
			if(fabs(trkEta[itrk])>2.4 || trkPt[itrk]<1) continue;
			float trkweight = getTrkWeight(trkCorr,itrk);
			htrkptetaphivcorr[0][0]->Fill(trkPt[itrk],weight*trkweight);
			htrkptetaphivcorr[0][1]->Fill(trkEta[itrk],weight*trkweight);
			htrkptetaphivcorr[0][2]->Fill(trkPhi[itrk],weight*trkweight);

			
			htrkptetaphi[0][0]->Fill(trkPt[itrk],weight*trkweight);
			htrkptetaphi[0][1]->Fill(trkEta[itrk],weight*trkweight);
			htrkptetaphi[0][2]->Fill(trkPhi[itrk],weight*trkweight);
			htrkptetaphi[1][0]->Fill(trkPt[itrk]);
			htrkptetaphi[1][1]->Fill(trkEta[itrk]);
			htrkptetaphi[1][2]->Fill(trkPhi[itrk]);
			
      double deta = fabs(phoEta[ipho]-trkEta[itrk]);
      double detac = fabs(-phoEta[ipho]-trkEta[itrk]);
      double dphi = fabs(phoPhi[ipho]-trkPhi[itrk]);
      if( dphi > pi ) dphi = 2*pi - dphi;
			float drpho = sqrt((deta*deta) + (dphi*dphi));
			float drphoc = sqrt((detac*detac) + (dphi*dphi));
			
      
			hGammaSig->Fill(deta,dphi,weight*trkweight);
      hGammaSig->Fill(-deta,dphi,weight*trkweight);
      hGammaSig->Fill(deta,-dphi,weight*trkweight);
      hGammaSig->Fill(-deta,-dphi,weight*trkweight);
      hGammaSig->Fill(deta,(2*pi)-dphi,weight*trkweight);
      hGammaSig->Fill(-deta,(2*pi)-dphi,weight*trkweight);
      
      deta = fabs(jeteta[0]-trkEta[itrk]);
      detac = fabs(-jeteta[0]-trkEta[itrk]);
      dphi = fabs(jetphi[0]-trkPhi[itrk]);
      if( dphi > pi ) dphi = 2*pi - dphi;
			float drjet = sqrt((deta*deta) + (dphi*dphi));
			float drjetc = sqrt((detac*detac) + (dphi*dphi));
			
			
			hJetSig->Fill(deta,dphi,weight*trkweight);
      hJetSig->Fill(-deta,dphi,weight*trkweight);
      hJetSig->Fill(deta,-dphi,weight*trkweight);
      hJetSig->Fill(-deta,-dphi,weight*trkweight);
      hJetSig->Fill(deta,(2*pi)-dphi,weight*trkweight);
      hJetSig->Fill(-deta,(2*pi)-dphi,weight*trkweight);
      
      for(int iptbin = 0 ; iptbin < 4 ; ++iptbin)
			{
				if(trkPt[itrk]>ptbinsrocket[iptbin] && trkPt[itrk]<ptbinsrocket[iptbin+1])
				{
					if(drpho<0.5) hrocket[0][iptbin]->Fill(drpho,trkPt[itrk]/drpho*trkweight);
					if(drjet<0.5) hrocket[1][iptbin]->Fill(drjet,trkPt[itrk]/drjet*trkweight);
					if(valid_phocone) {
						if(drphoc<0.5) hrocone[0][iptbin]->Fill(drphoc,trkPt[itrk]/drphoc*trkweight);
					}
					if(valid_jetcone) {
						if(drjetc<0.5) hrocone[1][iptbin]->Fill(drjetc,trkPt[itrk]/drjetc*trkweight);
					}
				}
			}
			
    }
  }
  
  fout->Write();
  fout->Close();
}

void ztree::MixedEvent(std::string outfname)
{
	TrkCorr* trkCorr = new TrkCorr("TrkCorr_Feb16_Iterative_PbPb/");
  TFile *fmix = TFile::Open("/home/ursu/HIMinimumBiasJet30Skim/HIMinimumBiasJet30Skim-xaa.root");
  TTree * mixtree = (TTree*) fmix->Get("ztree");
  InitMix(mixtree);
  
  
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  TFile * fout = new TFile(Form("mix_%s",outfname.data()),"recreate");
  TH2D * hGammaMix = new TH2D(Form("hGammaMix"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
  TH2D * hJetMix = new TH2D(Form("hJetMix"),";#Delta#eta;#Delta#phi",33,-5,5,48,-pi,2*pi);
	string rocketpts[4] = {"12","24","48","8p"};
	string rockettypes[2] = {"pho","jet"};
	float ptbinsrocket[5] = {1,2,4,8,1000};
	TH1D * hrocket[2][4];
	TH1D * hrocone[2][4];
	for(int i = 0 ; i < 2 ; ++i)
	{
		for(int j = 0 ; j < 4 ; ++j)
		{
			hrocket[i][j] = new TH1D(Form("hrocketmix_%s_%s",rockettypes[i].data(),rocketpts[j].data()),";#DeltaR jet;",30,-1.5,1.5); 
			hrocone[i][j] = new TH1D(Form("hroconemix_%s_%s",rockettypes[i].data(),rocketpts[j].data()),";#DeltaR jet;",30,-1.5,1.5); 

		}
	}
	string hascorr[2] = {"corr","nocorr"};
	string trktype[3] = {"pt","eta","phi"};
	double trkbins[6] = {0,100,-2.5,2.5,-pi,pi};
	TH1D * htrkptetaphi[2][3];
	TH2D * htrkptetaphivcorr[1][3];
	for(int i = 0 ; i < 2 ; ++i)
	{
		for(int j = 0 ; j < 3 ; ++j)
		{
			htrkptetaphi[i][j] = new TH1D(Form("htrkmix_%s_%s",hascorr[i].data(),trktype[j].data()),Form(";trk %s ;",trktype[j].data()),24,trkbins[2*j],trkbins[2*j+1]); 
			if(i==0) {
				htrkptetaphivcorr[0][j] = new TH2D(Form("htrkmix_%s_vcorr",trktype[j].data()),Form(";trk %s;correction",trktype[j].data()),24,trkbins[2*j],trkbins[2*j+1],50,0,10); 
			}
		}
	}

	TH1D * hjetpt = new TH1D(Form("hjetptmix"),";p_{T} jet;",30,0,300); 
	TH1D * hphoet = new TH1D(Form("hphoetmix"),";p_{T} jet;",30,0,300); 
	TH1D * hphoconeeta = new TH1D(Form("hphoconeetamix"),";#eta reflected cone pho;",50,-2.5,2.5); 
	TH1D * hjetconeeta = new TH1D(Form("hjetconeetamix"),";#eta reflected cone jet;",50,-2.5,2.5); 
  
	
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
			if(i==jentry) continue;
      if(fabs(vz-vvz[i])<0.5 && abs(hiBin-vhiBin[i])<5)
      {
        // cout<<i<<" "<<fabs(vz-vvz[i])<<" "<<abs(hiBin-vhiBin[i])<<endl;
        imatched[nmatched]=i;
        nmatched++;	
      }
    }
    float gammajetdphi = fabs(phoPhi[0]-jetphi[0]);
    if(gammajetdphi > pi) gammajetdphi = 2*pi - gammajetdphi;
    if(gammajetdphi < 5.0 * pi / 6.0) 
    {
      continue;
    }
    
    
    for(int i = 0 ; i < nmatched ; ++i)
    {
      Long64_t mixentry = LoadTreeMix(imatched[i]);
      if (mixentry < 0) break;
      nb = mix_fChain->GetEntry(imatched[i]);   nbytes += nb;

			hjetpt->Fill(jetpt[0]);
			hphoet->Fill(phoEt[ipho]);      
			bool valid_phocone = fabs(phoEta[ipho])>0.5;
			bool valid_jetcone = fabs(jeteta[0])>0.5;
			if(valid_phocone) hphoconeeta->Fill(phoEta[ipho]);
			if(valid_jetcone) hjetconeeta->Fill(jeteta[0]);
      for(int itrk = 0 ; itrk < mix_nTrk ; ++itrk)
      {
				if(fabs(trkEta[itrk])>2.4 || trkPt[itrk]<1) continue;
				float trkweight = getTrkWeight(trkCorr,itrk);
				htrkptetaphivcorr[0][0]->Fill(trkPt[itrk],weight*trkweight);
				htrkptetaphivcorr[0][1]->Fill(trkEta[itrk],weight*trkweight);
				htrkptetaphivcorr[0][2]->Fill(trkPhi[itrk],weight*trkweight);
				
				htrkptetaphi[0][0]->Fill(trkPt[itrk],weight*trkweight);
				htrkptetaphi[0][1]->Fill(trkEta[itrk],weight*trkweight);
				htrkptetaphi[0][2]->Fill(trkPhi[itrk],weight*trkweight);
				htrkptetaphi[1][0]->Fill(trkPt[itrk]);
				htrkptetaphi[1][1]->Fill(trkEta[itrk]);
				htrkptetaphi[1][2]->Fill(trkPhi[itrk]);
				
        double deta = fabs(phoEta[ipho]-mix_trkEta[itrk]);
        double detac = fabs(-phoEta[ipho]-mix_trkEta[itrk]);
        double dphi = fabs(phoPhi[ipho]-mix_trkPhi[itrk]);
        if( dphi > pi ) dphi = 2*pi - dphi;
				float drpho = sqrt((deta*deta) + (dphi*dphi));
				float drphoc = sqrt((detac*detac) + (dphi*dphi));
        hGammaMix->Fill(deta,dphi,weight*trkweight);
        hGammaMix->Fill(-deta,dphi,weight*trkweight);
        hGammaMix->Fill(deta,-dphi,weight*trkweight);
        hGammaMix->Fill(-deta,-dphi,weight*trkweight);
        hGammaMix->Fill(deta,(2*pi)-dphi,weight*trkweight);
        hGammaMix->Fill(-deta,(2*pi)-dphi,weight*trkweight);
        
        deta = fabs(jeteta[0]-mix_trkEta[itrk]);
        detac = fabs(-jeteta[0]-mix_trkEta[itrk]);
        dphi = fabs(jetphi[0]-mix_trkPhi[itrk]);
        if( dphi > pi ) dphi = 2*pi - dphi;
				float drjet = sqrt((deta*deta) + (dphi*dphi));
				float drjetc = sqrt((detac*detac) + (dphi*dphi));
        hJetMix->Fill(deta,dphi,weight*trkweight);
        hJetMix->Fill(-deta,dphi,weight*trkweight);
        hJetMix->Fill(deta,-dphi,weight*trkweight);
        hJetMix->Fill(-deta,-dphi,weight*trkweight);
        hJetMix->Fill(deta,(2*pi)-dphi,weight*trkweight);
        hJetMix->Fill(-deta,(2*pi)-dphi,weight*trkweight);
        
				
				for(int iptbin = 0 ; iptbin < 4 ; ++iptbin)
				{
					if(trkPt[itrk]>ptbinsrocket[iptbin] && trkPt[itrk]<ptbinsrocket[iptbin+1])
					{
						if(drpho<0.5) hrocket[0][iptbin]->Fill(drpho,trkPt[itrk]/drpho*trkweight);
						if(drjet<0.5) hrocket[1][iptbin]->Fill(drjet,trkPt[itrk]/drjet*trkweight);
						if(valid_phocone) {
							if(drphoc<0.5) hrocone[0][iptbin]->Fill(drphoc,trkPt[itrk]/drphoc*trkweight);
						}
						if(valid_jetcone) {
							if(drjetc<0.5) hrocone[1][iptbin]->Fill(drjetc,trkPt[itrk]/drjetc*trkweight);
						}
					}
				}
      }
      
    }
    
    
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


