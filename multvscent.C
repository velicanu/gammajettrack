#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TProfile.h"
#include "TCanvas.h"

int multvscent(const char* embed, const char* mb, const char* output) {
    TFile* fembed = new TFile(embed, "read");
    TFile* fmb = new TFile(mb, "read");

    TTree* tembed = (TTree*)fembed->Get("anaTrack/trackTree");
    tembed->AddFriend("hiEvtAnalyzer/HiTree");
    TTree* tmb = (TTree*)fmb->Get("anaTrack/trackTree");
    tmb->AddFriend("hiEvtAnalyzer/HiTree");

    TFile* foutput = new TFile(output, "recreate");

    TProfile* hembed = new TProfile("hembed", "", 200, 0, 200);
    TProfile* hmb = new TProfile("hmb", "", 200, 0, 200);

    tembed->Draw("hiNpix:hiBin>>hembed", "", "prof goff");
    tmb->Draw("hiNpix:hiBin>>hmb", "", "prof goff");

    TProfile* hratio = (TProfile*)hembed->Clone("hratio");
    hratio->Divide(hmb);

    TCanvas* c1 = new TCanvas("c1", "", 600, 600);
    hratio->SetStats(0);
    hratio->SetAxisRange(0, 5, "Y");
    hratio->Draw("hist");
    c1->SaveAs("npixvscent-ratio.png");

    foutput->Write("", TObject::kOverwrite);
    foutput->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 4)
        return multvscent(argv[1], argv[2], argv[3]);
    else
        return 1;
}
