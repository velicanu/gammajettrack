#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

#include <fstream>
#include <vector>
#include <string>

#include "systematics.h"
#include "error_bands.h"

std::string sys_types[20] = {
    "jer_03", "jer_06", "jer_10", "jes_03", "jes_06", "jes_10", "jes_m03", "jes_m06", "jes_m10", "pes_03", "pes_06", "pes_10", "pes_m03", "pes_m06", "pes_m10", "trk", "purity_up", "purity_up_minus", "purity_down_plus", "purity_down"
};

std::string fit_funcs[20] = {
    "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2", "pol2"
};

int options[20] = {
    4, 4, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 0
};

int special[20] = {
    0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1
};

std::string sys_labels[20] = {
    "JER", "JER", "JER", "JES", "JES", "JES", "JES", "JES", "JES", "photon energy", "photon energy", "photon energy", "photon energy", "photon energy", "photon energy", "tracking", "photon purity", "photon purity", "photon purity", "photon purity"
};

int calc_systematics(const char* nominal_file, const char* filelist, const char* histlist, const char* label) {
    TH1::AddDirectory(kFALSE);
    TH1::SetDefaultSumw2(kTRUE);

    std::string line;

    std::vector<std::string> hist_list;
    std::ifstream hist_stream(histlist);
    if (!hist_stream) return 1;
    while (std::getline(hist_stream, line))
        hist_list.push_back(line);

    std::size_t nhists = hist_list.size();
    if (!nhists) {printf("0 total hists!\n"); return 1;}

    std::vector<std::string> file_list;
    std::ifstream file_stream(filelist);
    if (!file_stream) return 1;
    while (std::getline(file_stream, line))
        file_list.push_back(line);

    std::size_t nfiles = file_list.size();
    if (!nfiles) {printf("0 total files!\n"); return 1;}

    TFile* fnominal = new TFile(nominal_file, "read");
    TH1F* hnominals[nhists] = {0};
    for (std::size_t i=0; i<nhists; ++i)
        hnominals[i] = (TH1F*)fnominal->Get(hist_list[i].c_str());

    TFile* fsys[nfiles] = {0};
    for (std::size_t i=0; i<nfiles; ++i)
        fsys[i] = new TFile(file_list[i].c_str(), "read");

    TFile* fout = new TFile(Form("%s-systematics.root", label), "update");

    total_sys_var_t* total_sys_vars[nhists] = {0};
    sys_var_t* sys_vars[nhists][nfiles] = {0};
    for (std::size_t i=0; i<nhists; ++i) {
        total_sys_vars[i] = new total_sys_var_t(hist_list[i], hnominals[i]);

        for (std::size_t j=0; j<nfiles; ++j) {
            sys_vars[i][j] = new sys_var_t(hist_list[i], sys_types[j], hnominals[i], (TH1F*)fsys[j]->Get(hist_list[i].c_str()));
            sys_vars[i][j]->fit_sys(fit_funcs[j].c_str(), "pol2");
            sys_vars[i][j]->write();

            if (special[j]) {
                sys_var_t* tmp_sys_var = sys_vars[i][j];
                sys_vars[i][j] = new sys_var_t(sys_vars[i][j-1], tmp_sys_var);
                sys_vars[i][j]->fit_sys(fit_funcs[j].c_str(), "pol2");
                sys_vars[i][j]->write();
            }

            total_sys_vars[i]->add_sys_var(sys_vars[i][j], options[j]);
        }
        total_sys_vars[i]->write();
    }

    for (std::size_t i=0; i<nfiles; ++i)
        fsys[i]->Close();

    TCanvas* c1[nhists] = {0};
    for (std::size_t i=0; i<nhists; ++i) {
        c1[i] = new TCanvas(Form("sys_%s", hist_list[i].c_str()), "", 900, 900);

        int p = 1;
        c1[i]->Divide(3, 3);
        for (std::size_t j=0; j<nfiles; ++j) {
            c1[i]->cd(p);
            if (options[j] != 4) {
                sys_vars[i][j]->get_diff_abs()->SetStats(0);
                sys_vars[i][j]->get_diff_abs()->SetTitle(sys_labels[j].c_str());
                sys_vars[i][j]->get_diff_abs()->Draw("hist e");
                ++p;
            }
        }
        if (p < 10) {
            c1[i]->cd(p);
            total_sys_vars[i]->get_total()->SetStats(0);
            total_sys_vars[i]->get_total()->SetTitle("total systematics");
            total_sys_vars[i]->get_total()->Draw();
        }

        c1[i]->SaveAs(Form("sys_%s-%s.png", hist_list[i].c_str(), label));
    }

    fout->Write("", TObject::kOverwrite);
    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 5)
       return calc_systematics(argv[1], argv[2], argv[3], argv[4]);
    else
        return 1;
}
