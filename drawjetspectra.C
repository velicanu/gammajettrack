#include "makeMultiPanelCanvas.C"

void drawjetspectra(int phoetmin, int phoetmax) {
  TFile *_file0 = TFile::Open(Form("all_%d_%d.root",phoetmin,phoetmax));
  int save = 1;

  const int yaxismax = 5;
  int yaxissubmin = -1;
  int yaxissubmax = 2;
  const static int ncentbins = 4;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};

  TH1D * hjetpt_pbpbdata_[ncentbins];
  TH1D * hjetpt_ppdata_[ncentbins];
  TLegend * leg_ff_ppdata[ncentbins];

  TCanvas * call = new TCanvas("call","",1400,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {

    call->cd(icent+2);
    hjetpt_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppdata_[icent] = (TH1D*) _file0->Get(Form("hjetpt_ppdata__1_200"));
    hjetpt_ppdata_[icent]->SetMarkerColor(kRed);
    hjetpt_ppdata_[icent]->GetXaxis()->CenterTitle();
    hjetpt_ppdata_[icent]->DrawNormalized("pe");
    hjetpt_pbpbdata_[icent]->DrawNormalized("pe same");

    leg_ff_ppdata[icent] = new TLegend(0.42,0.69,0.69,0.92);
    leg_ff_ppdata[icent]->SetFillColor(0);
    leg_ff_ppdata[icent]->SetTextSize(0.05);
    leg_ff_ppdata[icent]->SetFillStyle(0);
    leg_ff_ppdata[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg_ff_ppdata[icent]->AddEntry(hjetpt_ppdata_[icent],"pp #sqrt{s}=5 TeV","p");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"PbPb #sqrt{s_{NN}}=5 TeV","p");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    } else {
      leg_ff_ppdata[icent]->AddEntry(hjetpt_ppdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
    }
    leg_ff_ppdata[icent]->AddEntry(hjetpt_ppdata_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_ppdata[icent]->Draw();
    gPad->SetLogy();

  }
  call->cd(1);
  gPad->SetLogy();
}
