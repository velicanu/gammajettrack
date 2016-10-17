#include "makeMultiPanelCanvas.C"

void dataff2step(int phoetmin, int phoetmax, int jetptmin = 30) {
  TFile *_file0 = TFile::Open(Form("all_%d_%d_%d.root",phoetmin,phoetmax,jetptmin));
  const static int ncentbins = 4;
  const int yaxismax = 8;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-70%","70-100%"};
  TH1D * rawff_pbpbdata_reco[ncentbins];
  TH1D * rawffjetmix_pbpbdata_reco[ncentbins];
  TH1D * hjetpt_pbpbdata_reco[ncentbins];
  TH1D * hjetptjetmix_pbpbdata_reco[ncentbins];
  TH1D * hnmixsignal_pbpbdata_reco[ncentbins];
  TH1D * hgammaffxiuemix_pbpbdata_reco[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

  TCanvas * call = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {
    call->cd(2+icent);
    dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetYaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy_pbpbsub[icent]->Draw();
    rawff_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    // rawff_pbpbdata_reco[icent]->Draw("same");
    rawffjetmix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    // rawffjetmix_pbpbdata_reco[icent]->SetMarkerColor(kBlue);
    // rawffjetmix_pbpbdata_reco[icent]->Draw("same");
    rawffjetmix_pbpbdata_reco[icent]->Scale(-1);
    rawff_pbpbdata_reco[icent]->Add(rawffjetmix_pbpbdata_reco[icent]);
    hjetpt_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetpt_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hnmixsignal_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hnmixsignal_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    float nrawjets = hjetpt_pbpbdata_reco[icent]->Integral();
    float nmixjets = hjetptjetmix_pbpbdata_reco[icent]->Integral();
    float nmixtot = hnmixsignal_pbpbdata_reco[icent]->Integral();
    float avgnmix = nmixtot/nmixjets;
    float denominator = nrawjets - nmixjets/avgnmix;
    rawff_pbpbdata_reco[icent]->Scale(1.0/denominator);
    rawff_pbpbdata_reco[icent]->Draw("same");

    hgammaffxiuemix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxiuemix_pbpbdata_reco[icent]->Scale(1/nrawjets);
    hgammaffxiuemix_pbpbdata_reco[icent]->SetMarkerColor(kRed);
    hgammaffxiuemix_pbpbdata_reco[icent]->Draw("same");

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
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"Raw FF - Jet Mix FF","p");
      leg_ff_pbpbsub[icent]->AddEntry(hgammaffxiuemix_pbpbdata_reco[icent],"UE Mix FF","p");
    }
    else if(icent==1)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"Pythia+Hydjet","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
  }

  call->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi 1/nJet");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  int labelspace = yaxismax / 4;
  const int nlabels = yaxismax/labelspace;
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    laxis[ilatex] = new TLatex(2.,ilatex*labelspace-0.1,Form("%d",ilatex*labelspace));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
    laxis[ilatex]->Draw();
  }
  ldndxi->Draw();
  call->SaveAs(Form("rawminusjetff_%d_%d_uemixff_jetpt%d_pbpbdata_reco.png",phoetmin,phoetmax,jetptmin));
}
