#include "makeMultiPanelCanvas.C"
// histogram.photon.bins_pt_gt = {40, 60, 40, 50, 60, 80, 80, 100};
// histogram.photon.bins_pt_lt = {9999, 9999, 50, 60, 80, 9999, 100, 9999};
// histogram.event.bins_hiBin_gt = {0,   0,  60, 0, 20, 60, 100}   # the current centrality bin is greater or equal to these centrality bins
// histogram.event.bins_hiBin_lt = {200, 60, 200, 20, 60, 100, 200}  # the current centrality bin is less than these centrality bins
float allpuritypbpb[] = {0.725758, 0.720249, 0.753094, 0.703853, 0.730487, 0.756007, 0.741809, 0.737945, 0.725995, 0.786819, 0.704426, 0.743147, 0.775786, 0.827101, 0.715906, 0.710863, 0.739059, 0.687001, 0.719965, 0.743805, 0.720358, 0.724734, 0.719121, 0.758637, 0.699659, 0.73539, 0.76691, 0.731031, 0.730948, 0.717619, 0.786722, 0.695959, 0.733827, 0.771255, 0.836782, 0.749695, 0.739283, 0.788322, 0.711966, 0.763817, 0.786493, 0.816522, 0.733207, 0.719114, 0.785248, 0.705784, 0.734519, 0.769831, 0.84767, 0.772594, 0.766181, 0.802428, 0.720997, 0.80606, 0.822834, 0.774406};
float allpuritypp[] = {0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244};

float getpurity(float phoetmin, float hibinmin, bool ispp)
{
  int row = -1;
  int col = -1;
  if(phoetmin==40)  row = 0;
  if(phoetmin==60)  row = 1;
  if(phoetmin==100) row = 7;
  if(hibinmin==0)   col = 3;
  if(hibinmin==20)  col = 4;
  if(hibinmin==60)  col = 5;
  if(hibinmin==100) col = 6;
  if(row>-1 && col > -1 && ispp) return allpuritypp[row*7+col];
  if(row>-1 && col > -1 && !ispp) return allpuritypbpb[row*7+col];
  return 1; //no purity applied
}

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
  TH1D * hgammaffxi_refcone_pbpbdata_[ncentbins];
  TH1D * hgammaffxisideband_pbpbdata_[ncentbins];
  TH1D * hgammaffxisideband_refcone_pbpbdata_[ncentbins];
  TH1D * hjetpt_pbpbdata_[ncentbins];
  float njets_pbpbdata[ncentbins];
  TH1D * hjetptsideband_pbpbdata_[ncentbins];
  float njetssideband_pbpbdata[ncentbins];
  TLegend * leg_ff_pbpbdata[ncentbins];

  TCanvas * c1_ppdata[ncentbins];
  TH1D * hgammaffxi_ppdata_[ncentbins];
  TH1D * hjetpt_ppdata_[ncentbins];
  TH1D * hgammaffxi_refcone_ppdata_[ncentbins];
  TH1D * hgammaffxi_ppdata__[ncentbins];
  TH1D * hjetpt_ppdata__[ncentbins];
  TH1D * hgammaffxi_refcone_ppdata__[ncentbins];
  float njets_ppdata[ncentbins];
  TH1D * hgammaffxisideband_ppdata_[ncentbins];
  TH1D * hjetptsideband_ppdata_[ncentbins];
  TH1D * hgammaffxisideband_refcone_ppdata_[ncentbins];
  TH1D * hgammaffxisideband_ppdata__[ncentbins];
  TH1D * hjetptsideband_ppdata__[ncentbins];
  TH1D * hgammaffxisideband_refcone_ppdata__[ncentbins];
  float njetssideband_ppdata[ncentbins];
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
  
  TH1D * clone2_hgammaffxi_pbpbdata_[ncentbins];
  TH1D * clone2_hgammaffxi_ppdata_[ncentbins];
  
  TH1D * clone_hgammaffxisideband_refcone_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxisideband_pbpbdata_[ncentbins];
  TH1D * clone_hgammaffxisideband_refcone_ppdata_[ncentbins];
  TH1D * clone_hgammaffxisideband_ppdata_[ncentbins];
  TH1D * clone_hgammaffxisideband_refcone_pbpbdata_ppsub_[ncentbins];
  TH1D * clone_hgammaffxisideband_ppdata_ppsub_[ncentbins];

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
    
    hgammaffxisideband_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hgammaffxisideband_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    hjetptsideband_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hjetptsideband_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxisideband_refcone_pbpbdata_[icent] = (TH1D*) _file0->Get(Form("hgammaffxisideband_refcone_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    njetssideband_pbpbdata[icent] = hjetptsideband_pbpbdata_[icent]->Integral();
    hgammaffxisideband_pbpbdata_[icent]->Sumw2();
    hgammaffxisideband_refcone_pbpbdata_[icent]->Sumw2();
    hgammaffxisideband_pbpbdata_[icent]->Scale(1.0/njetssideband_pbpbdata[icent]/binwidth);
    hgammaffxisideband_refcone_pbpbdata_[icent]->Scale(1.0/njetssideband_pbpbdata[icent]/binwidth);
    hgammaffxisideband_pbpbdata_[icent]->GetXaxis()->CenterTitle();
    hgammaffxisideband_pbpbdata_[icent]->SetYTitle("dN/d#xi");
    hgammaffxisideband_pbpbdata_[icent]->GetYaxis()->CenterTitle();
    // hgammaffxisideband_pbpbdata_[icent]->Draw();

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

    hgammaffxisideband_ppdata__[icent] = (TH1D*) _file0->Get(Form("hgammaffxisideband_ppdata__1_200"));
    hjetptsideband_ppdata__[icent] = (TH1D*) _file0->Get(Form("hjetptsideband_ppdata__1_200"));
    hgammaffxisideband_refcone_ppdata__[icent] = (TH1D*) _file0->Get(Form("hgammaffxisideband_refcone_ppdata__1_200"));

    hgammaffxisideband_ppdata_[icent] = (TH1D*) hgammaffxisideband_ppdata__[icent]->Clone(Form("hgammaffxisideband_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    hjetptsideband_ppdata_[icent] = (TH1D*) hjetpt_ppdata__[icent]->Clone(Form("hjetptsideband_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxisideband_refcone_ppdata_[icent] = (TH1D*) hgammaffxisideband_refcone_ppdata__[icent]->Clone(Form("hgammaffxisideband_refcone_ppdata__%d_%d",centmins[icent],centmaxs[icent]));

    njetssideband_ppdata[icent] = hjetptsideband_ppdata_[icent]->Integral();
    hgammaffxisideband_ppdata_[icent]->Sumw2();
    hgammaffxisideband_refcone_ppdata_[icent]->Sumw2();
    hgammaffxisideband_ppdata_[icent]->Scale(1.0/njetssideband_ppdata[icent]/binwidth);
    hgammaffxisideband_refcone_ppdata_[icent]->Scale(1.0/njetssideband_ppdata[icent]/binwidth);
    hgammaffxisideband_ppdata_[icent]->GetXaxis()->CenterTitle();
    hgammaffxisideband_ppdata_[icent]->SetYTitle("dN/d#xi");
    hgammaffxisideband_ppdata_[icent]->GetYaxis()->CenterTitle();
    // hgammaffxisideband_ppdata_[icent]->Draw();

    hgammaffxisideband_refcone_ppdata_[icent]->SetMarkerStyle(24);
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
    dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0.01,10*yaxismax);
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
    
    clone_hgammaffxisideband_refcone_pbpbdata_[icent] = (TH1D*) hgammaffxisideband_refcone_pbpbdata_[icent]->Clone(Form("clone_hgammaffxisideband_refcone_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxisideband_refcone_pbpbdata_[icent]->Scale(-1);
    clone_hgammaffxisideband_pbpbdata_[icent] = (TH1D*) hgammaffxisideband_pbpbdata_[icent]->Clone(Form("clone_hgammaffxisideband_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxisideband_pbpbdata_[icent]->Add(clone_hgammaffxisideband_refcone_pbpbdata_[icent]);

    clone_hgammaffxisideband_refcone_ppdata_[icent] = (TH1D*) hgammaffxisideband_refcone_ppdata_[icent]->Clone(Form("clone_hgammaffxisideband_refcone_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxisideband_refcone_ppdata_[icent]->Scale(-1);
    clone_hgammaffxisideband_ppdata_[icent] = (TH1D*) hgammaffxisideband_ppdata_[icent]->Clone(Form("clone_hgammaffxisideband_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone_hgammaffxisideband_ppdata_[icent]->Add(clone_hgammaffxisideband_refcone_ppdata_[icent]);

    
    float purity   = getpurity(phoetmin,centmins[icent],false);
    float pppurity = getpurity(phoetmin,centmins[icent],true);
    clone2_hgammaffxi_pbpbdata_[icent] = (TH1D*) clone_hgammaffxi_pbpbdata_[icent]->Clone(Form("clone2_hgammaffxi_pbpbdata__%d_%d",centmins[icent],centmaxs[icent]));
    clone2_hgammaffxi_ppdata_[icent] = (TH1D*) clone_hgammaffxi_ppdata_[icent]->Clone(Form("clone2_hgammaffxi_ppdata__%d_%d",centmins[icent],centmaxs[icent]));
    
    clone_hgammaffxisideband_pbpbdata_[icent]->Scale((1.0-purity)/purity);
    clone_hgammaffxisideband_ppdata_[icent]->Scale((1.0-pppurity)/pppurity);
    clone_hgammaffxisideband_pbpbdata_[icent]->Scale(-1);
    clone_hgammaffxisideband_ppdata_[icent]->Scale(-1);
    
    // top doesnt use sideband in ppsub bottom uses
    // clone2_hgammaffxi_pbpbdata_[icent]->Scale(1.0/purity);
    // clone2_hgammaffxi_ppdata_[icent]->Scale(1.0/pppurity);
    // clone2_hgammaffxi_pbpbdata_[icent]->Add(clone_hgammaffxisideband_pbpbdata_[icent]);
    // clone2_hgammaffxi_ppdata_[icent]->Add(clone_hgammaffxisideband_ppdata_[icent]);
    clone_hgammaffxi_pbpbdata_[icent]->Scale(1.0/purity);
    clone_hgammaffxi_ppdata_[icent]->Scale(1.0/pppurity);
    clone_hgammaffxi_pbpbdata_[icent]->Add(clone_hgammaffxisideband_pbpbdata_[icent]);
    clone_hgammaffxi_ppdata_[icent]->Add(clone_hgammaffxisideband_ppdata_[icent]);
    
    
    
    // clone_hgammaffxi_ppdata_[icent]->SetMarkerColor(kRed);
    clone_hgammaffxisideband_ppdata_[icent]->SetMarkerStyle(24);
    clone_hgammaffxisideband_ppdata_[icent]->SetMarkerColor(kRed);
    clone_hgammaffxisideband_pbpbdata_[icent]->SetMarkerColor(kRed);
    clone2_hgammaffxi_ppdata_[icent]->SetMarkerStyle(24);
    clone_hgammaffxi_ppdata_[icent]->SetMarkerStyle(24);
    // fixedFontHist(dummy_pbpbsub[icent]);
    dummy_pbpbsub[icent]->Draw();
    // hgammaffxi_ppdata_[icent]->Draw("same");
    // hgammaffxi_refcone_ppdata_[icent]->Draw("same");

    // clone2_hgammaffxi_pbpbdata_[icent]->Draw("same");
    // clone_hgammaffxisideband_pbpbdata_[icent]->Draw("same");
    
    // clone_hgammaffxisideband_ppdata_[icent]->Draw("same");
    // clone2_hgammaffxi_ppdata_[icent]->Draw("same");

    
    // sideband subtracted
    // clone2_hgammaffxi_pbpbdata_[icent]->SetMarkerColor(kBlue);
    // clone2_hgammaffxi_pbpbdata_[icent]->Draw("same");
    // clone2_hgammaffxi_ppdata_[icent]->SetMarkerColor(kBlue);
    // clone2_hgammaffxi_ppdata_[icent]->Draw("same");

    // no sideband subtraction
    clone_hgammaffxi_pbpbdata_[icent]->Draw("same");
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
    gPad->SetLogy();

  }
  call->cd(1);
  gPad->SetLogy();

  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0.01,10*yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.3);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  
  TLatex * laxis[yaxismax];
  string powers[] = {"0.1"," 1","10"};
  float values[] = {0.1*0.9,1*0.9,10*0.9};
  for (int ilatex = 0; ilatex < 3; ilatex++) {
    if(ilatex==1)
      laxis[ilatex] = new TLatex(2.,values[ilatex],Form("%s",powers[ilatex].data()));
    else
      laxis[ilatex] = new TLatex(1.,values[ilatex],Form("%s",powers[ilatex].data()));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.3);
    laxis[ilatex]->Draw();
  }
  ldndxi->Draw();
  // call->SaveAs(Form("centffgamma-pbpbpp-phoet_%d_%d.pdf",phoetmin,phoetmax));
  call->SaveAs(Form("sideband_centffgamma-pbpbpp-phoet_%d_%d.png",phoetmin,phoetmax));

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
    // clone_hgammaffxi_refcone_pbpbdata_ppsub_[icent]->SetMarkerStyle(24);
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
    call_ppsub->SaveAs(Form("sideband-centffgamma-pbpb-minus-pp-phoet_%d_%d.png",phoetmin,phoetmax));
  } else {
    call_ppsub->SaveAs(Form("centffgamma-pbpb-ratio-pp-phoet_%d_%d.pdf",phoetmin,phoetmax));
    call_ppsub->SaveAs(Form("centffgamma-pbpb-ratio-pp-phoet_%d_%d.png",phoetmin,phoetmax));
  }
  // gROOT->ProcessLine(".q");
}
