#include "TRandom3.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include "photonjettrack.h"

#define _NSMEAR 1
#define _NSMEAR_JER 1

TRandom3 smear_rand(12345);

float lowxi_jec[4] = {1.073, 1.079, 1.083, 1.074};
float midxi_jec[4] = {1.0514, 1.0478, 1.0483, 1.0471};

std::vector<float> sys_table_pp = {0, 1.02, 1.01, 0.99, 0.98, 1.05, 1.10, 1.15};
std::vector<float> sys_table_pbpb = {0, 1.05, 1.025, 0.975, 0.95, 1.05, 1.10, 1.15};

void photonjettrack::ffgammajet(std::string label, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string gen, int checkjetid, float trkptmin, int gammaxi, int whichSys, float sysScaleFactor) {
  return;
}

// systematic:
// 1: JES_UP
// 2: JES_UP_MINUS
// 3: JES_DOWN_PLUS
// 4: JES_DOWN
// 5: JER_MINUS_MINUS
// 6: JER_MINUS
// 7: JER
// 8: PES
// 9: ISO

void photonjettrack::jetshape(std::string sample, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string genlevel, float trkptmin, int gammaxi, std::string label, int systematic) {
  // TFile* fweight = (isPP) ? TFile::Open("pp-weights.root") : TFile::Open("PbPb-weights.root");
  // TH1D* hvzweight = (TH1D*)fweight->Get("hvz");
  // TH1D* hcentweight = (TH1D*)fweight->Get("hcent");

  bool isMC = (sample.find("mc") != std::string::npos);

  if (fChain == 0 || pfChain == 0) return;
  int64_t nentries = fChain->GetEntriesFast();

  TFile* fout = new TFile(Form("%s_%s_%s_%d_%d_%i_%d_%d.root", label.data(), sample.data(), genlevel.data(), (int)phoetmin, (int)jetptcut, gammaxi, abs(centmin), abs(centmax)), "recreate");

  TH1D* hjetpt[2]; TH1D* hjetptjetmix[2];
  hjetpt[0] = new TH1D(Form("hjetpt_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";jet p_{T};", 20, 0, 500);
  hjetpt[1] = new TH1D(Form("hjetptsideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";jet p_{T};", 20, 0, 500);
  hjetptjetmix[0] = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";jet p_{T};", 20, 0, 500);
  hjetptjetmix[1] = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";jet p_{T};", 20, 0, 500);

  TH1D* hgammaffxi[2]; TH1D* hgammaffxiue[2]; TH1D* hgammaffxijetmix[2]; TH1D* hgammaffxijetmixue[2];
  hgammaffxi[0] = new TH1D(Form("hgammaffxi_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxi[1] = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxiue[0] = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxiue[1] = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxijetmix[0] = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxijetmix[1]= new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxijetmixue[0] = new TH1D(Form("hgammaffxijetmixue_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);
  hgammaffxijetmixue[1] = new TH1D(Form("hgammaffxijetmixuesideband_%s_%s_%d_%d", sample.data(), genlevel.data(), abs(centmin), abs(centmax)), ";#xi;", 10, 0, 5);

  // TFile* fffjec = new TFile(Form("ffjec_%i_%i.root", (int)phoetmin, (int)jetptcut), "read");
  // TH1D* hffjec = (TH1D*)fffjec->Get(Form("hffjec_%i_%i", abs(centmin), abs(centmax)));

  std::vector<float> sys_table = isPP ? sys_table_pp : sys_table_pbpb;

  // generic pointers
  int nij;
  std::vector<float>* j_pt;
  std::vector<float>* j_eta;
  std::vector<float>* j_phi;

  int nip;
  std::vector<float>* p_pt;
  std::vector<float>* p_eta;
  std::vector<float>* p_phi;
  std::vector<float>* p_weight;

  int nij_mix;
  std::vector<int>* j_ev_mix;
  std::vector<float>* j_pt_mix;
  std::vector<float>* j_eta_mix;
  std::vector<float>* j_phi_mix;

  int nip_mix;
  std::vector<int>* p_ev_mix;
  std::vector<float>* p_pt_mix;
  std::vector<float>* p_eta_mix;
  std::vector<float>* p_phi_mix;
  std::vector<float>* p_weight_mix;

  std::vector<float> dummy_trkweight(125000, 1);

  if (jet_type_is("reco", genlevel) || jet_type_is("sreco", genlevel)) {
    j_pt = jetptCorr;
    j_eta = jeteta;
    j_phi = jetphi;
    j_pt_mix = jetptCorr_mix;
    j_eta_mix = jeteta_mix;
    j_phi_mix = jetphi_mix;
    j_ev_mix = nmixEv_mix;
  } else {
    j_pt = genpt;
    j_eta = geneta;
    j_phi = genphi;
    j_pt_mix = genpt_mix;
    j_eta_mix = geneta_mix;
    j_phi_mix = genphi_mix;
    j_ev_mix = genev_mix;
  }

  if (part_type_is("reco", genlevel)) {
    p_pt = trkPt;
    p_eta = trkEta;
    p_phi = trkPhi;
    p_weight = trkWeight;
    p_pt_mix = trkPt_mix;
    p_eta_mix = trkEta_mix;
    p_phi_mix = trkPhi_mix;
    p_ev_mix = trkFromEv_mix;
    p_weight_mix = trkWeight_mix;
  } else {
    p_pt = pt;
    p_eta = eta;
    p_phi = phi;
    p_weight = &dummy_trkweight;
    p_pt_mix = pt_mix;
    p_eta_mix = eta_mix;
    p_phi_mix = phi_mix;
    p_ev_mix = nev_mix;
    p_weight_mix = &dummy_trkweight;
  }

  // main loop
  for (int64_t jentry = 0; jentry < nentries; jentry++) {
    if (jentry % 10000 == 0) { printf("%li/%li\n", jentry, nentries); }
    int64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    fChain->GetEntry(jentry);
    pfChain->GetEntry(jentry);

    // check for number of mixed events
    if (!isPP && nmix < 3) continue;

    // event selections
    if (!isPP) { if (hiBin < centmin || hiBin >= centmax) continue; }
    if (phoNoise == 0) continue;

    // photon energy systematics
    if (systematic == 8) {
      if (isPP) { ; }
      else { phoEtCorrected = (hiBin < 60) ? phoEtCorrected * (90.94649 / 90.00079) : phoEtCorrected * (90.94943 / 90.64840); }
    }
    if (phoEtCorrected < phoetmin || phoEtCorrected > phoetmax) continue;

    // photon isolation systematics
    if (systematic == 9) {
      if (isMC)
        if (pho_genMatchedIndex == -1 || (*mcCalIsoDR04)[pho_genMatchedIndex] > 5.0)
          continue;
    }

    // apply fix to gamma-jet jec
    float jec_fix = isPP ? 0.99 : 0.98;

    // if (isMC) weight = weight * hvzweight->GetBinContent(hvzweight->FindBin(vz));
    // if (isMC && !isPP) weight = weight * hcentweight->GetBinContent(hcentweight->FindBin(hiBin));

    int centBin = getCentralityBin(centmin);

    bool signal = (phoSigmaIEtaIEta_2012 < 0.010);
    bool background = (phoSigmaIEtaIEta_2012 > 0.011 && phoSigmaIEtaIEta_2012 < 0.017);
    if (!signal && !background) continue;

    if (jet_type_is("reco", genlevel) || jet_type_is("sreco", genlevel)) {
      nij = njet;
      nij_mix = njet_mix;
    } else {
      nij = ngen;
      nij_mix = ngen_mix;
    }

    if (part_type_is("reco", genlevel)) {
      nip = nTrk;
      nip_mix = nTrk_mix;
    } else {
      nip = mult;
      nip_mix = mult_mix;
    }

    // jet loop
    for (int ij = 0; ij < nij; ij++) {
      if (jet_type_is("gen0", genlevel)) {
        if ((*gensubid)[ij] != 0) continue;
      }

      float tmpjetpt = (*j_pt)[ij];
      float tmpjeteta = (*j_eta)[ij];
      float tmpjetphi = (*j_phi)[ij];

      // jet eta cut
      if (fabs(tmpjeteta) > 1.6) continue;

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      // apply smearing
      if (isPP) {
        if (jet_type_is("sreco", genlevel)) {
          res_pt = getSigmaRelPt(centmin, tmpjetpt);
          res_phi = getSigmaRelPhi(centmin, tmpjetpt);
          nsmear = _NSMEAR;
        } else if (jet_type_is("sgen", genlevel)) {
          res_pt = getResolutionPP(tmpjetpt);
          res_phi = getPhiResolutionPP(tmpjetpt);
          nsmear = _NSMEAR;
        }
      } else {
        if (jet_type_is("sgen", genlevel)) {
          res_pt = getResolutionHI(tmpjetpt, centBin);
          res_phi = getPhiResolutionHI(tmpjetpt, centBin);
          nsmear = _NSMEAR;
        }
      }

      if (systematic == 5 || systematic == 6 || systematic == 7) nsmear *= _NSMEAR_JER;

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = (*j_pt)[ij] * smear_rand.Gaus(1, res_pt) * jec_fix;
        tmpjetphi = (*j_phi)[ij] + smear_rand.Gaus(0, res_phi);

        // jet phi cut
        if (acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8) continue;

        switch (systematic) {
          case 1: case 2: case 3: case 4:
            tmpjetpt = tmpjetpt * sys_table[systematic];
            break;
          case 5: case 6: case 7: {
            float jer_factor = sys_table[systematic];
            float initial_res = getResolutionHI(tmpjetpt, centBin);
            tmpjetpt = tmpjetpt * smear_rand.Gaus(1, jer_factor * initial_res * sqrt(jer_factor * jer_factor - 1));
            break; }
          default:
            break;
        }

        TLorentzVector vjet;
        vjet.SetPtEtaPhiM(tmpjetpt, tmpjeteta, tmpjetphi, 0);

        // apply ff-based jec
        // if (!isPP && jet_type_is("reco", genlevel)) {
        //   float min_xi = 99.;
        //   for (int ip = 0; ip < nip; ++ip) {
        //     if ((*p_pt)[ip] < trkptmin) continue;
        //     float dphi = acos(cos(tmpjetphi - (*p_phi)[ip]));
        //     float deta = tmpjeteta - (*p_eta)[ip];
        //     float deltar2 = (dphi * dphi) + (deta * deta);
        //     if (deltar2 < 0.09) {
        //       TLorentzVector vtrack;
        //       vtrack.SetPtEtaPhiM((*p_pt)[ip], (*p_eta)[ip], (*p_phi)[ip], 0);
        //       float angle = vjet.Angle(vtrack.Vect());
        //       float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
        //       float z = (*p_pt)[ip] * cos(angle) / refpt;
        //       float xi = log(1.0 / z);
        //       if (xi < min_xi) min_xi = xi;
        //     }
        //   }

        //   if (min_xi >= hffjec->GetBinLowEdge(1) && min_xi < hffjec->GetBinLowEdge(hffjec->GetNbinsX() + 1))
        //     tmpjetpt = tmpjetpt / hffjec->GetBinContent(hffjec->FindBin(min_xi));
        // }

        // if (!isPP && jet_type_is("reco", genlevel)) {
        //   if ((*npfcand_4)[ij] >= hffjec->GetBinLowEdge(1) && (*npfcand_4)[ij] < hffjec->GetBinLowEdge(hffjec->GetNbinsX() + 1))
        //     tmpjetpt = tmpjetpt / hffjec->GetBinContent(hffjec->FindBin((*npfcand_4)[ij]));
        // }

        // jet pt cut
        if (tmpjetpt < jetptcut) continue;

        hjetpt[background]->Fill(tmpjetpt, weight * smear_weight);

        float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
        // raw jets - jetshape
        for (int ip = 0; ip < nip; ++ip) {
          if ((*p_pt)[ip] < trkptmin) continue;
          if (part_type_is("gen0", genlevel)) {
            if ((*sube)[ip] != 0) continue;
            if ((*chg)[ip] == 0) continue;
          }
          if (part_type_is("gen", genlevel)) {
            if ((*chg)[ip] == 0) continue;
          }

          float dphi = acos(cos(tmpjetphi - (*p_phi)[ip]));
          float deta = tmpjeteta - (*p_eta)[ip];
          float deltar2 = (dphi * dphi) + (deta * deta);
          if (deltar2 < 0.09) {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM((*p_pt)[ip], (*p_eta)[ip], (*p_phi)[ip], 0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = (*p_pt)[ip] * cos(angle) / refpt;
            float xi = log(1.0 / z);
            hgammaffxi[background]->Fill(xi, weight * (*p_weight)[ip] * smear_weight);
          }
        }

        if (isPP) continue;
        if (part_type_is("gen0", genlevel)) continue;

        // raw jets - underlying event jetshape
        float nmixedevents_ue = (nmix + 2) / 3;
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (((*p_ev_mix)[ip_mix]) % 3 != 0) continue;
          if ((*p_pt_mix)[ip_mix] < trkptmin) continue;
          if (part_type_is("gen", genlevel)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }

          float dphi = acos(cos(tmpjetphi - (*p_phi_mix)[ip_mix]));
          float deta = tmpjeteta - (*p_eta_mix)[ip_mix];
          float deltar2 = (dphi * dphi) + (deta * deta);
          if (deltar2 < 0.09) {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM((*p_pt_mix)[ip_mix], (*p_eta_mix)[ip_mix], (*p_phi_mix)[ip_mix], 0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = (*p_pt_mix)[ip_mix] * cos(angle) / refpt;
            float xi = log(1.0 / z);
            hgammaffxiue[background]->Fill(xi, weight * (*p_weight_mix)[ip_mix] * smear_weight / nmixedevents_ue);
          }
        }
      }
    }

    if (isPP) continue;
    if (jet_type_is("gen0", genlevel)) continue;

    // mix jet loop
    float nmixedevents_jet = nmix - (nmix + 2) / 3;
    for (int ij_mix = 0; ij_mix < nij_mix; ij_mix++) {
      if ((*j_ev_mix)[ij_mix] % 3 == 0) continue;

      float tmpjetpt = (*j_pt_mix)[ij_mix];
      float tmpjeteta = (*j_eta_mix)[ij_mix];
      float tmpjetphi = (*j_phi_mix)[ij_mix];

      // jet eta cut
      if (fabs(tmpjeteta) > 1.6) continue;

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      if (jet_type_is("sgen", genlevel)) {
        res_pt = getResolutionHI(tmpjetpt, centBin);
        res_phi = getPhiResolutionHI(tmpjetpt, centBin);
        nsmear = _NSMEAR;
      }

      if (systematic == 5 || systematic == 6 || systematic == 7) nsmear *= _NSMEAR_JER;

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = (*j_pt_mix)[ij_mix] * smear_rand.Gaus(1, res_pt) * jec_fix;
        tmpjetphi = (*j_phi_mix)[ij_mix] + smear_rand.Gaus(0, res_phi);

        // jet phi cut
        if (acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8) continue;

        switch (systematic) {
          case 1: case 2: case 3: case 4:
            tmpjetpt = tmpjetpt * sys_table[systematic];
            break;
          case 5: case 6: case 7: {
            float jer_factor = sys_table[systematic];
            float initial_res = getResolutionHI(tmpjetpt, centBin);
            tmpjetpt = tmpjetpt * smear_rand.Gaus(1, jer_factor * initial_res * sqrt(jer_factor * jer_factor - 1));
            break; }
          default:
            break;
        }

        TLorentzVector vjet;
        vjet.SetPtEtaPhiM(tmpjetpt, tmpjeteta, tmpjetphi, 0);

        // apply ff-based jec
        // if (!isPP && jet_type_is("reco", genlevel)) {
        //   float min_xi = 99.;
        //   for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
        //     if ((*p_pt_mix)[ip_mix] < trkptmin) continue;
        //     float dphi = acos(cos(tmpjetphi - (*p_phi_mix)[ip_mix]));
        //     float deta = tmpjeteta - (*p_eta_mix)[ip_mix];
        //     float deltar2 = (dphi * dphi) + (deta * deta);
        //     if (deltar2 < 0.09) {
        //       TLorentzVector vtrack;
        //       vtrack.SetPtEtaPhiM((*p_pt_mix)[ip_mix], (*p_eta_mix)[ip_mix], (*p_phi_mix)[ip_mix], 0);
        //       float angle = vjet.Angle(vtrack.Vect());
        //       float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
        //       float z = (*p_pt_mix)[ip_mix] * cos(angle) / refpt;
        //       float xi = log(1.0 / z);
        //       if (xi < min_xi) min_xi = xi;
        //     }
        //   }

        //   if (min_xi >= hffjec->GetBinLowEdge(1) && min_xi < hffjec->GetBinLowEdge(hffjec->GetNbinsX() + 1))
        //     tmpjetpt = tmpjetpt / hffjec->GetBinContent(hffjec->FindBin(min_xi));
        // }

        // if (!isPP && jet_type_is("reco", genlevel)) {
        //   if ((*npfcand_4_mix)[ij_mix] >= hffjec->GetBinLowEdge(1) && (*npfcand_4_mix)[ij_mix] < hffjec->GetBinLowEdge(hffjec->GetNbinsX() + 1))
        //     tmpjetpt = tmpjetpt / hffjec->GetBinContent(hffjec->FindBin((*npfcand_4_mix)[ij_mix]));
        // }

        // jet pt cut
        if (tmpjetpt < jetptcut) continue;

        hjetptjetmix[background]->Fill(tmpjetpt, weight * smear_weight / nmixedevents_jet);

        float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
        // mix jets - jetshape
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          // tracks and jet must come from same mixed event
          if ((*j_ev_mix)[ij_mix] != (*p_ev_mix)[ip_mix]) continue;
          if ((*p_pt_mix)[ip_mix] < trkptmin) continue;
          if (part_type_is("gen0", genlevel) || part_type_is("gen", genlevel)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }

          float dphi = acos(cos(tmpjetphi - (*p_phi_mix)[ip_mix]));
          float deta = tmpjeteta - (*p_eta_mix)[ip_mix];
          float deltar2 = (dphi * dphi) + (deta * deta);
          if (deltar2 < 0.09) {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM((*p_pt_mix)[ip_mix], (*p_eta_mix)[ip_mix], (*p_phi_mix)[ip_mix], 0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = (*p_pt_mix)[ip_mix] * cos(angle) / refpt;
            float xi = log(1.0 / z);
            hgammaffxijetmix[background]->Fill(xi, weight * (*p_weight_mix)[ip_mix] * smear_weight / nmixedevents_jet);
          }
        }

        if (part_type_is("gen0", genlevel)) continue;

        // mix jets - underlying event jetshape
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if ((*p_ev_mix)[ip_mix] % 3 == 0) continue;
          if ((*j_ev_mix)[ij_mix] == (*p_ev_mix)[ip_mix]) continue;
          if ((*p_pt_mix)[ip_mix] < trkptmin) continue;
          if (part_type_is("gen", genlevel)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }

          float dphi = acos(cos(tmpjetphi - (*p_phi_mix)[ip_mix]));
          float deta = tmpjeteta - (*p_eta_mix)[ip_mix];
          float deltar2 = (dphi * dphi) + (deta * deta);
          if (deltar2 < 0.09) {
            TLorentzVector vtrack;
            vtrack.SetPtEtaPhiM((*p_pt_mix)[ip_mix], (*p_eta_mix)[ip_mix], (*p_phi_mix)[ip_mix], 0);
            float angle = vjet.Angle(vtrack.Vect());
            float z = (*p_pt_mix)[ip_mix] * cos(angle) / refpt;
            float xi = log(1.0 / z);
            hgammaffxijetmixue[background]->Fill(xi, weight * (*p_weight_mix)[ip_mix] * smear_weight / nmixedevents_jet / (nmixedevents_jet - 1));
          }
        }
      }
    }
  }

  fout->Write();
  fout->Close();
}

int main(int argc, char* argv[]) {
  if (argc > 13 || argc < 3) {
    printf("usage: ./jetshape [input] [sample] [centmin centmax] [phoetmin phoetmax] [jetptcut] [genlevel] [trkptmin] [gammaxi] [label] [systematic]\n");
    return 1;
  }

  photonjettrack* t = new photonjettrack(argv[1]);
  if (argc == 5)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]));
  else if (argc == 6)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]));
  else if (argc == 7)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]));
  else if (argc == 8)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]));
  else if (argc == 9)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), argv[8]);
  else if (argc == 10)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), argv[8], std::atof(argv[9]));
  else if (argc == 11)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), argv[8], std::atof(argv[9]), std::atoi(argv[10]));
  else if (argc == 12)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), argv[8], std::atof(argv[9]), std::atoi(argv[10]), argv[11]);
  else if (argc == 13)
    t->jetshape(argv[2], std::atoi(argv[3]), std::atoi(argv[4]), std::atof(argv[5]), std::atof(argv[6]), std::atof(argv[7]), argv[8], std::atof(argv[9]), std::atoi(argv[10]), argv[11], std::atoi(argv[12]));

  return 0;
}
