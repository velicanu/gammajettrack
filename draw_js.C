#include "TFile.h"
#include "TH1.h"
#include "TMath.h"

#include <string>

float purity_pbpbdata[4] = {0.681689, 0.730339, 0.775276, 0.825922};
float purity_pbpbmc[4] = {0.922658, 0.957185, 0.973422, 0.982594};
float purity_ppdata[4] = {0.841322, 0.841322, 0.841322, 0.841322};

int min_hiBin[4] = {0, 20, 60, 100};
int max_hiBin[4] = {20, 60, 100, 200};

int draw_js(std::string sample, const char* type, const char* fname, const char* outfname) {
    TFile* finput = new TFile(fname, "read");

    TFile* fout = new TFile(outfname, "update");

    TH1::SetDefaultSumw2();

    float purity[4];
    for (int i=0; i<4; ++i) {
        if (sample == "pbpbmc")
            purity[i] = purity_pbpbmc[i];
        else if (sample == "pbpbdata")
            purity[i] = purity_pbpbdata[i];
        else if (sample == "ppdata")
            purity[i] = purity_ppdata[i];
        else
            return 1;
    }

    TH1D* hjetpt[4] = {0};
    TH1D* hjetpt_mix[4] = {0};
    TH1D* hjetpt_sb[4] = {0};
    TH1D* hjetpt_mix_sb[4] = {0};

    TH1D* hjs[4] = {0};
    TH1D* hjs_ue[4] = {0};
    TH1D* hjs_jet[4] = {0};
    TH1D* hjs_jet_ue[4] = {0};
    TH1D* hjs_sb[4] = {0};
    TH1D* hjs_ue_sb[4] = {0};
    TH1D* hjs_jet_sb[4] = {0};
    TH1D* hjs_jet_ue_sb[4] = {0};

    TH1D* hjs_sub[4] = {0};
    TH1D* hjs_jet_sub[4] = {0};
    TH1D* hjs_sb_sub[4] = {0};
    TH1D* hjs_jet_sb_sub[4] = {0};

    TH1D* hjs_signal[4] = {0};
    TH1D* hjs_sideband[4] = {0};

    TH1D* hjs_final[4] = {0};

    for (int i=0; i<4; ++i) {
        std::string tag = Form("%s_%s_%i_%i", sample.c_str(), type, min_hiBin[i], max_hiBin[i]);

        hjetpt[i] = (TH1D*)finput->Get(Form("hjetpt_%s", tag.c_str()));
        hjetpt_mix[i] = (TH1D*)finput->Get(Form("hjetptjetmix_%s", tag.c_str()));
        hjetpt_sb[i] = (TH1D*)finput->Get(Form("hjetptsideband_%s", tag.c_str()));
        hjetpt_mix_sb[i] = (TH1D*)finput->Get(Form("hjetptjetmixsideband_%s", tag.c_str()));

        hjs[i] = (TH1D*)finput->Get(Form("hgammaffxi_%s", tag.c_str()));
        hjs_ue[i] = (TH1D*)finput->Get(Form("hgammaffxiuemix_%s", tag.c_str()));
        hjs_jet[i] = (TH1D*)finput->Get(Form("hgammaffxijetmix_%s", tag.c_str()));
        hjs_jet_ue[i] = (TH1D*)finput->Get(Form("hgammaffxijetmixue_%s", tag.c_str()));
        hjs_sb[i] = (TH1D*)finput->Get(Form("hgammaffxisideband_%s", tag.c_str()));
        hjs_ue_sb[i] = (TH1D*)finput->Get(Form("hgammaffxiuemixsideband_%s", tag.c_str()));
        hjs_jet_sb[i] = (TH1D*)finput->Get(Form("hgammaffxijetmixsideband_%s", tag.c_str()));
        hjs_jet_ue_sb[i] = (TH1D*)finput->Get(Form("hgammaffxijetmixuesideband_%s", tag.c_str()));

        hjs_sub[i] = (TH1D*)hjs[i]->Clone(Form("hjs_sub_%s", tag.c_str()));
        hjs_jet_sub[i] = (TH1D*)hjs_jet[i]->Clone(Form("hjs_jet_sub_%s", tag.c_str()));
        hjs_sb_sub[i] = (TH1D*)hjs_sb[i]->Clone(Form("hjs_sb_sub_%s", tag.c_str()));
        hjs_jet_sb_sub[i] = (TH1D*)hjs_jet_sb[i]->Clone(Form("hjs_jet_sb_sub_%s", tag.c_str()));

        hjs_sub[i]->Add(hjs_ue[i], -1);
        hjs_jet_sub[i]->Add(hjs_jet_ue[i], -1);
        hjs_sb_sub[i]->Add(hjs_ue_sb[i], -1);
        hjs_jet_sb_sub[i]->Add(hjs_jet_ue_sb[i], -1);

        hjs_signal[i] = (TH1D*)hjs_sub[i]->Clone(Form("hjs_signal_%s", tag.c_str()));
        hjs_sideband[i] = (TH1D*)hjs_sb_sub[i]->Clone(Form("hjs_sideband_%s", tag.c_str()));

        hjs_signal[i]->Add(hjs_jet_sub[i], -1);
        hjs_signal[i]->Scale(1.0/(hjetpt[i]->Integral() - hjetpt_mix[i]->Integral()));
        hjs_sideband[i]->Add(hjs_jet_sb_sub[i], -1);
        hjs_sideband[i]->Scale(1.0/(hjetpt_sb[i]->Integral() - hjetpt_mix_sb[i]->Integral()));

        hjs_final[i] = (TH1D*)hjs_signal[i]->Clone(Form("hjs_final_%s", tag.c_str()));

        hjs_final[i]->Scale(1.0/purity[i]);
        hjs_final[i]->Add(hjs_sideband[i], (purity[i] - 1.0)/purity[i]);

        for (int j=1; j<=hjs_final[i]->GetNbinsX(); ++j) {
            float bin_ll = hjs_final[i]->GetBinLowEdge(j);
            float bin_ul = hjs_final[i]->GetBinLowEdge(j+1);
            hjs_final[i]->SetBinContent(j, hjs_final[i]->GetBinContent(j)/(TMath::Pi() * (bin_ul + bin_ll) * (bin_ul - bin_ll)));
            hjs_final[i]->SetBinError(j, hjs_final[i]->GetBinError(j)/(TMath::Pi() * (bin_ul + bin_ll) * (bin_ul - bin_ll)));
        }

        hjs_final[i]->SetYTitle("#rho(r)");
    }

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc > 4)
        for (int i=4; i<argc; ++i)
            draw_js(argv[1], argv[i], argv[2], argv[3]);

    return 0;
}
