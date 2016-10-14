mkdir test
for i in `ls | grep -v tmp_run.sh | grep -v pmerge.condor | grep -v gammajetSkim.exe | grep -v residuals | grep -v test `
do
    cp -r $i test
done
cd test
tar -czvf residuals.tgz *
mv residuals.tgz ..
cd ..
rm -rf test
