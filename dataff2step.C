#include "makeMultiPanelCanvas.C"

//nominal

std::vector<float> purity_pbpbdata_60 = {0.681689, 0.730339, 0.775276, 0.825922};
std::vector<float> purity_ppdata_60 = {0.841322, 0.841322, 0.841322, 0.841322};
std::vector<float> purity_pbpbdata_80 = {0.685621, 0.751769, 0.787902, 0.816627};
std::vector<float> purity_ppdata_80 = {0.853694, 0.853694, 0.853694, 0.853694};

float getpurity(float phoetmin, int centbin, bool ispp)
{
  if(phoetmin==60) {
    if(ispp) {
      return purity_ppdata_60[0];
    } else {
      return purity_pbpbdata_60[centbin];
    }
  } else if(phoetmin==80) {
    if(ispp) {
      return purity_ppdata_80[0];
    } else {
      return purity_pbpbdata_80[centbin];
    }
  } else {
    std::cout<<"pho et currently not implemented"<<endl;
    exit(1);
  }
  return 1; //no purity applied
}

void dataff2step(int phoetmin, int phoetmax, int jetptmin = 30, int trkptcut = 4, int do_divide = 0, int gammaxi = 0, string inpath="./", string outfname = "outfile.root", int whichpurity = 0) {
  float uescale[] = {1,1, 0.97, 0.87};
  TFile *_file0 = TFile::Open(Form("%sall_%d_%d_%d_gammaxi%d.root",inpath.data(),phoetmin,phoetmax,jetptmin,gammaxi));
  const static int ncentbins = 4;
  const int yaxismax = 6000;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  int centscale[] = {1,1,5,20};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};
  TH1D * rawff_pbpbdata_recoreco[ncentbins];
  TH1D * rawffue_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmix_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixue_pbpbdata_recoreco[ncentbins];
  TH1D * hjetpt_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptjetmix_pbpbdata_recoreco[ncentbins];

  TH1D * rawffsideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffuesideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixsideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixuesideband_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptsideband_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptjetmixsideband_pbpbdata_recoreco[ncentbins];

  TH1D * rawff_ppdata_recoreco[ncentbins];
  TH1D * hjetpt_ppdata_recoreco[ncentbins];
  TH1D * rawffsideband_ppdata_recoreco[ncentbins];
  TH1D * hjetptsideband_ppdata_recoreco[ncentbins];

  TH1D * rawff_pbpbdata_gengen[ncentbins];
  TH1D * hgenjetpt_pbpbdata_gengen[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

  TFile * outf = new TFile(outfname.data(),"recreate");

  TCanvas * call = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {
    call->cd(2+icent);
    dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetYaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy_pbpbsub[icent]->Draw();

    rawff_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_pbpbdata_recoreco[icent]->Sumw2();
    rawffue_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffue_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmix_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmixue_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixue_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixue_pbpbdata_recoreco[icent]->Sumw2();
    rawffue_pbpbdata_recoreco[icent]->Scale(-1*uescale[icent]);
    rawffjetmixue_pbpbdata_recoreco[icent]->Scale(-1);
    rawff_pbpbdata_recoreco[icent]->Add(rawffue_pbpbdata_recoreco[icent]);
    rawffjetmix_pbpbdata_recoreco[icent]->Add(rawffjetmixue_pbpbdata_recoreco[icent]);
    // rawffjetmix_pbpbdata_recoreco[icent]->Scale(-1);
    // rawff_pbpbdata_recoreco[icent]->Add(rawffjetmix_pbpbdata_recoreco[icent]);

    hjetpt_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetpt_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjets = hjetpt_pbpbdata_recoreco[icent]->Integral();
    float nmixjets = hjetptjetmix_pbpbdata_recoreco[icent]->Integral();


    // rawff_pbpbdata_recoreco[icent]->Scale(1/(nrawjets-nmixjets));


    rawffsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffsideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffuesideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmixsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmixuesideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixuesideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixuesideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbdata_recoreco[icent]->Scale(-1*uescale[icent]);
    rawffjetmixuesideband_pbpbdata_recoreco[icent]->Scale(-1);
    // rawffsideband_pbpbdata_recoreco[icent]->Add(rawffuesideband_pbpbdata_recoreco[icent]);
    // rawffjetmixsideband_pbpbdata_recoreco[icent]->Add(rawffjetmixuesideband_pbpbdata_recoreco[icent]);
    rawffjetmixsideband_pbpbdata_recoreco[icent]->Scale(-1);
    // rawffsideband_pbpbdata_recoreco[icent]->Add(rawffjetmixsideband_pbpbdata_recoreco[icent]);

    hjetptsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmixsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjetssideband = hjetptsideband_pbpbdata_recoreco[icent]->Integral();
    float nmixjetssideband = hjetptjetmixsideband_pbpbdata_recoreco[icent]->Integral();


    rawffsideband_pbpbdata_recoreco[icent]->Scale(1/(nrawjetssideband-nmixjetssideband));
    rawffsideband_pbpbdata_recoreco[icent]->SetMarkerColor(kGreen);
    // rawffsideband_pbpbdata_recoreco[icent]->Draw("same");

    float purity   = getpurity(phoetmin,icent,false);
    rawff_pbpbdata_recoreco[icent]->Scale(1.0/purity);
    rawffsideband_pbpbdata_recoreco[icent]->Scale(-1.0*(1.0-purity)/purity);
    // rawff_pbpbdata_recoreco[icent]->Add(rawffsideband_pbpbdata_recoreco[icent]);



    // rawff_pbpbdata_gengen[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    // hgenjetpt_pbpbdata_gengen[icent] = (TH1D*)_file0->Get(Form("hgenjetpt_pbpbdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    // float ngenjets = hgenjetpt_pbpbdata_gengen[icent]->Integral();
    // rawff_pbpbdata_gengen[icent]->Scale(1/ngenjets);

    rawff_pbpbdata_recoreco[icent]->Draw("same");
    // rawff_pbpbdata_gengen[icent]->Draw("same");

    rawff_ppdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_ppdata_recoreco[icent]->Sumw2();
    hjetpt_ppdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetpt_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffsideband_ppdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffsideband_ppdata_recoreco[icent]->Sumw2();
    hjetptsideband_ppdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_ppdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    int minbin = hjetpt_ppdata_recoreco[icent]->FindBin(30);
    int maxbin = hjetpt_ppdata_recoreco[icent]->FindBin(500);
    nrawjets = hjetpt_ppdata_recoreco[icent]->Integral(minbin,maxbin);
    nrawjetssideband = hjetptsideband_ppdata_recoreco[icent]->Integral(minbin,maxbin);
    rawff_ppdata_recoreco[icent]->Scale(1.0/nrawjets);
    rawffsideband_ppdata_recoreco[icent]->Scale(1.0/nrawjetssideband);

    float pppurity = getpurity(phoetmin,icent,true);
    rawff_ppdata_recoreco[icent]->Scale(1.0/pppurity);
    rawffsideband_ppdata_recoreco[icent]->Scale(-1.0*(1.0-pppurity)/pppurity);
    // rawff_ppdata_recoreco[icent]->Add(rawffsideband_ppdata_recoreco[icent]);


    rawff_pbpbdata_recoreco[icent]->SetMarkerSize(2);
    rawff_ppdata_recoreco[icent]->SetMarkerSize(2);


    if(do_divide==0) {
      rawffjetmix_pbpbdata_recoreco[icent]->Scale(centscale[icent]);
      rawff_pbpbdata_recoreco[icent]->Scale(centscale[icent]);
      rawffjetmix_pbpbdata_recoreco[icent]->SetMarkerColor(kRed);
      rawffjetmix_pbpbdata_recoreco[icent]->Draw("same");
      rawff_pbpbdata_recoreco[icent]->Draw("same");
      rawff_ppdata_recoreco[icent]->SetMarkerColor(kRed);
      // rawff_ppdata_recoreco[icent]->Draw("same");
    } else {
      rawff_pbpbdata_recoreco[icent]->Divide(rawff_ppdata_recoreco[icent]);
      // rawff_pbpbdata_recoreco[icent]->Draw("same");
      TLine * lone = new TLine(0,1,5,1);
      lone->SetLineStyle(9);
      lone->Draw();
    }


    if(icent==0)
    {
      leg_ff_pbpbsub[icent] = new TLegend(0.03,0.697,0.3,0.92);
    }
    else
    {
      leg_ff_pbpbsub[icent] = new TLegend(0,0.697,0.27,0.92);
    }
    leg_ff_pbpbsub[icent]->SetTextSize(0.05*1.3);
    leg_ff_pbpbsub[icent]->SetFillColor(0);
    leg_ff_pbpbsub[icent]->SetFillStyle(0);
    leg_ff_pbpbsub[icent]->SetTextFont(42);
    if(icent==0)
    {
      if(do_divide==0) {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"Raw-UE PbPb FF","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawffjetmix_pbpbdata_recoreco[icent],"Fake-UE PbPb FF","p");
	leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("scale x%d",centscale[icent]),"");
      } else {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"PbPb/pp FF","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_ppdata_recoreco[icent],"","");
	leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("scale x%d",centscale[icent]),"");
      }
      // leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_gengen[icent],"Gen FF","l");
      // leg_ff_pbpbsub[icent]->AddEntry(rawffjetmix_pbpbdata_recoreco[icent],"Jet Mix FF","p");
      // leg_ff_pbpbsub[icent]->AddEntry(rawffue_pbpbdata_recoreco[icent],"Raw UE FF","p");
      // leg_ff_pbpbsub[icent]->AddEntry(rawffjetmixue_pbpbdata_recoreco[icent],"Jet Mix UE FF","p");
    }
    else if(icent==1)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("trk p_{T}>%d GeV, R < 0.3",trkptcut),"");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("scale x%d",centscale[icent]),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"|#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("scale x%d",centscale[icent]),"");
    }
    else if(icent==3)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"PbPb Data","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"#sigma_{i#eta#eta}<0.10","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("scale x%d",centscale[icent]),"");
    }
    leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();

    if(gammaxi==0) {
      rawff_pbpbdata_recoreco[icent]->GetYaxis()->SetTitle("dN/d#xi_{jet}");
      rawff_pbpbdata_recoreco[icent]->GetXaxis()->SetTitle("#xi_{jet}=-ln(p_{T}^{trk}/p_{T}^{jet})");
      rawff_ppdata_recoreco[icent]->GetYaxis()->SetTitle("dN/d#xi_{jet}");
      rawff_ppdata_recoreco[icent]->GetXaxis()->SetTitle("#xi_{jet}=-ln(p_{T}^{trk}/p_{T}^{jet})");
    } else {
      rawff_pbpbdata_recoreco[icent]->GetYaxis()->SetTitle("dN/d#xi_{#gamma}");
      rawff_pbpbdata_recoreco[icent]->GetXaxis()->SetTitle("#xi_{#gamma}=-ln(p_{T}^{trk}/E_{T}^{#gamma})");
      rawff_ppdata_recoreco[icent]->GetYaxis()->SetTitle("dN/d#xi_{#gamma}");
      rawff_ppdata_recoreco[icent]->GetXaxis()->SetTitle("#xi_{#gamma}=-ln(p_{T}^{trk}/E_{T}^{#gamma})");
    }
    // rawff_pbpbdata_recoreco[icent]->Write();
    // rawff_ppdata_recoreco[icent]->Write();

  }

  call->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi;
  if(gammaxi==0)
    ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{jet}");
  else
    ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{#gamma}");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.4);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  int labelspace = yaxismax / 4;
  const int nlabels = yaxismax/labelspace;
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    laxis[ilatex] = new TLatex(2.,ilatex*labelspace-0.1,Form("%d",ilatex*labelspace));
    laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
    laxis[ilatex]->Draw();
  }
  ldndxi->Draw();
  // if(do_divide==0) {
  //   call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d.png",phoetmin,phoetmax,jetptmin,gammaxi));
  //   call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  // } else {
  //   call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d_ratio.png",phoetmin,phoetmax,jetptmin,gammaxi));
  //   call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d_ratio.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  // }
  // outf->Close();
}
