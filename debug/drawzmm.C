{
  TFile *_file0 = TFile::Open("zmm.root");
  TCanvas * c1 = new TCanvas();
  hzjetratio_ppdata_05->Draw();
  c1->SaveAs("hzjetratio_ppdata_05_zmm.png");
  hzjetratio_ppdata_06->Draw();
  c1->SaveAs("hzjetratio_ppdata_06_zmm.png");
  hzjetratio_ppdata_07->Draw();
  c1->SaveAs("hzjetratio_ppdata_07_zmm.png");
  hzjetratio_ppdata_08->Draw();
  c1->SaveAs("hzjetratio_ppdata_08_zmm.png");
  hzjetratio_ppdata_09->Draw();
  c1->SaveAs("hzjetratio_ppdata_09_zmm.png");
}
