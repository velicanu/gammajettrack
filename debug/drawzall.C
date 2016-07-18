{
  TFile *_file0 = TFile::Open("zall.root");
  TCanvas * c1 = new TCanvas();
  hzjetratio_ppdata_05->Draw();
  c1->SaveAs("hzjetratio_ppdata_05_zall.png");
  hzjetratio_ppdata_06->Draw();
  c1->SaveAs("hzjetratio_ppdata_06_zall.png");
  hzjetratio_ppdata_07->Draw();
  c1->SaveAs("hzjetratio_ppdata_07_zall.png");
  hzjetratio_ppdata_08->Draw();
  c1->SaveAs("hzjetratio_ppdata_08_zall.png");
  hzjetratio_ppdata_09->Draw();
  c1->SaveAs("hzjetratio_ppdata_09_zall.png");
}
