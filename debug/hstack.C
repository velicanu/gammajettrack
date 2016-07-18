TCanvas *hstack() {
// Example of stacked histograms: class THStack
//
//  Author: Rene Brun
   
   THStack *hs = new THStack("hs","Stacked 1D histograms");
   //create three 1-d histograms
   TH1F *h1st = new TH1F("h1st","test hstack",100,-4,4);
   h1st->FillRandom("gaus",20000);
   h1st->SetFillColor(TColor::GetColor("#9999FF"));
   hs->Add(h1st);
   TH1F *h2st = new TH1F("h2st","test hstack",100,-4,4);
   h2st->FillRandom("gaus",15000);
   h2st->SetFillColor(TColor::GetColor("#FFFF99"));
   hs->Add(h2st);
   TH1F *h3st = new TH1F("h3st","test hstack",100,-4,4);
   h3st->FillRandom("gaus",10000);
   h3st->SetFillColor(TColor::GetColor("#FF9933"));
   hs->Add(h3st);
   TH1F *h4st = new TH1F("h4st","test hstack",100,-4,4);
   h4st->FillRandom("gaus",10000);
   h4st->SetFillColor(TColor::GetColor("#9933CC"));
   hs->Add(h4st);
   TH1F *h5st = new TH1F("h5st","test hstack",100,-4,4);
   h5st->FillRandom("gaus",10000);
   h5st->SetFillColor(TColor::GetColor("#006600"));
   hs->Add(h5st);
   TH1F *h6st = new TH1F("h6st","test hstack",100,-4,4);
   h6st->FillRandom("gaus",10000);
   h6st->SetFillColor(TColor::GetColor("#CC0000"));
   hs->Add(h6st);
   
   TCanvas *cst = new TCanvas("cst","stacked hists");
   hs->Draw("hist");
   return cst;
}