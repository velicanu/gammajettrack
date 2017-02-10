#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"

#include <fstream>
#include <vector>
#include <string>

int min_hiBin[4] = {0, 20, 60, 100};
int max_hiBin[4] = {20, 60, 100, 200};

int rows = 1;
int columns = 4;

typedef struct box_t {
    float x1, y1, x2, y2;
} box_t;

void divide_canvas(TCanvas* c1, int rows, int columns, float margin, float edge, float row_scale_factor, float column_scale_factor);
void set_hist_style(TH1D* h1, int k);
void set_axis_style(TH1D* h1, int i, int j);
void adjust_coordinates(box_t& box, float margin, float edge, int i, int j);
void cover_axis(float margin, float edge, float column_scale_factor, float row_scale_factor);
void draw_sys_unc(TBox* box, TH1* h1, TH1* h1_sys);

int plot_ff(const char* fresults, const char* fsys, const char* plot_name, int draw_log_scale) {

    TFile* fmcinput = TFile::Open("pbpbmcff.root");
    std::vector<std::string> mchist_names = {
        "PbPb MC",                            // Legend label
        "hgammaffxi_pbpbmc_recoreco_0_20",
        "hgammaffxi_pbpbmc_recoreco_20_60",
        "hgammaffxi_pbpbmc_recoreco_60_100",
        "hgammaffxi_pbpbmc_recoreco_100_200"
    };

    TFile* finput = new TFile(fresults, "read");

    TFile* fsysfile = new TFile(fsys, "read");

    std::vector<std::string> hist_names = {
        "PbPb Data",                            // Legend label
        "hgammaffxi_pbpbdata_recoreco_0_20",
        "hgammaffxi_pbpbdata_recoreco_20_60",
        "hgammaffxi_pbpbdata_recoreco_60_100",
        "hgammaffxi_pbpbdata_recoreco_100_200",
        "pp Data",
        "hgammaffxi_ppdata_recoreco_0_20",
        "hgammaffxi_ppdata_recoreco_20_60",
        "hgammaffxi_ppdata_recoreco_60_100",
        "hgammaffxi_ppdata_recoreco_100_200"
    };

    float margin = 0.16; // left/bottom margins (with labels)
    float edge = 0.1;    // right/top edges (no labels)

    float row_scale_factor = (rows > 1) ? 1.0/(1.0-margin) + 1.0/(1.0-edge) + rows - 2 : 1.0/(1.0-margin-edge);

    float column_scale_factor = (columns > 1) ? 1.0/(1.0-margin) + 1.0/(1.0-edge) + columns - 2 : 1.0/(1.0-margin-edge);

    float pad_width = 250 * column_scale_factor;
    float pad_height = 250 * row_scale_factor;

    TCanvas* c1 = new TCanvas("c1", "", pad_width, pad_height);
    divide_canvas(c1, rows, columns, margin, edge, row_scale_factor, column_scale_factor);

    TH1D* h1_sys[4][2] = {0};
    h1_sys[0][0] = (TH1D*)fsysfile->Get("pbpbdata_0_20");
    h1_sys[1][0] = (TH1D*)fsysfile->Get("pbpbdata_20_60");
    h1_sys[2][0] = (TH1D*)fsysfile->Get("pbpbdata_60_100");
    h1_sys[3][0] = (TH1D*)fsysfile->Get("pbpbdata_100_200");
    h1_sys[0][1] = (TH1D*)fsysfile->Get("ppdata_0_20");
    h1_sys[1][1] = (TH1D*)fsysfile->Get("ppdata_20_60");
    h1_sys[2][1] = (TH1D*)fsysfile->Get("ppdata_60_100");
    h1_sys[3][1] = (TH1D*)fsysfile->Get("ppdata_100_200");

    TH1D* h1[4][2] = {0};
    TH1D* hmc[4] = {0};
    for (int i=0; i<4; ++i) {
        c1->cd(i+1);
        if (draw_log_scale)
            gPad->SetLogy();

        hmc[i] = (TH1D*)fmcinput->Get(mchist_names[i+1].c_str());
        set_axis_style(hmc[i], i, 0);
        if (draw_log_scale)
            hmc[i]->SetAxisRange(0.001, 10, "Y");
        hmc[i]->SetYTitle("dN/d#xi_{#gamma}");
        hmc[i]->SetLineStyle(3);
        hmc[i]->SetLineWidth(1);
        hmc[i]->SetLineColor(kRed);


        for (int k=0; k<2; ++k) {
            h1[i][k] = (TH1D*)finput->Get(hist_names[5*k+i+1].c_str());
            set_hist_style(h1[i][k], k);
            set_axis_style(h1[i][k], i, 0);
            if (draw_log_scale)
                h1[i][k]->SetAxisRange(0.001, 10, "Y");
            h1[i][k]->SetYTitle("dN/d#xi_{#gamma}");
        }

        TBox* sys_box_pp = new TBox();
        sys_box_pp->SetFillStyle(1001);
        sys_box_pp->SetFillColorAlpha(30, 0.7);
        draw_sys_unc(sys_box_pp, h1[i][1], h1_sys[i][1]);
        h1[i][1]->Draw("e x0");

        TBox* sys_box_PbPb = new TBox();
        sys_box_PbPb->SetFillStyle(1001);
        sys_box_PbPb->SetFillColorAlpha(46, 0.7);
        draw_sys_unc(sys_box_PbPb, h1[i][0], h1_sys[i][0]);
        h1[i][0]->Draw("same e x0");

        h1[i][1]->SetFillColor(sys_box_pp->GetFillColor());
        h1[i][1]->SetFillStyle(1001);

        h1[i][0]->SetFillColor(sys_box_PbPb->GetFillColor());
        h1[i][0]->SetFillStyle(1001);

        // hmc[i]->Draw("hist same");
        hmc[i]->Draw("e same");

        TLatex* centInfo = new TLatex();
        centInfo->SetTextFont(43);
        centInfo->SetTextSize(15);
        centInfo->SetTextAlign(31);
        box_t info_box = (box_t) {0, 0, 0.96, 0.9};
        adjust_coordinates(info_box, margin, edge, i, 0);
        centInfo->DrawLatexNDC(info_box.x2, info_box.y2, Form("%i - %i%%", min_hiBin[i]/2, max_hiBin[i]/2));

        if (i == 0) {
            TLatex* latexCMS = new TLatex();
            latexCMS->SetTextFont(63);
            latexCMS->SetTextSize(15);
            box_t cms_box = (box_t) {0.06, 0.9, 1, 1};
            adjust_coordinates(cms_box, margin, edge, 0, 0);
            latexCMS->DrawLatexNDC(cms_box.x1, cms_box.y1, "CMS");

            TLatex* latexPrelim = new TLatex();
            latexPrelim->SetTextFont(53);
            latexPrelim->SetTextSize(12);
            box_t prelim_box = (box_t) {0.06, 0.84, 1, 1};
            adjust_coordinates(prelim_box, margin, edge, 0, 0);
            latexPrelim->DrawLatexNDC(prelim_box.x1, prelim_box.y1, "Preliminary");

            box_t l_box = (box_t) {0.06, 0.64, 0.64, 0.8};
            if (draw_log_scale)
                l_box = (box_t) {0.25, 0.32, 0.84, 0.48};
            adjust_coordinates(l_box, margin, edge, i, 0);
            TLegend* l1 = new TLegend(l_box.x1, l_box.y1, l_box.x2, l_box.y2);
            l1->SetTextFont(43);
            l1->SetTextSize(16);
            l1->SetBorderSize(0);
            l1->SetFillStyle(0);

            for (std::size_t m=0; m<hist_names.size()/5; ++m)
                l1->AddEntry(h1[0][m], hist_names[5*m].c_str(), "pf");

            l1->AddEntry(hmc[0], mchist_names[0].c_str(), "l");
            l1->Draw();
        }
    }

    c1->cd();

    float canvas_left_margin = (columns > 1) ? margin / (1-margin) / column_scale_factor : margin;
    float canvas_right_margin = (columns > 1) ? edge / (1-edge) / column_scale_factor : edge;
    float canvas_top_edge = (rows > 1) ? 1.03 - edge / (1-edge) / row_scale_factor : 1.03 - edge;

    TLatex* energyLatex = new TLatex();
    energyLatex->SetTextFont(43);
    energyLatex->SetTextSize(15);
    energyLatex->SetTextAlign(11);
    energyLatex->DrawLatexNDC(canvas_left_margin+0.01, canvas_top_edge, "#sqrt{s_{NN}} = 5.02 TeV");

    TLatex* lumiLatex = new TLatex();
    lumiLatex->SetTextFont(43);
    lumiLatex->SetTextSize(15);
    lumiLatex->SetTextAlign(31);
    lumiLatex->DrawLatexNDC(1-canvas_right_margin-0.01, canvas_top_edge, "PbPb 404 #mub^{-1}, pp 25.8 pb^{-1}");

    TLatex* infoLatex = new TLatex();
    infoLatex->SetTextFont(43);
    infoLatex->SetTextSize(15);
    infoLatex->SetTextAlign(21);
    infoLatex->DrawLatexNDC((canvas_left_margin+1-canvas_right_margin)/2, canvas_top_edge, "p_{T}^{trk} > 1 GeV/c, anti-k_{T} Jet R = 0.3, p_{T}^{Jet} > 30 GeV/c, #left|#eta^{Jet}#right| < 1.6, p_{T}^{#gamma} > 60 GeV/c, #Delta#phi_{J#gamma} > #frac{7#pi}{8}");

    cover_axis(margin, edge, column_scale_factor, row_scale_factor);

    c1->SaveAs(Form("%s.pdf", plot_name));
    c1->SaveAs(Form("%s.png", plot_name));

    finput->Close();

    return 0;
}

void divide_canvas(TCanvas* c1, int rows, int columns, float margin, float edge, float row_scale_factor, float column_scale_factor) {
    c1->Clear();

    TPad* pads[rows][columns];

    float pad_width = 1.0 / column_scale_factor;
    float pad_height = 1.0 / row_scale_factor;

    float x_min[columns], x_max[columns];
    x_min[0] = 0;
    x_max[0] = pad_width/(1.0-margin);
    for (int i=1; i<columns; ++i) {
        x_min[i] = x_max[i-1];
        x_max[i] = x_max[i-1] + pad_width;
    }
    x_max[columns-1] = 1;

    float y_min[rows], y_max[rows];
    y_min[0] = 1.0-pad_height/(1.0-edge);
    y_max[0] = 1;
    for (int i=1; i<rows; ++i) {
        y_min[i] = y_min[i-1] - pad_height;
        y_max[i] = y_min[i-1];
    }
    y_min[rows-1] = 0;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            c1->cd();
            pads[i][j] = new TPad(Form("pad_%d_%d", i, j), Form("pad_%d_%d", i, j), x_min[j], y_min[i], x_max[j], y_max[i]);

            if (i == 0) pads[i][j]->SetTopMargin(edge);
            else pads[i][j]->SetTopMargin(0);
            if (i == rows - 1) pads[i][j]->SetBottomMargin(margin);
            else pads[i][j]->SetBottomMargin(0);
            if (j == 0) pads[i][j]->SetLeftMargin(margin);
            else pads[i][j]->SetLeftMargin(0);
            if (j == columns - 1) pads[i][j]->SetRightMargin(edge);
            else pads[i][j]->SetRightMargin(0);

            pads[i][j]->Draw();
            pads[i][j]->cd();
            pads[i][j]->SetNumber(i*columns+j+1);

            pads[i][j]->SetTickx();
            pads[i][j]->SetTicky();
        }
    }
}

void set_hist_style(TH1D* h1, int k) {
    h1->SetStats(0);

    switch (k) {
        case 0:
            h1->SetLineColor(kBlack);
            h1->SetMarkerSize(0.75);
            h1->SetMarkerStyle(kFullCircle);
            h1->SetMarkerColor(kBlack);
            h1->SetLineWidth(1);
            break;
        case 1:
            h1->SetLineColor(kBlack);
            h1->SetMarkerSize(0.75);
            h1->SetMarkerStyle(kOpenCircle);
            h1->SetMarkerColor(kBlack);
            h1->SetLineWidth(1);
            break;
    }
}

void set_axis_style(TH1D* h1, int i, int j) {
    h1->SetAxisRange(0, 3, "Y");
    h1->SetNdivisions(609);

    TAxis* x_axis = h1->GetXaxis();
    TAxis* y_axis = h1->GetYaxis();

    x_axis->SetLabelFont(43);
    x_axis->SetLabelSize(16);
    y_axis->SetLabelFont(43);
    y_axis->SetLabelSize(16);

    x_axis->SetLabelOffset(0.012);
    y_axis->SetLabelOffset(0.012);

    x_axis->SetTitleFont(43);
    x_axis->SetTitleSize(16);
    y_axis->SetTitleFont(43);
    y_axis->SetTitleSize(16);

    if (j == rows - 1) {
        x_axis->SetTitleOffset(1.0);
        x_axis->CenterTitle();
    } else {
        x_axis->SetTitleOffset(999);
        x_axis->SetTitle("");
    }

    if (i == 0) {
        y_axis->SetTitleOffset(1.15);
        y_axis->CenterTitle();
    } else {
        y_axis->SetTitleOffset(999);
        y_axis->SetTitle("");
    }
}

void adjust_coordinates(box_t& box, float margin, float edge, int i, int j) {
    if (columns == 1) {
        box.x1 = box.x1 * (1-margin-edge) + margin;
        box.x2 = box.x2 * (1-margin-edge) + margin;
    } else if (i == 0) {
        box.x1 = box.x1 * (1-margin) + margin;
        box.x2 = box.x2 * (1-margin) + margin;
    } else if (i == columns - 1) {
        box.x1 = box.x1 * (1-edge);
        box.x2 = box.x2 * (1-edge);
    }

    if (rows == 1) {
        box.y1 = box.y1 * (1-margin-edge) + margin;
        box.y2 = box.y2 * (1-margin-edge) + margin;
    } else if (j == 0) {
        box.y1 = box.y1 * (1-edge);
        box.y2 = box.y2 * (1-edge);
    } else if (j == rows - 1) {
        box.y1 = box.y1 * (1-margin) + margin;
        box.y2 = box.y2 * (1-margin) + margin;
    }
}

void cover_axis(float margin, float edge, float column_scale_factor, float row_scale_factor) {
    TPad* x_covers[columns - 1];
    TPad* y_covers[rows - 1];

    float pad_width = 1.0 / column_scale_factor;
    float pad_height = 1.0 / row_scale_factor;

    float x_min[columns];
    x_min[0] = (columns > 1) ? pad_width*margin/(1.0-margin) : margin;
    for (int i=1; i<columns; ++i)
        x_min[i] = x_min[i-1] + pad_width;

    float y_min[rows];
    y_min[0] = (rows > 1) ? 1.0-pad_height/(1.0-edge) : margin;
    for (int i=1; i<rows; ++i)
        y_min[i] = y_min[i-1] - pad_height;

    float axis_label_cover_size = 0.024;
    for (int p=0; p<rows-1; ++p) {
        y_covers[p] = new TPad(Form("y_cover_%d", p), Form("y_cover_%d", p), x_min[0]-0.04, y_min[p]-axis_label_cover_size, x_min[0]-0.0016, y_min[p]+0.0016);
        y_covers[p]->Draw();
    }

    for (int p=1; p<columns; ++p) {
        x_covers[p] = new TPad(Form("x_cover_%d", p), Form("x_cover_%d", p), x_min[p]-axis_label_cover_size, y_min[rows-1]-0.06, x_min[p]+axis_label_cover_size, y_min[rows-1]-0.0024);
        x_covers[p]->Draw();
    }
}

void draw_sys_unc(TBox* box, TH1* h1, TH1* h1_sys) {
    int nBins = h1->GetNbinsX();
    for (int i=1; i<=nBins; ++i) {
        if (h1->GetBinError(i) == 0) continue;

        double x = h1->GetBinCenter(i);
        int sys_bin = h1_sys->FindBin(x);
        double bin_width = h1->GetBinLowEdge(i+1) - h1->GetBinLowEdge(i);

        double val = h1->GetBinContent(i);
        double error = TMath::Abs(h1_sys->GetBinContent(sys_bin));

        box->SetX1(x - (bin_width/2));
        box->SetX2(x + (bin_width/2));
        box->SetY1(std::max(val - error, h1->GetMinimum()));
        box->SetY2(std::min(val + error, h1->GetMaximum()));

        box->DrawClone();
    }
}

int main(int argc, char* argv[]) {
    if (argc == 5)
        return plot_ff(argv[1], argv[2], argv[3], atoi(argv[4]));
    else
        printf("./plot_ff <results file> <sys file> <plot name> <log scale>\n");

    return 1;
}
