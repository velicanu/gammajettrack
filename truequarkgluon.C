#include <iostream>
using namespace std;

int phomin[] = {60,80};
int jetmin[] = {30,40};
// int gammaxi[] = {0,1};
// int quarkgluon[] = {0,1,2};
int centmin[] = {0,20,60,100};
int centmax[] = {20,60,100,200};
const int nptbin = 2;
const int ngammaxi = 1;
const int nquarkgluon = 3;
const int ncentbin = 4;

TFile * finput[nptbin][ngammaxi][nquarkgluon];
TH1D * hjetpt[nptbin][ngammaxi][nquarkgluon][ncentbin];
float njets[nptbin][ngammaxi][nquarkgluon][ncentbin];

void truequarkgluon() {
  for(int ipt = 0 ; ipt < nptbin ; ipt++) {
    for(int iga = 0 ; iga < ngammaxi ; iga++) {
      for(int iqg = 0 ; iqg < nquarkgluon ; iqg++) {
	finput[ipt][iga][iqg] = TFile::Open(Form("closure_pbpb_%d_1000_%d_%d_gammaxi%d.root",phomin[ipt],jetmin[ipt],iqg,iga));
	for(int icent = 0 ; icent < ncentbin ; icent++) {
	  hjetpt[ipt][iga][iqg][icent] = (TH1D*) finput[ipt][iga][iqg]->Get(Form("hjetpt_pbpbmc_recoreco_%d_%d",centmin[icent],centmax[icent]));
	  njets[ipt][iga][iqg][icent] = hjetpt[ipt][iga][iqg][icent]->Integral();
	}
      }
    }
  }
  
  for(int ipt = 0 ; ipt < nptbin ; ipt++) {
    for(int iga = 0 ; iga < ngammaxi ; iga++) {
      for(int icent = 0 ; icent < ncentbin ; icent++) {
	float total = njets[ipt][iga][0][icent];
	float quark = njets[ipt][iga][1][icent];
	float gluon = njets[ipt][iga][2][icent];
	float fake  = total - quark - gluon;
	float qfrac = quark / (quark + gluon);
	float gfrac = 1 - qfrac;
	float ffrac = fake / total;
	cout<<phomin[ipt]<<" "<<jetmin[ipt]<<" "<<iga<<" "<<centmin[icent]<<"_"<<centmax[icent]<<" "<<total<<" "<<quark<<" "<<gluon<<" "<<fake<<"      "<<qfrac<<"      "<<gfrac<<"      "<<ffrac<<endl;
      }
    }
  }
}
