#include "TFile.h"
#include "TH1.h"
#include "TMath.h"

#include <vector>
#include <string>

int min_hiBin[4] = {0, 20, 60, 100};
int max_hiBin[4] = {20, 60, 100, 200};

double rebinning[9] = {0, 0.05, 0.1, 0.15, 0.2, 0.3, 0.5, 0.7, 1.0};

int draw_js(std::string sample, const char* type, const char* fname, const char* outfname, int phoetmin, int purity_group) {
    TFile* finput = new TFile(fname, "read");

    TFile* fout = new TFile(outfname, "update");

    TH1::SetDefaultSumw2();

    std::vector<float> purity_pbpbdata_60;
    std::vector<float> purity_pbpbmc_60;
    std::vector<float> purity_ppdata_60;
    std::vector<float> purity_ppmc_60;

    std::vector<float> purity_pbpbdata_80;
    std::vector<float> purity_pbpbmc_80;
    std::vector<float> purity_ppdata_80;
    std::vector<float> purity_ppmc_80;

    std::vector<float> purity_pbpbdata_100;
    std::vector<float> purity_pbpbmc_100;
    std::vector<float> purity_ppdata_100;
    std::vector<float> purity_ppmc_100;

    if (purity_group == 0) {
        purity_pbpbdata_60 = {0.681689, 0.730339, 0.775276, 0.825922};
        purity_pbpbmc_60 = {0.922658, 0.957185, 0.973422, 0.982594};
        purity_ppdata_60 = {0.841322, 0.841322, 0.841322, 0.841322};
        purity_ppmc_60 = {0.984076, 0.984076, 0.984076, 0.984076};

        purity_pbpbdata_80 = {0.685621, 0.751769, 0.787902, 0.816627};
        purity_pbpbmc_80 = {0.92439, 0.957436, 0.96544, 0.980661};
        purity_ppdata_80 = {0.853694, 0.853694, 0.853694, 0.853694};
        purity_ppmc_80 = {0.986312, 0.986312, 0.986312, 0.986312};

        purity_pbpbdata_100 = {0.700252, 0.792531, 0.821031, 0.797929};
        purity_pbpbmc_100 = {0.888486, 0.950618, 0.97097, 0.980991};
        purity_ppdata_100 = {0.851183, 0.851183, 0.851183, 0.851183};
        purity_ppmc_100 = {0.989016, 0.989016, 0.989016, 0.989016};
    } else if (purity_group == 1) {
        purity_pbpbdata_60 = {0.733169, 0.7693595, 0.797728, 0.8325445};
        purity_pbpbmc_60 = {0, 0, 0, 0};
        purity_ppdata_60 = {0.8548435, 0.8548435, 0.8548435, 0.8548435};
        purity_ppmc_60 = {0, 0, 0, 0};

        purity_pbpbdata_80 = {0.733652, 0.7916765, 0.803312, 0.815832};
        purity_pbpbmc_80 = {0, 0, 0, 0};
        purity_ppdata_80 = {0.8611955, 0.8611955, 0.8611955, 0.8611955};
        purity_ppmc_80 = {0, 0, 0, 0};

        purity_pbpbdata_100 = {0.7520495, 0.8221685, 0.8272325, 0.8300335};
        purity_pbpbmc_100 = {0, 0, 0, 0};
        purity_ppdata_100 = {0.859517, 0.859517, 0.859517, 0.859517};
        purity_ppmc_100 = {0, 0, 0, 0};
    } else if (purity_group == 2) {
        purity_pbpbdata_60 = {0.784649, 0.80838, 0.82018, 0.839167};
        purity_pbpbmc_60 = {0, 0, 0, 0};
        purity_ppdata_60 = {0.868365, 0.868365, 0.868365, 0.868365};
        purity_ppmc_60 = {0, 0, 0, 0};

        purity_pbpbdata_80 = {0.781683, 0.831584, 0.818722, 0.815832};
        purity_pbpbmc_80 = {0, 0, 0, 0};
        purity_ppdata_80 = {0.868697, 0.868697, 0.868697, 0.868697};
        purity_ppmc_80 = {0, 0, 0, 0};

        purity_pbpbdata_100 = {0.803847, 0.851806, 0.833434, 0.862138};
        purity_pbpbmc_100 = {0, 0, 0, 0};
        purity_ppdata_100 = {0.867851, 0.867851, 0.867851, 0.867851};
        purity_ppmc_100 = {0, 0, 0, 0};
    } else if (purity_group == -1) {
        purity_pbpbdata_60 = {0.632742, 0.68729, 0.72768, 0.775074};
        purity_pbpbmc_60 = {0, 0, 0, 0};
        purity_ppdata_60 = {0.8248265, 0.8248265, 0.8248265, 0.8248265};
        purity_ppmc_60 = {0, 0, 0, 0};

        purity_pbpbdata_80 = {0.641418, 0.7216615, 0.7562905, 0.7557395};
        purity_pbpbmc_80 = {0, 0, 0, 0};
        purity_ppdata_80 = {0.844883, 0.844883, 0.844883, 0.844883};
        purity_ppmc_80 = {0, 0, 0, 0};

        purity_pbpbdata_100 = {0.685424, 0.7598415, 0.829376, 0.755146};
        purity_pbpbmc_100 = {0, 0, 0, 0};
        purity_ppdata_100 = {0.8485415, 0.8485415, 0.8485415, 0.8485415};
        purity_ppmc_100 = {0, 0, 0, 0};
    } else if (purity_group == -2) {
        purity_pbpbdata_60 = {0.583795, 0.644241, 0.680084, 0.724226};
        purity_pbpbmc_60 = {0, 0, 0, 0};
        purity_ppdata_60 = {0.808331, 0.808331, 0.808331, 0.808331};
        purity_ppmc_60 = {0, 0, 0, 0};

        purity_pbpbdata_80 = {0.597215, 0.691554, 0.724679, 0.694852};
        purity_pbpbmc_80 = {0, 0, 0, 0};
        purity_ppdata_80 = {0.836072, 0.836072, 0.836072, 0.836072};
        purity_ppmc_80 = {0, 0, 0, 0};

        purity_pbpbdata_100 = {0.670596, 0.727152, 0.837721, 0.712363};
        purity_pbpbmc_100 = {0, 0, 0, 0};
        purity_ppdata_100 = {0.8459, 0.8459, 0.8459, 0.8459};
        purity_ppmc_100 = {0, 0, 0, 0};
    }

    std::vector<float> purity_pbpbdata;
    std::vector<float> purity_pbpbmc;
    std::vector<float> purity_ppdata;
    std::vector<float> purity_ppmc;

    switch (phoetmin) {
        case 60:
            purity_pbpbdata = purity_pbpbdata_60;
            purity_pbpbmc = purity_pbpbmc_60;
            purity_ppdata = purity_ppdata_60;
            purity_ppmc = purity_ppmc_60;
            break;
        case 80:
            purity_pbpbdata = purity_pbpbdata_80;
            purity_pbpbmc = purity_pbpbmc_80;
            purity_ppdata = purity_ppdata_80;
            purity_ppmc = purity_ppmc_80;
            break;
        case 120:
            purity_pbpbdata = purity_pbpbdata_100;
            purity_pbpbmc = purity_pbpbmc_100;
            purity_ppdata = purity_ppdata_100;
            purity_ppmc = purity_ppmc_100;
            break;
        default:
            printf("no purity values available!\n");
            return 1;
    }

    float purity[4];
    for (int i=0; i<4; ++i) {
        if (sample == "pbpbmc")
            purity[i] = purity_pbpbmc[i];
        else if (sample == "pbpbdata")
            purity[i] = purity_pbpbdata[i];
        else if (sample == "ppdata")
            purity[i] = purity_ppdata[i];
        else if (sample == "ppmc")
            purity[i] = purity_ppmc[i];
    }

    TH1D* hjetpt[4] = {0};
    TH1D* hjetpt_mix[4] = {0};
    TH1D* hjetpt_bkg[4] = {0};
    TH1D* hjetpt_mix_bkg[4] = {0};

    TH1D* hjs[4] = {0};
    TH1D* hjs_ue[4] = {0};
    TH1D* hjs_mix[4] = {0};
    TH1D* hjs_mix_ue[4] = {0};
    TH1D* hjs_bkg[4] = {0};
    TH1D* hjs_ue_bkg[4] = {0};
    TH1D* hjs_mix_bkg[4] = {0};
    TH1D* hjs_mix_ue_bkg[4] = {0};

    TH1D* hjs_sub[4] = {0};
    TH1D* hjs_mix_sub[4] = {0};
    TH1D* hjs_sub_bkg[4] = {0};
    TH1D* hjs_mix_sub_bkg[4] = {0};

    TH1D* hjs_signal[4] = {0};
    TH1D* hjs_background[4] = {0};

    TH1D* hjs_final_raw[4] = {0};
    TH1D* hjs_final[4] = {0};

    for (int i=0; i<4; ++i) {
        std::string tag = Form("%s_%s_%i_%i", sample.c_str(), type, min_hiBin[i], max_hiBin[i]);

        hjetpt[i] = (TH1D*)finput->Get(Form("hjetpt_%s", tag.c_str()));
        hjetpt_mix[i] = (TH1D*)finput->Get(Form("hjetpt_mix_%s", tag.c_str()));
        hjs[i] = (TH1D*)finput->Get(Form("hjetshape_%s", tag.c_str()));
        hjs_ue[i] = (TH1D*)finput->Get(Form("hjetshape_ue_%s", tag.c_str()));
        hjs_mix[i] = (TH1D*)finput->Get(Form("hjetshape_mix_%s", tag.c_str()));
        hjs_mix_ue[i] = (TH1D*)finput->Get(Form("hjetshape_mix_ue_%s", tag.c_str()));

        hjetpt_bkg[i] = (TH1D*)finput->Get(Form("hjetpt_bkg_%s", tag.c_str()));
        hjetpt_mix_bkg[i] = (TH1D*)finput->Get(Form("hjetpt_mix_bkg_%s", tag.c_str()));
        hjs_bkg[i] = (TH1D*)finput->Get(Form("hjetshape_bkg_%s", tag.c_str()));
        hjs_ue_bkg[i] = (TH1D*)finput->Get(Form("hjetshape_ue_bkg_%s", tag.c_str()));
        hjs_mix_bkg[i] = (TH1D*)finput->Get(Form("hjetshape_mix_bkg_%s", tag.c_str()));
        hjs_mix_ue_bkg[i] = (TH1D*)finput->Get(Form("hjetshape_mix_ue_bkg_%s", tag.c_str()));

        hjs_sub[i] = (TH1D*)hjs[i]->Clone(Form("hjs_sub_%s", tag.c_str()));
        hjs_mix_sub[i] = (TH1D*)hjs_mix[i]->Clone(Form("hjs_mix_sub_%s", tag.c_str()));
        hjs_sub[i]->Add(hjs_ue[i], -1);
        hjs_mix_sub[i]->Add(hjs_mix_ue[i], -1);

        hjs_sub_bkg[i] = (TH1D*)hjs_bkg[i]->Clone(Form("hjs_sub_bkg_%s", tag.c_str()));
        hjs_mix_sub_bkg[i] = (TH1D*)hjs_mix_bkg[i]->Clone(Form("hjs_mix_sub_bkg_%s", tag.c_str()));
        hjs_sub_bkg[i]->Add(hjs_ue_bkg[i], -1);
        hjs_mix_sub_bkg[i]->Add(hjs_mix_ue_bkg[i], -1);

        hjs_signal[i] = (TH1D*)hjs_sub[i]->Clone(Form("hjs_signal_%s", tag.c_str()));
        hjs_signal[i]->Add(hjs_mix_sub[i], -1);
        hjs_signal[i]->Scale(1.0/(hjetpt[i]->Integral() - hjetpt_mix[i]->Integral()));

        hjs_background[i] = (TH1D*)hjs_sub_bkg[i]->Clone(Form("hjs_background_%s", tag.c_str()));
        hjs_background[i]->Add(hjs_mix_sub_bkg[i], -1);
        hjs_background[i]->Scale(1.0/(hjetpt_bkg[i]->Integral() - hjetpt_mix_bkg[i]->Integral()));

        hjs_final_raw[i] = (TH1D*)hjs_signal[i]->Clone(Form("hjs_final_raw_%s", tag.c_str()));
        hjs_final_raw[i]->Scale(1.0/purity[i]);
        hjs_final_raw[i]->Add(hjs_background[i], (purity[i] - 1.0)/purity[i]);

        // rebin large deltar
        hjs_final[i] = (TH1D*)hjs_final_raw[i]->Rebin(8, Form("hjs_final_%s", tag.c_str()), rebinning);

        hjs_final[i]->Scale(1/hjs_final[i]->Integral(hjs_final[i]->FindBin(0.01), hjs_final[i]->FindBin(0.29)), "width");

        hjs_final[i]->SetYTitle("#rho(r)");
    }

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc > 6)
        for (int i=6; i<argc; ++i)
            draw_js(argv[1], argv[i], argv[2], argv[3], atoi(argv[4]), atoi(argv[5]));

    return 0;
}
