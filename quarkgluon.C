TH1D * histToFit;
TH1D * quarktemplate;
TH1D * gluontemplate;
int centmins[] = {0,20,60,100,140};
int centmaxs[] = {20,60,100,200,200};
string ylabel[] = {"1/N_{jet} dN/d#xi_{jet}","1/N_{jet} dN/d#xi_{#gamma}"};
string xlabel[] = {"#xi_{jet}","#xi_{#gamma}"};


Double_t myfunction(Double_t *x, Double_t *par)
{
  Float_t xx =x[0];
  float qf = 1-par[1];
  if(qf > 1) qf = 1;
  if(qf < 0) qf = 0;
  float gf = 1-qf;
  Double_t f = par[0]*((qf*quarktemplate->GetBinContent(quarktemplate->FindBin(xx))) + (gf*gluontemplate->GetBinContent(gluontemplate->FindBin(xx))));
  return f;
}

void myfunc() {
  TF1 *f1 = new TF1("myfunc",myfunction,0.5,2.5,2);
  f1->SetParameters(1,0.5);
  f1->SetParNames("scale","gluonfraction");
}

TF1 * quarkgluon(int phoetmin = 60, int jetptmin = 30, int icent=0, int datamc = 0, int gammaxi = 0) {
  TFile * fin = TFile::Open("mc_pbpb.root");
  if(datamc==0)  histToFit = (TH1D*) fin->Get(Form("hgammaffxi_pbpbmc_recoreco_%d_1000_%d_%d_gammaxi%d_%d_%d",phoetmin,jetptmin,0,gammaxi,centmins[icent],centmaxs[icent]));
  if(datamc==1)  histToFit = (TH1D*) fin->Get(Form("hgammaffxi_pbpbdata_recoreco_%d_1000_%d_gammaxi%d_%d_%d",phoetmin,jetptmin,gammaxi,centmins[icent],centmaxs[icent]));
  quarktemplate = (TH1D*) fin->Get(Form("hgammaffxi_pbpbmc_recoreco_%d_1000_%d_%d_gammaxi%d_%d_%d",phoetmin,jetptmin,1,gammaxi,centmins[icent],centmaxs[icent]));
  gluontemplate = (TH1D*) fin->Get(Form("hgammaffxi_pbpbmc_recoreco_%d_1000_%d_%d_gammaxi%d_%d_%d",phoetmin,jetptmin,2,gammaxi,centmins[icent],centmaxs[icent]));

  TF1 *f1 = (TF1 *)gROOT->GetFunction("myfunc");
  // f1->SetParameter(0,0.5);
  histToFit->Fit("myfunc","","",0.5,2.5);
  histToFit->SetMinimum(0);
  histToFit->SetMaximum(5);
  histToFit->SetXTitle(xlabel[gammaxi].data());
  histToFit->SetYTitle(ylabel[gammaxi].data());
  histToFit->GetXaxis()->CenterTitle();
  histToFit->GetYaxis()->CenterTitle();
  return f1;
}
