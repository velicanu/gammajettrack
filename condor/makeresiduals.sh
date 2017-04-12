mkdir test
for i in `ls | grep -v .sh | grep -v .condor | grep -v gammajetSkim.exe | grep -v residuals | grep -v test `
do
    cp -r $i test
done
cd test
tar -czvf residuals.tgz *
mv residuals.tgz ..
cd ..
rm -rf test
