#include "makeMultiPanelCanvas.C"

void drawclosureffgamma() {
  const int yaxismax = 4;
  const int yaxismax2 = 3;
  TFile *_file0 = TFile::Open("closure.root");
  int save = 1;
  const static int ncentbins = 5;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,140,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-70%","70-100%"};
  TCanvas * c1_pbpbmc_gen[ncentbins]; // ncentbins
  TH1D * hgammaffxi_pbpbmc_gen_[ncentbins];
  TH1D * hjetpt_pbpbmc_gen_[ncentbins];
  TH1D * hgammaffxi_refcone_pbpbmc_gen_[ncentbins];
  float njets_pbpbmc_gen[ncentbins];

  TCanvas * c1_pbpbmc[ncentbins];
  TH1D * hgammaffxi_pbpbmc_[ncentbins];
  TH1D * hjetpt_pbpbmc_[ncentbins];
  TH1D * hgammaffxi_refcone_pbpbmc_[ncentbins];
  float njets_pbpbmc[ncentbins];

  TCanvas * c1_subpbpb[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TH2D * dummy2_pbpbsub[ncentbins];
  TH1D * clone_hgammaffxi_refcone_pbpbmc_gen_[ncentbins];
  TH1D * clone_hgammaffxi_pbpbmc_gen_[ncentbins];
  TH1D * clone_hgammaffxi_refcone_pbpbmc_[ncentbins];
  TH1D * clone_hgammaffxi_pbpbmc_[ncentbins];
  TH2D * clone2_hgammaffxi_pbpbmc_gen_[ncentbins];
  TH2D * clone2_hgammaffxi_pbpbmc_[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub2[ncentbins];

  TCanvas * call = new TCanvas("call","",1600,500);
  // makeMultiPanelCanvas(call,5,1,0,0,0.2,0.2,0.04);
  makeMultiPanelCanvas(call,6,1,0.02,0.0,-6,0.2,0.04);
  for (int icent = 0; icent < 5; icent++) {
    // Raw FF pbpdata
    hgammaffxi_pbpbmc_gen_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_pbpbmc_gen_[icent] = (TH1D*) _file0->Get(Form("hjetpt_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_refcone_pbpbmc_gen_[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_refcone_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    njets_pbpbmc_gen[icent] = hjetpt_pbpbmc_gen_[icent]->Integral();
    hgammaffxi_pbpbmc_gen_[icent]->Sumw2();
    hgammaffxi_refcone_pbpbmc_gen_[icent]->Sumw2();
    hgammaffxi_pbpbmc_gen_[icent]->Scale(1.0/njets_pbpbmc_gen[icent]/binwidth);
    hgammaffxi_refcone_pbpbmc_gen_[icent]->Scale(1.0/njets_pbpbmc_gen[icent]/binwidth);
    hgammaffxi_pbpbmc_gen_[icent]->GetXaxis()->CenterTitle();
    hgammaffxi_pbpbmc_gen_[icent]->SetYTitle("dN/d#xi");
    hgammaffxi_pbpbmc_gen_[icent]->GetYaxis()->CenterTitle();
    hgammaffxi_refcone_pbpbmc_gen_[icent]->SetMarkerStyle(24);
    // Raw FF pbpdata


    // Raw FF pbmc
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
    hgammaffxi_refcone_pbpbmc_[icent]->SetMarkerStyle(24);
    // Raw FF pbpbmc


    // Eta cone subtracted FF pbpbmc_gen and pbpbmc
    call->cd(icent+2);
    dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetYaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.4);

    clone_hgammaffxi_refcone_pbpbmc_gen_[icent] = (TH1D*) hgammaffxi_refcone_pbpbmc_gen_[icent]->Clone(Form("clone_hgammaffxi_refcone_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_refcone_pbpbmc_gen_[icent]->Scale(-1);
    clone_hgammaffxi_pbpbmc_gen_[icent] = (TH1D*) hgammaffxi_pbpbmc_gen_[icent]->Clone(Form("clone_hgammaffxi_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    // clone_hgammaffxi_pbpbmc_gen_[icent]->Add(clone_hgammaffxi_refcone_pbpbmc_gen_[icent]); // no longer needed when using sube == 0

    clone_hgammaffxi_refcone_pbpbmc_[icent] = (TH1D*) hgammaffxi_refcone_pbpbmc_[icent]->Clone(Form("clone_hgammaffxi_refcone_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_refcone_pbpbmc_[icent]->Scale(-1);
    clone_hgammaffxi_pbpbmc_[icent] = (TH1D*) hgammaffxi_pbpbmc_[icent]->Clone(Form("clone_hgammaffxi_pbpbmc__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_pbpbmc_[icent]->Add(clone_hgammaffxi_refcone_pbpbmc_[icent]);
    clone_hgammaffxi_pbpbmc_[icent]->SetMarkerColor(kRed);
    clone_hgammaffxi_pbpbmc_gen_[icent]->SetMarkerColor(kBlue);
    // fixedFontHist(dummy_pbpbsub[icent]);
    dummy_pbpbsub[icent]->Draw();
    clone_hgammaffxi_pbpbmc_gen_[icent]->Draw("same");
    // hgammaffxi_pbpbmc_[icent]->Draw("same");
    // hgammaffxi_refcone_pbpbmc_[icent]->Draw("same");
    clone_hgammaffxi_pbpbmc_[icent]->Draw("same");
    if(icent==0)
    {
      leg_ff_pbpbsub[icent] = new TLegend(0.03,0.697,0.3,0.92);
    }
    else
    {
      leg_ff_pbpbsub[icent] = new TLegend(0,0.697,0.27,0.92);
    }
    leg_ff_pbpbsub[icent]->SetTextSize(0.05*1.3);
    leg_ff_pbpbsub[icent]->SetFillColor(0);
    leg_ff_pbpbsub[icent]->SetFillStyle(0);
    leg_ff_pbpbsub[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_gen_[icent],"gen(jet,trk) ff","p");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"reco(jet,trk) ff","p");
    }
    else if(icent==1)
    {
      // leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"#eta cone sub","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"100>#gamma p_{T}>300 GeV","");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"p_{T}^{jet} > 40 GeV","");
    }
    else
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
    // c1_subpbpb[icent]->SaveAs("pbpbmc_gen_pbpbmc_etaconesubtracted_45_gamma_100.png");
    // Eta cone subtracted FF pbpbmc_gen and pbpbmc

  }
  call->cd(1);

  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  TLatex * laxis[yaxismax];
  for (int ilatex = 0; ilatex < yaxismax; ilatex++) {
    laxis[ilatex] = new TLatex(3.,ilatex-0.1,Form("%d",ilatex));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
    laxis[ilatex]->Draw();
  }
  ldndxi->Draw();

  TCanvas * callratio = new TCanvas("callratio","",1600,500);
  makeMultiPanelCanvas(callratio,6,1,0.02,0.0,-6,0.2,0.04);
  for (int icent = 0; icent < 5; icent++) {
    callratio->cd(icent+2);
    clone2_hgammaffxi_pbpbmc_gen_[icent] = (TH2D*) clone_hgammaffxi_pbpbmc_gen_[icent]->Clone(Form("clone2_hgammaffxi_pbpbmc_gen_%d_%d",centmins[icent],centmaxs[icent]));
    clone2_hgammaffxi_pbpbmc_[icent] = (TH2D*) clone_hgammaffxi_pbpbmc_[icent]->Clone(Form("clone2_hgammaffxi_pbpbmc_%d_%d",centmins[icent],centmaxs[icent]));
    clone2_hgammaffxi_pbpbmc_gen_[icent]->Divide(clone2_hgammaffxi_pbpbmc_[icent]);

    dummy2_pbpbsub[icent] = new TH2D(Form("dummy2_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax2);
    dummy2_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy2_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy2_pbpbsub[icent]->GetYaxis()->CenterTitle();
    dummy2_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy2_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy2_pbpbsub[icent]->Draw();
    // clone2_hgammaffxi_pbpbmc_gen_[icent]->SetMarkerColor(kViolet);
    clone2_hgammaffxi_pbpbmc_gen_[icent]->SetMarkerColor(kBlack);
    clone2_hgammaffxi_pbpbmc_gen_[icent]->Draw("same");
    TLine * lone = new TLine(0,1,5,1);
    lone->SetLineStyle(9);
    lone->Draw();

    if(icent==0)
    {
      leg_ff_pbpbsub2[icent] = new TLegend(0.03,0.697,0.3,0.92);
    }
    else
    {
      leg_ff_pbpbsub2[icent] = new TLegend(0,0.697,0.27,0.92);
    }
    leg_ff_pbpbsub2[icent]->SetTextSize(0.05*1.3);
    leg_ff_pbpbsub2[icent]->SetFillColor(0);
    leg_ff_pbpbsub2[icent]->SetFillStyle(0);
    leg_ff_pbpbsub2[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"gen(jet,trk)/reco(jet,trk) ff","p");
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"","");
    }
    else if(icent==1)
    {
      // leg_ff_pbpbsub2[icent]->AddEntry(clone_hgammaffxi_pbpbmc_[icent],"#eta cone sub","");
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"100>#gamma p_{T}>300 GeV","");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"p_{T}^{jet} > 40 GeV","");
    }
    else
    {
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"","");
      leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],"","");
    }
    leg_ff_pbpbsub2[icent]->AddEntry(clone2_hgammaffxi_pbpbmc_gen_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub2[icent]->Draw();

  }
  callratio->cd(1);

  TH2D * axis_dummy_ratio = new TH2D("axis_dummy_ratio","",1,0.01,4.99,1,0,yaxismax2);
  gStyle->SetFrameLineColor(0);
  axis_dummy_ratio->UseCurrentStyle();
  axis_dummy_ratio->Draw("FB BB A");

  TLatex * ldndxi2 = new TLatex(0.4,0.4,"dN/d#xi Gen/Reco");
  ldndxi2->SetTextSize(ldndxi2->GetTextSize()*1.2);
  ldndxi2->SetNDC();
  ldndxi2->SetTextAngle(90);

  TLatex * laxis2[yaxismax2];
  for (int ilatex = 0; ilatex < yaxismax2; ilatex++) {
    laxis2[ilatex] = new TLatex(3.,ilatex-0.1,Form("%d",ilatex));
    laxis2[ilatex]->SetTextSize(laxis2[ilatex]->GetTextSize()*1.2);
    laxis2[ilatex]->Draw();
  }
  ldndxi2->Draw();


}
