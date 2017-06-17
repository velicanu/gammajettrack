#!/bin/bash
a=(60 60 60 80 80 80)
b=(30 30 30 40 40 40)
c=(0 1 2 0 1 2)

for i in `seq 0 5`
do
    root -b -q draw3step.C\(${a[i]},1000,${b[i]},1,0,0,${c[i]}\)  
    root -b -q draw3step.C\(${a[i]},1000,${b[i]},1,0,1,${c[i]}\)  
done

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
	root -b -q dataff5step.C\(${aphoetmin[$i]},1000,${ajetptmin[$i]},1,0,${xigamma},\"v3syst/nominal/\",\"finalff_${aphoetmin[$i]}_1000_uemixff_jetpt${ajetptmin[$i]}_pbpbdata_recoreco_${xigamma}.root\"\)
done

hadd -f mc_pbpb.root finalff_*.root mc_pbpb_*_1000_*_*_gammaxi*.root
# rm finalff_*.root mc_pbpb_*_1000_*_*_gammaxi*.root
