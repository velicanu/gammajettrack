{
  bool save1dstuff = false;
  string thistype = "mm";
  // both.azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_3.azsigmon-HIRun2015E-PromptReco-AOD-DimuonSkim-Mass40-v3_forest_csjet_v1_2.root
  // both.PromptReco-AOD-DielectronSkim-262274-262328_ppFOREST_v24.PromptReco-AOD-DimuonSkim-Mass40-262274-262328_ppFOREST_v24.root

  // g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root
  // g.pp-photonHLTFilter-v0-HiForest.root
  // TFile * ppfile = TFile::Open("/home/ursu/g.pp-photonHLTFilter-v0-HiForest.root");
  // TFile * pbpbfile = TFile::Open("/home/ursu/g.newtrkcuts.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root");
  // TFile * pbpbfile = TFile::Open("/home/ursu/g.noiso.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root");
  // TFile * pbpbfile = TFile::Open("/home/ursu/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v3.root");

  TFile * ppfile = TFile::Open("/home/ursu/g.pp-photonHLTFilter-v0-HiForest-newphosel-fix.root");
  TFile * pbpbfile = TFile::Open("/home/ursu/g.HIPhoton40AndZ-PbPb-photonHLTFilter-v12.root");

  TTree * ppztree = (TTree*) ppfile->Get("ztree");
  TTree * pbpbztree = (TTree*) pbpbfile->Get("ztree");

  const int ntrkcuts = 6;

  // int trkptcuts [ntrkcuts] = {4,8};
  float trkptmin [ntrkcuts] = {0.5,1,2,3,4,8};
  float trkptmax [ntrkcuts] = {1,2,3,4,8,1000};
  // float trkptmin [ntrkcuts] = {0.5,1,2,3,8,20};
  // float trkptmax [ntrkcuts] = {1,2,3,4,20,1000};
  int zptcuts   [2] = {100, 60};
  float ymins [2] = {0,0};
  float subymins [2] = {-1,-1};
  float ymaxs [2] = {6,3};
  float subymaxs [2] = {5,2};
  int histcolors [ntrkcuts] = {TColor::GetColor("#9999FF"),TColor::GetColor("#FFFF99"),TColor::GetColor("#FF9933"),TColor::GetColor("#9933CC"),TColor::GetColor("#006600"),TColor::GetColor("#CC0000")};
  TH1D * hppzdphi [2][ntrkcuts];
  TH1D * clone_hppzdphi [2][ntrkcuts];
  TH1D * hsubppzdphi [2][ntrkcuts];
  TH1D * hpbpbzdphi [2][ntrkcuts];
  TH1D * hsubppzdphinorm [2][ntrkcuts];
  TH1D * hsubpbpbzdphinorm [2][ntrkcuts];
  TH1D * clone_hpbpbzdphi [2][ntrkcuts];
  TH1D * hsubpbpbzdphi [2][ntrkcuts];
  TF1 * flat[2][ntrkcuts][2]; // [izcut][itrkcut][pp or PbPb]
  string collision[2] = {"pp","PbPb"};
  int linestyle[2] = {2,1};
  TCanvas * canvases1D [2][ntrkcuts];
  TCanvas * canvases [2][ntrkcuts];
  TCanvas * clone_canvases [2][ntrkcuts];
  TCanvas * subcanvases [2][ntrkcuts];
  TCanvas * stackedcanvasepp [2];
  TCanvas * stackedcanvasepbpb [2];
  TCanvas * stacked_pbpbp_pp [2];
  THStack * hspp[2];
  THStack * hspbpb[2];
  THStack * hsppnorm[2];
  THStack * hspbpbnorm[2];
  TH2D * dummydphi[2];
  int itrkstart = 5;
  for(int izcut = 1 ; izcut < 2 ; ++izcut)
  {
    for(int itrkcut = itrkstart ; itrkcut < ntrkcuts ; ++itrkcut)
    {

      hppzdphi[izcut][itrkcut] = new TH1D(Form("hppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),";#gamma-trk #Delta#phi",12,0,3.1415);
      hpbpbzdphi[izcut][itrkcut] = new TH1D(Form("hpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),";#gamma-trk #Delta#phi",12,0,3.1415);
      int nppzpassingcuts = ppztree->Draw("phoEt[0]",Form("phoEt[0]>%d",zptcuts[izcut]),"goff");
      int npbpbzpassingcuts = pbpbztree->Draw("phoEt[0]",Form("phoEt[0]>%d",zptcuts[izcut]),"goff");
      float ppbinwidth   = hppzdphi[izcut][itrkcut]->GetBinWidth(1);
      float pbpbbinwidth = hpbpbzdphi[izcut][itrkcut]->GetBinWidth(1);
      // ppztree->Draw(Form("acos(cos(phoPhi[0] - trkPhi))>>hppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),Form("(phoEt[0]>%d && trkPt>%2.1f && trkPt<%2.1f)*trkPt*highPurity",zptcuts[izcut],trkptmin[itrkcut],trkptmax[itrkcut]),"goff");
      // pbpbztree->Draw(Form("acos(cos(phoPhi[0] - trkPhi))>>hpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),Form("(phoEt[0]>%d && trkPt>%2.1f && trkPt<%2.1f)*trkPt*highPurity",zptcuts[izcut],trkptmin[itrkcut],trkptmax[itrkcut]),"goff");
      ppztree->Draw(Form("acos(cos(phoPhi[0] - trkPhi))>>hppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),Form("(phoEt[0]>%d && trkPt>%2.1f && trkPt<%2.1f)*trkPt*highPurity*trkWeight",zptcuts[izcut],trkptmin[itrkcut],trkptmax[itrkcut]),"goff");
      pbpbztree->Draw(Form("acos(cos(phoPhi[0] - trkPhi))>>hpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])),Form("(phoEt[0]>%d && trkPt>%2.1f && trkPt<%2.1f)*trkPt*highPurity*trkWeight",zptcuts[izcut],trkptmin[itrkcut],trkptmax[itrkcut]),"goff");
      hppzdphi[izcut][itrkcut]->Sumw2();
      hppzdphi[izcut][itrkcut]->SetMarkerStyle(24);
      hpbpbzdphi[izcut][itrkcut]->Sumw2();

      hppzdphi[izcut][itrkcut]->Scale(1.0/(float)nppzpassingcuts/ppbinwidth);
      hpbpbzdphi[izcut][itrkcut]->Scale(1.0/(float)npbpbzpassingcuts/pbpbbinwidth);

      hsubppzdphi[izcut][itrkcut] = (TH1D*) hppzdphi[izcut][itrkcut]->Clone(Form("hsubppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      hsubpbpbzdphi[izcut][itrkcut] = (TH1D*) hpbpbzdphi[izcut][itrkcut]->Clone(Form("hsubpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      

      
      canvases[izcut][itrkcut] = new TCanvas();
      float maxvalue = hppzdphi[izcut][itrkcut]->GetMaximum();
      if( hpbpbzdphi[izcut][itrkcut]->GetMaximum() > maxvalue ) maxvalue = hpbpbzdphi[izcut][itrkcut]->GetMaximum();
      float minvalue = hppzdphi[izcut][itrkcut]->GetMinimum();
      if( hpbpbzdphi[izcut][itrkcut]->GetMinimum() < minvalue ) minvalue = hpbpbzdphi[izcut][itrkcut]->GetMinimum();

      TH2D * dummy = new TH2D("dummy",";#gamma-trk #Delta#phi;#frac{1}{N_{#gamma}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,minvalue-1,maxvalue+1);
      dummy->GetXaxis()->CenterTitle();
      dummy->GetYaxis()->CenterTitle();
      dummy->GetYaxis()->SetTitleOffset(1.25);
      TH2D * subdummy = new TH2D("subdummy",";#gamma-trk #Delta#phi;subtracted #frac{1}{N_{#gamma}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,-4,13);
      subdummy->GetXaxis()->CenterTitle();
      subdummy->GetYaxis()->CenterTitle();
      subdummy->GetYaxis()->SetTitleOffset(1.25);

      //canvases1D[izcut][itrkcut] = new TCanvas(Form("canvas1D_%d_%d",izcut,itrkcut));
      for(int icoll = 0 ; icoll < 2 ; ++icoll)
      {
        flat[izcut][itrkcut][icoll] = new TF1(Form("flat_%s",collision[icoll].data()),"[0]", 0, TMath::Pi());
        flat[izcut][itrkcut][icoll]->SetParameter(0,0);
        if(icoll==0)
        {
          hppzdphi[izcut][itrkcut]->Fit(Form("flat_%s",collision[icoll].data()),"0","",0, TMath::Pi()/2.0);
        }
        else
        {
          hpbpbzdphi[izcut][itrkcut]->Fit(Form("flat_%s",collision[icoll].data()),"0","",0, TMath::Pi()/2.0);
        }
        flat[izcut][itrkcut][icoll]->SetLineStyle(linestyle[icoll]);
        // flat[izcut][itrkcut][icoll]->Draw("same");
      }

      TLegend * leg = new TLegend(0.45,0.58,0.75,0.9);
      leg->AddEntry(hpbpbzdphi[izcut][itrkcut],"#sqrt{s_{NN}}=5TeV PbPb","lp");
      leg->AddEntry(hppzdphi[izcut][itrkcut],"#sqrt{s}   =5TeV pp","lp");
      leg->AddEntry(hppzdphi[izcut][itrkcut],Form("#gamma p_{T}>%d GeV",zptcuts[izcut]),"");
      leg->AddEntry(hppzdphi[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV",trkptmin[itrkcut],trkptmax[itrkcut]),"");
      // leg->AddEntry(hppzdphi[izcut][itrkcut],Form("80<Zmass<110 GeV"),"");
      leg->SetFillColor(0);
      leg->SetTextSize(0.05);
      leg->SetFillStyle(0);
      leg->SetTextFont(42);

      TLatex * lint = new TLatex(.22,0.95,"CMS Preliminary");
      lint->SetNDC();
      TLatex * lztype = new TLatex(.52,0.95,Form("%d pp, %d PbPb #gamma",nppzpassingcuts,npbpbzpassingcuts));
      // TLatex * lztype = new TLatex(.52,0.95,Form("%d pp, %d PbPb Z-#mu#mu",nppzpassingcuts,npbpbzpassingcuts));
      lztype->SetNDC();
      if(save1dstuff)
      {
        dummy->Draw();
        hppzdphi[izcut][itrkcut]->Draw("same");
        hpbpbzdphi[izcut][itrkcut]->Draw("same");
        leg->Draw();
        lztype->Draw();
        lint->Draw();
        canvases[izcut][itrkcut]->SaveAs(Form("gtrkdphi_%d_%d_%d_%s.png",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut]),thistype.data()));
      }
      



      subcanvases[izcut][itrkcut] = new TCanvas();
      for(int ibin = 0 ; ibin < hsubppzdphi[izcut][itrkcut]->GetNbinsX()+1 ; ++ibin)
      {
        hsubppzdphi[izcut][itrkcut]->SetBinContent(ibin,hppzdphi[izcut][itrkcut]->GetBinContent(ibin) - flat[izcut][itrkcut][0]->Eval(1.0));
        hsubpbpbzdphi[izcut][itrkcut]->SetBinContent(ibin,hpbpbzdphi[izcut][itrkcut]->GetBinContent(ibin) - flat[izcut][itrkcut][1]->Eval(1.0));
      }
      if(save1dstuff)
      {
        subdummy->Draw();
        hsubppzdphi[izcut][itrkcut]->Draw("same");
        hsubpbpbzdphi[izcut][itrkcut]->Draw("same");
        leg->Draw();
        lint->Draw();
        lztype->Draw();
        TLine * lzero = new TLine(0,0,TMath::Pi(),0);
        lzero->SetLineStyle(9);
        lzero->Draw();
        subcanvases[izcut][itrkcut]->SaveAs(Form("sub_gtrkdphi_%d_%d_%d_%s.png",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut]),thistype.data()));
      }

      hsubppzdphinorm[izcut][itrkcut] = (TH1D*) hsubppzdphi[izcut][itrkcut]->Clone(Form("hsubppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      hsubpbpbzdphinorm[izcut][itrkcut] = (TH1D*) hsubpbpbzdphi[izcut][itrkcut]->Clone(Form("hsubpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      float histscalepp = hsubppzdphinorm[izcut][itrkcut]->Integral();
      float histscalepbpb = hsubpbpbzdphinorm[izcut][itrkcut]->Integral();
      hsubppzdphinorm[izcut][itrkcut]->Scale(1/histscalepp);
      hsubpbpbzdphinorm[izcut][itrkcut]->Scale(1/histscalepbpb);

      
      clone_canvases [izcut][itrkcut]  = new TCanvas();


      TH2D * ratiodummy = new TH2D("ratiodummy",";#gamma-trk #Delta#phi;PbPb/pp",1,0,3.1415,1,0,3);
      ratiodummy->GetXaxis()->CenterTitle();
      ratiodummy->GetYaxis()->CenterTitle();
      ratiodummy->GetYaxis()->SetTitleOffset(1.25);

      clone_hppzdphi[izcut][itrkcut] = (TH1D*) hppzdphi[izcut][itrkcut]->Clone(Form("clone_hppzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      clone_hpbpbzdphi[izcut][itrkcut] = (TH1D*) hpbpbzdphi[izcut][itrkcut]->Clone(Form("clone_hpbpbzdphi_%d_%d_%d",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut])));
      clone_hpbpbzdphi[izcut][itrkcut]->Divide(clone_hppzdphi[izcut][itrkcut]);
      
      ///
      TLegend * leg2 = new TLegend(0.45,0.58,0.75,0.9);
      leg2->AddEntry(clone_hpbpbzdphi[izcut][itrkcut],"#sqrt{s_{NN}}=5TeV PbPb","lp");
      // leg2->AddEntry(hppzdphi[izcut][itrkcut],"#sqrt{s}   =5TeV pp","lp");
      leg2->AddEntry(hppzdphi[izcut][itrkcut],Form("#gamma p_{T}>%d GeV",zptcuts[izcut]),"");
      leg2->AddEntry(hppzdphi[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV",trkptmin[itrkcut],trkptmax[itrkcut]),"");
      leg2->SetFillColor(0);
      leg2->SetTextSize(0.05);
      leg2->SetFillStyle(0);
      leg2->SetTextFont(42);

      if(save1dstuff)
      {
        ratiodummy->Draw();
        clone_hpbpbzdphi[izcut][itrkcut]->Draw("same");
        leg2->Draw();


        lint->Draw();
        lztype->Draw();

        lint->Draw();
        lztype->Draw();
        TLine * lone = new TLine(0,1,TMath::Pi(),1);
        lone->SetLineStyle(9);
        lone->Draw();
        clone_canvases[izcut][itrkcut]->SaveAs(Form("ratio_gtrkdphi_%d_%d_%d_%s.png",zptcuts[izcut],int(trkptmin[itrkcut]),int(trkptmax[itrkcut]),thistype.data()));
      }
      ///
    }
    // continue;
    stackedcanvasepp[izcut] = new TCanvas();
    hspp[izcut] = new THStack(Form("hspp_%d",zptcuts[izcut]),"");
    hsppnorm[izcut] = new THStack(Form("hsppnorm_%d",zptcuts[izcut]),"");

    TLegend * leg = new TLegend(0.25,0.45,0.55,0.9);
    leg->SetFillColor(0);
    leg->SetTextSize(0.05);
    leg->SetFillStyle(0);
    leg->SetTextFont(42);


    TLatex * lint = new TLatex(.22,0.95,"CMS Preliminary");
    lint->SetNDC();
    TLatex * lztype = new TLatex(.52,0.95,Form("pp #gamma"));
    // TLatex * lztype = new TLatex(.52,0.95,Form("%d pp, %d PbPb Z-#mu#mu",nppzpassingcuts,npbpbzpassingcuts));
    lztype->SetNDC();

    for(int itrkcut = itrkstart ; itrkcut < ntrkcuts ; ++itrkcut)
    {
      hsubppzdphi[izcut][itrkcut]->SetFillColor(histcolors[itrkcut]);
      hspp[izcut]->Add(hsubppzdphi[izcut][itrkcut]);
      leg->AddEntry(hsubppzdphi[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV",trkptmin[itrkcut],trkptmax[itrkcut]),"fl");
    }
    leg->AddEntry(hppzdphi[izcut][itrkstart],Form("#gamma p_{T}>%d GeV",zptcuts[izcut]),"");
    // leg->AddEntry(hppzdphi[izcut][itrkstart],Form("80<Zmass<110 GeV"),"");

    // hspp[izcut]->GetXaxis()->SetTitle("Z-trk #Delta#phi");
    dummydphi[izcut] = new TH2D("dummydphi",";#gamma-trk #Delta#phi;#frac{1}{N_{#gamma}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,-10,160);
    dummydphi[izcut]->GetXaxis()->CenterTitle();
    dummydphi[izcut]->GetYaxis()->CenterTitle();
    dummydphi[izcut]->GetYaxis()->SetTitleOffset(1.25);

    dummydphi[izcut]->Draw();
    hspp[izcut]->Draw("hist same");
    hspp[izcut]->Draw("pe same");
    lint->Draw();
    leg->Draw();
    lztype->Draw();
    stackedcanvasepp[izcut]->SaveAs(Form("sub_gtrkdphi_stacked_pp_%d_data.png",zptcuts[izcut]));

    stackedcanvasepbpb[izcut] = new TCanvas();

    hspbpb[izcut] = new THStack(Form("hspbpb_%d",zptcuts[izcut]),"");
    hspbpbnorm[izcut] = new THStack(Form("hspbpbnorm_%d",zptcuts[izcut]),"");
    TLegend * legpbpb = new TLegend(0.25,0.45,0.55,0.9);
    legpbpb->SetFillColor(0);
    legpbpb->SetTextSize(0.05);
    legpbpb->SetFillStyle(0);
    legpbpb->SetTextFont(42);
    TLatex * lztypepbpb = new TLatex(.52,0.95,Form("PbPb #gamma"));
    // TLatex * lztype = new TLatex(.52,0.95,Form("%d pbpb, %d PbPb Z-#mu#mu",npbpbzpassingcuts,npbpbzpassingcuts));
    lztypepbpb->SetNDC();

    for(int itrkcut = itrkstart ; itrkcut < ntrkcuts ; ++itrkcut)
    {
      hsubpbpbzdphi[izcut][itrkcut]->SetFillColor(histcolors[itrkcut]);
      hspbpb[izcut]->Add(hsubpbpbzdphi[izcut][itrkcut]);
      legpbpb->AddEntry(hsubpbpbzdphi[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV",trkptmin[itrkcut],trkptmax[itrkcut]),"fl");
    }
    legpbpb->AddEntry(hpbpbzdphi[izcut][itrkstart],Form("#gamma p_{T}>%d GeV",zptcuts[izcut]),"");
    //legpbpb->AddEntry(hpbpbzdphi[izcut][itrkstart],Form("80<Zmass<110 GeV"),"");

    dummydphi[izcut]->Draw();
    hspbpb[izcut]->Draw("hist same");
    hspbpb[izcut]->Draw("pe same");
    lint->Draw();
    legpbpb->Draw();
    lztypepbpb->Draw();
    stackedcanvasepbpb[izcut]->SaveAs(Form("sub_gtrkdphi_stacked_pbpb_%d_data.png",zptcuts[izcut]));
    // break;
    
    
    
    
    stacked_pbpbp_pp[izcut] = new TCanvas();
    TLegend * legnorm = new TLegend(0.25,0.45,0.55,0.9);
    legnorm->SetFillColor(0);
    legnorm->SetTextSize(0.05);
    legnorm->SetFillStyle(0);
    legnorm->SetTextFont(42);
    for(int itrkcut = itrkstart ; itrkcut < ntrkcuts ; ++itrkcut)
    {
      hsubppzdphinorm[izcut][itrkcut]->SetFillColor(histcolors[itrkcut]);
      hsubppzdphinorm[izcut][itrkcut]->SetFillStyle(3325);
      hsppnorm[izcut]->Add(hsubppzdphinorm[izcut][itrkcut]);
      legnorm->AddEntry(hsubppzdphinorm[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV pp",trkptmin[itrkcut],trkptmax[itrkcut]),"fl");
    }
    for(int itrkcut = itrkstart ; itrkcut < ntrkcuts ; ++itrkcut)
    {
      hsubpbpbzdphinorm[izcut][itrkcut]->SetMarkerColor(histcolors[itrkcut]);
      // hsubpbpbzdphinorm[izcut][itrkcut]->SetFillStyle(3325);
      hspbpbnorm[izcut]->Add(hsubpbpbzdphinorm[izcut][itrkcut]);
      legnorm->AddEntry(hsubpbpbzdphinorm[izcut][itrkcut],Form("%2.1f<trk p_{T}<%2.1f GeV pbpb",trkptmin[itrkcut],trkptmax[itrkcut]),"p");
    }
    
    legnorm->AddEntry(hppzdphi[izcut][itrkstart],Form("#gamma p_{T}>%d GeV",zptcuts[izcut]),"");
    dummydphi[izcut] = new TH2D("dummydphi",";#gamma-trk #Delta#phi;#frac{1}{N_{#gamma}} #frac{dN}{d#Delta#phi}",1,0,3.1415,1,0.001,1.5);
    dummydphi[izcut]->GetXaxis()->CenterTitle();
    dummydphi[izcut]->GetYaxis()->CenterTitle();
    dummydphi[izcut]->GetYaxis()->SetTitleOffset(1.25);

    dummydphi[izcut]->Draw();
    hsppnorm[izcut]->Draw("hist same");
    hspbpbnorm[izcut]->Draw("pe same");
    lint->Draw();
    legnorm->Draw();
    lztype->Draw();
    stacked_pbpbp_pp[izcut]->SetLogy(1);
    
  }
}
