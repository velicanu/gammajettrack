rm g.DijetSkim-xaa11-*.root
echo running pF FF histos...
./ztree.exe /data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/DijetSkim-xaa.root g.DijetSkim-xaa11-all.root pbpbdatamb -99 &
./ztree.exe /data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/DijetSkim-xaa.root g.DijetSkim-xaa11-m1.root pbpbdatamb -1 &
./ztree.exe /data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/DijetSkim-xaa.root g.DijetSkim-xaa11-1.root pbpbdatamb 1 &
./ztree.exe /data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/DijetSkim-xaa.root g.DijetSkim-xaa11-2.root pbpbdatamb 2 &
./ztree.exe /data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/DijetSkim-xaa.root g.DijetSkim-xaa11-3.root pbpbdatamb 3 &
wait
echo done, merging output...
hadd -f allmb.root g.DijetSkim-xaa11-*.root
echo done
