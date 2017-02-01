{
  TFile *_file0 = TFile::Open("closure_pbpb_60_1000_30_gammaxi0.root");
  TFile *_file1 = TFile::Open("all_60_1000_30_gammaxi0.root");
  TH1D * hmc;
  TH1D * hdata;
  hmc = (TH1D*) _file0->Get("hvz_pbpbmc_recoreco_0_20");
  hdata = (TH1D*) _file1->Get("hvz_pbpbdata_recoreco_0_20");
  hdata->DrawNormalized("pe");
  hmc->DrawNormalized("hist same");

  TLegend *leg = new TLegend(0.2,0.8,0.5,0.9);
  leg->SetTextFont(62);
  leg->SetTextSize(0.039);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(hdata,"0-10% PbPb data","p");
  leg->AddEntry(hmc,"0-10% PbPb mc","l");
  leg->Draw();

  // c1->SaveAs("hvz_data_mc_postweight.png");
}
