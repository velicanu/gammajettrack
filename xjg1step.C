#include "makeMultiPanelCanvas.C"

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

void xjg1step(int phoetmin, int phoetmax, int jetptmin)
{
  TFile * _file0 = TFile::Open(Form("all_%d_%d_%d.root",phoetmin,phoetmax,jetptmin));
  TFile * _fran = TFile::Open("/home/ursu/PbPb_Data_gammaJetHistogramArithmetic.root");

  const static int nCentBins = 4;

  float yaxismax = 2;

  TH1D * xjgsignal_pbpbdata_recoreco[nCentBins];
  TH1D * xjgmixsignal_pbpbdata_recoreco[nCentBins];
  TH1D * phoetsignal_pbpbdata_recoreco[nCentBins];
  TH1D * xjgsideband_pbpbdata_recoreco[nCentBins];
  TH1D * xjgmixsideband_pbpbdata_recoreco[nCentBins];
  TH1D * phoetsideband_pbpbdata_recoreco[nCentBins];

  TH1D * h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[nCentBins];

  TH2D * dummy[nCentBins];
  TLegend * leg[nCentBins];

  int centmins[] = {0,20,60,100};
  int centmaxs[] = {20,60,100,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%"};



  TCanvas * c1 = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(c1,5,1,0.02,0.0,-6,0.2,0.04);


  for (int icent = 0; icent < nCentBins; icent++) {
    c1->cd(2+icent);
    xjgsignal_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("xjgsignal_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgmixsignal_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("xjgmixsignal_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    phoetsignal_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("phoetsignal_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgsideband_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("xjgsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    xjgmixsideband_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("xjgmixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    phoetsideband_pbpbdata_recoreco[icent] = (TH1D*) _file0->Get(Form("phoetsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent] = (TH1D*) _fran->Get(Form("HI/h1D_xjg_ptBin1_hiBin%d_phoRAW_jetRAW_final_norm",icent+3));

    xjgsignal_pbpbdata_recoreco[icent]->Sumw2();
    xjgmixsignal_pbpbdata_recoreco[icent]->Sumw2();
    xjgsideband_pbpbdata_recoreco[icent]->Sumw2();
    xjgmixsideband_pbpbdata_recoreco[icent]->Sumw2();

    float nphosignal = phoetsignal_pbpbdata_recoreco[icent]->Integral();
    float nphosideband = phoetsideband_pbpbdata_recoreco[icent]->Integral();
    float binwidth = xjgsignal_pbpbdata_recoreco[icent]->GetBinWidth(1);

    dummy[icent] = new TH2D(Form("dummy_%d_%d",centmins[icent],centmaxs[icent]),";x_{J#gamma};1/N#gamma dN/dx_{J#gamma}",1,0.01,1.99,1,0,yaxismax);
    dummy[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy[icent]->GetXaxis()->CenterTitle();
    dummy[icent]->GetYaxis()->CenterTitle();
    dummy[icent]->GetXaxis()->SetTitleSize(dummy[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy[icent]->Draw();

    xjgsignal_pbpbdata_recoreco[icent]->Scale(1.0/(binwidth*nphosignal));
    xjgmixsignal_pbpbdata_recoreco[icent]->Scale(1.0/(binwidth*nphosignal));
    // xjgmixsignal_pbpbdata_recoreco[icent]->Draw("same");
    h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent]->SetMarkerStyle(24);
    h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent]->SetMarkerColor(kRed);
    xjgsignal_pbpbdata_recoreco[icent]->Divide(h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent]);
    xjgsignal_pbpbdata_recoreco[icent]->Draw("same");
    // h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent]->Draw("same");

    if(icent==0)
    {
      leg[icent] = new TLegend(0.03,0.697,0.3,0.92);
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
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],"PbPb #sqrt{s_{NN}}=5 TeV","p");
      leg[icent]->AddEntry(h1D_xjg_ptBin1_hiBin_phoSIG_jetSIG_final_norm[icent],"HIN-16-002","p");
    }
    else if(icent==1)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],"#sigma_{I#eta#eta}<0.1","");
    }
    else if(icent==2)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],"|#eta^{jet}| < 1.6","");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],"","");
      leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],"","");
    }
    leg[icent]->AddEntry(xjgsignal_pbpbdata_recoreco[icent],Form("%s",cents[icent].data()),"");

    leg[icent]->Draw();
  }

  c1->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,1.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.27,"1/N#gamma dN/dx_{J#gamma} Raw Signal");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);
  ldndxi->Draw();

  // float labelspace = yaxismax / 4.0;
  const int nlabels = 5;
  float fylabels[] = {0,0.5,1,1.5,2};
  string sylabels[] = {"0",".5","1","1.5","2"};
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    laxis[ilatex] = new TLatex(0.9,fylabels[ilatex]-0.1,Form("%s",sylabels[ilatex].data()));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.3);
    laxis[ilatex]->Draw();
  }

  c1->SaveAs("xjg_step1_allsubtractions.png");
}
