#ifndef _JET_TREE_H
#define _JET_TREE_H

#include "TTree.h"

class jetTree {
  public:
    jetTree() {
        nref = -99;
        rawpt = 0;
        jtpt = 0;
        jteta = 0;
        jtphi = 0;
        refpt = 0;
        refeta = 0;
        refphi = 0;
        refparton_flavor = 0;
        subid = 0;
        chargedSum = 0;
        neutralSum = 0;
        photonSum = 0;
        eSum = 0;
        chargedMax = 0;
        chargedN = 0;
        neutralN = 0;
        photonN = 0;
        eN = 0;
        muN = 0;

        ngen = -99;
        genpt = 0;
        geneta = 0;
        genphi = 0;
        gensubid = 0;
    }
    ~jetTree() {
        clear_memory();
    };

    jetTree(TTree* t) : jetTree() {
        this->read_tree(t);
    }

    bool goodJet(int i) {
        if (neutralSum[i] / rawpt[i] < 0.9 &&
            chargedSum[i] / rawpt[i] > 0.01 &&
            chargedN[i] + photonN[i] + neutralN[i] + eN[i] + muN[i] > 0 &&
            chargedMax[i] / rawpt[i] < 0.99 &&
            photonSum[i] / rawpt[i] < 0.99 &&
            eSum[i] / rawpt[i] < 0.99)
            return true;
        else
            return false;
    }

    void init_memory();
    void clear_memory();
    void read_tree(TTree* t);

    int nref;
    float* rawpt;
    float* jtpt;
    float* jteta;
    float* jtphi;
    float* refpt;
    float* refeta;
    float* refphi;
    int* refparton_flavor;
    int* subid;
    float* chargedSum;
    float* neutralSum;
    float* photonSum;
    float* eSum;
    float* chargedMax;
    int* chargedN;
    int* neutralN;
    int* photonN;
    int* eN;
    int* muN;

    int ngen;
    float* genpt;
    float* geneta;
    float* genphi;
    int* gensubid;
};

void jetTree::init_memory() {
    rawpt = (float*) malloc(sizeof(float) * 300);
    jtpt = (float*) malloc(sizeof(float) * 300);
    jteta = (float*) malloc(sizeof(float) * 300);
    jtphi = (float*) malloc(sizeof(float) * 300);
    refpt = (float*) malloc(sizeof(float) * 300);
    refeta = (float*) malloc(sizeof(float) * 300);
    refphi = (float*) malloc(sizeof(float) * 300);
    refparton_flavor = (int*) malloc(sizeof(int) * 300);
    subid = (int*) malloc(sizeof(int) * 300);
    chargedSum = (float*) malloc(sizeof(float) * 300);
    neutralSum = (float*) malloc(sizeof(float) * 300);
    photonSum = (float*) malloc(sizeof(float) * 300);
    eSum = (float*) malloc(sizeof(float) * 300);
    chargedMax = (float*) malloc(sizeof(float) * 300);
    chargedN = (int*) malloc(sizeof(int) * 300);
    neutralN = (int*) malloc(sizeof(int) * 300);
    photonN = (int*) malloc(sizeof(int) * 300);
    eN = (int*) malloc(sizeof(int) * 300);
    muN = (int*) malloc(sizeof(int) * 300);

    genpt = (float*) malloc(sizeof(float) * 5000);
    geneta = (float*) malloc(sizeof(float) * 5000);
    genphi = (float*) malloc(sizeof(float) * 5000);
    gensubid = (int*) malloc(sizeof(int) * 5000);
}

void jetTree::clear_memory() {
    free(rawpt);
    free(jtpt);
    free(jteta);
    free(jtphi);
    free(refpt);
    free(refeta);
    free(refphi);
    free(refparton_flavor);
    free(subid);
    free(chargedSum);
    free(neutralSum);
    free(photonSum);
    free(eSum);
    free(chargedMax);
    free(chargedN);
    free(neutralN);
    free(photonN);
    free(eN);
    free(muN);

    free(genpt);
    free(geneta);
    free(genphi);
    free(gensubid);
}

void jetTree::read_tree(TTree* t) {
    init_memory();

    t->SetBranchStatus("nref", 1);
    t->SetBranchStatus("rawpt", 1);
    t->SetBranchStatus("jtpt", 1);
    t->SetBranchStatus("jteta", 1);
    t->SetBranchStatus("jtphi", 1);
    t->SetBranchStatus("refpt", 1);
    t->SetBranchStatus("refeta", 1);
    t->SetBranchStatus("refphi", 1);
    t->SetBranchStatus("refparton_flavor", 1);
    t->SetBranchStatus("chargedSum", 1);
    t->SetBranchStatus("neutralSum", 1);
    t->SetBranchStatus("photonSum", 1);
    t->SetBranchStatus("eSum", 1);
    t->SetBranchStatus("chargedMax", 1);
    t->SetBranchStatus("chargedN", 1);
    t->SetBranchStatus("neutralN", 1);
    t->SetBranchStatus("photonN", 1);
    t->SetBranchStatus("eN", 1);
    t->SetBranchStatus("muN", 1);
    t->SetBranchStatus("subid", 1);

    t->SetBranchStatus("ngen", 1);
    t->SetBranchStatus("genpt", 1);
    t->SetBranchStatus("geneta", 1);
    t->SetBranchStatus("genphi", 1);
    t->SetBranchStatus("gensubid", 1);

    t->SetBranchAddress("nref", &nref);
    t->SetBranchAddress("rawpt", rawpt);
    t->SetBranchAddress("jtpt", jtpt);
    t->SetBranchAddress("jteta", jteta);
    t->SetBranchAddress("jtphi", jtphi);
    t->SetBranchAddress("refpt", refpt);
    t->SetBranchAddress("refeta", refeta);
    t->SetBranchAddress("refphi", refphi);
    t->SetBranchAddress("refparton_flavor", refparton_flavor);
    t->SetBranchAddress("chargedSum", chargedSum);
    t->SetBranchAddress("neutralSum", neutralSum);
    t->SetBranchAddress("photonSum", photonSum);
    t->SetBranchAddress("eSum", eSum);
    t->SetBranchAddress("chargedMax", chargedMax);
    t->SetBranchAddress("chargedN", chargedN);
    t->SetBranchAddress("neutralN", neutralN);
    t->SetBranchAddress("photonN", photonN);
    t->SetBranchAddress("eN", eN);
    t->SetBranchAddress("muN", muN);
    t->SetBranchAddress("subid", subid);

    t->SetBranchAddress("ngen", &ngen);
    t->SetBranchAddress("genpt", genpt);
    t->SetBranchAddress("geneta", geneta);
    t->SetBranchAddress("genphi", genphi);
    t->SetBranchAddress("gensubid", gensubid);
}

#endif
