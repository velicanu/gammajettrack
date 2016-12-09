#include "makeMultiPanelCanvas.C"

void drawcentffgamma() {
  TFile *_file0 = TFile::Open("all.root");
  int save = 1;
  
  const int yaxismax = 5;
  const static int ncentbins = 4;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};
  TCanvas * c1_pbpbdata[ncentbins]; // ncentbins
  TH1D * hgammaffxi_pbpbdata_[ncentbins];
  TH1D * hjetpt_pbpbdata_[ncentbins];
  TH1D * hgammaffxi_refcone_pbpbdata_[ncentbins];
  float njets_pbpbdata[ncentbins];
  TLegend * leg_ff_pbpbdata[ncentbins];

  TCanvas * c1_pbpbmc[ncentbins];
  TH1D * hgammaffxi_pbpbmc_[ncentbins];
  TH1D * hjetpt_pbpbmc_[ncentbins];
  TH1D * hgammaffxi_refcone_pbpbmc_[ncentbins];
  float njets_pbpbmc[ncentbins];
  TLegend * leg_ff_pbpbmc[ncentbins];

  TCanvas * c1_subpbpb[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TH1D * clone_hgammaffxi_refcone_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxi_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxi_refcone_pbpbmc_[ncentbins];
  TH1D * clone_hgammaffxi_pbpbmc_[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

  TCanvas * call = new TCanvas("call","",1400,500);
  // makeMultiPanelCanvas(call,6,1,0,0,-2.99,0.2,0.04);
  // makeMultiPanelCanvas(call,6,1,0.02,0.0,-6,0.2,0.04);
  // makeMultiPanelCanvas(call,4,1,0,0,0.2,0.2,0.04);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);
  for (int icent = 0; icent < ncentbins; icent++) {
    // Raw FF pbpdata
    // c1_pbpbdata[icent] = new TCanvas(Form("c1_pbpbdata_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_refcone_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_refcone_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    njets_pbpbdata[icent] = hjetpt_pbpbdata_[icent]->Integral();
    hgammaffxi_pbpbdata_[icent]->Sumw2();
    hgammaffxi_refcone_pbpbdata_[icent]->Sumw2();
    hgammaffxi_pbpbdata_[icent]->Scale(1.0/njets_pbpbdata[icent]/binwidth);
    hgammaffxi_refcone_pbpbdata_[icent]->Scale(1.0/njets_pbpbdata[icent]/binwidth);
    hgammaffxi_pbpbdata_[icent]->GetXaxis()->CenterTitle();
    hgammaffxi_pbpbdata_[icent]->SetYTitle("dN/d#xi");
    hgammaffxi_pbpbdata_[icent]->GetYaxis()->CenterTitle();
    // hgammaffxi_pbpbdata_[icent]->Draw();

    hgammaffxi_refcone_pbpbdata_[icent]->SetMarkerStyle(24);
    // hgammaffxi_refcone_pbpbdata_[icent]->Draw("same");
    leg_ff_pbpbdata[icent] = new TLegend(0.23,0.59,0.50,0.92);
    leg_ff_pbpbdata[icent]->SetFillColor(0);
    leg_ff_pbpbdata[icent]->SetTextSize(0.05);
    leg_ff_pbpbdata[icent]->SetFillStyle(0);
    leg_ff_pbpbdata[icent]->SetTextFont(42);
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_pbpbdata_[icent],"raw frag. func","p");
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_refcone_pbpbdata_[icent],"#eta reflected cone","p");
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_refcone_pbpbdata_[icent],"PbPb #sqrt{s_{NN}}=5 TeV","");
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_refcone_pbpbdata_[icent],"trk p_{T}>1 GeV","");
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_refcone_pbpbdata_[icent],"100>#gamma p_{T}>300 GeV","");
    // leg_ff_pbpbdata[icent]->Draw();
    // c1_pbpbdata[icent]->SaveAs("pbpbdata_unsubffspectrum_45_gamma_100.png");

    // Raw FF pbpdata


    // Raw FF pbmc
    // c1_pbpbmc[icent] = new TCanvas(Form("c1_pbpbmc_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_pbpbmc_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_pbpbmc_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_refcone_pbpbmc_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_refcone_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    njets_pbpbmc[icent] = hjetpt_pbpbmc_[icent]->Integral();
    hgammaffxi_pbpbmc_[icent]->Sumw2();
    hgammaffxi_refcone_pbpbmc_[icent]->Sumw2();
    hgammaffxi_pbpbmc_[icent]->Scale(1.0/njets_pbpbmc[icent]/binwidth);
    hgammaffxi_refcone_pbpbmc_[icent]->Scale(1.0/njets_pbpbmc[icent]/binwidth);
    hgammaffxi_pbpbmc_[icent]->GetXaxis()->CenterTitle();
    hgammaffxi_pbpbmc_[icent]->SetYTitle("dN/d#xi");
    hgammaffxi_pbpbmc_[icent]->GetYaxis()->CenterTitle();
    // hgammaffxi_pbpbmc_[icent]->Draw();

    hgammaffxi_refcone_pbpbmc_[icent]->SetMarkerStyle(24);
    // hgammaffxi_refcone_pclone_hgammaffxi_refcone_pbpbdata_bpbmc_[icent]->Draw("same");

    leg_ff_pbpbmc[icent] = new TLegend(0.22,0.59,0.49,0.92);
    leg_ff_pbpbmc[icent]->SetFillColor(0);
    leg_ff_pbpbmc[icent]->SetTextSize(0.05);
    leg_ff_pbpbmc[icent]->SetFillStyle(0);
    leg_ff_pbpbmc[icent]->SetTextFont(42);
    leg_ff_pbpbmc[icent]->AddEntry(hgammaffxi_pbpbmc_[icent],"raw frag. func","p");
    leg_ff_pbpbmc[icent]->AddEntry(hgammaffxi_refcone_pbpbmc_[icent],"#eta reflected cone","p");
    leg_ff_pbpbmc[icent]->AddEntry(hgammaffxi_refcone_pbpbmc_[icent],"Pythia+Hydjet #hat{p}_{T}=","");
    leg_ff_pbpbmc[icent]->AddEntry(hgammaffxi_refcone_pbpbmc_[icent],"trk p_{T}>1 GeV","");
    leg_ff_pbpbmc[icent]->AddEntry(hgammaffxi_refcone_pbpbmc_[icent],"45>#gamma p_{T}>100 GeV","");
    // leg_ff_pbpbmc[icent]->Draw();
    // c1_pbpbmc[icent]->SaveAs("pbpbmc_unsubffspectrum_45_gamma_100.png");
    // Raw FF pbpbmc


    // Eta cone subtracted FF pbpbdata and pbpbmc
    // c1_subpbpb[icent] = new TCanvas(Form("c1_subpbpb_%d_%d",centmins[icent],centmaxs[icent]));
    // call->cd(icent+2);
    call->cd(icent+2);
    dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetYaxis()->CenterTitle();
    // if(icent!=0)
    // {
      dummy_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.5);
    // }

    clone_hgammaffxi_refcone_pbpbdata_[icent] = (TH1D*) hgammaffxi_refcone_pbpbdata_[icent]->Clone(Form("clone_hgammaffxi_refcone_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_refcone_pbpbdata_[icent]->Scale(-1);
    clone_hgammaffxi_pbpbdata_[icent] = (TH1D*) hgammaffxi_pbpbdata_[icent]->Clone(Form("clone_hgammaffxi_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_pbpbdata_[icent]->Add(clone_hgammaffxi_refcone_pbpbdata_[icent]);

    clone_hgammaffxi_refcone_pbpbmc_[icent] = (TH1D*) hgammaffxi_refcone_pbpbmc_[icent]->Clone(Form("clone_hgammaffxi_refcone_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_refcone_pbpbmc_[icent]->Scale(-1);
    clone_hgammaffxi_pbpbmc_[icent] = (TH1D*) hgammaffxi_pbpbmc_[icent]->Clone(Form("clone_hgammaffxi_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_pbpbmc_[icent]->Add(clone_hgammaffxi_refcone_pbpbmc_[icent]);
    clone_hgammaffxi_pbpbmc_[icent]->SetMarkerColor(kRed);
    // fixedFontHist(dummy_pbpbsub[icent]);
    dummy_pbpbsub[icent]->Draw();
    clone_hgammaffxi_pbpbdata_[icent]->Draw("same");
    // hgammaffxi_pbpbmc_[icent]->Draw("same");
    // hgammaffxi_refcone_pbpbmc_[icent]->Draw("same");
    clone_hgammaffxi_pbpbmc_[icent]->Draw("same");
    if(icent==0)
    {
      // leg_ff_pbpbsub[icent] = new TLegend(0.25,0.697,0.875,0.92);
      leg_ff_pbpbsub[icent] = new TLegend(0.05,0.697,0.27,0.92);
      leg_ff_pbpbsub[icent]->SetTextSize(0.05*1.3);
    }
    else
    {
      leg_ff_pbpbsub[icent] = new TLegend(0,0.697,0.27,0.92);
      // leg_ff_pbpbsub[icent]->SetTextSize(0.05*1.2);
      leg_ff_pbpbsub[icent]->SetTextSize(0.05*1.3);
    }
    leg_ff_pbpbsub[icent]->SetFillColor(0);
    leg_ff_pbpbsub[icent]->SetFillStyle(0);
    leg_ff_pbpbsub[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbdata_[icent],"PbPb #sqrt{s_{NN}}=5 TeV","p");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"Pythia+Hydjet","p");
    }
    else if(icent==1)
    {
      // leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"#eta cone sub","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"100>#gamma p_{T}>300 GeV","");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"|#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"p_{T}^{jet} > 40 GeV","");
    }
    else
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
    // c1_subpbpb[icent]->SaveAs("pbpbdata_pbpbmc_etaconesubtracted_45_gamma_100.png");
    // Eta cone subtracted FF pbpbdata and pbpbmc

  }
  call->cd(1);

  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.3);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  TLatex * laxis[yaxismax];
  for (int ilatex = 0; ilatex < yaxismax; ilatex++) {
    laxis[ilatex] = new TLatex(3.,ilatex-0.1,Form("%d",ilatex));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.3);
    laxis[ilatex]->Draw();
  }
  ldndxi->Draw();

  
  // call->cd(1);
  // TLatex * ldndxi = new TLatex(0.7,0.5,"dN/d#xi");
  // ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  // ldndxi->SetNDC();
  // ldndxi->SetTextAngle(90);
  // ldndxi->Draw();
}
