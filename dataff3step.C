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

void dataff3step(int phoetmin, int phoetmax, int jetptmin = 30) {
  TFile *_file0 = TFile::Open(Form("all_%d_%d_%d.root",phoetmin,phoetmax,jetptmin));
  const static int ncentbins = 4;
  const int yaxismax = 4;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-70%","70-100%"};
  TH1D * rawff_pbpbdata_reco[ncentbins];
  TH1D * rawffjetmix_pbpbdata_reco[ncentbins];
  TH1D * hjetpt_pbpbdata_reco[ncentbins];
  TH1D * hjetptjetmix_pbpbdata_reco[ncentbins];
  TH1D * hnmixsignal_pbpbdata_reco[ncentbins];
  TH1D * hgammaffxiuemix_pbpbdata_reco[ncentbins];
  TH1D * rawffsideband_pbpbdata_reco[ncentbins];
  TH1D * rawffjetmixsideband_pbpbdata_reco[ncentbins];
  TH1D * hjetptsideband_pbpbdata_reco[ncentbins];
  TH1D * hjetptjetmixsideband_pbpbdata_reco[ncentbins];
  TH1D * hnmixsideband_pbpbdata_reco[ncentbins];
  TH1D * hgammaffxiuemixsideband_pbpbdata_reco[ncentbins];
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

    rawff_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmix_pbpbdata_reco[icent]->Scale(-1);
    rawff_pbpbdata_reco[icent]->Add(rawffjetmix_pbpbdata_reco[icent]);
    hjetpt_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetpt_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hnmixsignal_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hnmixsignal_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    float nrawjets = hjetpt_pbpbdata_reco[icent]->Integral();
    float nmixjets = hjetptjetmix_pbpbdata_reco[icent]->Integral();
    float nmixtot = hnmixsignal_pbpbdata_reco[icent]->Integral();
    float avgnmix = nmixtot/nmixjets;
    float denominator = nrawjets - nmixjets/avgnmix;
    rawff_pbpbdata_reco[icent]->Scale(1.0/denominator);

    hgammaffxiuemix_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemix_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxiuemix_pbpbdata_reco[icent]->Scale(-1.0/nrawjets);
    hgammaffxiuemix_pbpbdata_reco[icent]->SetMarkerColor(kRed);
    // hgammaffxiuemix_pbpbdata_reco[icent]->Draw("same");
    
    rawff_pbpbdata_reco[icent]->Add(hgammaffxiuemix_pbpbdata_reco[icent]);

    rawffsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_pbpbdata_reco[icent]->Scale(-1);
    rawffsideband_pbpbdata_reco[icent]->Add(rawffjetmixsideband_pbpbdata_reco[icent]);
    hjetptsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmixsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmixsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hnmixsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hnmixsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    nrawjets = hjetptsideband_pbpbdata_reco[icent]->Integral();
    nmixjets = hjetptjetmixsideband_pbpbdata_reco[icent]->Integral();
    nmixtot = hnmixsideband_pbpbdata_reco[icent]->Integral();
    avgnmix = nmixtot/nmixjets;
    denominator = nrawjets - nmixjets/avgnmix;
    
    rawffsideband_pbpbdata_reco[icent]->Scale(1.0/denominator);

    hgammaffxiuemixsideband_pbpbdata_reco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemixsideband_pbpbdata_reco_%d_%d",centmins[icent],centmaxs[icent]));
    hgammaffxiuemixsideband_pbpbdata_reco[icent]->Scale(-1.0/nrawjets);
    hgammaffxiuemixsideband_pbpbdata_reco[icent]->SetMarkerColor(kRed);
    // hgammaffxiuemixsideband_pbpbdata_reco[icent]->Draw("same");
    
    rawffsideband_pbpbdata_reco[icent]->Add(hgammaffxiuemix_pbpbdata_reco[icent]);
    rawffsideband_pbpbdata_reco[icent]->SetMarkerColor(kGreen);

    float purity   = getpurity(phoetmin,centmins[icent],false);
    float pppurity = getpurity(phoetmin,centmins[icent],true);

    rawff_pbpbdata_reco[icent]->Scale(1.0/purity);
    rawff_pbpbdata_reco[icent]->Draw("same");
    
    rawffsideband_pbpbdata_reco[icent]->Scale((1.0-purity)/purity);
    rawffsideband_pbpbdata_reco[icent]->Draw("same");
    

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
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"Raw-Jet-UE FF signal","p");
      leg_ff_pbpbsub[icent]->AddEntry(rawffsideband_pbpbdata_reco[icent],"Raw-Jet-UE FF sideband","p");
    }
    else if(icent==1)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"trk p_{T}>1 GeV, R < 0.3","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("%d>#gamma p_{T}>%d GeV",phoetmin,phoetmax),"");
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"|#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"Pythia+Hydjet","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_reco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
  }

  call->cd(1);
  TH2D * axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  gStyle->SetFrameLineColor(0);
  axis_dummy->UseCurrentStyle();
  axis_dummy->Draw("FB BB A");

  TLatex * ldndxi = new TLatex(0.4,0.5,"dN/d#xi 1/nJet purity");
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
  call->SaveAs(Form("rawminusjetueff_%d_%d_signalsideband_jetpt%d_pbpbdata_reco.png",phoetmin,phoetmax,jetptmin));
}
