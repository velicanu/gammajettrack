#include "makeMultiPanelCanvas.C"
float allpuritypbpb[] = {0.725758, 0.720249, 0.753094, 0.703853, 0.730487, 0.756007, 0.741809, 0.737945, 0.725995, 0.786819, 0.704426, 0.743147, 0.775786, 0.827101, 0.715906, 0.710863, 0.739059, 0.687001, 0.719965, 0.743805, 0.720358, 0.724734, 0.719121, 0.758637, 0.699659, 0.73539, 0.76691, 0.731031, 0.730948, 0.717619, 0.786722, 0.695959, 0.733827, 0.771255, 0.836782, 0.749695, 0.739283, 0.788322, 0.711966, 0.763817, 0.786493, 0.816522, 0.733207, 0.719114, 0.785248, 0.705784, 0.734519, 0.769831, 0.84767, 0.772594, 0.766181, 0.802428, 0.720997, 0.80606, 0.822834, 0.774406};
float allpuritypp[] = {0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.823368, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.846154, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.820975, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.830048, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.846293, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.859037, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.863744, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244, 0.857244};
float getpurity(float phoetmin, float hibinmin, bool ispp)
{
  int row = -1;
  int col = -1;
  if(phoetmin==40)  row = 0;
  if(phoetmin==60)  row = 1;
  if(phoetmin==100) row = 7;
  if(hibinmin==0)   col = 3;
  if(hibinmin==20)  col = 4;
  if(hibinmin==60)  col = 5;
  if(hibinmin==100) col = 6;
  if(row>-1 && col > -1 && ispp) return allpuritypp[row*7+col];
  if(row>-1 && col > -1 && !ispp) return allpuritypbpb[row*7+col];
  return 1; //no purity applied
}

void drawpp4step(int phoetmin, int phoetmax, int jetptmin = 30, int trkptcut = 4, int do_divide = 0, int gammaxi = 0) {
  TFile *_file0 = TFile::Open(Form("closure_pp_%d_%d_%d_gammaxi%d.root",phoetmin,phoetmax,jetptmin,gammaxi));
  // return;
  const static int ncentbins = 4;
  const int yaxismax = 2;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};
  TH1D * rawff_ppmc_recoreco[ncentbins];
  TH1D * rawff_ppmc_gen[ncentbins];
  TH1D * rawffjetmix_ppmc_recoreco[ncentbins];
  TH1D * hgenjetpt_ppmc_gen[ncentbins];
  TH1D * hjetpt_ppmc_recoreco[ncentbins];
  TH1D * hjetptjetmix_ppmc_recoreco[ncentbins];
  TH1D * hnmixsignal_ppmc_recoreco[ncentbins];
  TH1D * hgammaffxiuemix_ppmc_recoreco[ncentbins];
  TH1D * rawffsideband_ppmc_recoreco[ncentbins];
  TH1D * rawffjetmixsideband_ppmc_recoreco[ncentbins];
  TH1D * hjetptsideband_ppmc_recoreco[ncentbins];
  TH1D * hjetptjetmixsideband_ppmc_recoreco[ncentbins];
  TH1D * hnmixsideband_ppmc_recoreco[ncentbins];
  TH1D * hgammaffxiuemixsideband_ppmc_recoreco[ncentbins];
  TH2D * dummy_ppsub[ncentbins];
  TLegend * leg_ff_ppsub[ncentbins];

  TCanvas * call = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {
    call->cd(2+icent);
    dummy_ppsub[icent] = new TH2D(Form("dummy_ppsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    dummy_ppsub[icent]->GetXaxis()->SetTitleOffset(0.8);
    dummy_ppsub[icent]->GetXaxis()->CenterTitle();
    dummy_ppsub[icent]->GetYaxis()->CenterTitle();
    dummy_ppsub[icent]->GetXaxis()->SetTitleSize(dummy_ppsub[icent]->GetXaxis()->GetTitleSize()*1.4);
    dummy_ppsub[icent]->Draw();

    rawff_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_ppmc_recoreco[icent]->Scale(-1);
    rawff_ppmc_recoreco[icent]->Add(rawffjetmix_ppmc_recoreco[icent]);
    hjetpt_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetpt_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hnmixsignal_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hnmixsignal_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    float nrawjets = hjetpt_ppmc_recoreco[icent]->Integral();
    float nmixjets = hjetptjetmix_ppmc_recoreco[icent]->Integral();
    float nmixtot = hnmixsignal_ppmc_recoreco[icent]->Integral();
    float avgnmix = nmixtot/nmixjets;
    float denominator;
    if(avgnmix!=0 && nmixjets!=0)
    {
      denominator = nrawjets - nmixjets/avgnmix;
    }
    else
    {
      denominator = nrawjets;
    }
    hgammaffxiuemix_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    if(nrawjets!=0)
    {
      hgammaffxiuemix_ppmc_recoreco[icent]->Scale(-1.0/nrawjets);
    }
    hgammaffxiuemix_ppmc_recoreco[icent]->SetMarkerColor(kRed);
    if(denominator!=0)
    {
      rawff_ppmc_recoreco[icent]->Scale(1.0/denominator);
    }
    rawff_ppmc_recoreco[icent]->Add(hgammaffxiuemix_ppmc_recoreco[icent]);

    rawffsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixsideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_ppmc_recoreco[icent]->Scale(-1);
    rawffsideband_ppmc_recoreco[icent]->Add(rawffjetmixsideband_ppmc_recoreco[icent]);
    hjetptsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmixsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmixsideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hnmixsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hnmixsideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    nrawjets = hjetptsideband_ppmc_recoreco[icent]->Integral();
    nmixjets = hjetptjetmixsideband_ppmc_recoreco[icent]->Integral();
    nmixtot = hnmixsideband_ppmc_recoreco[icent]->Integral();
    avgnmix = nmixtot/nmixjets;
    denominator = nrawjets - nmixjets/avgnmix;
    if(denominator!=0 && nmixjets!=0 && avgnmix!=0)
    {
      rawffsideband_ppmc_recoreco[icent]->Scale(1.0/denominator);
    }
    hgammaffxiuemixsideband_ppmc_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemixsideband_ppmc_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    if(nrawjets!=0)
    {
      hgammaffxiuemixsideband_ppmc_recoreco[icent]->Scale(-1.0/nrawjets);
      rawffsideband_ppmc_recoreco[icent]->Add(hgammaffxiuemixsideband_ppmc_recoreco[icent]);
    }
    hgammaffxiuemixsideband_ppmc_recoreco[icent]->SetMarkerColor(kRed);
    // hgammaffxiuemixsideband_ppmc_recoreco[icent]->Draw("same");

    rawffsideband_ppmc_recoreco[icent]->SetMarkerColor(kGreen);

    float purity   = getpurity(phoetmin,centmins[icent],false);
    float pppurity = getpurity(phoetmin,centmins[icent],true);

    if(purity!=0)
    {
      rawff_ppmc_recoreco[icent]->Scale(1.0/purity);
      rawffsideband_ppmc_recoreco[icent]->Scale(-1.0*(1.0-purity)/purity);
    }
    if(denominator!=0 && nmixjets!=0 && avgnmix!=0)
    {
      rawff_ppmc_recoreco[icent]->Add(rawffsideband_ppmc_recoreco[icent]);
    }
    else
    {
      rawff_ppmc_recoreco[icent]->Scale(purity);
    }



    rawff_ppmc_gen[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_ppmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    rawff_ppmc_gen[icent]->Sumw2();
    hgenjetpt_ppmc_gen[icent] = (TH1D*)_file0->Get(Form("hgenjetpt_ppmc_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    float ngengets = hgenjetpt_ppmc_gen[icent]->Integral();
    // ngenjets = hjetpt_ppmc_recoreco[icent]->Integral();
    // rawff_ppmc_gen[icent]->Scale(1.0/nrawjets);
    rawff_ppmc_gen[icent]->Scale(1.0/ngengets);

    if(do_divide==0) {
      rawff_ppmc_recoreco[icent]->Draw("same");
      rawff_ppmc_gen[icent]->Draw("hist same");
    } else {
      rawff_ppmc_recoreco[icent]->Divide(rawff_ppmc_gen[icent]);
      rawff_ppmc_recoreco[icent]->Draw("same");
      TLine * lone = new TLine(0,1,5,1);
      lone->SetLineStyle(9);
      lone->Draw();
    }

    if(icent==0)
    {
      leg_ff_ppsub[icent] = new TLegend(0.03,0.697,0.3,0.92);
    }
    else
    {
      leg_ff_ppsub[icent] = new TLegend(0,0.697,0.27,0.92);
    }
    leg_ff_ppsub[icent]->SetTextSize(0.05*1.3);
    leg_ff_ppsub[icent]->SetFillColor(0);
    leg_ff_ppsub[icent]->SetFillStyle(0);
    leg_ff_ppsub[icent]->SetTextFont(42);
    if(icent==0)
    {
      if(do_divide==0)
      {
        leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],"Final FF reco pp","p");
        leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_gen[icent],"GenGen FF pp","l");
      } else {
        leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],"reco/gen pp","p");
        leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_gen[icent],"","");
      }
    }
    else if(icent==1)
    {
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],Form("trk p_{T}>%d GeV, R < 0.3",trkptcut),"");
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],"|#eta^{jet}| < 1.6","");
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],"Pythia","");
      leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg_ff_ppsub[icent]->AddEntry(rawff_ppmc_recoreco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_ppsub[icent]->Draw();
  }

  call->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi;
  if(do_divide==0) {
    if(gammaxi==0) ldndxi = new TLatex(0.4,0.4,"dN/d#xi_{jet} 1/nJet");
    else           ldndxi = new TLatex(0.4,0.4,"dN/d#xi_{#gamma} 1/nJet");
  } else {
    ldndxi = new TLatex(0.4,0.4,"Ratio");
  }
  ldndxi->SetTextSize(ldndxi->GetTextSize()*1.2);
  ldndxi->SetNDC();
  ldndxi->SetTextAngle(90);
  ldndxi->Draw();

  const int nlabels = 5;
  float fylabels[] = {0.6,0.8,1.0,1.2,1.4};
  string sylabels[] = {"0.6","0.8","1.0","1.2","1.4"};
  TLatex * laxis[nlabels];
  for (int ilatex = 0; ilatex < nlabels; ilatex++) {
    laxis[ilatex] = new TLatex(2,fylabels[ilatex]-0.01,Form("%s",sylabels[ilatex].data()));
    // laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.3);
    laxis[ilatex]->Draw();
  }
  if(do_divide==0)
  {
    call->SaveAs(Form("finalff_%d_%d_gen_jetpt%d_trkpt%d_ppmc_recoreco_gammaxi%d.png",phoetmin,phoetmax,jetptmin,trkptcut,gammaxi));
    call->SaveAs(Form("finalff_%d_%d_gen_jetpt%d_trkpt%d_ppmc_recoreco_gammaxi%d.pdf",phoetmin,phoetmax,jetptmin,trkptcut,gammaxi));
  } else {
    call->SaveAs(Form("finalff_%d_%d_gen_jetpt%d_trkpt%d_ppmc_recoreco_gammaxi%d_ratio.png",phoetmin,phoetmax,jetptmin,trkptcut,gammaxi));
    call->SaveAs(Form("finalff_%d_%d_gen_jetpt%d_trkpt%d_ppmc_recoreco_gammaxi%d_ratio.pdf",phoetmin,phoetmax,jetptmin,trkptcut,gammaxi));
  }
}
