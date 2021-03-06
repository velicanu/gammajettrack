#include "TFile.h"
#include "TH1.h"
#include "TMath.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

TH1D * h1D_nominal[8];

void TH1D_Max(TH1D* h1, TH1D* h2) {
    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double sys1 = h1->GetBinContent(i);
        double err1 = h1->GetBinError(i);

        double sys2 = h2->GetBinContent(i);
        double err2 = h2->GetBinError(i);

        if (sys1 > sys2) {
            h1->SetBinContent(i, sys1);
            h1->SetBinError(i, err1);
        } else {
            h1->SetBinContent(i, sys2);
            h1->SetBinError(i, err2);
        }
    }
}

void TH1D_SqrtSumofSquares(TH1D* h1, TH1D* h2) {
    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double sys1 = h1->GetBinContent(i);
        double sys2 = h2->GetBinContent(i);
        double sys_total = TMath::Sqrt(sys1 * sys1 + sys2 * sys2);

        double err1 = h1->GetBinError(i);
        double err2 = h2->GetBinError(i);
        double err_total = TMath::Sqrt(err1 * err1 + err2 * err2);

        h1->SetBinContent(i, sys_total);
        h1->SetBinError(i, err_total);
    }
}

void TH1D_SSoS_Constant(TH1D* h1, float constant) {
    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        double sys1 = h1->GetBinContent(i);
        double sys_total = TMath::Sqrt(sys1 * sys1 + constant * constant);

        h1->SetBinContent(i, sys_total);
    }
}

float meansyst(TH1D* h1, int whichhist) {
    h1->Divide(h1D_nominal[whichhist]);
    return roundf(h1->Integral() / (h1->GetNbinsX()) * 1000 ) / 10.0 ;
}

// float meansyst(TH1D* h1, int whichhist) {
//     h1->Divide(h1D_nominal[whichhist]);
//     return roundf(h1->Integral(9,10) / 2 * 1000 ) / 10.0 ;
// }

int add_sys(const char* sys_file, const char* outname) {

    TFile *fnominal = new TFile("nominal_xigamma.root");

    std::vector<std::string> nominal_names {
        "hgammaffxi_pbpbdata_recoreco_0_20", "hgammaffxi_ppdata_recoreco_0_20",
        "hgammaffxi_pbpbdata_recoreco_20_60", "hgammaffxi_ppdata_recoreco_20_60",
        "hgammaffxi_pbpbdata_recoreco_60_100", "hgammaffxi_ppdata_recoreco_60_100",
        "hgammaffxi_pbpbdata_recoreco_100_200", "hgammaffxi_ppdata_recoreco_100_200",
    };
    for (int i = 0; i < 8; i++) {
      h1D_nominal[i] = (TH1D*) fnominal->Get(nominal_names[i].c_str());
    }

    TFile* finput = new TFile(sys_file, "read");

    std::vector<std::string> hist_names = {
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_JES_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_JES_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_purity_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_purity_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_JER",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_pes_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_pes_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_trk",
        "h1D_hgammaffxi_pbpbdata_recoreco_0_20_diff_abs_nbkg",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_JES_up",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_JES_down",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_purity_up",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_purity_down",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_JER",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_pes_up",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_pes_down",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_trk",
        "h1D_hgammaffxi_ppdata_recoreco_0_20_diff_abs_nbkg",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_JES_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_JES_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_purity_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_purity_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_JER",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_pes_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_pes_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_trk",
        "h1D_hgammaffxi_pbpbdata_recoreco_20_60_diff_abs_nbkg",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_JES_up",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_JES_down",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_purity_up",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_purity_down",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_JER",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_pes_up",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_pes_down",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_trk",
        "h1D_hgammaffxi_ppdata_recoreco_20_60_diff_abs_nbkg",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_JES_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_JES_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_purity_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_purity_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_JER",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_pes_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_pes_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_trk",
        "h1D_hgammaffxi_pbpbdata_recoreco_60_100_diff_abs_nbkg",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_JES_up",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_JES_down",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_purity_up",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_purity_down",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_JER",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_pes_up",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_pes_down",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_trk",
        "h1D_hgammaffxi_ppdata_recoreco_60_100_diff_abs_nbkg",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_JES_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_JES_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_purity_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_purity_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_JER",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_pes_up",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_pes_down",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_trk",
        "h1D_hgammaffxi_pbpbdata_recoreco_100_200_diff_abs_nbkg",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_JES_up",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_JES_down",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_purity_up",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_purity_down",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_JER",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_pes_up",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_pes_down",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_trk",
        "h1D_hgammaffxi_ppdata_recoreco_100_200_diff_abs_nbkg"
    };

    std::vector<std::string> new_names = {
        "pbpbdata_0_20", "ppdata_0_20",
        "pbpbdata_20_60", "ppdata_20_60",
        "pbpbdata_60_100", "ppdata_60_100",
        "pbpbdata_100_200", "ppdata_100_200"
    };

    TFile* fout = new TFile(outname, "recreate");

    TH1D* h_sum[8];
    TH1D* h_jer_sum[8];
    TH1D* h_jes_sum[8];
    TH1D* h_purity_sum[8];
    TH1D* h_pes_sum[8];
    TH1D* h_trk_sum[8];
    TH1D* h_nbkg_sum[8];

    for (int i=0; i<8; ++i) {
        h_sum[i] = (TH1D*)finput->Get(hist_names[i*9+4].c_str())->Clone(new_names[i].c_str()); // JER
        h_jer_sum[i] = (TH1D*)h_sum[i]->Clone(Form("tmp_%s",hist_names[i*9+4].c_str()));
        h_trk_sum[i] = (TH1D*)finput->Get(hist_names[i*9+7].c_str())->Clone(new_names[i].c_str()); //trk
        h_nbkg_sum[i] = (TH1D*)finput->Get(hist_names[i*9+8].c_str())->Clone(new_names[i].c_str()); //nbkg
        h_jes_sum[i] = (TH1D*)finput->Get(hist_names[i*9].c_str())->Clone(); //JES
        h_purity_sum[i] = (TH1D*)finput->Get(hist_names[i*9+2].c_str())->Clone(); //Purity
        h_pes_sum[i] = (TH1D*)finput->Get(hist_names[i*9+5].c_str())->Clone(); //pes

        TH1D_Max(h_jes_sum[i], (TH1D*)finput->Get(hist_names[i*9+1].c_str()));
        TH1D_Max(h_purity_sum[i], (TH1D*)finput->Get(hist_names[i*9+3].c_str()));
        TH1D_Max(h_pes_sum[i], (TH1D*)finput->Get(hist_names[i*9+6].c_str()));



        TH1D_SqrtSumofSquares(h_sum[i], h_jes_sum[i]);
        TH1D_SqrtSumofSquares(h_sum[i], h_purity_sum[i]);
        TH1D_SqrtSumofSquares(h_sum[i], h_pes_sum[i]);
        TH1D_SqrtSumofSquares(h_sum[i], h_trk_sum[i]);
        TH1D_SqrtSumofSquares(h_sum[i], h_nbkg_sum[i]);

        h_sum[i]->Write("", TObject::kOverwrite);
    }
    cout<<"Photon Purity           &  "<<meansyst(h_purity_sum[0],0)<<"\\%   & "<<meansyst(h_purity_sum[1],1)<<"\\%       &   "<<-1<<"\\% &   "<<-1<<"\\% \\\\"<<endl;
    cout<<"Photon Energy Scale     &  "<<meansyst(h_pes_sum[0],0)<<"\\%   & "<<meansyst(h_pes_sum[1],1)<<"\\%        &   "<<-1<<"\\%  &   "<<-1<<"\\%  \\\\"<<endl;
    cout<<"Jet Energy Scale        &  "<<meansyst(h_jes_sum[0],0)<<"\\%     & "<<meansyst(h_jes_sum[1],1)<<"\\%      &   "<<-1<<"\\%    &   "<<-1<<"\\%  \\\\"<<endl;
    cout<<"Jet Energy Resolution   &  "<<meansyst(h_jer_sum[0],0)<<"\\%     & "<<meansyst(h_jer_sum[1],1)<<"\\%      &   "<<-1<<"\\%    &   "<<-1<<"\\%    \\\\"<<endl;
    cout<<"Tracking Correction     &  "<<meansyst(h_trk_sum[0],0)<<"\\%     & "<<meansyst(h_trk_sum[1],1)<<"\\%        &   "<<-1<<"\\%    &   "<<-1<<"\\%    \\\\"<<endl;


    fout->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return add_sys(argv[1], argv[2]);
    else
        printf("Usage: ./add_sys <output from ff_systematics> <file to use for plot_ff>\n");

    return 1;
}
