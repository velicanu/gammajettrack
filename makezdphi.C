{
  TFile *_file0 = TFile::Open("/export/d00/scratch/dav2105/ztrees/z.PromptReco-AOD-DimuonSkim-Mass40-262274-262328_ppFOREST_v24.root");
  TFile *_file1 = TFile::Open("/export/d00/scratch/dav2105/ztrees/z.azsigmon-HIRun2015E-PromptReco-AOD-DimuonSkim-Mass40-v3_forest_csjet_v1_2.root");
  
  TTree * ppztree = (TTree*) _file0->Get("ztree");
  TTree * pbpbztree = (TTree*) _file1->Get("ztree");
  
  int trkptcuts [2] = {4,8};
  int zptcuts   [2] = {20,  40};
  TH1D * hppzdphi [2][2];
  TH1D * hpbpbzdphi [2][2];
  for(int izcut = 0 ; izcut < n ; ++izcut)
  {
    for(int itrkcut = 0 ; itrkcut < n ; ++itrkcut)
    {
      
      hppzdphi[izcut][itrkcut] = new TH1D(Form("hppzdphi_%d_%d"),";Z-trk #Delta#phi",12,0,3.1415);
      hpbpbzdphi[izcut][itrkcut] = new TH1D(Form("hpbpbzdphi_%d_%d"),";Z-trk #Delta#phi",12,0,3.1415);
      int nppzpassingcuts = ppztree->Draw("Zpt","Zpt>40","goff");
      int npbpbzpassingcuts = pbpbztree->Draw("Zpt","Zpt>40","goff");
      
      ppztree->Draw("acos(cos(Zphi - trkPhi))>>hppzdphi","Zpt>40&&trkPt>4","goff");
      pbpbztree->Draw("acos(cos(Zphi - trkPhi))>>hpbpbzdphi","Zpt>40&&trkPt>4","goff");
      
      hppzdphi->Sumw2();
      hppzdphi->SetMarkerStyle(24);
      hpbpbzdphi->Sumw2();
      
      hppzdphi->Scale(1.0/(float)nppzpassingcuts);
      hpbpbzdphi->Scale(1.0/(float)npbpbzpassingcuts);
      
      
      
      TCanvas c1;
      TH2D * dummy = new TH2D("dummy",";Z-trk #Delta#phi;#frac{1}{N_{Z}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,0.01,0.99);
      dummy->GetXaxis()->CenterTitle();
      dummy->GetYaxis()->CenterTitle();
      dummy->GetYaxis()->SetTitleOffset(1.25);
      
      // TCanvas c2;
      dummy->Draw();
      hppzdphi->Draw("same");
      hpbpbzdphi->Draw("same");
      
      TLegend * leg = new TLegend(0.45,0.64,0.75,0.9);
      leg->AddEntry(hpbpbzdphi,"#sqrt{s_{NN}}=5TeV PbPb","lp");
      leg->AddEntry(hppzdphi,"#sqrt{s}   =5TeV pp","lp");
      leg->AddEntry(hppzdphi,"Z p_{T}>40 GeV","");
      leg->AddEntry(hppzdphi,"trk p_{T}>4 GeV","");
      leg->SetFillColor(0);
      leg->SetTextSize(0.05);
      leg->SetFillStyle(0);
      leg->SetTextFont(42);
      leg->Draw();

      
      TLatex * lint = new TLatex(.22,0.95,"CMS Preliminary");
      lint->SetNDC();
      lint->Draw();
      TLatex * lztype = new TLatex(.82,0.95,"Z-#mu#mu");
      lztype->SetNDC();
      lztype->Draw();

    }
  }
}