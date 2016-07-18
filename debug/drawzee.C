{
  
  TFile *_file0 = TFile::Open("zall.root");
  TCanvas * c1_zall = new TCanvas();
  TH2D * dummy = new TH2D("dummy",";z-jet balance;",1,0,2,1,0,1);

  TH1D * hzjetratio_ppmc_01 = (TH1D *)_file0->Get("hzjetratio_ppmc_01");
  TH1D * hzjetratio_ppdata_01 = (TH1D *)_file0->Get("hzjetratio_ppdata_01");

  hzjetratio_ppmc_01->SetMarkerColor(2);
  hzjetratio_ppmc_01->SetFillColor(800);
  hzjetratio_ppmc_01->SetLineWidth(0);
  hzjetratio_ppdata_01->DrawNormalized("pe");
  hzjetratio_ppmc_01->DrawNormalized("hist same");
  hzjetratio_ppdata_01->DrawNormalized("pe same");

  TLatex * lpt = new TLatex(.6,.88,"30 GeV<p_{T}^{Z}<60 GeV");
  lpt->SetNDC();
  lpt->Draw();
  TLatex * lak = new TLatex(0.6,0.81,"Anti-k_{T} R=0.3 PF Jets");
  lak->SetNDC();
  lak->Draw();
  TLatex * lint = new TLatex(.22,0.95,"CMS, L = 26 pb^{-1}");
  lint->SetNDC();
  lint->Draw();
  TLatex * lroots = new TLatex(0.8,0.95,"#sqrt{s}=5 TeV");
  lroots->SetNDC();
  lroots->Draw();

  TLegend * leg_ff_pf1_jt30_40 = new TLegend(0.6,0.6,0.9,0.72);
  leg_ff_pf1_jt30_40->SetFillColor(0);
  leg_ff_pf1_jt30_40->SetTextSize(0.05);
  leg_ff_pf1_jt30_40->SetFillStyle(0);
  leg_ff_pf1_jt30_40->SetTextFont(42);
  leg_ff_pf1_jt30_40->AddEntry(hzjetratio_ppdata_01,"Data","lp");
  leg_ff_pf1_jt30_40->AddEntry(hzjetratio_ppmc_01,"Monte Carlo","f");
  leg_ff_pf1_jt30_40->Draw();



  c1_zall->SaveAs("hzjetratio01_datamcpp.png");
}
