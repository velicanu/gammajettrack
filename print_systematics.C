#include "TFile.h"
#include "TH1.h"

#include <fstream>
#include <string>
#include <vector>

#include "systematics.h"

std::string sys_labels[6] = {
    "Jet Energy Scale", "Jet Energy Resolution", "Photon Energy", "Photon Purity", "Tracking", "Photon Isolation"
};

std::string sample[4] = {
    "pbpbdata", "ppdata", "pbpbdata", "ppdata"
};

std::vector<std::string> jsreco = {
    "recoreco", "srecoreco", "recoreco", "srecoreco"
};

std::vector<std::string> ffreco = {
    "recoreco", "recoreco", "recoreco", "recoreco"
};

int print_systematics(const char* filelist, const char* histlist, const char* label) {
    std::string line;

    std::vector<std::string> hist_list;
    std::ifstream hist_stream(histlist);
    if (!hist_stream) return 1;
    while (std::getline(hist_stream, line))
        hist_list.push_back(line);

    std::size_t nhists = hist_list.size();
    if (!nhists) { printf("0 total hists!\n"); return 1; }

    std::vector<std::string> file_list;
    std::ifstream file_stream(filelist);
    if (!file_stream) return 1;
    while (std::getline(file_stream, line))
        file_list.push_back(line);

    std::size_t nfiles = file_list.size();
    if (!nfiles) { printf("0 total files!\n"); return 1; }

    TFile* fsys[nfiles] = {0};
    for (std::size_t i=0; i<nfiles; ++i)
        fsys[i] = new TFile(file_list[i].c_str(), "read");

    std::vector<std::string> reco;
    if (strcmp(label, "js") == 0)
        reco = jsreco;
    else
        reco = ffreco;

    // print systematics in Latex format
    printf("\\begin{table}[hbtp]\n");
    printf("  \\begin{center}\n");
    printf("    \\begin{tabular}{|l|r|r|r|r|}\n");
    printf("      \\hline\n");
    printf("      Systematic Uncertainty  & \\shortstack{$\\xi_{jet}$ \\\\ PbPb} & \\shortstack{$\\xi_{jet}$ \\\\ pp} & \\shortstack{$\\xi_{\\gamma}$ \\\\ PbPb} & \\shortstack{$\\xi_{\\gamma}$ \\\\ pp} \\\\\n");
    printf("      \\hline\n");
    for (std::size_t i=0; i<nhists; ++i) {
        printf("      %-22s", sys_labels[i].c_str());
        for (std::size_t j=0; j<nfiles; ++j) {
            std::string hist_name = Form("h%s_final_%s_%s_0_20_%s_ratio_abs", label, sample[j].c_str(), reco[j].c_str(), hist_list[i].c_str());
            printf("  & %6.1f\\%%", 100 * th1_average_content((TH1F*)fsys[j]->Get(hist_name.c_str())));
        }
        printf(" \\\\\n");
    }
    // printf("      \\hline\n");
    // printf("      Total Uncertainty     ");
    // for (std::size_t j=0; j<nfiles; ++j) {
    //     std::string hist_name = Form("h%s_final_%s_%s_0_20_systematics", label, sample[j].c_str(), reco[j].c_str());
    //     printf("  & %6.1f\\%%", 100 * th1_average_content((TH1F*)fsys[j]->Get(hist_name.c_str())));
    // }
    // printf(" \\\\\n");
    printf("      \\hline\n");
    printf("    \\end{tabular}\n");
    printf("    \\caption{\\label{table:sys_unc_summary_%s} Summary of the systematic uncertainties from each source in the 0-10\\%% centrality range, averaged over $0 < \\xi < 5$}\n", label);
    printf("  \\end{center}\n");
    printf("\\end{table}\n");
    printf("\n");

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return print_systematics(argv[1], argv[2], argv[3]);
    else
        return 1;
}
