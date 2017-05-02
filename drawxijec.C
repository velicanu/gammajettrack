{
  for(int phobin = 0 ; phobin < 2 ; phobin++) {
    for(int icorr = 0 ; icorr < 2 ; icorr++) {
      string acorr[] = {"","corr"};
      string corr = acorr[icorr];
      int phoetmin[] = {60,80};
      int jetptmin[] = {30,40};
      TFile *_file0 = TFile::Open(Form("closure_pbpb_%d_1000_%d_gammaxi0.root",phoetmin[phobin],jetptmin[phobin]));
      TH2D * hjecvsxi[4];
      TH1D * hjec[4][10];
      int centmin[] = {0,20,60,100};
      int centmax[] = {20,60,100,200};
      string scent[] = {"0-10%","10-30%","30-50%","50-100%"};
      TCanvas * c1[4][10];

      for(int icent = 0 ; icent < 4 ; icent++) {
	hjecvsxi[icent] = (TH2D*) _file0->Get(Form("hjecvsxi%s_pbpbmc_recoreco_%d_%d",corr.data(),centmin[icent],centmax[icent]));
	TH1D * hxijec = new TH1D(Form("hxijec%s_%d_%d",corr.data(),phoetmin[phobin],icent),Form(";%s   jet/gjet p_{T};%s   #gamma E_{T}>%d   jet p_{T}>%d",scent[icent].data(),corr.data(),phoetmin[phobin],jetptmin[phobin]),10,0,5);
	gStyle->SetOptStat(1);
	for(int ixi = 0 ; ixi < 10 ; ixi++) {
	  hjec[icent][ixi] = hjecvsxi[icent]->ProjectionY(Form("jec_%d_%d_%d",centmin[icent],centmax[icent],ixi),ixi,ixi+1);
	  cout<<Form("jec_%d_%d_%d: ",centmin[icent],centmax[icent],ixi)<<hjec[icent][ixi]->GetMean()<<endl;
	  c1[icent][ixi]  = new TCanvas();
	  hjec[icent][ixi]->GetXaxis()->SetTitle(Form("%s   jet/gjet p_{T}   %2.1f<#xi<%2.1f",scent[icent].data(),ixi/2.0,(ixi+1)/2.0));
	  hjec[icent][ixi]->GetYaxis()->SetTitle(Form("%s   #gamma E_{T}>%d   jet p_{T}>%d",corr.data(),phoetmin[phobin],jetptmin[phobin]));
	  hjec[icent][ixi]->Draw();
	  c1[icent][ixi]->SaveAs(Form("xijec%s_%d_%d_%d.png",corr.data(),phoetmin[phobin],icent,ixi));
	  hxijec->SetBinContent(ixi+1,hjec[icent][ixi]->GetMean());
	  hxijec->SetBinError(ixi+1,hjec[icent][ixi]->GetMeanError());
	}
	gStyle->SetOptStat(0);
	TCanvas * c2 = new TCanvas();
	hxijec->SetAxisRange(0.95,1.19,"Y");
	hxijec->Draw();
	c2->SaveAs(Form("hxijec%s_%d_%d.png",corr.data(),phoetmin[phobin],icent));
      }
    }
  }
}
