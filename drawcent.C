{
  TFile *_file0 = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v14.root");
  TFile *_file1 = TFile::Open("/export/d00/scratch/dav2105/ztrees/g.Pythia8_Photon_Hydjet_MB-HINPbPbWinter16DR-75X_mcRun2_HeavyIon_forest_v1.root");

  TCanvas * c1[4];
  TTree * zdata = (TTree*) _file0->Get("ztree");
  TTree * zmc = (TTree*) _file1->Get("ztree");
  TFile * fcentweight = new TFile("fcentweight.root","recreate");

  TH1D * hcentdata[4];
  TH1D * hcentmc[4];
  int centmin[] = {0,20,60,100};
  int centmax[] = {20,60,100,200};
  for(int icent = 0 ; icent < 4 ; ++icent)
  {
    hcentdata[icent] = new TH1D(Form("hcentdata_%d_%d",centmin[icent],centmax[icent]),";cent;",100,0,200);
    hcentmc[icent] = new TH1D(Form("hcentmc_%d_%d",centmin[icent],centmax[icent]),";cent;",100,0,200);
    zdata->Draw(Form("hiBin>>hcentdata_%d_%d",centmin[icent],centmax[icent]),Form("hiBin >= %d && hiBin < %d",centmin[icent],centmax[icent]));
    zmc->Draw(Form("hiBin>>hcentmc_%d_%d",centmin[icent],centmax[icent]),Form("hiBin >= %d && hiBin < %d",centmin[icent],centmax[icent]));    

    c1[icent] = new TCanvas();
    hcentdata[icent]->DrawNormalized();
    hcentmc[icent]->SetMarkerColor(kRed);
    hcentmc[icent]->DrawNormalized("same");

    TLegend * leg = new TLegend(0.25,0.73,0.55,0.87);
    leg->SetTextSize(0.05*1.3);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(42);

    leg->AddEntry(hcentdata[icent],"data","p");
    leg->AddEntry(hcentmc[icent],"mc","p");

    leg->Draw();
    c1[icent]->SaveAs(Form("data-mc-comparison-prenorm_%d_%d.png",centmin[icent],centmax[icent]));


    float ndataentries = hcentdata[icent]->GetEntries();
    float nmcentries = hcentmc[icent]->GetEntries();

    hcentdata[icent]->Scale(1.0/ndataentries);
    hcentmc[icent]->Scale(1.0/nmcentries);

    hcentdata[icent]->Divide(hcentmc[icent]);
    TCanvas * c2 = new TCanvas();
    hcentdata[icent]->Draw();

    TLegend * leg1 = new TLegend(0.25,0.73,0.55,0.87);
    leg1->SetTextSize(0.05*1.3);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->SetTextFont(42);

    leg1->AddEntry(hcentdata[icent],"weight","p");

    leg1->Draw();

    c2->SaveAs(Form("data-mc-centweight_%d_%d.png",centmin[icent],centmax[icent]));

  }
  fcentweight->Write();
  fcentweight->Close();
}
