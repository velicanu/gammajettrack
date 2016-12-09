#include "makeMultiPanelCanvas.C"

void draw2step(int phoetmin, int phoetmax, int jetptmin = 30, int trkptcut = 4, int do_divide = 0, int gammaxi = 0) {
  TFile *_file0 = TFile::Open(Form("closure_pbpb_%d_%d_%d_gammaxi%d.root",phoetmin,phoetmax,jetptmin,gammaxi));
  const static int ncentbins = 4;
  const int yaxismax = 4;
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

  TH1D * rawff_pbpbmc_gengen[ncentbins];
  TH1D * hgenjetpt_pbpbmc_gengen[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

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

    rawff_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_pbpbmc_recoreco[icent]->Sumw2();
    rawffue_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffue_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmix_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_pbpbmc_recoreco[icent]->Sumw2();
    rawffjetmixue_pbpbmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixue_pbpbmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixue_pbpbmc_recoreco[icent]->Sumw2();
    rawffue_pbpbmc_recoreco[icent]->Scale(-1);
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
    rawffuesideband_pbpbmc_recoreco[icent]->Scale(-1);
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

    
    rawff_pbpbmc_gengen[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_pbpbmc_gengen[icent]->Sumw2();
    hgenjetpt_pbpbmc_gengen[icent] = (TH1D*)_file0->Get(Form("hgenjetpt_pbpbmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    float ngenjets = hgenjetpt_pbpbmc_gengen[icent]->Integral();
    rawff_pbpbmc_gengen[icent]->Scale(1/ngenjets);
 
    if(do_divide==0)
    {
      rawff_pbpbmc_recoreco[icent]->Draw("same");
      rawff_pbpbmc_gengen[icent]->Draw("hist same");
    } else {

      rawff_pbpbmc_recoreco[icent]->Divide(rawff_pbpbmc_gengen[icent]);
      rawff_pbpbmc_recoreco[icent]->Draw("same");
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
      if(do_divide==0)
      {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"Raw FF presideband","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_gengen[icent],"Gen FF","l");
      } else {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbmc_recoreco[icent],"Raw/Gen FF presideband","p");
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
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi;
  if(gammaxi==0)
    ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{jet} Raw");
  else
    ldndxi = new TLatex(0.4,0.5,"dN/d#xi_{#gamma} Raw");
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
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
  if(do_divide==0) {
    call->SaveAs(Form("rawminusjetff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d.png",phoetmin,phoetmax,jetptmin,gammaxi));
  } else {
    call->SaveAs(Form("rawminusjetff_%d_%d_uemixff_jetpt%d_pbpbmc_recoreco_%d_ratio.png",phoetmin,phoetmax,jetptmin,gammaxi));
  }
}
