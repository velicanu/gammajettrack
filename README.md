# quark gluon fitting

## Step 1: Getting the mc jet pt spectrum for re-normalizing

```bash
./runmc.sh 999            # makes jet pt histograms
./haddpyreweight.sh       # combines mc and PbPb data histograms to create weight files , input is output of above line and all files in v3syst/nominal/
```

## Step 2: Running ffgamma on MC

```bash
./runmc.sh                # run FF on MC in the bins configured inside
mkdir tmp_closure
cp closure_* tmp_closure  # just to backup mc histograms since runmc takes a while to run on all the bins
```

## Step 3: Quark gluon fit

```bash
./drawqg.sh
```

