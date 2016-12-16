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

int plot_js(const char* ffinal, const char* plot_name, const char* hist_list, int draw_ratio = 0) {
    TFile* finput = new TFile(ffinal, "update");

    std::vector<std::string> hist_names;
    std::ifstream file_stream(hist_list);
    if (!file_stream) return 1;
    std::string line;
    while (std::getline(file_stream, line))
        hist_names.push_back(line);

    if (hist_names.size() % 5)
        return 1;

    if (draw_ratio && hist_names.size()/5 == 2)
        rows = 2;
    else
        draw_ratio = 0;

    float margin = 0.16; // left/bottom margins (with labels)
    float edge = 0.1;    // right/top edges (no labels)

    float row_scale_factor = (rows > 1) ? 1.0/(1.0-margin) + 1.0/(1.0-edge) + rows - 2 : 1.0/(1.0-margin-edge);
    float column_scale_factor = (columns > 1) ? 1.0/(1.0-margin) + 1.0/(1.0-edge) + columns - 2 : 1.0/(1.0-margin-edge);

    float pad_width = 250 * column_scale_factor;
    float pad_height = 250 * row_scale_factor;

    TCanvas* c1 = new TCanvas("c1", "", pad_width, pad_height);
    divide_canvas(c1, rows, columns, margin, edge, row_scale_factor, column_scale_factor);

    TH1D* h1[4][hist_names.size()/5] = {0};
    TH1D* hratio[4] = {0};
    for (int i=0; i<4; ++i) {
        c1->cd(i+1);
        gPad->SetLogy();

        for (int k=0; k<2; ++k) {
            h1[i][k] = (TH1D*)finput->Get(hist_names[5*k+i+1].c_str());
            set_hist_style(h1[i][k], k);
            set_axis_style(h1[i][k], i, 0);
        }

        h1[i][0]->Draw();
        for (std::size_t l=1; l<hist_names.size()/5; ++l)
            h1[i][l]->Draw("same");
        h1[i][0]->Draw("same");

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
            box_t cms_box = (box_t) {0.15, 0.9, 1, 1};
            adjust_coordinates(cms_box, margin, edge, 0, 0);
            latexCMS->DrawLatexNDC(cms_box.x1, cms_box.y1, "CMS");

            TLatex* latexPrelim = new TLatex();
            latexPrelim->SetTextFont(53);
            latexPrelim->SetTextSize(12);
            box_t prelim_box = (box_t) {0.15, 0.84, 1, 1};
            adjust_coordinates(prelim_box, margin, edge, 0, 0);
            latexPrelim->DrawLatexNDC(prelim_box.x1, prelim_box.y1, "Preliminary");

            TLegend* l1 = new TLegend(0.48, 0.6, 0.75, 0.72);
            l1->SetTextFont(43);
            l1->SetTextSize(15);
            l1->SetBorderSize(0);
            l1->SetFillStyle(0);

            for (std::size_t m=0; m<hist_names.size()/5; ++m)
                l1->AddEntry(h1[0][m], hist_names[5*m].c_str(), "pl");

            l1->Draw();
        }

        if (draw_ratio) {
            c1->cd(i+5);

            hratio[i] = (TH1D*)h1[i][0]->Clone(Form("hratio_%i", i));
            hratio[i]->Divide(h1[i][1]);
            hratio[i]->SetYTitle("Ratio");

            TLine* line1 = new TLine(0, 1, 1, 1);
            line1->SetLineWidth(1);
            line1->SetLineStyle(2);
            line1->Draw();

            set_hist_style(hratio[i], 2);
            set_axis_style(hratio[i], i, 1);
            hratio[i]->SetAxisRange(0, 2, "Y");

            hratio[i]->Draw();
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
    infoLatex->DrawLatexNDC((canvas_left_margin+1-canvas_right_margin)/2, canvas_top_edge, "anti-k_{T} Jet R = 0.3, p_{T}^{Jet} > 30 GeV/c, #left|#eta^{Jet}#right| < 1.6, p_{T}^{#gamma} > 60 GeV/c, #Delta#phi_{J#gamma} > #frac{7#pi}{8}");

    cover_axis(margin, edge, column_scale_factor, row_scale_factor);

    c1->SaveAs(Form("%s.pdf", plot_name));
    c1->Write("", TObject::kOverwrite);

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
            h1->SetLineColor(1);
            h1->SetMarkerSize(0.64);
            h1->SetMarkerStyle(20);
            h1->SetMarkerColor(1);
            break;
        case 1:
            h1->SetLineColor(2);
            h1->SetMarkerSize(0.64);
            h1->SetMarkerStyle(24);
            h1->SetMarkerColor(2);
            break;
        case 2:
            h1->SetLineColor(1);
            h1->SetMarkerSize(0.64);
            h1->SetMarkerStyle(21);
            h1->SetMarkerColor(1);
            break;
    }
}

void set_axis_style(TH1D* h1, int i, int j) {
    h1->SetAxisRange(0.05, 50, "Y");
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

int main(int argc, char* argv[]) {
    if (argc == 4)
        return plot_js(argv[1], argv[2], argv[3]);
    else if (argc == 5)
        return plot_js(argv[1], argv[2], argv[3], atoi(argv[4]));
    else
        printf("./plot_js <ROOT file> <plot file name> <histogram list> <draw ratio>\n"
               "./plot_js jsdata_60.root jsdata_60 jsdata.list 1\n");

    return 1;
}
