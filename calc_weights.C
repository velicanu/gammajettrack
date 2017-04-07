#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

int calc_weights(const char* data_file, const char* mc_file, const char* output_file) {
    TFile* fdata = new TFile(data_file, "read");
    TFile* fmc = new TFile(mc_file, "read");

    TTree* tdata = (TTree*)fdata->Get("pjtt");
    TTree* tmc = (TTree*)fmc->Get("pjtt");

    TFile* foutput = new TFile(output_file, "recreate");

    TH1D* hvz_data = new TH1D("hvz_data", "", 50, -15, 15);
    TH1D* hvz_mc = new TH1D("hvz_mc", "", 50, -15, 15);

    tdata->Draw("vz>>hvz_data", "abs(vz)<15", "goff");
    tmc->Draw("vz>>hvz_mc", "abs(vz)<15", "goff");

    TH1D* hvz = (TH1D*)hvz_data->Clone("hvz");
    hvz->Divide(hvz_mc);

    TH1D* hcent_data = new TH1D("hcent_data", "", 50, 0, 200);
    TH1D* hcent_mc = new TH1D("hcent_mc", "", 50, 0, 200);

    tdata->Draw("hiBin>>hcent_data", "abs(vz)<15", "goff");
    tmc->Draw("hiBin>>hcent_mc", "abs(vz)<15", "goff");

    TH1D* hcent = (TH1D*)hcent_data->Clone("hcent");
    hcent->Divide(hcent_mc);

    foutput->Write("", TObject::kOverwrite);
    foutput->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return calc_weights(argv[1], argv[2], argv[3]);
    else
        return 1;
}
