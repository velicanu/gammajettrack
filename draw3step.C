#include "makeMultiPanelCanvas.C"

std::vector<float> purity_pbpbmc_60  = {0.922658, 0.957185, 0.973422, 0.982594};
std::vector<float> purity_pbpbmc_80 = {0.92439, 0.957436, 0.96544, 0.980661};


float getpurity(float phoetmin, int centbin)
{
  if(phoetmin==60) {
    return purity_pbpbmc_60[centbin];
  } else if(phoetmin==80) {
    return purity_pbpbmc_80[centbin];
  } else {
    std::cout<<"pho et currently not implemented"<<endl;
    exit(1);
  }
  return 1; //no purity applied
}

void draw3step(int phoetmin, int phoetmax, int jetptmin = 30, int trkptcut = 4, int do_divide=0, int gammaxi = 0) {
  // float uescale[] = {1,1,1,1};
  float uescale[] = {1,1, 0.97, 0.87};
  gStyle->SetFrameLineColor(0);
  TFile *_file0 = TFile::Open(Form("closure_pbpb_%d_%d_%d_gammaxi%d.root",phoetmin,phoetmax,jetptmin,gammaxi));
  TFile *_fout = new TFile("pbpbmcff.root","recreate");
  const static int ncentbins = 4;
  float yaxismax = 4.0;
  float yaxismin = 0.0;
  if(do_divide==1) yaxismax = 1.5;
  if(do_divide==1) yaxismin = 0.5;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};
  TH1D * rawff_pbpbmc_recoreco[ncentbins];
  TH1D * rawffue_pbpbmc_recoreco[ncentbins];
  TH1D * rawffjetmix_pbpbmc_recoreco[ncentbins];
  TH1D * rawffjetmixue_pbpbmc_recoreco[ncentbins];
  TH1D * hjetpt_pbpbmc_recoreco[ncentbins];
  TH1D * hjetptjetmix_pbpbmc_recoreco[ncentbins];

  TH1D * rawffsideband_pbpbmc_recoreco[ncentbins];
  TH1D * rawffuesideband_pbpbmc_recoreco[ncentbins];
  TH1D * rawffjetmixsideband_pbpbmc_recoreco[ncentbins];
  TH1D * rawffjetmixuesideband_pbpbmc_recoreco[ncentbins];
  TH1D * hjetptsideband_pbpbmc_recoreco[ncentbins];
  TH1D * hjetptjetmixsideband_pbpbmc_recoreco[ncentbins];

  TH1D * rawff_pbpbmc_gengen0[ncentbins];
  TH1D * hgenjetpt_pbpbmc_gengen0[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

  TCanvas * call = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {
    call->cd(2+icent);
    if(gammaxi==0) {
      dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi_{jet};dN/d#xi",1,0.01,4.99,1,yaxismin,yaxismax);
    } else {
      dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi_{#gamma};dN/d#xi",1,0.01,4.99,1,yaxismin,yaxismax);
    }
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_pbpbsub[icent]->GetXaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetYaxis()->CenterTitle();
    dummy_pbpbsub[icent]->GetXaxis()->SetTitleSize(dummy_pbpbsub[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy_pbpbsub[icent]->Draw();

    rawff_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_pbpbmc_recoreco[icent]->Sumw2();
    rawffue_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffue_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmix_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmixue_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixue_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixue_pbpbmc_recoreco[icent]->Sumw2();
    rawffue_pbpbmc_recoreco[icent]->Scale(-1*uescale[icent]);
    rawffjetmixue_pbpbmc_recoreco[icent]->Scale(-1);
    rawff_pbpbmc_recoreco[icent]->Add(rawffue_pbpbmc_recoreco[icent]);
    rawffjetmix_pbpbmc_recoreco[icent]->Add(rawffjetmixue_pbpbmc_recoreco[icent]);
    rawffjetmix_pbpbmc_recoreco[icent]->Scale(-1);
    rawff_pbpbmc_recoreco[icent]->Add(rawffjetmix_pbpbmc_recoreco[icent]);

    hjetpt_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetpt_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjets = hjetpt_pbpbmc_recoreco[icent]->Integral();
    float nmixjets = hjetptjetmix_pbpbmc_recoreco[icent]->Integral();


    rawff_pbpbmc_recoreco[icent]->Scale(1/(nrawjets-nmixjets));


    rawffsideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffsideband_pbpbmc_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemixsideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffuesideband_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmixsideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixsideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmixuesideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixuesideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixuesideband_pbpbmc_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbmc_recoreco[icent]->Scale(-1*uescale[icent]);
    rawffjetmixuesideband_pbpbmc_recoreco[icent]->Scale(-1);
    rawffsideband_pbpbmc_recoreco[icent]->Add(rawffuesideband_pbpbmc_recoreco[icent]);
    rawffjetmixsideband_pbpbmc_recoreco[icent]->Add(rawffjetmixuesideband_pbpbmc_recoreco[icent]);
    rawffjetmixsideband_pbpbmc_recoreco[icent]->Scale(-1);
    rawffsideband_pbpbmc_recoreco[icent]->Add(rawffjetmixsideband_pbpbmc_recoreco[icent]);

    hjetptsideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmixsideband_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmixsideband_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjetssideband = hjetptsideband_pbpbmc_recoreco[icent]->Integral();
    float nmixjetssideband = hjetptjetmixsideband_pbpbmc_recoreco[icent]->Integral();


    rawffsideband_pbpbmc_recoreco[icent]->Scale(1/(nrawjetssideband-nmixjetssideband));
    rawffsideband_pbpbmc_recoreco[icent]->SetMarkerColor(kGreen);
    // rawffsideband_pbpbmc_recoreco[icent]->Draw("same");

    float purity   = getpurity(phoetmin,icent);
    rawff_pbpbmc_recoreco[icent]->Scale(1.0/purity);
    rawffsideband_pbpbmc_recoreco[icent]->Scale(-1.0*(1.0-purity)/purity);
    rawff_pbpbmc_recoreco[icent]->Add(rawffsideband_pbpbmc_recoreco[icent]);



    rawff_pbpbmc_gengen0[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbmc_gengen0_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_pbpbmc_gengen0[icent]->Sumw2();
    hgenjetpt_pbpbmc_gengen0[icent] = (TH1D*)_file0->Get(Form("hgenjetpt_pbpbmc_gengen0_%d_%d",centmins[icent],centmaxs[icent]));
    hgenjetpt_pbpbmc_gengen0[icent]->Sumw2();
    float ngenjets = hgenjetpt_pbpbmc_gengen0[icent]->Integral();
    rawff_pbpbmc_gengen0[icent]->Scale(1/ngenjets);

    if(do_divide==0) {
      rawff_pbpbmc_recoreco[icent]->Draw("same");
      rawff_pbpbmc_gengen0[icent]->Draw("hist same");
    } else {
      rawff_pbpbmc_recoreco[icent]->Divide(rawff_pbpbmc_gengen0[icent]);
      rawff_pbpbmc_recoreco[icent]->Draw("same");
      TLine * lone = new TLine(0,1,5,1);
      lone->SetLineStyle(9);
      lone->Draw();
    }
    rawff_pbpbmc_recoreco[icent]->Write();

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
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"recoreco bkg-sub","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_gengen0[icent],"gengen0 sube==0","l");
      } else {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"recoreco bkg-sub/genen0","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_gengen0[icent],"","");
      }
      // leg_ff_pbpbsub[icent]->AddEntry(rawffjetmix_pbpbmc_recoreco[icent],"Jet Mix FF","p");
      // leg_ff_pbpbsub[icent]->AddEntry(rawffue_pbpbmc_recoreco[icent],"Raw UE FF","p");
      // leg_ff_pbpbsub[icent]->AddEntry(rawffjetmixue_pbpbmc_recoreco[icent],"Jet Mix UE FF","p");
    }
    else if(icent==1)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],Form("trk p_{T}>%d GeV, R < 0.3",trkptcut),"");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"|#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"Pythia+Hydjet","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
  }

  call->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,yaxismin,yaxismax);
  axis_dummy->UseCurrentStyle();
  // axis_dummy->Draw("COLA");
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi;
  if(do_divide==1) {
    ldndxi = new TLatex(0.4,0.5,"Ratio");
  } else {
    if(gammaxi==0)
      ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{jet}");
    else
      ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{#gamma}");
  }
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.4);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);

  const int nlabels = 5;
  std::vector<float> fylabels;
  std::vector<string> sylabels;

  if(do_divide==1) {
    fylabels = {0.6,0.8,1.0,1.2,1.4};
    sylabels = {"0.6","0.8","1.0","1.2","1.4"};
  } else {
    fylabels = {0,1,2,3,4};
    sylabels = {"0","1","2","3","4"};
  }
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    if(do_divide==0) {
      laxis[ilatex] = new TLatex(3,fylabels[ilatex]-0.2,Form("%s",sylabels[ilatex].data()));
      laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.3);
    } else {
      laxis[ilatex] = new TLatex(2,fylabels[ilatex]-0.03,Form("%s",sylabels[ilatex].data()));
      laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.15);
    }
    laxis[ilatex]->Draw();
  }

  // float labelspace = (yaxismax-yaxismin) / 4.0;
  // const int nlabels = int(yaxismax/labelspace);
  // TLatex * laxis[nlabels];
  // for (int ilatex = 0; ilatex < nlabels; ilatex++) {
  //   laxis[ilatex] = new TLatex(2.,ilatex*labelspace-(0.1*(yaxismax-yaxismin)/4.0),Form("%2.1f",ilatex*labelspace));
  //   laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
  //   laxis[ilatex]->Draw();
  // }
  ldndxi->Draw();
  if(do_divide==0) {
    call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d.png",phoetmin,phoetmax,jetptmin,gammaxi));
    call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  } else {
    call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d_ratio.png",phoetmin,phoetmax,jetptmin,gammaxi));
    call->SaveAs(Form("finalff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d_ratio.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  }
  // _fout->Write();
  _fout->Save();
}
