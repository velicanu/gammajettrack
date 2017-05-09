#ifndef _PARTICLEFLOW_TREE_H
#define _PARTICLEFLOW_TREE_H

#include "jet_tree.h"

class particleflowTree {
  public:
    particleflowTree() {
        nPFpart = -1;
        pfId = 0;
        pfPt = 0;
        pfEnergy = 0;
        pfEta = 0;
        pfPhi = 0;
    }
    ~particleflowTree() {};

    particleflowTree(TTree* t) : particleflowTree() {
        this->read_tree(t);
    }

    void read_tree(TTree* t);
    int get_npfcand_4(jetTree* jt, int ijet);

    int nPFpart;
    std::vector<float>* pfId;
    std::vector<float>* pfPt;
    std::vector<float>* pfEnergy;
    std::vector<float>* pfEta;
    std::vector<float>* pfPhi;
};

void particleflowTree::read_tree(TTree* t) {
    t->SetBranchStatus("nPFpart", 1);
    t->SetBranchStatus("pfId", 1);
    t->SetBranchStatus("pfPt", 1);
    t->SetBranchStatus("pfEnergy", 1);
    t->SetBranchStatus("pfEta", 1);
    t->SetBranchStatus("pfPhi", 1);

    t->SetBranchAddress("nPFpart", &nPFpart);
    t->SetBranchAddress("pfId", &pfId);
    t->SetBranchAddress("pfPt", &pfPt);
    t->SetBranchAddress("pfEnergy", &pfEnergy);
    t->SetBranchAddress("pfEta", &pfEta);
    t->SetBranchAddress("pfPhi", &pfPhi);
}

int particleflowTree::get_npfcand_4(jetTree* jt, int ijet) {
    int npfcand_4 = 0;
    for (int ipf = 0; ipf < nPFpart; ++ipf) {
        if ((*pfPt)[ipf] < 4) continue;
        float dphi = acos(cos(jt->jtphi[ijet] - (*pfPhi)[ipf]));
        float deta = jt->jteta[ijet] - (*pfEta)[ipf];
        float deltar2 = (dphi * dphi) + (deta * deta);
        if (deltar2 < 0.09)
            npfcand_4++;
    }

    return npfcand_4;
}

#endif
