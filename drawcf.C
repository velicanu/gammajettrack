{
  TFile *_file0 = TFile::Open("all.root");
  TH2D * jsig = (TH2D*)_file0->Get("hJetSig");
  TH2D * jmix = (TH2D*)_file0->Get("hJetMix");
  TH2D * gsig = (TH2D*)_file0->Get("hGammaSig");
  TH2D * gmix = (TH2D*)_file0->Get("hGammaMix");
  TH2D * jcor = (TH2D*)jsig->Clone("jcor");
  TH2D * gcor = (TH2D*)gsig->Clone("gcor");
  
  TCanvas c1;
  jsig->Draw("surf1");
  c1.SaveAs("jsig.png");
  TCanvas c2;
  gsig->Draw("surf1");
  c2.SaveAs("gsig.png");
  TCanvas c3;
  jmix->Draw("surf1");
  c3.SaveAs("jmix.png");
  TCanvas c4;
  gmix->Draw("surf1");
  c4.SaveAs("gmix.png");
  
  jcor->Divide(jmix);
  gcor->Divide(jmix);
  
  TCanvas c5;
  jcor->Draw("surf1");
  c5.SaveAs("jcor.png");
  TCanvas c6;
  gcor->Draw("surf1");
  c6.SaveAs("gcor.png");
  jcor->SetAxisRange(-2,2,"X");
  jcor->SetAxisRange(-TMath::Pi()/2.0,TMath::Pi()*3/2.0,"Y");
  gcor->SetAxisRange(-2,2,"X");
  gcor->SetAxisRange(-TMath::Pi()/2.0,TMath::Pi()*3/2.0,"Y");
  TCanvas c7;
  jcor->Draw("surf1");
  c7.SaveAs("jcor_zoom.png");
  TCanvas c8;
  gcor->Draw("surf1");
  c8.SaveAs("gcor_zoom.png");
  


  
}
