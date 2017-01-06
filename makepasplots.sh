cd /home/ursu/gammajettrack/
root -b -q dataff5step.C\(60,1000,30,1,0,0,\"syst/syst_nominal/\",\"finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0.root\"\)
root -b -q dataff5step.C\(60,1000,30,1,1,0,\"syst/syst_nominal/\",\"finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0_ratio.root\"\)
root -b -q dataff5step.C\(60,1000,30,1,0,1,\"syst/syst_nominal/\",\"finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1.root\"\)
root -b -q dataff5step.C\(60,1000,30,1,1,1,\"syst/syst_nominal/\",\"finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1_ratio.root\"\)
./plot_ff finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0.root sum_xijet_sys.root finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0
./plot_ff_ratio finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0_ratio.root sum_xijet_sys.root finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_0_ratio
./plot_ff finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1.root sum_xigamma_sys.root finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1
./plot_ff_ratio finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1_ratio.root sum_xigamma_sys.root finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco_1_ratio

cp finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco*.pdf ~/cmspapers/tdr2/notes/AN-16-082/trunk/figures/
mv finalff_60_1000_uemixff_jetpt30_pbpbdata_recoreco*.pdf ~/cmspapers/tdr2/notes/HIN-16-014/trunk/figures/
cd -
