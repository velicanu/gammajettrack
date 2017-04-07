#ifndef _PHOTON_TREE
#define _PHOTON_TREE

#include "TTree.h"

#include <vector>

class photonTree {
  public:
    photonTree() {
        nEle = -99;
        elePt = 0;
        eleEta = 0;
        elePhi = 0;
        eleEoverP = 0;

        nPho = -99;
        phoE = 0;
        phoEt = 0;
        phoEta = 0;
        phoPhi = 0;
        phoSCE = 0;
        phoSCRawE = 0;
        phoESEn = 0;
        phoSCEta = 0;
        phoSCPhi = 0;
        phoSCEtaWidth = 0;
        phoSCPhiWidth = 0;
        phoSCBrem = 0;
        phoR9 = 0;
        phoHoverE = 0;
        phoSigmaIEtaIEta = 0;
        phoSigmaIEtaIEta_2012 = 0;
        phoE1x3 = 0;
        phoE2x2 = 0;
        phoE3x3 = 0;
        phoE2x5Max = 0;
        phoE1x5 = 0;
        phoE2x5 = 0;
        phoE5x5 = 0;

        pho_ecalClusterIsoR3 = 0;
        pho_ecalClusterIsoR4 = 0;
        pho_ecalClusterIsoR5 = 0;
        pho_hcalRechitIsoR3 = 0;
        pho_hcalRechitIsoR4 = 0;
        pho_hcalRechitIsoR5 = 0;
        pho_trackIsoR3PtCut20 = 0;
        pho_trackIsoR4PtCut20 = 0;
        pho_trackIsoR5PtCut20 = 0;

        pho_swissCrx = 0;
        pho_seedTime = 0;

        pho_genMatchedIndex = 0;

        nMC = -99;
        mcCalIsoDR04 = 0;
        mcPID = 0;
        mcStatus = 0;
        mcPt = 0;
        mcEt = 0;
        mcEta = 0;
        mcPhi = 0;
        mcMomPt = 0;
        mcMomEta = 0;
        mcMomPhi = 0;
        mcMomPID = 0;
    }
    ~photonTree() {};

    photonTree(TTree* t) : photonTree() {
        this->read_tree(t);
    }

    void read_tree(TTree* t);

    int nEle;
    std::vector<float>* elePt;
    std::vector<float>* eleEta;
    std::vector<float>* elePhi;
    std::vector<float>* eleEoverP;

    int nPho;
    std::vector<float>* phoE;
    std::vector<float>* phoEt;
    std::vector<float>* phoEta;
    std::vector<float>* phoPhi;
    std::vector<float>* phoSCE;
    std::vector<float>* phoSCRawE;
    std::vector<float>* phoESEn;
    std::vector<float>* phoSCEta;
    std::vector<float>* phoSCPhi;
    std::vector<float>* phoSCEtaWidth;
    std::vector<float>* phoSCPhiWidth;
    std::vector<float>* phoSCBrem;
    std::vector<float>* phoR9;
    std::vector<float>* phoHoverE;
    std::vector<float>* phoSigmaIEtaIEta;
    std::vector<float>* phoSigmaIEtaIEta_2012;
    std::vector<float>* phoE1x3;
    std::vector<float>* phoE2x2;
    std::vector<float>* phoE3x3;
    std::vector<float>* phoE2x5Max;
    std::vector<float>* phoE1x5;
    std::vector<float>* phoE2x5;
    std::vector<float>* phoE5x5;

    std::vector<float>* pho_ecalClusterIsoR3;
    std::vector<float>* pho_ecalClusterIsoR4;
    std::vector<float>* pho_ecalClusterIsoR5;
    std::vector<float>* pho_hcalRechitIsoR3;
    std::vector<float>* pho_hcalRechitIsoR4;
    std::vector<float>* pho_hcalRechitIsoR5;
    std::vector<float>* pho_trackIsoR3PtCut20;
    std::vector<float>* pho_trackIsoR4PtCut20;
    std::vector<float>* pho_trackIsoR5PtCut20;

    std::vector<float>* pho_swissCrx;
    std::vector<float>* pho_seedTime;

    std::vector<int>* pho_genMatchedIndex;

    int nMC;
    std::vector<float>* mcCalIsoDR04;
    std::vector<int>* mcPID;
    std::vector<int>* mcStatus;
    std::vector<float>* mcPt;
    std::vector<float>* mcEt;
    std::vector<float>* mcEta;
    std::vector<float>* mcPhi;
    std::vector<float>* mcMomPt;
    std::vector<float>* mcMomEta;
    std::vector<float>* mcMomPhi;
    std::vector<int>* mcMomPID;
};

void photonTree::read_tree(TTree* t) {
    t->SetBranchStatus("nEle", 1);
    t->SetBranchStatus("elePt", 1);
    t->SetBranchStatus("eleEta", 1);
    t->SetBranchStatus("elePhi", 1);
    t->SetBranchStatus("eleEoverP", 1);

    t->SetBranchStatus("nPho", 1);
    t->SetBranchStatus("phoE", 1);
    t->SetBranchStatus("phoEt", 1);
    t->SetBranchStatus("phoEta", 1);
    t->SetBranchStatus("phoPhi", 1);
    t->SetBranchStatus("phoSCE", 1);
    t->SetBranchStatus("phoSCRawE", 1);
    t->SetBranchStatus("phoESEn", 1);
    t->SetBranchStatus("phoSCEta", 1);
    t->SetBranchStatus("phoSCPhi", 1);
    t->SetBranchStatus("phoSCEtaWidth", 1);
    t->SetBranchStatus("phoSCPhiWidth", 1);
    t->SetBranchStatus("phoSCBrem", 1);
    t->SetBranchStatus("phoR9", 1);
    t->SetBranchStatus("phoHoverE", 1);
    t->SetBranchStatus("phoSigmaIEtaIEta", 1);
    t->SetBranchStatus("phoSigmaIEtaIEta_2012", 1);
    t->SetBranchStatus("phoE1x3", 1);
    t->SetBranchStatus("phoE2x2", 1);
    t->SetBranchStatus("phoE3x3", 1);
    t->SetBranchStatus("phoE2x5Max", 1);
    t->SetBranchStatus("phoE1x5", 1);
    t->SetBranchStatus("phoE2x5", 1);
    t->SetBranchStatus("phoE5x5", 1);

    t->SetBranchStatus("pho_ecalClusterIsoR3", 1);
    t->SetBranchStatus("pho_ecalClusterIsoR4", 1);
    t->SetBranchStatus("pho_ecalClusterIsoR5", 1);
    t->SetBranchStatus("pho_hcalRechitIsoR3", 1);
    t->SetBranchStatus("pho_hcalRechitIsoR4", 1);
    t->SetBranchStatus("pho_hcalRechitIsoR5", 1);
    t->SetBranchStatus("pho_trackIsoR3PtCut20", 1);
    t->SetBranchStatus("pho_trackIsoR4PtCut20", 1);
    t->SetBranchStatus("pho_trackIsoR5PtCut20", 1);

    t->SetBranchStatus("pho_swissCrx", 1);
    t->SetBranchStatus("pho_seedTime", 1);

    t->SetBranchStatus("pho_genMatchedIndex", 1);

    t->SetBranchStatus("nMC", 1);
    t->SetBranchStatus("mcCalIsoDR04", 1);
    t->SetBranchStatus("mcPID", 1);
    t->SetBranchStatus("mcStatus", 1);
    t->SetBranchStatus("mcPt", 1);
    t->SetBranchStatus("mcEt", 1);
    t->SetBranchStatus("mcEta", 1);
    t->SetBranchStatus("mcPhi", 1);
    t->SetBranchStatus("mcMomPt", 1);
    t->SetBranchStatus("mcMomEta", 1);
    t->SetBranchStatus("mcMomPhi", 1);
    t->SetBranchStatus("mcMomPID", 1);

    t->SetBranchAddress("nEle", &nEle);
    t->SetBranchAddress("elePt", &elePt);
    t->SetBranchAddress("eleEta", &eleEta);
    t->SetBranchAddress("elePhi", &elePhi);
    t->SetBranchAddress("eleEoverP", &eleEoverP);

    t->SetBranchAddress("nPho", &nPho);
    t->SetBranchAddress("phoE", &phoE);
    t->SetBranchAddress("phoEt", &phoEt);
    t->SetBranchAddress("phoEta", &phoEta);
    t->SetBranchAddress("phoPhi", &phoPhi);
    t->SetBranchAddress("phoSCE", &phoSCE);
    t->SetBranchAddress("phoSCRawE", &phoSCRawE);
    t->SetBranchAddress("phoESEn", &phoESEn);
    t->SetBranchAddress("phoSCEta", &phoSCEta);
    t->SetBranchAddress("phoSCPhi", &phoSCPhi);
    t->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth);
    t->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth);
    t->SetBranchAddress("phoSCBrem", &phoSCBrem);
    t->SetBranchAddress("phoR9", &phoR9);
    t->SetBranchAddress("phoHoverE", &phoHoverE);
    t->SetBranchAddress("phoSigmaIEtaIEta", &phoSigmaIEtaIEta);
    t->SetBranchAddress("phoSigmaIEtaIEta_2012", &phoSigmaIEtaIEta_2012);
    t->SetBranchAddress("phoE1x3", &phoE1x3);
    t->SetBranchAddress("phoE2x2", &phoE2x2);
    t->SetBranchAddress("phoE3x3", &phoE3x3);
    t->SetBranchAddress("phoE2x5Max", &phoE2x5Max);
    t->SetBranchAddress("phoE1x5", &phoE1x5);
    t->SetBranchAddress("phoE2x5", &phoE2x5);
    t->SetBranchAddress("phoE5x5", &phoE5x5);

    t->SetBranchAddress("pho_ecalClusterIsoR3", &pho_ecalClusterIsoR3);
    t->SetBranchAddress("pho_ecalClusterIsoR4", &pho_ecalClusterIsoR4);
    t->SetBranchAddress("pho_ecalClusterIsoR5", &pho_ecalClusterIsoR5);
    t->SetBranchAddress("pho_hcalRechitIsoR3", &pho_hcalRechitIsoR3);
    t->SetBranchAddress("pho_hcalRechitIsoR4", &pho_hcalRechitIsoR4);
    t->SetBranchAddress("pho_hcalRechitIsoR5", &pho_hcalRechitIsoR5);
    t->SetBranchAddress("pho_trackIsoR3PtCut20", &pho_trackIsoR3PtCut20);
    t->SetBranchAddress("pho_trackIsoR4PtCut20", &pho_trackIsoR4PtCut20);
    t->SetBranchAddress("pho_trackIsoR5PtCut20", &pho_trackIsoR5PtCut20);

    t->SetBranchAddress("pho_swissCrx", &pho_swissCrx);
    t->SetBranchAddress("pho_seedTime", &pho_seedTime);

    t->SetBranchAddress("pho_genMatchedIndex", &pho_genMatchedIndex);

    t->SetBranchAddress("nMC", &nMC);
    t->SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04);
    t->SetBranchAddress("mcPID", &mcPID);
    t->SetBranchAddress("mcStatus", &mcStatus);
    t->SetBranchAddress("mcPt", &mcPt);
    t->SetBranchAddress("mcEt", &mcEt);
    t->SetBranchAddress("mcEta", &mcEta);
    t->SetBranchAddress("mcPhi", &mcPhi);
    t->SetBranchAddress("mcMomPt", &mcMomPt);
    t->SetBranchAddress("mcMomEta", &mcMomEta);
    t->SetBranchAddress("mcMomPhi", &mcMomPhi);
    t->SetBranchAddress("mcMomPID", &mcMomPID);
}

#endif
