#include "TFile.h"
#include "TH1.h"

#include "TCanvas.h"
#include "TLegend.h"

#include "SysVar.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define _JES_UP      1
#define _JES_DOWN    2
#define _PURITY_UP   3
#define _PURITY_DOWN 4

int ff_systematics(const char* file_list, const char* outputfile) {
    std::vector<std::string> sys_types {
        "nominal",
        "JES_up", "JES_down", "purity_up", "purity_down",
        "JER", "pes_up", "pes_down"
    };
    int n_sys_types = sys_types.size();

    std::vector<std::string> sys_files;
    std::ifstream file_stream(file_list);
    if (!file_stream) return 1;
    std::string line;
    while (std::getline(file_stream, line))
        sys_files.push_back(line);
    file_stream.close();

    int n_input_files = sys_files.size();

    TFile* input_files[n_input_files] = {0};
    std::vector<bool> valid_input(n_input_files, false);
    for (int i=0; i<n_input_files; ++i) {
        input_files[i] = new TFile(sys_files[i].c_str(), "read");
        valid_input[i] = (input_files[i] && input_files[i]->IsOpen());
    }

    std::vector<std::string> hist_names {
        "hgammaffxi_pbpbdata_recoreco_0_20", "hgammaffxi_ppdata_recoreco_0_20",
        "hgammaffxi_pbpbdata_recoreco_20_60", "hgammaffxi_ppdata_recoreco_20_60",
        "hgammaffxi_pbpbdata_recoreco_60_100", "hgammaffxi_ppdata_recoreco_60_100",
        "hgammaffxi_pbpbdata_recoreco_100_200", "hgammaffxi_ppdata_recoreco_100_200",
    };
    int n_hists = hist_names.size();

    TFile* output = new TFile(outputfile, "recreate");

    std::vector< std::vector<SysVar*> > systematics(n_hists, std::vector<SysVar*>());
    for (int i=0; i<n_hists; ++i) {
        std::string hist_name = hist_names[i];

        printf("nominal: %s\n", hist_name.c_str());
        TH1D* h1D_nominal = (TH1D*)input_files[0]->Get(hist_name.c_str());

        printf("calculating systematics...\n");
        for (int m=1; m<n_sys_types; ++m) {
            if (!valid_input[m])
                continue;

            TH1D* h1D_varied = (TH1D*)input_files[m]->Get(hist_name.c_str());

            SysVar* sys_hists = new SysVar(hist_name, sys_types[m]);
            sys_hists->init(h1D_nominal, h1D_varied);
            sys_hists->calc_sys();

            systematics[i].push_back(sys_hists);
        }
    }

    // std::vector<TotalSysVar*> total_sys;

    // printf("calculating total systematics...\n");

    // printf("size: %lu\n", systematics.size());
    // for (std::size_t i=0; i<systematics.size(); ++i) {
    //     printf("size: %lu\n", systematics[i].size());
    //     printf("i: %lu\n", i);
    //     std::size_t m = 0;
    //     TotalSysVar* total_sys_hists = new TotalSysVar();

    //     if (valid_input[_JES_UP] && valid_input[_JES_DOWN]) {
    //         TotalSysVar* JES_sys_hists = new TotalSysVar(systematics[i][m], systematics[i][m+1]);
    //         total_sys_hists->add_SysVar(JES_sys_hists);
    //         ++m; ++m;
    //     } else if (valid_input[_JES_UP] ^ valid_input[_JES_DOWN]) {
    //         total_sys_hists->add_SysVar(systematics[i][m]);
    //         ++m;
    //     }

    //     if (valid_input[_PURITY_UP] && valid_input[_PURITY_DOWN]) {
    //         TotalSysVar* purity_sys_hists = new TotalSysVar(systematics[i][m], systematics[i][m+1]);
    //         total_sys_hists->add_SysVar(purity_sys_hists);
    //         ++m; ++m;
    //     } else if (valid_input[_PURITY_UP] ^ valid_input[_PURITY_DOWN]) {
    //         total_sys_hists->add_SysVar(systematics[i][m]);
    //         ++m;
    //     }
    //     for (; m<systematics[i].size(); ++m) {
    //         total_sys_hists->add_SysVar(systematics[i][m]);
    //     }

    //     total_sys.push_back(total_sys_hists);
    // }

    printf("writing objects...\n");
    output->Write("", TObject::kOverwrite);
    output->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return ff_systematics(argv[1], argv[2]);
    else
        printf("Usage: ./ff_systematics <list of variations, e.g. gammaxi0_sys.list> <output to be used as input for add_sys>\n");

    return 1;
}
