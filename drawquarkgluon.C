#include "quarkgluon.C"
string sdatamc[] = {"MC","Data"};

void drawquarkgluon(int phoetmin, int jetptmin, int icent, int datamc, int gammaxi) {
  TCanvas * c1 = new TCanvas();
  myfunc();
  TF1 * fitted = quarkgluon(phoetmin,jetptmin,icent,datamc,gammaxi);
  TH1D * hquarktemplate = (TH1D*)h2->Clone("hquarktemplate");
  TH1D * hgluontemplate = (TH1D*)h3->Clone("hgluontemplate");
  float gluonfraction = fitted->GetParameter(1);
  if(gluonfraction > 1) gluonfraction = 1;
  if(gluonfraction < 0) gluonfraction = 0;
  float quarkfraction = 1 - gluonfraction;
  float scale = fitted->GetParameter(0);
  float error = fitted->GetParError(1);
  
  hquarktemplate->Scale(quarkfraction*scale);
  hgluontemplate->Scale(gluonfraction*scale);
  TH1D * hsum = (TH1D*)hquarktemplate->Clone("hsum");
  hsum->Add(hgluontemplate);
  hquarktemplate->SetLineColor(kBlue);
  hgluontemplate->SetLineColor(kGreen);
  hgluontemplate->Draw("hist same");
  hquarktemplate->Draw("hist same");
  hsum->Draw("hist same");

  TLegend * leg = new TLegend(0.25,0.6,0.47,0.9);
  leg->SetTextSize(0.05*1.3);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(leg->GetTextSize()*0.95);
  leg->AddEntry(h1,Form("PbPb %s %d-%d%%",sdatamc[datamc].data(),centmins[icent]/2,centmaxs[icent]/2),"pe");
  leg->AddEntry(hquarktemplate,Form("quark fraction %2.1f%% (%2.1f%%)",quarkfraction*100,error*100),"l");
  leg->AddEntry(hgluontemplate,Form("gluon fraction %2.1f%% (%2.1f%%)",gluonfraction*100,error*100),"l");
  leg->AddEntry(fitted,Form("fit E^{#gamma}_{T}>%d",phoetmin),"l");
  leg->Draw();
  c1->SaveAs(Form("quarkgluon_%d_%d_1000_%d_gammaxi%d_%d_%d.png",datamc,phoetmin,jetptmin,gammaxi,centmins[icent],centmaxs[icent]));
}
