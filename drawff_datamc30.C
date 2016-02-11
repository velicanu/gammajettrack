{
  TFile *_file0 = TFile::Open("all.root");
  int save = 0;
  
  
  // ---------------------------------------------------------------------- //
  // ------------------- jt30_40 ------------------------------------------ //
  // ---------------------------------------------------------------------- //
  TH1D * hjetpt_pbpbdatamb_jt30_40 = (TH1D*) _file0->Get("hjetpt_pbpbdatamb_jt30_40");
  TH1D * hjetpt_pbpbmc30_jt30_40 = (TH1D*) _file0->Get("hjetpt_pbpbmc30_jt30_40");
  // ------------------- jt30_40 Fragmentation Function Raw pfType=1 ------ //
  TCanvas * cff_pf1_jt30_40 = new TCanvas("cff_pf1_jt30_40");
  cff_pf1_jt30_40->SetLogy();
  cff_pf1_jt30_40->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf1_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf1_jt30_40");
  TH1D * hfragFunctIn_pbpbmc30_pf1_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf1_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf1_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf1_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf1_jt30_40);
  hfragFunctIn_pbpbdatamb_pf1_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf1_jt30_40);
  hfragFunctIn_pbpbmc30_pf1_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf1_jt30_40->Draw("pesame");
  TLegend * leg_ff_pf1_jt30_40 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf1_jt30_40->SetFillColor(0);
  leg_ff_pf1_jt30_40->SetTextSize(0.05);
  leg_ff_pf1_jt30_40->SetFillStyle(0);
  leg_ff_pf1_jt30_40->SetTextFont(42);
  leg_ff_pf1_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf1_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf1_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf1_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt30_40,"pfType=1, 30<jet p_{T}<40","");
  leg_ff_pf1_jt30_40->Draw();
  if(save==1) cff_pf1_jt30_40->SaveAs("cff_pf1_jt30_40.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt30_40 Fragmentation Function Raw pfType=2 ------ //
  TCanvas * cff_pf2_jt30_40 = new TCanvas("cff_pf2_jt30_40");
  cff_pf2_jt30_40->SetLogy();
  cff_pf2_jt30_40->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf2_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf2_jt30_40");
  TH1D * hfragFunctIn_pbpbmc30_pf2_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf2_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf2_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf2_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf2_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf2_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf2_jt30_40);
  hfragFunctIn_pbpbdatamb_pf2_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf2_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf2_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf2_jt30_40);
  hfragFunctIn_pbpbmc30_pf2_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf2_jt30_40->Draw("pesame");
  TLegend * leg_ff_pf2_jt30_40 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf2_jt30_40->SetFillColor(0);
  leg_ff_pf2_jt30_40->SetTextSize(0.05);
  leg_ff_pf2_jt30_40->SetFillStyle(0);
  leg_ff_pf2_jt30_40->SetTextFont(42);
  leg_ff_pf2_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf2_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf2_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf2_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt30_40,"pfType=2, 30<jet p_{T}<40","");
  leg_ff_pf2_jt30_40->Draw();
  if(save==1) cff_pf2_jt30_40->SaveAs("cff_pf2_jt30_40.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt30_40 Fragmentation Function Raw pfType=3 ------ //
  TCanvas * cff_pf3_jt30_40 = new TCanvas("cff_pf3_jt30_40");
  cff_pf3_jt30_40->SetLogy();
  cff_pf3_jt30_40->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf3_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf3_jt30_40");
  TH1D * hfragFunctIn_pbpbmc30_pf3_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf3_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf3_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf3_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf3_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf3_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf3_jt30_40);
  hfragFunctIn_pbpbdatamb_pf3_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf3_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf3_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf3_jt30_40);
  hfragFunctIn_pbpbmc30_pf3_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf3_jt30_40->Draw("pesame");
  TLegend * leg_ff_pf3_jt30_40 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf3_jt30_40->SetFillColor(0);
  leg_ff_pf3_jt30_40->SetTextSize(0.05);
  leg_ff_pf3_jt30_40->SetFillStyle(0);
  leg_ff_pf3_jt30_40->SetTextFont(42);
  leg_ff_pf3_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf3_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf3_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf3_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt30_40,"pfType=3, 30<jet p_{T}<40","");
  leg_ff_pf3_jt30_40->Draw();
  if(save==1) cff_pf3_jt30_40->SaveAs("cff_pf3_jt30_40.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt30_40 Fragmentation Function Raw pfType=-1 ------ //
  TCanvas * cff_pf991_jt30_40 = new TCanvas("cff_pf991_jt30_40");
  cff_pf991_jt30_40->SetLogy();
  cff_pf991_jt30_40->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf991_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf991_jt30_40");
  TH1D * hfragFunctIn_pbpbmc30_pf991_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf991_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf991_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf991_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf991_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf991_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf991_jt30_40);
  hfragFunctIn_pbpbdatamb_pf991_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf991_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf991_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf991_jt30_40);
  hfragFunctIn_pbpbmc30_pf991_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf991_jt30_40->Draw("pesame");
  TLegend * leg_ff_pf991_jt30_40 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf991_jt30_40->SetFillColor(0);
  leg_ff_pf991_jt30_40->SetTextSize(0.05);
  leg_ff_pf991_jt30_40->SetFillStyle(0);
  leg_ff_pf991_jt30_40->SetTextFont(42);
  leg_ff_pf991_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf991_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf991_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf991_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt30_40,"pfType=-1, 30<jet p_{T}<40","");
  leg_ff_pf991_jt30_40->Draw();
  if(save==1) cff_pf991_jt30_40->SaveAs("cff_pf991_jt30_40.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt30_40 Fragmentation Function Raw all tracks ------ //
  TCanvas * cff_pf990_jt30_40 = new TCanvas("cff_pf990_jt30_40");
  cff_pf990_jt30_40->SetLogy();
  cff_pf990_jt30_40->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf990_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf990_jt30_40");
  TH1D * hfragFunctIn_pbpbmc30_pf990_jt30_40 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf990_jt30_40");
  float njet_hfragFunctIn_pbpbdatamb_pf990_jt30_40 = hjetpt_pbpbdatamb_jt30_40->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf990_jt30_40 = hjetpt_pbpbmc30_jt30_40->Integral();
  hfragFunctIn_pbpbdatamb_pf990_jt30_40->Sumw2();
  hfragFunctIn_pbpbdatamb_pf990_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf990_jt30_40);
  hfragFunctIn_pbpbdatamb_pf990_jt30_40->Draw("pe");
  hfragFunctIn_pbpbmc30_pf990_jt30_40->Sumw2();
  hfragFunctIn_pbpbmc30_pf990_jt30_40->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf990_jt30_40);
  hfragFunctIn_pbpbmc30_pf990_jt30_40->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf990_jt30_40->Draw("pesame");
  TLegend * leg_ff_pf990_jt30_40 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf990_jt30_40->SetFillColor(0);
  leg_ff_pf990_jt30_40->SetTextSize(0.05);
  leg_ff_pf990_jt30_40->SetFillStyle(0);
  leg_ff_pf990_jt30_40->SetTextFont(42);
  leg_ff_pf990_jt30_40->AddEntry(hfragFunctIn_pbpbdatamb_pf990_jt30_40,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf990_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt30_40,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf990_jt30_40->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt30_40,"all tracks, 30<jet p_{T}<40","");
  leg_ff_pf990_jt30_40->Draw();
  if(save==1) cff_pf990_jt30_40->SaveAs("cff_pf990_jt30_40.png");
  // ---------------------------------------------------------------------- //
  
  
  
  // ---------------------------------------------------------------------- //
  // ------------------- jt40_60 ------------------------------------------ //
  // ---------------------------------------------------------------------- //
  TH1D * hjetpt_pbpbdatamb_jt40_60 = (TH1D*) _file0->Get("hjetpt_pbpbdatamb_jt40_60");
  TH1D * hjetpt_pbpbmc30_jt40_60 = (TH1D*) _file0->Get("hjetpt_pbpbmc30_jt40_60");
  // ------------------- jt40_60 Fragmentation Function Raw pfType=1 ------ //
  TCanvas * cff_pf1_jt40_60 = new TCanvas("cff_pf1_jt40_60");
  cff_pf1_jt40_60->SetLogy();
  cff_pf1_jt40_60->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf1_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf1_jt40_60");
  TH1D * hfragFunctIn_pbpbmc30_pf1_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf1_jt40_60");
  float njet_hfragFunctIn_pbpbdatamb_pf1_jt40_60 = hjetpt_pbpbdatamb_jt40_60->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf1_jt40_60 = hjetpt_pbpbmc30_jt40_60->Integral();
  hfragFunctIn_pbpbdatamb_pf1_jt40_60->Sumw2();
  hfragFunctIn_pbpbdatamb_pf1_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf1_jt40_60);
  hfragFunctIn_pbpbdatamb_pf1_jt40_60->Draw("pe");
  hfragFunctIn_pbpbmc30_pf1_jt40_60->Sumw2();
  hfragFunctIn_pbpbmc30_pf1_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf1_jt40_60);
  hfragFunctIn_pbpbmc30_pf1_jt40_60->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf1_jt40_60->Draw("pesame");
  TLegend * leg_ff_pf1_jt40_60 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf1_jt40_60->SetFillColor(0);
  leg_ff_pf1_jt40_60->SetTextSize(0.05);
  leg_ff_pf1_jt40_60->SetFillStyle(0);
  leg_ff_pf1_jt40_60->SetTextFont(42);
  leg_ff_pf1_jt40_60->AddEntry(hfragFunctIn_pbpbdatamb_pf1_jt40_60,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf1_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt40_60,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf1_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt40_60,"pfType=1, 40<jet p_{T}<60","");
  leg_ff_pf1_jt40_60->Draw();
  if(save==1) cff_pf1_jt40_60->SaveAs("cff_pf1_jt40_60.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt40_60 Fragmentation Function Raw pfType=2 ------ //
  TCanvas * cff_pf2_jt40_60 = new TCanvas("cff_pf2_jt40_60");
  cff_pf2_jt40_60->SetLogy();
  cff_pf2_jt40_60->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf2_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf2_jt40_60");
  TH1D * hfragFunctIn_pbpbmc30_pf2_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf2_jt40_60");
  float njet_hfragFunctIn_pbpbdatamb_pf2_jt40_60 = hjetpt_pbpbdatamb_jt40_60->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf2_jt40_60 = hjetpt_pbpbmc30_jt40_60->Integral();
  hfragFunctIn_pbpbdatamb_pf2_jt40_60->Sumw2();
  hfragFunctIn_pbpbdatamb_pf2_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf2_jt40_60);
  hfragFunctIn_pbpbdatamb_pf2_jt40_60->Draw("pe");
  hfragFunctIn_pbpbmc30_pf2_jt40_60->Sumw2();
  hfragFunctIn_pbpbmc30_pf2_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf2_jt40_60);
  hfragFunctIn_pbpbmc30_pf2_jt40_60->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf2_jt40_60->Draw("pesame");
  TLegend * leg_ff_pf2_jt40_60 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf2_jt40_60->SetFillColor(0);
  leg_ff_pf2_jt40_60->SetTextSize(0.05);
  leg_ff_pf2_jt40_60->SetFillStyle(0);
  leg_ff_pf2_jt40_60->SetTextFont(42);
  leg_ff_pf2_jt40_60->AddEntry(hfragFunctIn_pbpbdatamb_pf2_jt40_60,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf2_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt40_60,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf2_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt40_60,"pfType=2, 40<jet p_{T}<60","");
  leg_ff_pf2_jt40_60->Draw();
  if(save==1) cff_pf2_jt40_60->SaveAs("cff_pf2_jt40_60.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt40_60 Fragmentation Function Raw pfType=3 ------ //
  TCanvas * cff_pf3_jt40_60 = new TCanvas("cff_pf3_jt40_60");
  cff_pf3_jt40_60->SetLogy();
  cff_pf3_jt40_60->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf3_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf3_jt40_60");
  TH1D * hfragFunctIn_pbpbmc30_pf3_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf3_jt40_60");
  float njet_hfragFunctIn_pbpbdatamb_pf3_jt40_60 = hjetpt_pbpbdatamb_jt40_60->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf3_jt40_60 = hjetpt_pbpbmc30_jt40_60->Integral();
  hfragFunctIn_pbpbdatamb_pf3_jt40_60->Sumw2();
  hfragFunctIn_pbpbdatamb_pf3_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf3_jt40_60);
  hfragFunctIn_pbpbdatamb_pf3_jt40_60->Draw("pe");
  hfragFunctIn_pbpbmc30_pf3_jt40_60->Sumw2();
  hfragFunctIn_pbpbmc30_pf3_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf3_jt40_60);
  hfragFunctIn_pbpbmc30_pf3_jt40_60->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf3_jt40_60->Draw("pesame");
  TLegend * leg_ff_pf3_jt40_60 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf3_jt40_60->SetFillColor(0);
  leg_ff_pf3_jt40_60->SetTextSize(0.05);
  leg_ff_pf3_jt40_60->SetFillStyle(0);
  leg_ff_pf3_jt40_60->SetTextFont(42);
  leg_ff_pf3_jt40_60->AddEntry(hfragFunctIn_pbpbdatamb_pf3_jt40_60,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf3_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt40_60,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf3_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt40_60,"pfType=3, 40<jet p_{T}<60","");
  leg_ff_pf3_jt40_60->Draw();
  if(save==1) cff_pf3_jt40_60->SaveAs("cff_pf3_jt40_60.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt40_60 Fragmentation Function Raw pfType=-1 ------ //
  TCanvas * cff_pf991_jt40_60 = new TCanvas("cff_pf991_jt40_60");
  cff_pf991_jt40_60->SetLogy();
  cff_pf991_jt40_60->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf991_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf991_jt40_60");
  TH1D * hfragFunctIn_pbpbmc30_pf991_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf991_jt40_60");
  float njet_hfragFunctIn_pbpbdatamb_pf991_jt40_60 = hjetpt_pbpbdatamb_jt40_60->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf991_jt40_60 = hjetpt_pbpbmc30_jt40_60->Integral();
  hfragFunctIn_pbpbdatamb_pf991_jt40_60->Sumw2();
  hfragFunctIn_pbpbdatamb_pf991_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf991_jt40_60);
  hfragFunctIn_pbpbdatamb_pf991_jt40_60->Draw("pe");
  hfragFunctIn_pbpbmc30_pf991_jt40_60->Sumw2();
  hfragFunctIn_pbpbmc30_pf991_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf991_jt40_60);
  hfragFunctIn_pbpbmc30_pf991_jt40_60->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf991_jt40_60->Draw("pesame");
  TLegend * leg_ff_pf991_jt40_60 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf991_jt40_60->SetFillColor(0);
  leg_ff_pf991_jt40_60->SetTextSize(0.05);
  leg_ff_pf991_jt40_60->SetFillStyle(0);
  leg_ff_pf991_jt40_60->SetTextFont(42);
  leg_ff_pf991_jt40_60->AddEntry(hfragFunctIn_pbpbdatamb_pf991_jt40_60,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf991_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt40_60,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf991_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt40_60,"pfType=-1, 40<jet p_{T}<60","");
  leg_ff_pf991_jt40_60->Draw();
  if(save==1) cff_pf991_jt40_60->SaveAs("cff_pf991_jt40_60.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt40_60 Fragmentation Function Raw all tracks ------ //
  TCanvas * cff_pf990_jt40_60 = new TCanvas("cff_pf990_jt40_60");
  cff_pf990_jt40_60->SetLogy();
  cff_pf990_jt40_60->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf990_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf990_jt40_60");
  TH1D * hfragFunctIn_pbpbmc30_pf990_jt40_60 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf990_jt40_60");
  float njet_hfragFunctIn_pbpbdatamb_pf990_jt40_60 = hjetpt_pbpbdatamb_jt40_60->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf990_jt40_60 = hjetpt_pbpbmc30_jt40_60->Integral();
  hfragFunctIn_pbpbdatamb_pf990_jt40_60->Sumw2();
  hfragFunctIn_pbpbdatamb_pf990_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf990_jt40_60);
  hfragFunctIn_pbpbdatamb_pf990_jt40_60->Draw("pe");
  hfragFunctIn_pbpbmc30_pf990_jt40_60->Sumw2();
  hfragFunctIn_pbpbmc30_pf990_jt40_60->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf990_jt40_60);
  hfragFunctIn_pbpbmc30_pf990_jt40_60->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf990_jt40_60->Draw("pesame");
  TLegend * leg_ff_pf990_jt40_60 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf990_jt40_60->SetFillColor(0);
  leg_ff_pf990_jt40_60->SetTextSize(0.05);
  leg_ff_pf990_jt40_60->SetFillStyle(0);
  leg_ff_pf990_jt40_60->SetTextFont(42);
  leg_ff_pf990_jt40_60->AddEntry(hfragFunctIn_pbpbdatamb_pf990_jt40_60,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf990_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt40_60,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf990_jt40_60->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt40_60,"all tracks, 40<jet p_{T}<60","");
  leg_ff_pf990_jt40_60->Draw();
  if(save==1) cff_pf990_jt40_60->SaveAs("cff_pf990_jt40_60.png");
  // ---------------------------------------------------------------------- //
  
  
  // ---------------------------------------------------------------------- //
  // ------------------- jt60_100 ------------------------------------------ //
  // ---------------------------------------------------------------------- //
  TH1D * hjetpt_pbpbdatamb_jt60_100 = (TH1D*) _file0->Get("hjetpt_pbpbdatamb_jt60_100");
  TH1D * hjetpt_pbpbmc30_jt60_100 = (TH1D*) _file0->Get("hjetpt_pbpbmc30_jt60_100");
  // ------------------- jt60_100 Fragmentation Function Raw pfType=1 ------ //
  TCanvas * cff_pf1_jt60_100 = new TCanvas("cff_pf1_jt60_100");
  cff_pf1_jt60_100->SetLogy();
  cff_pf1_jt60_100->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf1_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf1_jt60_100");
  TH1D * hfragFunctIn_pbpbmc30_pf1_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf1_jt60_100");
  float njet_hfragFunctIn_pbpbdatamb_pf1_jt60_100 = hjetpt_pbpbdatamb_jt60_100->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf1_jt60_100 = hjetpt_pbpbmc30_jt60_100->Integral();
  hfragFunctIn_pbpbdatamb_pf1_jt60_100->Sumw2();
  hfragFunctIn_pbpbdatamb_pf1_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf1_jt60_100);
  hfragFunctIn_pbpbdatamb_pf1_jt60_100->Draw("pe");
  hfragFunctIn_pbpbmc30_pf1_jt60_100->Sumw2();
  hfragFunctIn_pbpbmc30_pf1_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf1_jt60_100);
  hfragFunctIn_pbpbmc30_pf1_jt60_100->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf1_jt60_100->Draw("pesame");
  TLegend * leg_ff_pf1_jt60_100 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf1_jt60_100->SetFillColor(0);
  leg_ff_pf1_jt60_100->SetTextSize(0.05);
  leg_ff_pf1_jt60_100->SetFillStyle(0);
  leg_ff_pf1_jt60_100->SetTextFont(42);
  leg_ff_pf1_jt60_100->AddEntry(hfragFunctIn_pbpbdatamb_pf1_jt60_100,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf1_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt60_100,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf1_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf1_jt60_100,"pfType=1, 60<jet p_{T}<100","");
  leg_ff_pf1_jt60_100->Draw();
  if(save==1) cff_pf1_jt60_100->SaveAs("cff_pf1_jt60_100.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt60_100 Fragmentation Function Raw pfType=2 ------ //
  TCanvas * cff_pf2_jt60_100 = new TCanvas("cff_pf2_jt60_100");
  cff_pf2_jt60_100->SetLogy();
  cff_pf2_jt60_100->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf2_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf2_jt60_100");
  TH1D * hfragFunctIn_pbpbmc30_pf2_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf2_jt60_100");
  float njet_hfragFunctIn_pbpbdatamb_pf2_jt60_100 = hjetpt_pbpbdatamb_jt60_100->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf2_jt60_100 = hjetpt_pbpbmc30_jt60_100->Integral();
  hfragFunctIn_pbpbdatamb_pf2_jt60_100->Sumw2();
  hfragFunctIn_pbpbdatamb_pf2_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf2_jt60_100);
  hfragFunctIn_pbpbdatamb_pf2_jt60_100->Draw("pe");
  hfragFunctIn_pbpbmc30_pf2_jt60_100->Sumw2();
  hfragFunctIn_pbpbmc30_pf2_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf2_jt60_100);
  hfragFunctIn_pbpbmc30_pf2_jt60_100->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf2_jt60_100->Draw("pesame");
  TLegend * leg_ff_pf2_jt60_100 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf2_jt60_100->SetFillColor(0);
  leg_ff_pf2_jt60_100->SetTextSize(0.05);
  leg_ff_pf2_jt60_100->SetFillStyle(0);
  leg_ff_pf2_jt60_100->SetTextFont(42);
  leg_ff_pf2_jt60_100->AddEntry(hfragFunctIn_pbpbdatamb_pf2_jt60_100,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf2_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt60_100,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf2_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf2_jt60_100,"pfType=2, 60<jet p_{T}<100","");
  leg_ff_pf2_jt60_100->Draw();
  if(save==1) cff_pf2_jt60_100->SaveAs("cff_pf2_jt60_100.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt60_100 Fragmentation Function Raw pfType=3 ------ //
  TCanvas * cff_pf3_jt60_100 = new TCanvas("cff_pf3_jt60_100");
  cff_pf3_jt60_100->SetLogy();
  cff_pf3_jt60_100->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf3_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf3_jt60_100");
  TH1D * hfragFunctIn_pbpbmc30_pf3_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf3_jt60_100");
  float njet_hfragFunctIn_pbpbdatamb_pf3_jt60_100 = hjetpt_pbpbdatamb_jt60_100->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf3_jt60_100 = hjetpt_pbpbmc30_jt60_100->Integral();
  hfragFunctIn_pbpbdatamb_pf3_jt60_100->Sumw2();
  hfragFunctIn_pbpbdatamb_pf3_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf3_jt60_100);
  hfragFunctIn_pbpbdatamb_pf3_jt60_100->Draw("pe");
  hfragFunctIn_pbpbmc30_pf3_jt60_100->Sumw2();
  hfragFunctIn_pbpbmc30_pf3_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf3_jt60_100);
  hfragFunctIn_pbpbmc30_pf3_jt60_100->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf3_jt60_100->Draw("pesame");
  TLegend * leg_ff_pf3_jt60_100 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf3_jt60_100->SetFillColor(0);
  leg_ff_pf3_jt60_100->SetTextSize(0.05);
  leg_ff_pf3_jt60_100->SetFillStyle(0);
  leg_ff_pf3_jt60_100->SetTextFont(42);
  leg_ff_pf3_jt60_100->AddEntry(hfragFunctIn_pbpbdatamb_pf3_jt60_100,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf3_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt60_100,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf3_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf3_jt60_100,"pfType=3, 60<jet p_{T}<100","");
  leg_ff_pf3_jt60_100->Draw();
  if(save==1) cff_pf3_jt60_100->SaveAs("cff_pf3_jt60_100.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt60_100 Fragmentation Function Raw pfType=-1 ------ //
  TCanvas * cff_pf991_jt60_100 = new TCanvas("cff_pf991_jt60_100");
  cff_pf991_jt60_100->SetLogy();
  cff_pf991_jt60_100->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf991_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf991_jt60_100");
  TH1D * hfragFunctIn_pbpbmc30_pf991_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf991_jt60_100");
  float njet_hfragFunctIn_pbpbdatamb_pf991_jt60_100 = hjetpt_pbpbdatamb_jt60_100->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf991_jt60_100 = hjetpt_pbpbmc30_jt60_100->Integral();
  hfragFunctIn_pbpbdatamb_pf991_jt60_100->Sumw2();
  hfragFunctIn_pbpbdatamb_pf991_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf991_jt60_100);
  hfragFunctIn_pbpbdatamb_pf991_jt60_100->Draw("pe");
  hfragFunctIn_pbpbmc30_pf991_jt60_100->Sumw2();
  hfragFunctIn_pbpbmc30_pf991_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf991_jt60_100);
  hfragFunctIn_pbpbmc30_pf991_jt60_100->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf991_jt60_100->Draw("pesame");
  TLegend * leg_ff_pf991_jt60_100 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf991_jt60_100->SetFillColor(0);
  leg_ff_pf991_jt60_100->SetTextSize(0.05);
  leg_ff_pf991_jt60_100->SetFillStyle(0);
  leg_ff_pf991_jt60_100->SetTextFont(42);
  leg_ff_pf991_jt60_100->AddEntry(hfragFunctIn_pbpbdatamb_pf991_jt60_100,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf991_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt60_100,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf991_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf991_jt60_100,"pfType=-1, 60<jet p_{T}<100","");
  leg_ff_pf991_jt60_100->Draw();
  if(save==1) cff_pf991_jt60_100->SaveAs("cff_pf991_jt60_100.png");
  // ---------------------------------------------------------------------- //
  
  // ------------------- jt60_100 Fragmentation Function Raw all tracks ------ //
  TCanvas * cff_pf990_jt60_100 = new TCanvas("cff_pf990_jt60_100");
  cff_pf990_jt60_100->SetLogy();
  cff_pf990_jt60_100->SetLogx();
  TH1D * hfragFunctIn_pbpbdatamb_pf990_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbdatamb_pf990_jt60_100");
  TH1D * hfragFunctIn_pbpbmc30_pf990_jt60_100 = (TH1D*) _file0->Get("hfragFunctIn_pbpbmc30_pf990_jt60_100");
  float njet_hfragFunctIn_pbpbdatamb_pf990_jt60_100 = hjetpt_pbpbdatamb_jt60_100->Integral();
  float njet_hfragFunctIn_pbpbmc30_pf990_jt60_100 = hjetpt_pbpbmc30_jt60_100->Integral();
  hfragFunctIn_pbpbdatamb_pf990_jt60_100->Sumw2();
  hfragFunctIn_pbpbdatamb_pf990_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbdatamb_pf990_jt60_100);
  hfragFunctIn_pbpbdatamb_pf990_jt60_100->Draw("pe");
  hfragFunctIn_pbpbmc30_pf990_jt60_100->Sumw2();
  hfragFunctIn_pbpbmc30_pf990_jt60_100->Scale(1.0/njet_hfragFunctIn_pbpbmc30_pf990_jt60_100);
  hfragFunctIn_pbpbmc30_pf990_jt60_100->SetMarkerColor(2);
  hfragFunctIn_pbpbmc30_pf990_jt60_100->Draw("pesame");
  TLegend * leg_ff_pf990_jt60_100 = new TLegend(0.50,0.68,0.78,0.93);
  leg_ff_pf990_jt60_100->SetFillColor(0);
  leg_ff_pf990_jt60_100->SetTextSize(0.05);
  leg_ff_pf990_jt60_100->SetFillStyle(0);
  leg_ff_pf990_jt60_100->SetTextFont(42);
  leg_ff_pf990_jt60_100->AddEntry(hfragFunctIn_pbpbdatamb_pf990_jt60_100,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pf990_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt60_100,"#hat{p}_{T}=30 Pythia+Hydjet","p");
  leg_ff_pf990_jt60_100->AddEntry(hfragFunctIn_pbpbmc30_pf990_jt60_100,"all tracks, 60<jet p_{T}<100","");
  leg_ff_pf990_jt60_100->Draw();
  if(save==1) cff_pf990_jt60_100->SaveAs("cff_pf990_jt60_100.png");
  // ---------------------------------------------------------------------- //
  
  
  
  
}