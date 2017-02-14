# xijet
## all systematics
# from root dataff5step.C\(60,1000,30,1,0,0,\"syst/syst_nominal/\",\"nominal.root\"\)
# from root dataff5step.C\(60,1000,30,1,1,0,\"v2syst/nominal/\",\"ratio_nominal.root\"\)

./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 0
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_all 0 all
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_all all

## just JES
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 1
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_JES 0 JES
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_JES JES
./plot2ff nominal_xijet.root systjes0_xijet.root sysSummary_JES_down 0 JES_down 0
./plot2ff nominal_xijet.root systjes1_xijet.root sysSummary_JES_up 0 JES_up 0
./plot2ff nominal_xijet.root systjes0_xijet.root sysSummary_JES_down_ratio 0 JES_down 1
./plot2ff nominal_xijet.root systjes1_xijet.root sysSummary_JES_up_ratio 0 JES_up 1


## just purity
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 2
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_purity 0 purity
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_purity purity
./plot2ff nominal_xijet.root systpurity0_xijet.root sysSummary_purity_down 0 purity_down 0
./plot2ff nominal_xijet.root systpurity1_xijet.root sysSummary_purity_up 0 purity_up 0
./plot2ff nominal_xijet.root systpurity0_xijet.root sysSummary_purity_down_ratio 0 purity_down 1
./plot2ff nominal_xijet.root systpurity1_xijet.root sysSummary_purity_up_ratio 0 purity_up 1

## just JER
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 3
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_JER 0 JER
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_JER JER
./plot2ff nominal_xijet.root systjer_mix_xijet.root sysSummary_JER 0 JER 0
./plot2ff nominal_xijet.root systjer_mix_xijet.root sysSummary_JER_ratio 0 JER 1



## just pes
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 4
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_pes 0 pes
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_pes pes
./plot2ff nominal_xijet.root systpes0_xijet.root sysSummary_pes_down 0 pes_down 0
./plot2ff nominal_xijet.root systpes1_xijet.root sysSummary_pes_up 0 pes_up 0
./plot2ff nominal_xijet.root systpes0_xijet.root sysSummary_pes_down_ratio 0 pes_down 1
./plot2ff nominal_xijet.root systpes1_xijet.root sysSummary_pes_up_ratio 0 pes_up 1

## just trk
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 5
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_trk 0 trk
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_trk trk
./plot2ff nominal_xijet.root systtrk_xijet.root sysSummary_trk 0 trk 0
./plot2ff nominal_xijet.root systtrk_xijet.root sysSummary_trk_ratio 0 trk 1

## just nbkg
./ff_systematics.exe gammaxi0_sys.list gammaxi0_sys.root 6
./add_sys.exe gammaxi0_sys.root gammaxi0_sys_plot.root
./plot_ff nominal.root gammaxi0_sys_plot.root sysSummary_result_nbkg 0 nbkg
./plot_ff_ratio ratio_nominal.root gammaxi0_sys_plot.root sysSummary_result_ratio_nbkg nbkg
./plot2ff nominal_xijet.root systnbkg_xijet.root sysSummary_nbkg 0 nbkg 0
./plot2ff nominal_xijet.root systnbkg_xijet.root sysSummary_nbkg_ratio 0 nbkg 1
