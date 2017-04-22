{
  int phoetmin[] = {60,80};
  int jetptmin[] = {30,40};
  for(int igammaxi = 0 ; igammaxi < 2 ; igammaxi++) {
    for(int iratio = 0 ; iratio < 2 ; iratio++) {
      for(int ipt = 0 ; ipt < 2 ; ipt++) {
	gROOT->ProcessLine(Form(".x draw3step.C(%d,1000,%d,1,%d,%d)",phoetmin[ipt],jetptmin[ipt],iratio,igammaxi));
	gROOT->ProcessLine(Form(".x drawpp4step.C(%d,1000,%d,1,%d,%d)",phoetmin[ipt],jetptmin[ipt],iratio,igammaxi));
      }
    }
  }
}
