#include "makeMultiPanelCanvas.C"

void drawpbpbppffgamma(int phoetmin, int phoetmax, int sub = 1) {
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
  TCanvas * c1_pbpbdata[ncentbins]; // ncentbins
  TH1D * hgammaffxi_pbpbdata_[ncentbins];
  TH1D * hjetpt_pbpbdata_[ncentbins];
  TH1D * hgammaffxi_refcone_pbpbdata_[ncentbins];
  float njets_pbpbdata[ncentbins];
  TLegend * leg_ff_pbpbdata[ncentbins];

  TCanvas * c1_ppdata[ncentbins];
  TH1D * hgammaffxi_ppdata_[ncentbins];
  TH1D * hjetpt_ppdata_[ncentbins];
  TH1D * hgammaffxi_refcone_ppdata_[ncentbins];
  TH1D * hgammaffxi_ppdata__[ncentbins];
  TH1D * hjetpt_ppdata__[ncentbins];
  TH1D * hgammaffxi_refcone_ppdata__[ncentbins];
  float njets_ppdata[ncentbins];
  TLegend * leg_ff_ppdata[ncentbins];

  TCanvas * c1_subpbpb[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TH2D * dummy_pbpbsub_ppsub[ncentbins];
  TH1D * clone_hgammaffxi_refcone_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxi_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxi_refcone_ppdata_[ncentbins];
  TH1D * clone_hgammaffxi_ppdata_[ncentbins];

  TH1D * clone_hgammaffxi_refcone_pbpbdata_ppsub_[ncentbins];
  TH1D * clone_hgammaffxi_ppdata_ppsub_[ncentbins];

  TLegend * leg_ff_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub_ppsub[ncentbins];

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
    leg_ff_pbpbdata[icent]->AddEntry(hgammaffxi_refcone_pbpbdata_[icent],Form("%d<#gamma p_{T}<%d GeV",phoetmin,phoetmax),"");
    // leg_ff_pbpbdata[icent]->Draw();
    // c1_pbpbdata[icent]->SaveAs("pbpbdata_unsubffspectrum_45_gamma_100.png");

    // Raw FF pbpdata


    // Raw FF pbmc
    // c1_ppdata[icent] = new TCanvas(Form("c1_ppdata_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_ppdata__[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_ppdata__1_200"));
    hjetpt_ppdata__[icent] = (TH1D*) _file0->Get(Form("hjetpt_ppdata__1_200"));
    hgammaffxi_refcone_ppdata__[icent] = (TH1D*) _file0->Get(Form("hgammaffxi_refcone_ppdata__1_200"));

    hgammaffxi_ppdata_[icent] = (TH1D*) hgammaffxi_ppdata__[icent]->Clone(Form("hgammaffxi_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    hjetpt_ppdata_[icent] = (TH1D*) hjetpt_ppdata__[icent]->Clone(Form("hjetpt_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxi_refcone_ppdata_[icent] = (TH1D*) hgammaffxi_refcone_ppdata__[icent]->Clone(Form("hgammaffxi_refcone_ppdata__%d_%d",centmins[icent],centmaxs[icent]));

    njets_ppdata[icent] = hjetpt_ppdata_[icent]->Integral();
    hgammaffxi_ppdata_[icent]->Sumw2();
    hgammaffxi_refcone_ppdata_[icent]->Sumw2();
    hgammaffxi_ppdata_[icent]->Scale(1.0/njets_ppdata[icent]/binwidth);
    hgammaffxi_refcone_ppdata_[icent]->Scale(1.0/njets_ppdata[icent]/binwidth);
    hgammaffxi_ppdata_[icent]->GetXaxis()->CenterTitle();
    hgammaffxi_ppdata_[icent]->SetYTitle("dN/d#xi");
    hgammaffxi_ppdata_[icent]->GetYaxis()->CenterTitle();
    // hgammaffxi_ppdata_[icent]->Draw();

    hgammaffxi_refcone_ppdata_[icent]->SetMarkerStyle(24);
    // hgammaffxi_refcone_pclone_hgammaffxi_refcone_pbpbdata_bpbmc_[icent]->Draw("same");

    leg_ff_ppdata[icent] = new TLegend(0.22,0.59,0.49,0.92);
    leg_ff_ppdata[icent]->SetFillColor(0);
    leg_ff_ppdata[icent]->SetTextSize(0.05);
    leg_ff_ppdata[icent]->SetFillStyle(0);
    leg_ff_ppdata[icent]->SetTextFont(42);
    leg_ff_ppdata[icent]->AddEntry(hgammaffxi_ppdata_[icent],"raw frag. func","p");
    leg_ff_ppdata[icent]->AddEntry(hgammaffxi_refcone_ppdata_[icent],"#eta reflected cone","p");
    leg_ff_ppdata[icent]->AddEntry(hgammaffxi_refcone_ppdata_[icent],"pp #sqrt{s}=5 TeV","");
    leg_ff_ppdata[icent]->AddEntry(hgammaffxi_refcone_ppdata_[icent],"trk p_{T}>1 GeV","");
    leg_ff_ppdata[icent]->AddEntry(hgammaffxi_refcone_ppdata_[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    // leg_ff_ppdata[icent]->Draw();
    // c1_ppdata[icent]->SaveAs("pbpbmc_unsubffspectrum_45_gamma_100.png");
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

    clone_hgammaffxi_refcone_ppdata_[icent] = (TH1D*) hgammaffxi_refcone_ppdata_[icent]->Clone(Form("clone_hgammaffxi_refcone_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_refcone_ppdata_[icent]->Scale(-1);
    clone_hgammaffxi_ppdata_[icent] = (TH1D*) hgammaffxi_ppdata_[icent]->Clone(Form("clone_hgammaffxi_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_ppdata_[icent]->Add(clone_hgammaffxi_refcone_ppdata_[icent]);
    // clone_hgammaffxi_ppdata_[icent]->SetMarkerColor(kRed);
    clone_hgammaffxi_ppdata_[icent]->SetMarkerStyle(24);
    // fixedFontHist(dummy_pbpbsub[icent]);
    dummy_pbpbsub[icent]->Draw();
    clone_hgammaffxi_pbpbdata_[icent]->Draw("same");
    // hgammaffxi_ppdata_[icent]->Draw("same");
    // hgammaffxi_refcone_ppdata_[icent]->Draw("same");
    clone_hgammaffxi_ppdata_[icent]->Draw("same");
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
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"pp #sqrt{s}=5 TeV","p");
    }
    else if(icent==1)
    {
      // leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"#eta cone sub","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],Form("%d<#gamma p_{T}<%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"p_{T}^{jet} > 40 GeV","");
    }
    else
    {
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"","");
      leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
    // c1_subpbpb[icent]->SaveAs("pbpbdata_ppdata_etaconesubtracted_45_gamma_100.png");
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
  call->SaveAs(Form("centffgamma-pbpbpp-phoet_%d_%d.pdf",phoetmin,phoetmax));
  call->SaveAs(Form("centffgamma-pbpbpp-phoet_%d_%d.png",phoetmin,phoetmax));

  if(sub!=1)
  {
    yaxissubmin = yaxissubmin+1;
    yaxissubmax = yaxissubmax+1;
  }

  TCanvas * call_ppsub = new TCanvas("call_ppsub","",1400,500);
  makeMultiPanelCanvas(call_ppsub,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);
  for (int icent = 0; icent < ncentbins; icent++) {
    call_ppsub->cd(icent+2);
    dummy_pbpbsub_ppsub[icent] = new TH2D(Form("dummy_pbpbsub_ppsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,yaxissubmin,yaxissubmax);
    dummy_pbpbsub_ppsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub_ppsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub_ppsub[icent]->GetYaxis()->CenterTitle();
    dummy_pbpbsub_ppsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub_ppsub[icent]->GetXaxis()->GetTitleSize()*1.5);

    clone_hgammaffxi_refcone_pbpbdata_ppsub_[icent] = (TH1D*) clone_hgammaffxi_pbpbdata_[icent]->Clone(Form("clone_hgammaffxi_refcone_ppsub_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxi_ppdata_ppsub_[icent] = (TH1D*) clone_hgammaffxi_ppdata_[icent]->Clone(Form("clone_hgammaffxi_pbpbdata_ppsub__%d_%d",centmins[icent],centmaxs[icent]));
    if(sub==1)
    {
      clone_hgammaffxi_ppdata_ppsub_[icent]->Scale(-1);
      clone_hgammaffxi_refcone_pbpbdata_ppsub_[icent]->Add(clone_hgammaffxi_ppdata_ppsub_[icent]);
    } else {
      clone_hgammaffxi_refcone_pbpbdata_ppsub_[icent]->Divide(clone_hgammaffxi_ppdata_ppsub_[icent]);
    }

    dummy_pbpbsub_ppsub[icent]->Draw();
    clone_hgammaffxi_refcone_pbpbdata_ppsub_[icent]->Draw("same");

    TLine * lzero = new TLine(0,0,4.99,0);
    lzero->SetLineStyle(9);
    TLine * lone = new TLine(0,1,4.99,1);
    lone->SetLineStyle(9);
    if(sub==1)
    {
      lzero->Draw();
    } else {
      lone->Draw();
    }

    if(icent==0)
    {
      // leg_ff_pbpbsub[icent] = new TLegend(0.25,0.697,0.875,0.92);
      leg_ff_pbpbsub_ppsub[icent] = new TLegend(0.05,0.697,0.27,0.92);
      leg_ff_pbpbsub_ppsub[icent]->SetTextSize(0.05*1.3);
    }
    else
    {
      leg_ff_pbpbsub_ppsub[icent] = new TLegend(0,0.697,0.27,0.92);
      leg_ff_pbpbsub_ppsub[icent]->SetTextSize(0.05*1.3);
    }
    leg_ff_pbpbsub_ppsub[icent]->SetFillColor(0);
    leg_ff_pbpbsub_ppsub[icent]->SetFillStyle(0);
    leg_ff_pbpbsub_ppsub[icent]->SetTextFont(42);
    if(icent==0)
    {
      if(sub==1)    leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_pbpbdata_[icent],"PbPb-pp #sqrt{s_{NN}}=5 TeV","p");
      else          leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_pbpbdata_[icent],"PbPb/pp #sqrt{s_{NN}}=5 TeV","p");
      // leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"pp #sqrt{s}=5 TeV","p");
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"","");
    }
    else if(icent==1)
    {
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],Form("%d<#gamma p_{T}<%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"p_{T}^{jet} > 40 GeV","");
    }
    else
    {
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"","");
      leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],"","");
    }
    leg_ff_pbpbsub_ppsub[icent]->AddEntry(clone_hgammaffxi_ppdata_[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub_ppsub[icent]->Draw();
    // c1_subpbpb[icent]->SaveAs("pbpbdata_ppdata_etaconesubtracted_45_gamma_100.png");
    // Eta cone subtracted FF pbpbdata and pbpbmc

  /*
  */
  }
  call_ppsub->cd(1);


  TH2D *     axis_dummy_ppsub = new TH2D("axis_dummy_ppsub","",1,0.01,4.99,1,yaxissubmin,yaxissubmax);
  gStyle->SetFrameLineColor(0);
  axis_dummy_ppsub->UseCurrentStyle();
  axis_dummy_ppsub->Draw("FB BB A");

  TLatex * ldndxi_ppsub;
  if(sub==1)    ldndxi_ppsub = new TLatex(0.4,0.4,"dN/d#xi PbPb-pp");
  else          ldndxi_ppsub = new TLatex(0.4,0.4,"dN/d#xi PbPb/pp");
  ldndxi_ppsub->SetTextSize(ldndxi_ppsub->GetTextSize()*1.3);
  ldndxi_ppsub->SetNDC();
  ldndxi_ppsub->SetTextAngle(90);

  const int nbinssub = yaxissubmax-yaxissubmin+1;
  TLatex * laxis_ppsub[nbinssub];
  for (int ilatex = yaxissubmin; ilatex <= yaxissubmax; ilatex++) {
    laxis_ppsub[ilatex-yaxissubmin] = new TLatex(3.,ilatex-0.1,Form("%d",ilatex));
    laxis_ppsub[ilatex-yaxissubmin]->SetTextSize(laxis_ppsub[ilatex-yaxissubmin]->GetTextSize()*1.3);
    laxis_ppsub[ilatex-yaxissubmin]->Draw();
  }
  ldndxi_ppsub->Draw();
  if(sub==1)
  {
    call_ppsub->SaveAs(Form("centffgamma-pbpb-minus-pp-phoet_%d_%d.pdf",phoetmin,phoetmax));
    call_ppsub->SaveAs(Form("centffgamma-pbpb-minus-pp-phoet_%d_%d.png",phoetmin,phoetmax));
  } else {
    call_ppsub->SaveAs(Form("centffgamma-pbpb-ratio-pp-phoet_%d_%d.pdf",phoetmin,phoetmax));
    call_ppsub->SaveAs(Form("centffgamma-pbpb-ratio-pp-phoet_%d_%d.png",phoetmin,phoetmax));
  }
  gROOT->ProcessLine(".q");
}
