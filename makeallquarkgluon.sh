phoet=(60 80)
jetpt=(30 40)
gammaxi=(0 1)

for gammaxi in `seq 0 1`
do
    for imc in `seq 0 1` # 0 is mc , 1 is data
    do
	for ipt in `seq 0 1`
	do
	    for icent in `seq 0 3`
	    do
		root -b -q drawquarkgluon.C\(${phoet[ipt]},${jetpt[ipt]},${icent},${imc},${gammaxi}\)
	    done
	done
    done
done
