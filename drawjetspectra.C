#include "makeMultiPanelCanvas.C"

void drawjetspectra(int phoetmin, int phoetmax) {
  TFile *_file0 = TFile::Open(Form("all_%d_%d_30.root",phoetmin,phoetmax));
  int save = 1;

  float yaxismax = 0.025;
  int yaxissubmin = -1;
  int yaxissubmax = 2;
  const static int ncentbins = 4;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};

  TH2D * dummy[ncentbins];
  TH1D * hjetpt_pbpbdata_[ncentbins];
  TH1D * hjetpt_ppdata_[ncentbins];
  TH1D * hphoet_pbpbdata_[ncentbins];
  TH1D * hphoet_ppdata_[ncentbins];
  // TH1D * hjetpt_pbpbdata_gengen[ncentbins];
  // TH1D * hjetpt_ppdata_gengen[ncentbins];
  TLegend * leg_ff_ppdata[ncentbins];

  TCanvas * call = new TCanvas("call","",1400,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {

    call->cd(icent+2);
    hjetpt_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppdata_[icent] = (TH1D*) _file0->Get(Form("hjetpt_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hphoet_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("phoetsignal_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hphoet_ppdata_[icent] = (TH1D*) _file0->Get(Form("phoetsignal_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    // hjetpt_pbpbdata_gengen[icent] = (TH1D*) _file0->Get(Form("hgenjetpt_pbpbdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    // hjetpt_ppdata_gengen[icent] = (TH1D*) _file0->Get(Form("hgenjetpt_ppdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppdata_[icent]->SetMarkerColor(kRed);
    // hjetpt_ppdata_gengen[icent]->SetLineColor(kRed);
    hjetpt_ppdata_[icent]->GetXaxis()->CenterTitle();

    float bw = hjetpt_pbpbdata_[icent]->GetBinWidth(1);
    float nphopp = hphoet_ppdata_[icent]->Integral();
    float nphopbpb = hphoet_pbpbdata_[icent]->Integral();

    hjetpt_ppdata_[icent]->Sumw2();
    hjetpt_pbpbdata_[icent]->Sumw2();
    // hjetpt_ppdata_gengen[icent]->Sumw2();
    // hjetpt_pbpbdata_gengen[icent]->Sumw2();
    hjetpt_ppdata_[icent]->Scale(1/bw/nphopp);
    hjetpt_pbpbdata_[icent]->Scale(1/bw/nphopbpb);
    // hjetpt_ppdata_gengen[icent]->Scale(1/bw/nphopp);
    // hjetpt_pbpbdata_gengen[icent]->Scale(1/bw/nphopbpb);


    dummy[icent] = new TH2D(Form("dummy_%d_%d",centmins[icent],centmaxs[icent]),";Jet p_{T};1/N_{#gamma} dn/dp_{T}",1,1,499,1,1e-6,yaxismax);
    dummy[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy[icent]->GetXaxis()->CenterTitle();
    dummy[icent]->GetYaxis()->CenterTitle();
    dummy[icent]->GetXaxis()->SetTitleSize(dummy[icent]->GetXaxis()->GetTitleSize()*1.4);

    dummy[icent]->Draw();
    hjetpt_ppdata_[icent]->Draw("pe same");
    hjetpt_pbpbdata_[icent]->Draw("pe same");
    // hjetpt_ppdata_gengen[icent]->Draw("hist same");
    // hjetpt_pbpbdata_gengen[icent]->Draw("hist same");


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
    } else if (icent==1 ){
      // leg_ff_ppdata[icent]->AddEntry(hjetpt_ppdata_gengen[icent],"Pythia","l");
      // leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_gengen[icent],"Pythia+Hydjet","l");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
    } else {
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
      leg_ff_ppdata[icent]->AddEntry(hjetpt_pbpbdata_[icent],"","");
    }
    leg_ff_ppdata[icent]->AddEntry(hjetpt_ppdata_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_ppdata[icent]->Draw();
    gPad->SetLogy();

  }
  call->cd(1);
  // TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  // gStyle->SetFrameLineColor(0);
  // axis_dummy->UseCurrentStyle();
  // axis_dummy->Draw("FB BB A");

  // TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi 1/nJet purity");
  // ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  // ldndxi->SetNDC();
  // ldndxi->SetTextAngle(90);
  // ldndxi->Draw();

  // const int nlabels = 5;
  // float fylabels[] = {0,0.5,1,1.5,2};
  // string sylabels[] = {"0",".5","1","1.5","2"};
  // TLatex * laxis[nlabels];
  // for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    // laxis[ilatex] = new TLatex(2,fylabels[ilatex]-0.01,Form("%s",sylabels[ilatex].data()));
    // laxis[ilatex]->Draw();
  // }
  gPad->SetLogy();
  call->SaveAs(Form("data_jetspectra_log_%d_%d.png",phoetmin,phoetmax));
}
