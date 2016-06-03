{
  // TFile *_file0 = TFile::Open("all100gev.root");
  TFile *_file0 = TFile::Open("all45-100.root");
  int save = 1;
  float binwidth = 5.000000e-01;

  // Raw FF pbpdata
  TCanvas * c1_pbpbdata = new TCanvas();
  TH1D * hgammaphoffxi_pbpbdata_ = (TH1D*) _file0->Get("hgammaphoffxi_pbpbdata_");
  TH1D * hgammaphoffxi_refcone_pbpbdata_ = (TH1D*) _file0->Get("hgammaphoffxi_refcone_pbpbdata_");
  float njets_pbpbdata = hjetpt_pbpbdata_->Integral();
  hgammaphoffxi_pbpbdata_->Sumw2();
  hgammaphoffxi_refcone_pbpbdata_->Sumw2();
  hgammaphoffxi_pbpbdata_->Scale(1.0/njets_pbpbdata/binwidth);
  hgammaphoffxi_refcone_pbpbdata_->Scale(1.0/njets_pbpbdata/binwidth);
  hgammaphoffxi_pbpbdata_->GetXaxis()->CenterTitle();
  hgammaphoffxi_pbpbdata_->SetYTitle("dN/d#xi_{#gamma}");
  hgammaphoffxi_pbpbdata_->GetYaxis()->CenterTitle();
  hgammaphoffxi_pbpbdata_->Draw();
  
  hgammaphoffxi_refcone_pbpbdata_->SetMarkerStyle(24);
  hgammaphoffxi_refcone_pbpbdata_->Draw("same");
  TLegend * leg_ff_pbpbdata = new TLegend(0.23,0.59,0.50,0.92);
  leg_ff_pbpbdata->SetFillColor(0);
  leg_ff_pbpbdata->SetTextSize(0.05);
  leg_ff_pbpbdata->SetFillStyle(0);
  leg_ff_pbpbdata->SetTextFont(42);
  leg_ff_pbpbdata->AddEntry(hgammaphoffxi_pbpbdata_,"raw frag. func","p");
  leg_ff_pbpbdata->AddEntry(hgammaphoffxi_refcone_pbpbdata_,"#eta reflected cone","p");
  leg_ff_pbpbdata->AddEntry(hgammaphoffxi_refcone_pbpbdata_,"PbPb #sqrt{s_{NN}}=5 TeV","");
  leg_ff_pbpbdata->AddEntry(hgammaphoffxi_refcone_pbpbdata_,"trk p_{T}>1 GeV","");
  leg_ff_pbpbdata->AddEntry(hgammaphoffxi_refcone_pbpbdata_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_pbpbdata->Draw();

  // c1_pbpbdata->SaveAs("pbpbdata_unsubffspectrum_pho_45_gamma_100.png");
  // Raw FF pbpdata 
  
  // Raw FF pbpbmc
  TCanvas * c1_pbpbmc50 = new TCanvas();
  TH1D * hgammaphoffxi_pbpbmc50_ = (TH1D*) _file0->Get("hgammaphoffxi_pbpbmc50_");
  TH1D * hgammaphoffxi_refcone_pbpbmc50_ = (TH1D*) _file0->Get("hgammaphoffxi_refcone_pbpbmc50_");
  float njets_pbpbmc50 = hjetpt_pbpbmc50_->Integral();
  hgammaphoffxi_pbpbmc50_->Sumw2();
  hgammaphoffxi_refcone_pbpbmc50_->Sumw2();
  hgammaphoffxi_pbpbmc50_->Scale(1.0/njets_pbpbmc50/binwidth);
  hgammaphoffxi_refcone_pbpbmc50_->Scale(1.0/njets_pbpbmc50/binwidth);
  hgammaphoffxi_pbpbmc50_->GetXaxis()->CenterTitle();
  hgammaphoffxi_pbpbmc50_->SetYTitle("dN/d#xi_{#gamma}");
  hgammaphoffxi_pbpbmc50_->GetYaxis()->CenterTitle();
  hgammaphoffxi_pbpbmc50_->Draw();
  
  hgammaphoffxi_refcone_pbpbmc50_->SetMarkerStyle(24);
  hgammaphoffxi_refcone_pbpbmc50_->Draw("same");
  
  TLegend * leg_ff_pbpbmc50 = new TLegend(0.22,0.59,0.49,0.92);
  leg_ff_pbpbmc50->SetFillColor(0);
  leg_ff_pbpbmc50->SetTextSize(0.05);
  leg_ff_pbpbmc50->SetFillStyle(0);
  leg_ff_pbpbmc50->SetTextFont(42);
  leg_ff_pbpbmc50->AddEntry(hgammaphoffxi_pbpbmc50_,"raw frag. func","p");
  leg_ff_pbpbmc50->AddEntry(hgammaphoffxi_refcone_pbpbmc50_,"#eta reflected cone","p");
  leg_ff_pbpbmc50->AddEntry(hgammaphoffxi_refcone_pbpbmc50_,"Pythia+Hydjet #hat{p}_{T}=50","");
  leg_ff_pbpbmc50->AddEntry(hgammaphoffxi_refcone_pbpbmc50_,"trk p_{T}>1 GeV","");
  leg_ff_pbpbmc50->AddEntry(hgammaphoffxi_refcone_pbpbmc50_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_pbpbmc50->Draw();
  // c1_pbpbmc50->SaveAs("pbpbmc50_unsubffspectrum_pho_45_gamma_100.png");
  // Raw FF pbpbmc

  // Eta cone subtracted FF pbpbdata and pbpbmc
  TCanvas * c1_subpbpb = new TCanvas();
  TH2D * dummy_pbpbsub = new TH2D("dummy_pbpbsub",";#xi_{#gamma};dN/d#xi_{#gamma}",1,0,5,1,0,3.1);
  dummy_pbpbsub->GetXaxis()->CenterTitle();
  dummy_pbpbsub->GetYaxis()->CenterTitle();
  
  TH1D * clone_hgammaphoffxi_refcone_pbpbdata_ = (TH1D*) hgammaphoffxi_refcone_pbpbdata_->Clone("clone_hgammaphoffxi_refcone_pbpbdata_");
  clone_hgammaphoffxi_refcone_pbpbdata_->Scale(-1);
  TH1D * clone_hgammaphoffxi_pbpbdata_ = (TH1D*) hgammaphoffxi_pbpbdata_->Clone("clone_hgammaphoffxi_pbpbdata_");
  clone_hgammaphoffxi_pbpbdata_->Add(clone_hgammaphoffxi_refcone_pbpbdata_);
  
  TH1D * clone_hgammaphoffxi_refcone_pbpbmc50_ = (TH1D*) hgammaphoffxi_refcone_pbpbmc50_->Clone("clone_hgammaphoffxi_refcone_pbpbmc50_");
  clone_hgammaphoffxi_refcone_pbpbmc50_->Scale(-1);
  TH1D * clone_hgammaphoffxi_pbpbmc50_ = (TH1D*) hgammaphoffxi_pbpbmc50_->Clone("clone_hgammaphoffxi_pbpbmc50_");
  clone_hgammaphoffxi_pbpbmc50_->Add(clone_hgammaphoffxi_refcone_pbpbmc50_);
  clone_hgammaphoffxi_pbpbmc50_->SetMarkerColor(kRed);
  
  dummy_pbpbsub->Draw();
  clone_hgammaphoffxi_pbpbdata_->Draw("same");
  clone_hgammaphoffxi_pbpbmc50_->Draw("same");
  
  TLegend * leg_ff_pbpbsub = new TLegend(0.23,0.59,0.50,0.92);
  leg_ff_pbpbsub->SetFillColor(0);
  leg_ff_pbpbsub->SetTextSize(0.05);
  leg_ff_pbpbsub->SetFillStyle(0);
  leg_ff_pbpbsub->SetTextFont(42);
  leg_ff_pbpbsub->AddEntry(clone_hgammaphoffxi_pbpbdata_,"PbPb #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_pbpbsub->AddEntry(clone_hgammaphoffxi_pbpbmc50_,"Pythia+Hydjet #hat{p}_{T}=50","p");
  leg_ff_pbpbsub->AddEntry(clone_hgammaphoffxi_pbpbmc50_,"#eta cone sub","");
  leg_ff_pbpbsub->AddEntry(clone_hgammaphoffxi_pbpbmc50_,"trk p_{T}>1 GeV","");
  leg_ff_pbpbsub->AddEntry(clone_hgammaphoffxi_pbpbmc50_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_pbpbsub->Draw();
  // c1_subpbpb->SaveAs("pbpbdata_pbpbmc_etaconesubtracted_pho_45_gamma_100.png");
  // Eta cone subtracted FF pbpbdata and pbpbmc

  // Raw FF ppata 
  TCanvas * c1_ppdata = new TCanvas();
  TH1D * hgammaphoffxi_ppdata_ = (TH1D*) _file0->Get("hgammaphoffxi_ppdata_");
  TH1D * hgammaphoffxi_refcone_ppdata_ = (TH1D*) _file0->Get("hgammaphoffxi_refcone_ppdata_");
  float njets_ppdata = hjetpt_ppdata_->Integral();
  hgammaphoffxi_ppdata_->Sumw2();
  hgammaphoffxi_refcone_ppdata_->Sumw2();
  hgammaphoffxi_ppdata_->Scale(1.0/njets_ppdata/binwidth);
  hgammaphoffxi_refcone_ppdata_->Scale(1.0/njets_ppdata/binwidth);
  hgammaphoffxi_ppdata_->GetXaxis()->CenterTitle();
  hgammaphoffxi_ppdata_->SetYTitle("dN/d#xi_{#gamma}");
  hgammaphoffxi_ppdata_->GetYaxis()->CenterTitle();
  hgammaphoffxi_ppdata_->Draw();
  
  hgammaphoffxi_refcone_ppdata_->SetMarkerStyle(24);
  hgammaphoffxi_refcone_ppdata_->Draw("same");
  
  TLegend * leg_ff_ppdata = new TLegend(0.23,0.59,0.50,0.92);
  leg_ff_ppdata->SetFillColor(0);
  leg_ff_ppdata->SetTextSize(0.05);
  leg_ff_ppdata->SetFillStyle(0);
  leg_ff_ppdata->SetTextFont(42);
  leg_ff_ppdata->AddEntry(hgammaphoffxi_ppdata_,"raw frag. func","p");
  leg_ff_ppdata->AddEntry(hgammaphoffxi_refcone_ppdata_,"#eta reflected cone","p");
  leg_ff_ppdata->AddEntry(hgammaphoffxi_refcone_ppdata_,"pp #sqrt{s_{NN}}=5 TeV","");
  leg_ff_ppdata->AddEntry(hgammaphoffxi_refcone_ppdata_,"trk p_{T}>1 GeV","");
  leg_ff_ppdata->AddEntry(hgammaphoffxi_refcone_ppdata_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_ppdata->Draw();
  // Raw FF ppata 


  
  // Raw FF ppmc
  TCanvas * c1_ppmc50 = new TCanvas();
  TH1D * hgammaphoffxi_ppmc50_ = (TH1D*) _file0->Get("hgammaphoffxi_ppmc50_");
  TH1D * hgammaphoffxi_refcone_ppmc50_ = (TH1D*) _file0->Get("hgammaphoffxi_refcone_ppmc50_");
  float njets_ppmc50 = hjetpt_ppmc50_->Integral();
  hgammaphoffxi_ppmc50_->Sumw2();
  hgammaphoffxi_refcone_ppmc50_->Sumw2();
  hgammaphoffxi_ppmc50_->Scale(1.0/njets_ppmc50/binwidth);
  hgammaphoffxi_refcone_ppmc50_->Scale(1.0/njets_ppmc50/binwidth);
  hgammaphoffxi_ppmc50_->GetXaxis()->CenterTitle();
  hgammaphoffxi_ppmc50_->SetYTitle("dN/d#xi_{#gamma}");
  hgammaphoffxi_ppmc50_->GetYaxis()->CenterTitle();
  hgammaphoffxi_ppmc50_->Draw();
  
  hgammaphoffxi_refcone_ppmc50_->SetMarkerStyle(24);
  hgammaphoffxi_refcone_ppmc50_->Draw("same");
  
  TLegend * leg_ff_ppmc50 = new TLegend(0.22,0.59,0.49,0.92);
  leg_ff_ppmc50->SetFillColor(0);
  leg_ff_ppmc50->SetTextSize(0.05);
  leg_ff_ppmc50->SetFillStyle(0);
  leg_ff_ppmc50->SetTextFont(42);
  leg_ff_ppmc50->AddEntry(hgammaphoffxi_ppmc50_,"raw frag. func","p");
  leg_ff_ppmc50->AddEntry(hgammaphoffxi_refcone_ppmc50_,"#eta reflected cone","p");
  leg_ff_ppmc50->AddEntry(hgammaphoffxi_refcone_ppmc50_,"Pythia #hat{p}_{T}=50","");
  leg_ff_ppmc50->AddEntry(hgammaphoffxi_refcone_ppmc50_,"trk p_{T}>1 GeV","");
  leg_ff_ppmc50->AddEntry(hgammaphoffxi_refcone_ppmc50_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_ppmc50->Draw();
  // Raw FF ppmc

  // Eta cone subtracted FF ppdata and ppmc
  TCanvas * c1_subpp = new TCanvas();
  TH2D * dummy_ppsub = new TH2D("dummy_ppsub",";#xi_{#gamma};dN/d#xi_{#gamma}",1,0,5,1,0,3.1);
  dummy_ppsub->GetXaxis()->CenterTitle();
  dummy_ppsub->GetYaxis()->CenterTitle();
  
  TH1D * clone_hgammaphoffxi_refcone_ppdata_ = (TH1D*) hgammaphoffxi_refcone_ppdata_->Clone("clone_hgammaphoffxi_refcone_ppdata_");
  clone_hgammaphoffxi_refcone_ppdata_->Scale(-1);
  TH1D * clone_hgammaphoffxi_ppdata_ = (TH1D*) hgammaphoffxi_ppdata_->Clone("clone_hgammaphoffxi_ppdata_");
  clone_hgammaphoffxi_ppdata_->Add(clone_hgammaphoffxi_refcone_ppdata_);
  
  TH1D * clone_hgammaphoffxi_refcone_ppmc50_ = (TH1D*) hgammaphoffxi_refcone_ppmc50_->Clone("clone_hgammaphoffxi_refcone_ppmc50_");
  clone_hgammaphoffxi_refcone_ppmc50_->Scale(-1);
  TH1D * clone_hgammaphoffxi_ppmc50_ = (TH1D*) hgammaphoffxi_ppmc50_->Clone("clone_hgammaphoffxi_ppmc50_");
  clone_hgammaphoffxi_ppmc50_->Add(clone_hgammaphoffxi_refcone_ppmc50_);
  clone_hgammaphoffxi_ppmc50_->SetMarkerColor(kRed);
  
  dummy_ppsub->Draw();
  clone_hgammaphoffxi_ppdata_->Draw("same");
  clone_hgammaphoffxi_ppmc50_->Draw("same");
  
  TLegend * leg_ff_ppsub = new TLegend(0.23,0.59,0.50,0.92);
  leg_ff_ppsub->SetFillColor(0);
  leg_ff_ppsub->SetTextSize(0.05);
  leg_ff_ppsub->SetFillStyle(0);
  leg_ff_ppsub->SetTextFont(42);
  leg_ff_ppsub->AddEntry(clone_hgammaphoffxi_ppdata_,"pp #sqrt{s_{NN}}=5 TeV","p");
  leg_ff_ppsub->AddEntry(clone_hgammaphoffxi_ppmc50_,"Pythia #hat{p}_{T}=50","p");
  leg_ff_ppsub->AddEntry(clone_hgammaphoffxi_ppmc50_,"#eta cone sub","");
  leg_ff_ppsub->AddEntry(clone_hgammaphoffxi_ppmc50_,"trk p_{T}>1 GeV","");
  leg_ff_ppsub->AddEntry(clone_hgammaphoffxi_ppmc50_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_ppsub->Draw();
  // c1_subpp->SaveAs("ppdata_ppmc_etaconesubtracted_pho_45_gamma_100.png");
  // Eta cone subtracted FF ppdata and ppmc
  
  // PbPb - pp data and mc
  TCanvas * c1_pbpb_minus_pp = new TCanvas();
  TH2D * dummy_pbpb_minus_pp = new TH2D("dummy_pbpb_minus_pp",";#xi_{#gamma};dN/d#xi_{#gamma} PbPb-pp",1,0,5,1,-1.3,1.1);
  dummy_pbpb_minus_pp->GetXaxis()->CenterTitle();
  dummy_pbpb_minus_pp->GetYaxis()->CenterTitle();
  dummy_pbpb_minus_pp->GetYaxis()->SetTitleOffset(1.2);
  
  TH1D * clone2_hgammaphoffxi_pbpbdata_ = (TH1D*) clone_hgammaphoffxi_pbpbdata_->Clone("clone2_hgammaphoffxi_pbpbdata_");
  TH1D * clone2_hgammaphoffxi_pbpbmc50_ = (TH1D*) clone_hgammaphoffxi_pbpbmc50_->Clone("clone2_hgammaphoffxi_pbpbmc50_");
  TH1D * clone2_hgammaphoffxi_ppdata_ = (TH1D*) clone_hgammaphoffxi_ppdata_->Clone("clone2_hgammaphoffxi_ppdata_");
  clone2_hgammaphoffxi_ppdata_->Scale(-1);
  TH1D * clone2_hgammaphoffxi_ppmc50_ = (TH1D*) clone_hgammaphoffxi_ppmc50_->Clone("clone2_hgammaphoffxi_ppmc50_");
  clone2_hgammaphoffxi_ppmc50_->Scale(-1);
  
  clone2_hgammaphoffxi_pbpbdata_->Add(clone2_hgammaphoffxi_ppdata_);
  clone2_hgammaphoffxi_pbpbmc50_->Add(clone2_hgammaphoffxi_ppmc50_);
  
  dummy_pbpb_minus_pp->Draw();
  clone2_hgammaphoffxi_pbpbdata_->Draw("same");
  clone2_hgammaphoffxi_pbpbmc50_->Draw("same");
  TLine * lzero = new TLine(0,0,5,0);
  lzero->SetLineStyle(9);
  lzero->Draw();

  TLegend * leg_ff_pbpb_minus_pp = new TLegend(0.23,0.59,0.50,0.92);
  leg_ff_pbpb_minus_pp->SetFillColor(0);
  leg_ff_pbpb_minus_pp->SetTextSize(0.05);
  leg_ff_pbpb_minus_pp->SetFillStyle(0);
  leg_ff_pbpb_minus_pp->SetTextFont(42);
  leg_ff_pbpb_minus_pp->AddEntry(clone_hgammaphoffxi_ppdata_,"PbPb - pp #sqrt{s}=5 TeV","p");
  leg_ff_pbpb_minus_pp->AddEntry(clone_hgammaphoffxi_ppmc50_,"Pythia+Hydjet - Pythia ","p");
  leg_ff_pbpb_minus_pp->AddEntry(clone_hgammaphoffxi_ppmc50_,"#hat{p}_{T}=50","");
  leg_ff_pbpb_minus_pp->AddEntry(clone_hgammaphoffxi_ppmc50_,"trk p_{T}>1 GeV","");
  leg_ff_pbpb_minus_pp->AddEntry(clone_hgammaphoffxi_ppmc50_,"45>#gamma p_{T}>100 GeV","");
  leg_ff_pbpb_minus_pp->Draw();
  c1_pbpb_minus_pp->SaveAs("pbpb_minus_pp_pho_45_gamma_100.png");
  // PbPb - pp data and mc
  
}

