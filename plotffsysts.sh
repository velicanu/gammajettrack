asyst=(all jer jes pes purity trk)
ajetptmin=(30 40)
aphoetmin=(60 80)
echo ${systarray[*]}

# make nominal data histograms
for xigamma in `seq 0 1`
do
    for i in `seq 0 1`
    do
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,0,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_0.root\"\)
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,1,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_0_ratio.root\"\)
    done
done


for xigamma in `seq 0 1`
do
    for syst in "${asyst[@]}"
    do
	for i in `seq 0 1`
	do
	    ./plot_ff finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_0.root data_${aphoetmin[$i]}_1000_${ajetptmin[$i]}_gammaxi0-systematics.root sysSummary_result 0 ${syst} 0 ${aphoetmin[$i]} 1000 ${ajetptmin[$i]}
	done
    done
done


# clean up
rm finalff_*.root




