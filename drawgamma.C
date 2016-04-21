{
  
  TFile *_file0 = TFile::Open("gall.root");
  TCanvas * c1_zall = new TCanvas();
  TH2D * dummy = new TH2D("dummy",";#gamma-jet balance;",1,0,2,1,0,0.3);

  TH1D * hgjetratio_ppmc_02 = (TH1D *)_file0->Get("hgjetratio_ppmc_02");
  TH1D * hgjetratio_ppdata_02 = (TH1D *)_file0->Get("hgjetratio_ppdata_02");

  hgjetratio_ppmc_02->SetMarkerColor(2);
  hgjetratio_ppmc_02->SetFillColor(800);
  hgjetratio_ppmc_02->SetLineWidth(0);
  dummy->Draw();
  // hgjetratio_ppdata_02->DrawNormalized("pe same");
  hgjetratio_ppmc_02->DrawNormalized("hist same");
  hgjetratio_ppdata_02->DrawNormalized("pe same");

  TLatex * lpt = new TLatex(.6,.88,"45 GeV<p_{T}^{#gamma}<60 GeV");
  lpt->SetNDC();
  lpt->Draw();
  TLatex * lak = new TLatex(0.6,0.81,"Anti-k_{T} R=0.3 PF Jets");
  lak->SetNDC();
  lak->Draw();
  TLatex * lint = new TLatex(.22,0.95,"CMS, L = 26 pb^{-1}");
  lint->SetNDC();
  lint->Draw();
  TLatex * lroots = new TLatex(0.75,0.95,"pp #sqrt{s}=5 TeV");
  lroots->SetNDC();
  lroots->Draw();

  TLegend * leg_ff_pf1_jt30_40 = new TLegend(0.25,0.8,0.55,0.92);
  leg_ff_pf1_jt30_40->SetFillColor(0);
  leg_ff_pf1_jt30_40->SetTextSize(0.05);
  leg_ff_pf1_jt30_40->SetFillStyle(0);
  leg_ff_pf1_jt30_40->SetTextFont(42);
  leg_ff_pf1_jt30_40->AddEntry(hgjetratio_ppdata_02,"Data","lp");
  leg_ff_pf1_jt30_40->AddEntry(hgjetratio_ppmc_02,"Monte Carlo","f");
  leg_ff_pf1_jt30_40->Draw();



  c1_zall->SaveAs("hgjetratio02_datamcpp.png");
}
