#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"

int calc_weights(const char* data_file, const char* mc_file, const char* output_file) {
    TFile* fdata = new TFile(data_file, "read");
    TFile* fmc = new TFile(mc_file, "read");

    TTree* tdata = (TTree*)fdata->Get("pjtt");
    TTree* tmc = (TTree*)fmc->Get("pjtt");

    TFile* foutput = new TFile(output_file, "recreate");

    TH1D* hvz_data = new TH1D("hvz_data", "", 50, -15, 15);
    TH1D* hvz_mc = new TH1D("hvz_mc", "", 50, -15, 15);

    tdata->Draw("vz>>hvz_data", "weight * abs(vz)<15", "goff");
    tmc->Draw("vz>>hvz_mc", "weight * abs(vz)<15", "goff");

    TH1D* hvz = (TH1D*)hvz_data->Clone("hvz");
    TH1D* hvz_hist = (TH1D*)hvz_data->Clone("hvz_hist");
    hvz_hist->Divide(hvz_mc);

    hvz_data->Fit("gaus");
    hvz_mc->Fit("gaus");

    TF1* fit_data = (TF1*)hvz_data->GetFunction("gaus");
    TF1* fit_mc = (TF1*)hvz_mc->GetFunction("gaus");

    for (int i=1; i<=hvz->GetNbinsX(); ++i)
        hvz->SetBinContent(i, fit_data->Eval(hvz->GetXaxis()->GetBinCenter(i)) / fit_mc->Eval(hvz->GetXaxis()->GetBinCenter(i)));

    TH1D* hcent_data = new TH1D("hcent_data", "", 50, 0, 200);
    TH1D* hcent_mc = new TH1D("hcent_mc", "", 50, 0, 200);

    tdata->Draw("hiBin>>hcent_data", "weight * abs(vz)<15", "goff");
    tmc->Draw("hiBin>>hcent_mc", "weight * abs(vz)<15", "goff");

    TH1D* hcent = (TH1D*)hcent_data->Clone("hcent");
    TH1D* hcent_hist = (TH1D*)hcent_data->Clone("hcent_hist");
    hcent_hist->Divide(hcent_mc);

    if (hcent->Integral(1, hcent->GetNbinsX()) > 0) {
        hcent_hist->Fit("pol9", "", "", 0, 195);
        TF1* fit_cent = (TF1*)hcent_hist->GetFunction("pol9");

        for (int i=1; i<hcent->GetNbinsX(); ++i)
            hcent->SetBinContent(i, fit_cent->Eval(hcent->GetXaxis()->GetBinCenter(i)));
        hcent->SetBinContent(hcent->GetNbinsX(), 0);
    }

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
