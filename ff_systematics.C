#include "TFile.h"
#include "TH1.h"

#include "TCanvas.h"
#include "TLegend.h"

#include "SysVar.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


/* whichsysts:
0 : all ,   m 1-8 
1 : JES ,   m 1,2
2 : purity  m 3,4
3 : JER     m 5
4 : pes     m 6,7
5 : trk     m 8
*/

int ff_systematics(const char* file_list, const char* outputfile, int whichsysts) {
    std::vector<std::string> sys_types {
        "nominal",
        "JES_up", "JES_down", "purity_up", "purity_down",
	  "JER", "pes_up", "pes_down", "trk"
    };
    int n_sys_types = sys_types.size(); // default of whichsysts = 0
        std::vector<bool> sys_control { 
	  false, false, false, false, false, false, false, false, false
    };
      if(whichsysts == 1) {     //turns off all but JES
      sys_control[3] = true; 
      sys_control[4] = true; 
      sys_control[5] = true; 
      sys_control[6] = true; 
      sys_control[7] = true; 
      sys_control[8] = true; 
      } else if(whichsysts == 2) { //turns off all but purity
      sys_control[1] = true; 
      sys_control[2] = true; 
      sys_control[5] = true; 
      sys_control[6] = true; 
      sys_control[7] = true; 
      sys_control[8] = true; 
      } else if(whichsysts == 3) { //turns off all but JER
      sys_control[1] = true; 
      sys_control[2] = true; 
      sys_control[3] = true; 
      sys_control[4] = true; 
      sys_control[6] = true; 
      sys_control[7] = true; 
      sys_control[8] = true; 
      } else if(whichsysts == 4) { // turns off all but PES
      sys_control[1] = true; 
      sys_control[2] = true; 
      sys_control[3] = true; 
      sys_control[4] = true; 
      sys_control[5] = true;
      sys_control[8] = true; 
      } else if(whichsysts == 5) { // turns off all but trk
      sys_control[1] = true; 
      sys_control[2] = true; 
      sys_control[3] = true; 
      sys_control[4] = true; 
      sys_control[5] = true; 
      sys_control[6] = true; 
      sys_control[7] = true; 
    }

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
            sys_hists->calc_sys(sys_control[m]); // returns 0 if true, returns syst if false 

            systematics[i].push_back(sys_hists);
        }
    }

    printf("writing objects...\n");
    output->Write("", TObject::kOverwrite);
    output->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return ff_systematics(argv[1], argv[2], std::atoi(argv[3]));
    else
        printf("Usage: ./ff_systematics <list of variations, e.g. gammaxi0_sys.list> <output to be used as input for add_sys> <which systs 0 for all>\n");

    return 1;
}
