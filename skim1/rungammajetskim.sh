if [ $# -ne 3 ]
then
  echo "Usage: ./rungammajetskim.sh <linenumber-1> <input-list> <out-dir>"
  exit 1
fi

echo ./rungammajetskim.sh $@
echo `hostname`
linenum=$(($1+1))

./gammajetSkim.exe `head -n${linenum} $2 | tail -n1 ` skim_${linenum}.root akPu4CaloJetAnalyzer

mv *.root $3
