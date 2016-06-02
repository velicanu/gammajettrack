{
  TFile *_file0 = TFile::Open("all.root");
  int save = 1;
  // BinWidth = 2.000000e-02
  
  TCanvas * cff[3][5];
  string sjetbins[3] = {"30_40","40_60","60_100"};
  string sjetname[3] = {"30<jet p_{T}<40","40<jet p_{T}<60","60<jet p_{T}<100"};
  int ipfbins[5] = {1,2,3,991,990};
  string spfnames[5] = {"pfType=1","pfType=2","pfType=3","pfType=-1","all tracks",};
  for(int ijet = 0 ; ijet < 3 ; ++ijet)
  {
    TH1D * hjetpt_pbpbdatamb = (TH1D*) _file0->Get(Form("hjetpt_pbpbdatamb_jt%s",sjetbins[ijet].data()));
    TH1D * hjetpt_pbpbmc30 = (TH1D*) _file0->Get(Form("hjetpt_pbpbmc30_jt%s",sjetbins[ijet].data()));
    for(int ipf = 0 ; ipf < 5 ; ++ipf)
    {
      cff[ijet][ipf] = new TCanvas(Form("cff_pf%d_jt%s",ipfbins[ipf],sjetbins[ijet].data()));
      cff[ijet][ipf]->SetLogy();
      cff[ijet][ipf]->SetLogx();
      TH1D * hfragFunctIn_pbpbdatamb = (TH1D*) _file0->Get(Form("hfragFunctIn_pbpbdatamb_pf%d_jt%s",ipfbins[ipf],sjetbins[ijet].data()));
      TH1D * hfragFunctIn_pbpbmc30 = (TH1D*) _file0->Get(Form("hfragFunctIn_pbpbmc30_pf%d_jt%s",ipfbins[ipf],sjetbins[ijet].data()));
      float njet_hfragFunctIn_pbpbdatamb = hjetpt_pbpbdatamb->Integral();
      float njet_hfragFunctIn_pbpbmc30 = hjetpt_pbpbmc30->Integral();
      hfragFunctIn_pbpbdatamb->Sumw2();
      hfragFunctIn_pbpbdatamb->Scale(1.0/2.000000e-02/njet_hfragFunctIn_pbpbdatamb);
      hfragFunctIn_pbpbdatamb->SetAxisRange(1e-05,1e02,"Y");
      hfragFunctIn_pbpbdatamb->GetYaxis()->SetTitle("1/N_{jet} dN/dz");
      hfragFunctIn_pbpbdatamb->SetTitleOffset(1.2,"Y");
      hfragFunctIn_pbpbdatamb->Draw("pe");
      hfragFunctIn_pbpbmc30->Sumw2();
      hfragFunctIn_pbpbmc30->Scale(1.0/2.000000e-02/njet_hfragFunctIn_pbpbmc30);
      hfragFunctIn_pbpbmc30->SetMarkerColor(2);
      hfragFunctIn_pbpbmc30->Draw("pesame");
      TLegend * leg_ff = new TLegend(0.50,0.68,0.78,0.93);
      leg_ff->SetFillColor(0);
      leg_ff->SetTextSize(0.05);
      leg_ff->SetFillStyle(0);
      leg_ff->SetTextFont(42);
      leg_ff->AddEntry(hfragFunctIn_pbpbdatamb,"PbPb MB #sqrt{s_{NN}}=5 TeV","p");
      leg_ff->AddEntry(hfragFunctIn_pbpbmc30,"#hat{p}_{T}=30 Pythia+Hydjet","p");
      leg_ff->AddEntry(hfragFunctIn_pbpbmc30,Form("%s, %s",spfnames[ipf].data(),sjetname[ijet].data()),"");
      leg_ff->Draw();
      if(save==1) cff[ijet][ipf]->SaveAs(Form("cff_pf%d_jt%s.png",ipfbins[ipf],sjetbins[ijet].data()));
    }
  }  
}

