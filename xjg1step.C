#include "makeMultiPanelCanvas.C"


void xjg1step(int phoetmin, int phoetmax, int jetptmin)
{
  TFile * _file0 = TFile::Open(Form("all_%d_%d_%d.root",phoetmin,phoetmax,jetptmin));

  const static int nCentBins = 4;

  float yaxismax = 4;

  TH1D * xjgsignal_pbpbdata_reco[nCentBins];
  TH1D * xjgmixsignal_pbpbdata_reco[nCentBins];
  TH1D * phoetsignal_pbpbdata_reco[nCentBins];
  TH1D * xjgsideband_pbpbdata_reco[nCentBins];
  TH1D * xjgmixsideband_pbpbdata_reco[nCentBins];
  TH1D * phoetsideband_pbpbdata_reco[nCentBins];


  TH2D * dummy[nCentBins];
  TLegend * leg[nCentBins];

  int centmins[] = {0,20,60,100};
  int centmaxs[] = {20,60,100,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%"};



  TCanvas * c1 = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(c1,5,1,0.02,0.0,-6,0.2,0.04);


  for (size_t icent = 0; icent < nCentBins; icent++) {
    c1->cd(2+icent);
    xjgsignal_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("xjgsignal_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgmixsignal_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("xjgmixsignal_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    phoetsignal_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("phoetsignal_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgsideband_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("xjgsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgmixsideband_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("xjgmixsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    phoetsideband_pbpbdata_reco[icent] = (TH1D*) _file0->Get(Form("phoetsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));


    float nphosignal = phoetsignal_pbpbdata_reco[icent]->Integral();
    float nphosideband = phoetsideband_pbpbdata_reco[icent]->Integral();
    float binwidth = xjgsignal_pbpbdata_reco[icent]->GetBinWidth(1);

    dummy[icent] = new TH2D(Form("dummy_%d_%d",centmins[icent],centmaxs[icent]),";x_{J#gamma};1/N#gamma dN/dx_{J#gamma}",1,0.01,1.99,1,0,yaxismax);
    dummy[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy[icent]->GetXaxis()->CenterTitle();
    dummy[icent]->GetYaxis()->CenterTitle();
    dummy[icent]->GetXaxis()->SetTitleSize(dummy[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy[icent]->Draw();

    xjgsignal_pbpbdata_reco[icent]->Scale(1/binwidth/nphosignal);
    xjgmixsignal_pbpbdata_reco[icent]->Scale(1/binwidth/nphosignal);
    xjgsignal_pbpbdata_reco[icent]->Draw("same");
    xjgmixsignal_pbpbdata_reco[icent]->SetMarkerColor(kBlue);
    xjgmixsignal_pbpbdata_reco[icent]->Draw("same");

    if(icent==0)
    {
      leg[icent] = new TLegend(0.63,0.697,0.9,0.92);
    }
    else
    {
      leg[icent] = new TLegend(0,0.697,0.27,0.92);
    }
    leg[icent]->SetTextSize(0.05*1.3);
    leg[icent]->SetFillColor(0);
    leg[icent]->SetFillStyle(0);
    leg[icent]->SetTextFont(42);
    if(icent==0)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],"Raw x_{J#gamma}","p");
      leg[icent]->AddEntry(xjgmixsignal_pbpbdata_reco[icent],"Mix x_{J#gamma}","p");
    }
    else if(icent==1)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],"","");
    }
    else if(icent==2)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],"|#eta^{jet}| < 1.6","");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],"PbPb #sqrt{s_{NN}}=5 TeV","");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg[icent]->AddEntry(xjgsignal_pbpbdata_reco[icent],Form("%s",cents[icent].data()),"");

    leg[icent]->Draw();
  }

  c1->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,1.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.37,"1/N#gamma dN/dx_{J#gamma} Raw");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);
  ldndxi->Draw();

  // float labelspace = yaxismax / 4.0;
  const int nlabels = 5;
  float fylabels[] = {0,1,2,3,4};
  string sylabels[] = {"0","1","2","3","4"};
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    laxis[ilatex] = new TLatex(.8,fylabels[ilatex]-0.001,Form("%s",sylabels[ilatex].data()));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.15);
    laxis[ilatex]->Draw();
  }

  c1->SaveAs("xjg_step1_rawmix.png");
}
