#include "makeMultiPanelCanvas.C"

//nominal
float allpuritypbpb[] = { 0.704402, 0.695052, 0.745314, 0.670393, 0.712452, 0.747344, 0.737428,
                          0.725267, 0.708896, 0.785853, 0.681689, 0.730339, 0.775276, 0.825922,
                          0.692733, 0.684606, 0.730031, 0.654991, 0.700615, 0.733907, 0.714753,
                          0.707091, 0.699483, 0.748273, 0.672784, 0.722749, 0.754953, 0.726901,
                          0.719437, 0.702283, 0.785353, 0.676977, 0.721539, 0.77048, 0.835029,
                          0.737224, 0.721948, 0.789327, 0.685621, 0.751769, 0.787902, 0.816627,
                          0.722065, 0.702349, 0.787935, 0.67868, 0.725783, 0.771699, 0.850336,
                          0.758906, 0.749149, 0.799366, 0.700252, 0.792531, 0.821031, 0.797929
                          };
float allpuritypp[] = {   0.820859, 0.820859, 0.820859, 0.820859, 0.820859, 0.820859, 0.820859,
                          0.841322, 0.841322, 0.841322, 0.841322, 0.841322, 0.841322, 0.841322,
                          0.819149, 0.819149, 0.819149, 0.819149, 0.819149, 0.819149, 0.819149,
                          0.827423, 0.827423, 0.827423, 0.827423, 0.827423, 0.827423, 0.827423,
                          0.841746, 0.841746, 0.841746, 0.841746, 0.841746, 0.841746, 0.841746,
                          0.853694, 0.853694, 0.853694, 0.853694, 0.853694, 0.853694, 0.853694,
                          0.858868, 0.858868, 0.858868, 0.858868, 0.858868, 0.858868, 0.858868,
                          0.851183, 0.851183, 0.851183, 0.851183, 0.851183, 0.851183, 0.851183
                          };
//up
float allpuritypbpb_up[] = {0.786483, 0.781925, 0.808699, 0.765789, 0.792815, 0.812663, 0.794217, 0.802484, 0.798719, 0.823989, 0.784649, 0.80838, 0.82018, 0.839167, 0.780588, 0.775496, 0.802794, 0.753684, 0.786004, 0.807622, 0.783555, 0.785176, 0.779132, 0.812662, 0.760196, 0.79591, 0.819588, 0.785941, 0.799376, 0.79425, 0.827123, 0.788432, 0.798401, 0.821262, 0.847832, 0.810702, 0.810325, 0.817984, 0.781683, 0.831584, 0.818722, 0.815832, 0.802133, 0.799319, 0.821158, 0.767797, 0.820925, 0.816056, 0.848964, 0.823743, 0.826856, 0.821099, 0.803847, 0.851806, 0.833434, 0.862138};
float allpuritypp_up[] = {0.860179, 0.860179, 0.860179, 0.860179, 0.860179, 0.860179, 0.860179, 0.868365, 0.868365, 0.868365, 0.868365, 0.868365, 0.868365, 0.868365, 0.859561, 0.859561, 0.859561, 0.859561, 0.859561, 0.859561, 0.859561, 0.864276, 0.864276, 0.864276, 0.864276, 0.864276, 0.864276, 0.864276, 0.871913, 0.871913, 0.871913, 0.871913, 0.871913, 0.871913, 0.871913, 0.868697, 0.868697, 0.868697, 0.868697, 0.868697, 0.868697, 0.868697, 0.872612, 0.872612, 0.872612, 0.872612, 0.872612, 0.872612, 0.872612, 0.867851, 0.867851, 0.867851, 0.867851, 0.867851, 0.867851, 0.867851};
// down
float allpuritypbpb_down[] = {0.58137, 0.570472, 0.640496, 0.552295, 0.589878, 0.641163, 0.641338, 0.62773, 0.61566, 0.686854, 0.583795, 0.644241, 0.680084, 0.724226, 0.55868, 0.547463, 0.623272, 0.542794, 0.559101, 0.627778, 0.616984, 0.576336, 0.564139, 0.644103, 0.514229, 0.608187, 0.642481, 0.660722, 0.615156, 0.59956, 0.691904, 0.573649, 0.625162, 0.668078, 0.765202, 0.654963, 0.647691, 0.689322, 0.597215, 0.691554, 0.724679, 0.694852, 0.645085, 0.643222, 0.668429, 0.597739, 0.677045, 0.689128, 0.815539, 0.680725, 0.66682, 0.776057, 0.670596, 0.727152, 0.837721, 0.712363};
float allpuritypp_down[] = {0.763177, 0.763177, 0.763177, 0.763177, 0.763177, 0.763177, 0.763177, 0.808331, 0.808331, 0.808331, 0.808331, 0.808331, 0.808331, 0.808331, 0.756098, 0.756098, 0.756098, 0.756098, 0.756098, 0.756098, 0.756098, 0.776145, 0.776145, 0.776145, 0.776145, 0.776145, 0.776145, 0.776145, 0.804209, 0.804209, 0.804209, 0.804209, 0.804209, 0.804209, 0.804209, 0.836072, 0.836072, 0.836072, 0.836072, 0.836072, 0.836072, 0.836072, 0.838053, 0.838053, 0.838053, 0.838053, 0.838053, 0.838053, 0.838053, 0.8459, 0.8459, 0.8459, 0.8459, 0.8459, 0.8459, 0.8459};


float getpurity(float phoetmin, float hibinmin, bool ispp, int updown)
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
  if(row>-1 && col > -1 && ispp && updown==0) return allpuritypp[row*7+col];
  if(row>-1 && col > -1 && !ispp && updown==0) return allpuritypbpb[row*7+col];
  if(row>-1 && col > -1 && ispp && updown==1) return allpuritypp_up[row*7+col];
  if(row>-1 && col > -1 && !ispp && updown==1) return allpuritypbpb_up[row*7+col];
  if(row>-1 && col > -1 && ispp && updown==-1) return allpuritypp_down[row*7+col];
  if(row>-1 && col > -1 && !ispp && updown==-1) return allpuritypbpb_down[row*7+col];
  return 1; //no purity applied
}

void syst_phopurity(int phoetmin, int phoetmax, int jetptmin = 30, int trkptcut = 4, int do_divide = 0, int gammaxi = 0) {
  TFile *_file0 = TFile::Open(Form("all_%d_%d_%d_gammaxi%d.root",phoetmin,phoetmax,jetptmin,gammaxi));
  const static int ncentbins = 4;
  const int yaxismax = 4;
  float ratioyaxismax = 1.7;
  float ratioyaxismin = 0.7;
  float binwidth = 5.000000e-01;
  int centmins[] = {0,20,60,100,140};
  int centmaxs[] = {20,60,100,200,200};
  string cents[] = {"0-10%","10-30%","30-50%","50-100%","70-100%"};
  TH1D * rawff_pbpbdata_recoreco[ncentbins];
  TH1D * rawff_pbpbdata_recoreco_up[ncentbins];
  TH1D * rawff_pbpbdata_recoreco_down[ncentbins];
  TH1D * rawffue_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmix_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixue_pbpbdata_recoreco[ncentbins];
  TH1D * hjetpt_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptjetmix_pbpbdata_recoreco[ncentbins];

  TH1D * rawffsideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffsideband_pbpbdata_recoreco_up[ncentbins];
  TH1D * rawffsideband_pbpbdata_recoreco_down[ncentbins];
  TH1D * rawffuesideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixsideband_pbpbdata_recoreco[ncentbins];
  TH1D * rawffjetmixuesideband_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptsideband_pbpbdata_recoreco[ncentbins];
  TH1D * hjetptjetmixsideband_pbpbdata_recoreco[ncentbins];

  TH1D * rawff_ppdata_recoreco[ncentbins];
  TH1D * rawff_ppdata_recoreco_up[ncentbins];
  TH1D * rawff_ppdata_recoreco_down[ncentbins];
  TH1D * hjetpt_ppdata_recoreco[ncentbins];
  TH1D * rawffsideband_ppdata_recoreco[ncentbins];
  TH1D * rawffsideband_ppdata_recoreco_up[ncentbins];
  TH1D * rawffsideband_ppdata_recoreco_down[ncentbins];
  TH1D * hjetptsideband_ppdata_recoreco[ncentbins];

  TH1D * rawff_pbpbdata_gengen[ncentbins];
  TH1D * hgenjetpt_pbpbdata_gengen[ncentbins];
  TH2D * dummy_pbpbsub[ncentbins];
  TLegend * leg_ff_pbpbsub[ncentbins];

  TCanvas * call = new TCanvas("call","",1600,500);
  makeMultiPanelCanvas(call,ncentbins+1,1,0.02,0.0,-6,0.2,0.04);

  for (int icent = 0; icent < ncentbins; icent++) {
    call->cd(2+icent);
    if(do_divide==0)
      dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,0,yaxismax);
    else
      dummy_pbpbsub[icent] = new TH2D(Form("dummy_pbpbsub_%d_%d",centmins[icent],centmaxs[icent]),";#xi;dN/d#xi",1,0.01,4.99,1,ratioyaxismin,ratioyaxismax);
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
    rawffue_pbpbdata_recoreco[icent]->Scale(-1);
    rawffjetmixue_pbpbdata_recoreco[icent]->Scale(-1);
    rawff_pbpbdata_recoreco[icent]->Add(rawffue_pbpbdata_recoreco[icent]);
    rawffjetmix_pbpbdata_recoreco[icent]->Add(rawffjetmixue_pbpbdata_recoreco[icent]);
    rawffjetmix_pbpbdata_recoreco[icent]->Scale(-1);
    rawff_pbpbdata_recoreco[icent]->Add(rawffjetmix_pbpbdata_recoreco[icent]);

    hjetpt_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetpt_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmix_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmix_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjets = hjetpt_pbpbdata_recoreco[icent]->Integral();
    float nmixjets = hjetptjetmix_pbpbdata_recoreco[icent]->Integral();


    rawff_pbpbdata_recoreco[icent]->Scale(1/(nrawjets-nmixjets));


    rawffsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxisideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffsideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxiuemixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffuesideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmixsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixsideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffjetmixuesideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hgammaffxijetmixuesideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    rawffjetmixuesideband_pbpbdata_recoreco[icent]->Sumw2();
    rawffuesideband_pbpbdata_recoreco[icent]->Scale(-1);
    rawffjetmixuesideband_pbpbdata_recoreco[icent]->Scale(-1);
    rawffsideband_pbpbdata_recoreco[icent]->Add(rawffuesideband_pbpbdata_recoreco[icent]);
    rawffjetmixsideband_pbpbdata_recoreco[icent]->Add(rawffjetmixuesideband_pbpbdata_recoreco[icent]);
    rawffjetmixsideband_pbpbdata_recoreco[icent]->Scale(-1);
    rawffsideband_pbpbdata_recoreco[icent]->Add(rawffjetmixsideband_pbpbdata_recoreco[icent]);

    hjetptsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));
    hjetptjetmixsideband_pbpbdata_recoreco[icent] = (TH1D*)_file0->Get(Form("hjetptjetmixsideband_pbpbdata_recoreco_%d_%d",centmins[icent],centmaxs[icent]));

    float nrawjetssideband = hjetptsideband_pbpbdata_recoreco[icent]->Integral();
    float nmixjetssideband = hjetptjetmixsideband_pbpbdata_recoreco[icent]->Integral();


    rawffsideband_pbpbdata_recoreco[icent]->Scale(1/(nrawjetssideband-nmixjetssideband));
    rawffsideband_pbpbdata_recoreco[icent]->SetMarkerColor(kGreen);
    // rawffsideband_pbpbdata_recoreco[icent]->Draw("same");

    float purity   = getpurity(phoetmin,centmins[icent],false,1);
    rawff_pbpbdata_recoreco_up[icent] = (TH1D*) rawff_pbpbdata_recoreco[icent]->Clone(Form("rawff_pbpbdata_recoreco_up%d",icent));
    rawff_pbpbdata_recoreco_up[icent]->Scale(1.0/purity);
    rawff_pbpbdata_recoreco[icent]->SetMarkerStyle(24);
    rawffsideband_pbpbdata_recoreco_up[icent] = (TH1D*) rawffsideband_pbpbdata_recoreco[icent]->Clone(Form("rawffsideband_pbpbdata_recoreco_up%d",icent));
    rawffsideband_pbpbdata_recoreco_up[icent]->Scale(-1.0*(1.0-purity)/purity);
    rawff_pbpbdata_recoreco_up[icent]->Add(rawffsideband_pbpbdata_recoreco_up[icent]);

    cout<<1.0/purity<<endl;
    purity   = getpurity(phoetmin,centmins[icent],false,-1);
    cout<<1.0/purity<<endl;
    rawff_pbpbdata_recoreco_down[icent] = (TH1D*) rawff_pbpbdata_recoreco[icent]->Clone(Form("rawff_pbpbdata_recoreco_down%d",icent));
    rawff_pbpbdata_recoreco_down[icent]->Scale(1.0/purity);
    rawffsideband_pbpbdata_recoreco_down[icent] = (TH1D*) rawffsideband_pbpbdata_recoreco[icent]->Clone(Form("rawffsideband_pbpbdata_recoreco_down%d",icent));
    rawffsideband_pbpbdata_recoreco_down[icent]->Scale(-1.0*(1.0-purity)/purity);
    rawff_pbpbdata_recoreco_down[icent]->Add(rawffsideband_pbpbdata_recoreco_down[icent]);


    // rawff_pbpbdata_recoreco_down[icent]->Draw("same");
    // rawff_pbpbdata_recoreco_up[icent]->Draw("same");


    // rawff_pbpbdata_gengen[icent] = (TH1D*)_file0->Get(Form("hgammaffxi_pbpbdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    // hgenjetpt_pbpbdata_gengen[icent] = (TH1D*)_file0->Get(Form("hgenjetpt_pbpbdata_gengen_%d_%d",centmins[icent],centmaxs[icent]));
    // float ngenjets = hgenjetpt_pbpbdata_gengen[icent]->Integral();
    // rawff_pbpbdata_gengen[icent]->Scale(1/ngenjets);

    // rawff_pbpbdata_recoreco[icent]->Draw("same");
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

    float pppurity   = getpurity(phoetmin,centmins[icent],true,1);
    rawff_ppdata_recoreco_up[icent] = (TH1D*) rawff_ppdata_recoreco[icent]->Clone(Form("rawff_ppdata_recoreco_up%d",icent));
    rawff_ppdata_recoreco_up[icent]->Scale(1.0/pppurity);
    rawffsideband_ppdata_recoreco_up[icent] = (TH1D*) rawffsideband_ppdata_recoreco[icent]->Clone(Form("rawffsideband_ppdata_recoreco_up%d",icent));
    rawffsideband_ppdata_recoreco_up[icent]->Scale(-1.0*(1.0-pppurity)/pppurity);
    rawff_ppdata_recoreco_up[icent]->Add(rawffsideband_ppdata_recoreco_up[icent]);

    pppurity   = getpurity(phoetmin,centmins[icent],true,-1);
    rawff_ppdata_recoreco_down[icent] = (TH1D*) rawff_ppdata_recoreco[icent]->Clone(Form("rawff_ppdata_recoreco_down%d",icent));
    rawff_ppdata_recoreco_down[icent]->Scale(1.0/pppurity);
    rawffsideband_ppdata_recoreco_down[icent] = (TH1D*) rawffsideband_ppdata_recoreco[icent]->Clone(Form("rawffsideband_ppdata_recoreco_down%d",icent));
    rawffsideband_ppdata_recoreco_down[icent]->Scale(-1.0*(1.0-pppurity)/pppurity);
    rawff_ppdata_recoreco_down[icent]->Add(rawffsideband_ppdata_recoreco_down[icent]);

    //
    // rawff_pbpbdata_recoreco[icent]->SetMarkerSize(2);
    // rawff_ppdata_recoreco[icent]->SetMarkerSize(2);
    rawff_pbpbdata_recoreco_down[icent]->SetMarkerStyle(24);
    rawff_ppdata_recoreco_up[icent]->SetMarkerColor(kRed);
    rawff_ppdata_recoreco_down[icent]->SetMarkerColor(kRed);
    rawff_ppdata_recoreco_down[icent]->SetMarkerStyle(24);
    if(do_divide==0) {
      rawff_pbpbdata_recoreco_up[icent]->Draw("same");
      rawff_pbpbdata_recoreco_down[icent]->Draw("same");
      rawff_ppdata_recoreco_up[icent]->Draw("same");
      rawff_ppdata_recoreco_down[icent]->Draw("same");
    } else {
      rawff_pbpbdata_recoreco_up[icent]->Divide(rawff_pbpbdata_recoreco_down[icent]);
      rawff_ppdata_recoreco_up[icent]->Divide(rawff_ppdata_recoreco_down[icent]);
      rawff_pbpbdata_recoreco_up[icent]->Draw("same");
      rawff_ppdata_recoreco_up[icent]->Draw("same");
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
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco_up[icent],"PbPb FF","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_ppdata_recoreco_up[icent],"pp FF","p");
      } else {
        leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco_up[icent],"purity +10/-10% PbPb FF","p");
        leg_ff_pbpbsub[icent]->AddEntry(rawff_ppdata_recoreco_up[icent],"purity +10/-10% pp FF","p");
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
    }
    else if(icent==2)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"0.3 < |#eta^{jet}| < 1.6","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("p_{T}^{jet} > %d GeV",jetptmin),"");
    }
    else if(icent==3)
    {
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"Pythia+Hydjet","");
      leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],"#sigma_{i#eta#eta}<0.10","");
    }
    leg_ff_pbpbsub[icent]->AddEntry(rawff_pbpbdata_recoreco[icent],Form("%s",cents[icent].data()),"");
    leg_ff_pbpbsub[icent]->Draw();
  }

  call->cd(1);
  TH2D * axis_dummy;
  if(do_divide==0) axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,0,yaxismax);
  else             axis_dummy = new TH2D("axis_dummy","",1,0.01,4.99,1,ratioyaxismin,ratioyaxismax);
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

  if(do_divide==0)
  {
    int labelspace = yaxismax / 4;
    const int nlabels = yaxismax/labelspace;
    TLatex * laxis[nlabels];
    for (int ilatex = 0; ilatex < nlabels; ilatex++) {
      laxis[ilatex] = new TLatex(2.,ilatex*labelspace-0.1,Form("%d",ilatex*labelspace));
      laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
      laxis[ilatex]->Draw();
    }
  } else  {
    TLatex * laxis[5];
    for (int ilatex = 0; ilatex < 5; ilatex++) {
      laxis[ilatex] = new TLatex(1.8,(4+ilatex)*0.2-0.02,Form("%2.1f",(4+ilatex)*0.2));
      laxis[ilatex]->SetTextSize(laxis[ilatex]->GetTextSize()*1.2);
      laxis[ilatex]->Draw();
    }
  }
  ldndxi->Draw();
  if(do_divide==0) {
    call->SaveAs(Form("syst_phopurity_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d.png",phoetmin,phoetmax,jetptmin,gammaxi));
    call->SaveAs(Form("syst_phopurity_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  } else {
    call->SaveAs(Form("syst_phopurity_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d_ratio.png",phoetmin,phoetmax,jetptmin,gammaxi));
    call->SaveAs(Form("syst_phopurity_%d_%d_uemixff_jetpt%d_pbpbdata_recoreco_%d_ratio.pdf",phoetmin,phoetmax,jetptmin,gammaxi));
  }
}
