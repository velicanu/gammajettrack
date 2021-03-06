#include "TFile.h"
#include "TH1.h"

int calc_iso_systematics(const char* nominal, const char* variation, const char* data, const char* sample, const char* output_sample, const char* type, int phoetmin, int jetptmin, int gammaxi) {
    TH1::SetDefaultSumw2(kTRUE);

    TFile* fnominal = new TFile(nominal, "read");
    TH1D* hnominal[4] = {0};
    hnominal[0] = (TH1D*)fnominal->Get(Form("hjs_final_%s_%s_0_20", sample, type))->Clone("hnominal_0_20");
    hnominal[1] = (TH1D*)fnominal->Get(Form("hjs_final_%s_%s_20_60", sample, type))->Clone("hnominal_20_60");
    hnominal[2] = (TH1D*)fnominal->Get(Form("hjs_final_%s_%s_60_100", sample, type))->Clone("hnominal_60_100");
    hnominal[3] = (TH1D*)fnominal->Get(Form("hjs_final_%s_%s_100_200", sample, type))->Clone("hnominal_100_200");

    TFile* fvariation = new TFile(variation, "read");
    TH1D* hvariation[4] = {0};
    hvariation[0] = (TH1D*)fvariation->Get(Form("hjs_final_%s_%s_0_20", sample, type))->Clone("hvariation_0_20");
    hvariation[1] = (TH1D*)fvariation->Get(Form("hjs_final_%s_%s_20_60", sample, type))->Clone("hvariation_20_60");
    hvariation[2] = (TH1D*)fvariation->Get(Form("hjs_final_%s_%s_60_100", sample, type))->Clone("hvariation_60_100");
    hvariation[3] = (TH1D*)fvariation->Get(Form("hjs_final_%s_%s_100_200", sample, type))->Clone("hvariation_100_200");

    TFile* fdata = new TFile(data, "read");
    TH1D* hdata[4] = {0};
    hdata[0] = (TH1D*)fdata->Get(Form("hjs_final_%s_%s_0_20", output_sample, type))->Clone("hdata_0_20");
    hdata[1] = (TH1D*)fdata->Get(Form("hjs_final_%s_%s_20_60", output_sample, type))->Clone("hdata_20_60");
    hdata[2] = (TH1D*)fdata->Get(Form("hjs_final_%s_%s_60_100", output_sample, type))->Clone("hdata_60_100");
    hdata[3] = (TH1D*)fdata->Get(Form("hjs_final_%s_%s_100_200", output_sample, type))->Clone("hdata_100_200");

    TFile* foutput = new TFile(Form("iso_%s_%i_%i_gxi%i_js_final.root", output_sample, phoetmin, jetptmin, gammaxi), "recreate");
    TH1D* houtput[4] = {0};
    houtput[0] = (TH1D*)hdata[0]->Clone(Form("hjs_final_%s_%s_0_20", output_sample, type));
    houtput[1] = (TH1D*)hdata[1]->Clone(Form("hjs_final_%s_%s_20_60", output_sample, type));
    houtput[2] = (TH1D*)hdata[2]->Clone(Form("hjs_final_%s_%s_60_100", output_sample, type));
    houtput[3] = (TH1D*)hdata[3]->Clone(Form("hjs_final_%s_%s_100_200", output_sample, type));

    for (int i=0; i<4; ++i) {
        hvariation[i]->Divide(hnominal[i]);
        houtput[i]->Multiply(hvariation[i]);
    }

    foutput->Write("", TObject::kOverwrite);
    foutput->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 10)
        return calc_iso_systematics(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], atoi(argv[7]), atoi(argv[8]), atoi(argv[9]));
    else
        return 1;
}
