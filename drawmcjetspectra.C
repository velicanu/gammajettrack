#include "makeMultiPanelCanvas.C"

void drawmcjetspectra(int phoetmin, int phoetmax) {
  TFile *_file0 = TFile::Open(Form("pbpb_pp_%d_%d_30.root",phoetmin,phoetmax));
  int save = 1;

  float yaxismax = 0.08;
  int yaxissubmin = -1;
  int yaxissubmax = 2;
  const static int ncentbins = 4;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};

  TH2D * dummy[ncentbins];
  TH1D * hjetpt_pbpbmc_[ncentbins];
  TH1D * hjetpt_ppmc_[ncentbins];
  TH1D * hphoet_pbpbmc_[ncentbins];
  TH1D * hphoet_ppmc_[ncentbins];
  TH1D * hjetpt_pbpbmc_gengen[ncentbins];
  TH1D * hjetpt_ppmc_gengen[ncentbins];
  TLegend * leg_ff_ppmc[ncentbins];

  TCanvas * call = new TCanvas("call","",1400,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {

    call->cd(icent+2);
    hjetpt_pbpbmc_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbmc_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppmc_[icent] = (TH1D*) _file0->Get(Form("hjetpt_ppmc_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hphoet_pbpbmc_[icent] = (TH1D*) _file0->Get(Form("phoetsignal_pbpbmc_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hphoet_ppmc_[icent] = (TH1D*) _file0->Get(Form("phoetsignal_ppmc_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_pbpbmc_gengen[icent] = (TH1D*) _file0->Get(Form("hgenjetpt_pbpbmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppmc_gengen[icent] = (TH1D*) _file0->Get(Form("hgenjetpt_ppmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppmc_[icent]->SetMarkerColor(kRed);
    hjetpt_ppmc_gengen[icent]->SetLineColor(kRed);
    hjetpt_ppmc_[icent]->GetXaxis()->CenterTitle();

    float bw = hgenjetpt_pbpbmc_gengen_0_20->GetBinWidth(1);
    float nphopp = hphoet_ppmc_[icent]->Integral();
    float nphopbpb = hphoet_pbpbmc_[icent]->Integral();

    hjetpt_ppmc_[icent]->Sumw2();
    hjetpt_pbpbmc_[icent]->Sumw2();
    hjetpt_ppmc_gengen[icent]->Sumw2();
    hjetpt_pbpbmc_gengen[icent]->Sumw2();
    hjetpt_ppmc_[icent]->Scale(1/bw/nphopp);
    hjetpt_pbpbmc_[icent]->Scale(1/bw/nphopbpb);
    hjetpt_ppmc_gengen[icent]->Scale(1/bw/nphopp);
    hjetpt_pbpbmc_gengen[icent]->Scale(1/bw/nphopbpb);


    dummy[icent] = new TH2D(Form("dummy_%d_%d",centmins[icent],centmaxs[icent]),";Jet p_{T};1/N_{#gamma} dn/dp_{T}",1,1,499,1,1e-6,yaxismax);
    dummy[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy[icent]->GetXaxis()->CenterTitle();
    dummy[icent]->GetYaxis()->CenterTitle();
    dummy[icent]->GetXaxis()->SetTitleSize(dummy[icent]->GetXaxis()->GetTitleSize()*1.4);

    dummy[icent]->Draw();
    hjetpt_ppmc_[icent]->Draw("pe same");
    hjetpt_pbpbmc_[icent]->Draw("pe same");
    hjetpt_ppmc_gengen[icent]->Draw("hist same");
    hjetpt_pbpbmc_gengen[icent]->Draw("hist same");


    leg_ff_ppmc[icent] = new TLegend(0.42,0.69,0.69,0.92);
    leg_ff_ppmc[icent]->SetFillColor(0);
    leg_ff_ppmc[icent]->SetTextSize(0.05);
    leg_ff_ppmc[icent]->SetFillStyle(0);
    leg_ff_ppmc[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg_ff_ppmc[icent]->AddEntry(hjetpt_ppmc_[icent],"pp #sqrt{s}=5 TeV","p");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],"PbPb #sqrt{s_{NN}}=5 TeV","p");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    } else if (icent==1 ){
      leg_ff_ppmc[icent]->AddEntry(hjetpt_ppmc_gengen[icent],"Pythia","l");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_gengen[icent],"Pythia+Hydjet","l");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],"","");
    } else {
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],"","");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],"","");
      leg_ff_ppmc[icent]->AddEntry(hjetpt_pbpbmc_[icent],"","");
    }
    leg_ff_ppmc[icent]->AddEntry(hjetpt_ppmc_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_ppmc[icent]->Draw();
    gPad->SetLogy();

  }
  call->cd(1);
  gPad->SetLogy();
  call->SaveAs("jetspectra.png");
}
