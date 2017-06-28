#!/bin/bash
phomin=(60 60 60 80 80 80)
jetmin=(30 30 30 40 40 40)
qg=(0 1 2 0 1 2)

for i in `seq 0 5`
do
    
    root -b -q draw3step.C\(${phomin[i]},1000,${jetmin[i]},1,0,0,${qg[i]}\)  
    root -b -q draw3step.C\(${phomin[i]},1000,${jetmin[i]},1,0,1,${qg[i]}\)  
done

ajetptmin=(30 40)
aphoetmin=(60 80)

# make nominal data histograms, input is nominal output of ffgamma.C
for xigamma in `seq 0 1`
do
    for i in `seq 0 1`
    do
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,0,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}.root\"\)
    done
done

hadd -f mc_pbpb.root finalff_*.root mc_pbpb_*_1000_*_*_gammaxi*.root
rm finalff_*.root mc_pbpb_*_1000_*_*_gammaxi*.root
