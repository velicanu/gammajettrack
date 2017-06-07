asyst=(all jer jes pes purity trk)
axigamma=(xijet xigamma)
ajetptmin=(30 40)
aphoetmin=(60 80)
echo ${systarray[*]}

# make nominal data histograms, input is nominal output of ffgamma.C
for xigamma in `seq 0 1`
do
    for i in `seq 0 1`
    do
	mkdir -p results/${axigamma[$xigamma]}_${aphoetmin[$i]}/
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,0,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}.root\"\)
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,1,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}_ratio.root\"\)
    done
done

# make plots with systs, input is syst histograms
for xigamma in `seq 0 1`
do
    for syst in "${asyst[@]}"
    do
	for i in `seq 0 1`
	do
	    ./plot_ff finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}.root data_${aphoetmin[$i]}_1000_${ajetptmin[$i]}_gammaxi${xigamma}-systematics.root sysSummary_result 0 ${syst} ${xigamma} ${aphoetmin[$i]} 1000 ${ajetptmin[$i]} 0
	    ./plot_ff finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}_ratio.root data_${aphoetmin[$i]}_1000_${ajetptmin[$i]}_gammaxi${xigamma}-systematics.root sysSummary_result_ratio 0 ${syst} ${xigamma} ${aphoetmin[$i]} 1000 ${ajetptmin[$i]} 1
	    mv sysSummary_result*.p* results/${axigamma[$xigamma]}_${aphoetmin[$i]}/
	done
    done
done


# clean up
rm finalff_*.root
