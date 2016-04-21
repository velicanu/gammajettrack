{
  // TFile *_file0 = TFile::Open("/home/ursu/z.PromptReco-AOD-DielectronSkim-262274-262328_ppFOREST_v24.root");
  // TFile *_file1 = TFile::Open("/home/ursu/z.azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_2.root");
  TFile *_file0 = TFile::Open("/home/ursu/z.PromptReco-AOD-DimuonSkim-Mass40-262274-262328_ppFOREST_v24.root");
  TFile *_file1 = TFile::Open("/home/ursu/z.azsigmon-HIRun2015E-PromptReco-AOD-DimuonSkim-Mass40-v3_forest_csjet_v1_2.root");
  
  TTree * ppztree = (TTree*) _file0->Get("ztree");
  TTree * pbpbztree = (TTree*) _file1->Get("ztree");
  
  int trkptcuts [2] = {4,8};
  int zptcuts   [2] = {20,  40};
  float ymins [2] = {0,0};
  float ymaxs [2] = {1.5,0.4};
  TH1D * hppzdphi [2][2];
  TH1D * hpbpbzdphi [2][2];
  TCanvas * canvases [2][2];
  for(int izcut = 0 ; izcut < 2 ; ++izcut)
  {
    for(int itrkcut = 0 ; itrkcut < 2 ; ++itrkcut)
    {
      
      hppzdphi[izcut][itrkcut] = new TH1D(Form("hppzdphi_%d_%d",zptcuts[izcut],trkptcuts[itrkcut]),";Z-trk #Delta#phi",12,0,3.1415);
      hpbpbzdphi[izcut][itrkcut] = new TH1D(Form("hpbpbzdphi_%d_%d",zptcuts[izcut],trkptcuts[itrkcut]),";Z-trk #Delta#phi",12,0,3.1415);
      int nppzpassingcuts = ppztree->Draw("Zpt",Form("Zpt>%d",zptcuts[izcut]),"goff");
      int npbpbzpassingcuts = pbpbztree->Draw("Zpt",Form("Zpt>%d",zptcuts[izcut]),"goff");
      
      ppztree->Draw(Form("acos(cos(Zphi - trkPhi))>>hppzdphi_%d_%d",zptcuts[izcut],trkptcuts[itrkcut]),Form("Zpt>%d&&trkPt>%d",zptcuts[izcut],trkptcuts[itrkcut]),"goff");
      pbpbztree->Draw(Form("acos(cos(Zphi - trkPhi))>>hpbpbzdphi_%d_%d",zptcuts[izcut],trkptcuts[itrkcut]),Form("Zpt>%d&&trkPt>%d",zptcuts[izcut],trkptcuts[itrkcut]),"goff");
      hppzdphi[izcut][itrkcut]->Sumw2();
      hppzdphi[izcut][itrkcut]->SetMarkerStyle(24);
      hpbpbzdphi[izcut][itrkcut]->Sumw2();
      
      hppzdphi[izcut][itrkcut]->Scale(1.0/(float)nppzpassingcuts);
      hpbpbzdphi[izcut][itrkcut]->Scale(1.0/(float)npbpbzpassingcuts);
      
      
      
      canvases[izcut][itrkcut] = new TCanvas();
      TH2D * dummy = new TH2D("dummy",";Z-trk #Delta#phi;#frac{1}{N_{Z}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,0.01+ymins[itrkcut],-0.01+ymaxs[itrkcut]);
      dummy->GetXaxis()->CenterTitle();
      dummy->GetYaxis()->CenterTitle();
      dummy->GetYaxis()->SetTitleOffset(1.25);
      
      // TCanvas c2;
      dummy->Draw();
      hppzdphi[izcut][itrkcut]->Draw("same");
      hpbpbzdphi[izcut][itrkcut]->Draw("same");
      
      TLegend * leg = new TLegend(0.45,0.64,0.75,0.9);
      leg->AddEntry(hpbpbzdphi[izcut][itrkcut],"#sqrt{s_{NN}}=5TeV PbPb","lp");
      leg->AddEntry(hppzdphi[izcut][itrkcut],"#sqrt{s}   =5TeV pp","lp");
      leg->AddEntry(hppzdphi[izcut][itrkcut],Form("Z p_{T}>%d GeV",zptcuts[izcut]),"");
      leg->AddEntry(hppzdphi[izcut][itrkcut],Form("trk p_{T}>%d GeV",trkptcuts[itrkcut]),"");
      leg->SetFillColor(0);
      leg->SetTextSize(0.05);
      leg->SetFillStyle(0);
      leg->SetTextFont(42);
      leg->Draw();

      
      TLatex * lint = new TLatex(.22,0.95,"CMS Preliminary");
      lint->SetNDC();
      lint->Draw();
      // TLatex * lztype = new TLatex(.52,0.95,Form("%d pp, %d PbPb Z-ee",nppzpassingcuts,npbpbzpassingcuts));
      TLatex * lztype = new TLatex(.52,0.95,Form("%d pp, %d PbPb Z-#mu#mu",nppzpassingcuts,npbpbzpassingcuts));
      lztype->SetNDC();
      lztype->Draw();
      
      canvases[izcut][itrkcut]->SaveAs(Form("ztrkdphi_%d_%d.png",zptcuts[izcut],trkptcuts[itrkcut]));
    }
  }
}
