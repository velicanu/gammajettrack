{
  TFile *_file0 = TFile::Open("all.root");
  TCanvas * cff_jt30_40 = new TCanvas("cff_jt30_40");
  cff_jt30_40->SetLogy();
  cff_jt30_40->SetLogx();
  // TH1D * hjetpt_pbpbdatamb_jt30_40 = (TH1D*) _file0->Get("hjetpt_pbpbdatamb_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf1_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf1_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf1_jt30_40);
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf1_jt30_40);
  hfragFunctIn_pbpbmc30_pf1_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Draw("pesame");
  TLegend * leg_ff_jt30_40 = new TLegend(0.39,0.61,0.74,0.91);
  leg_ff_jt30_40->SetFillColor(0);
  leg_ff_jt30_40->SetTextSize(0.06);
  leg_ff_jt30_40->SetFillStyle(0);
  leg_ff_jt30_40->SetTextFont(42);
  leg_ff_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf1_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_jt30_40->Draw();
}