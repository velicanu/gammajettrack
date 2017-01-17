{
  TFile *_file0 = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root");
  TFile *_file1 = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root");

  TCanvas * c1 = new TCanvas();

  TTree * zdata = (TTree*) _file0->Get("ztree");
  TTree * zmc = (TTree*) _file1->Get("ztree");
  TFile * fvzweight = new TFile("fvzweight.root","recreate");
  TH1D * hvzdata = new TH1D("hvzdata",";vz;",100,-17.5,17.5);
  TH1D * hvzmc = new TH1D("hvzmc",";vz;",100,-17.5,17.5);
  zdata->Draw("vz>>hvzdata");
  zmc->Draw("vz>>hvzmc");
  hvzdata->DrawNormalized();
  hvzmc->SetMarkerColor(kRed);
  hvzmc->DrawNormalized("same");

  TLegend * leg = new TLegend(0.25,0.73,0.55,0.87);
  leg->SetTextSize(0.05*1.3);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);

  leg->AddEntry(hvzdata,"data","p");
  leg->AddEntry(hvzmc,"mc","p");

  leg->Draw();

  c1->SaveAs("data-mc-comparison-prenorm.png");

  float ndataentries = hvzdata->GetEntries();
  float nmcentries = hvzmc->GetEntries();

  hvzdata->Scale(1.0/ndataentries);
  hvzmc->Scale(1.0/nmcentries);

  hvzdata->Divide(hvzmc);
  TCanvas * c2 = new TCanvas();
  hvzdata->Draw();

  TLegend * leg1 = new TLegend(0.25,0.73,0.55,0.87);
  leg1->SetTextSize(0.05*1.3);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->SetTextFont(42);

  leg1->AddEntry(hvzdata,"weight","p");

  leg1->Draw();

  c2->SaveAs("data-mc-vzweight.png");

  fvzweight->Write();
  fvzweight->Close();

}
