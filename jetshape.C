#include "TRandom3.h"
#include "TH1.h"

#include "photonjettrack.h"

#define _NSMEAR 1

TRandom3 smear_rand(12345);

float getTrkWeight(int trkindex, std::vector<float>* trkweight, std::string jet_part) {
  if (part_type_is("gen", jet_part) || part_type_is("gen0", jet_part))
    return 1;
  return (*trkweight)[trkindex];
}

void photonjettrack::ffgammajet(std::string label, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string gen, int checkjetid, float trkptmin, int gammaxi, int doJERsys) {
  return;
}

void photonjettrack::jetshape(std::string label, int centmin, int centmax, float phoetmin, float phoetmax, float jetptcut, std::string jet_part, float trkptmin, int gammaxi) {
  // bool isMC;
  // TFile* fvzweight = TFile::Open("fvzweight.root");
  // TH1D* hvzweight = (TH1D*)fvzweight->Get("hvzdata");
  // TFile* fcentweight = TFile::Open("fcentweight.root");
  // TH1D* hcentweight = (TH1D*)fcentweight->Get(Form("hcentdata_%d_%d", centmin, centmax));

  if (fChain == 0) return;
  int64_t nentries = fChain->GetEntriesFast();
  TFile* fout = new TFile(Form("%s_%s_%d_%d_%d.root", label.data(), jet_part.data(), (int)phoetmin, abs(centmin), abs(centmax)), "recreate");

  TH1D* hphoSigmaIEtaIEta_2012 = new TH1D(Form("hphoSigmaIEtaIEta_2012_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 40, 0, 0.02);
  TH1D* hjetpt = new TH1D(Form("hjetpt_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hjetptjetmix = new TH1D(Form("hjetptjetmix_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hjetptsideband = new TH1D(Form("hjetptsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hjetptjetmixsideband = new TH1D(Form("hjetptjetmixsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";jet p_{T};"), 20, 0, 500);
  TH1D* hgammaffxi = new TH1D(Form("hgammaffxi_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxisideband = new TH1D(Form("hgammaffxisideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxijetmix = new TH1D(Form("hgammaffxijetmix_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxijetmixsideband = new TH1D(Form("hgammaffxijetmixsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxijetmixue = new TH1D(Form("hgammaffxijetmixue_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxijetmixuesideband = new TH1D(Form("hgammaffxijetmixuesideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxiuemix = new TH1D(Form("hgammaffxiuemix_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hgammaffxiuemixsideband = new TH1D(Form("hgammaffxiuemixsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 20, 0, 1);
  TH1D* hnmixsignal = new TH1D(Form("hnmixsignal_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 1, 0, 2);
  TH1D* hnmixsideband = new TH1D(Form("hnmixsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";r;#rho(r)"), 1, 0, 2);
  TH1D* xjgsignal = new TH1D(Form("xjgsignal_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";xjg;"), 16, 0, 2);
  TH1D* xjgmixsignal = new TH1D(Form("xjgmixsignal_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";xjg;"), 16, 0, 2);
  TH1D* xjgsideband = new TH1D(Form("xjgsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";xjg;"), 16, 0, 2);
  TH1D* xjgmixsideband = new TH1D(Form("xjgmixsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";xjg;"), 16, 0, 2);
  TH1D* phoetsignal = new TH1D(Form("phoetsignal_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";#gamma E_{T};"), 50, 0, 500);
  TH1D* phoetsideband = new TH1D(Form("phoetsideband_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";#gamma E_{T};"), 50, 0, 500);

  TH1D* hvz = new TH1D(Form("hvz_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";vz;"), 30, -15, 15);
  TH1D* hcent = new TH1D(Form("hcent_%s_%s_%d_%d", label.data(), jet_part.data(), abs(centmin), abs(centmax)), Form(";cent;"), 200, 0, 200);

  // iterators
  int ij = -1, ij_mix = -1, ip = -1, ip_mix = -1;
  int nij = -1, nij_mix = -1, nip = -1, nip_mix = -1;
  std::vector<int> j_ev_mix;
  std::vector<int> p_ev_mix;

  std::vector<float> j_pt;
  std::vector<float> j_pt_mix;
  std::vector<float> p_pt;
  std::vector<float> p_pt_mix;
  std::vector<float> j_eta;
  std::vector<float> j_eta_mix;
  std::vector<float> p_eta;
  std::vector<float> p_eta_mix;
  std::vector<float> j_phi;
  std::vector<float> j_phi_mix;
  std::vector<float> p_phi;
  std::vector<float> p_phi_mix;

  //! (2) Loop
  for (int64_t jentry = 0; jentry < nentries; jentry++) {
    if (jentry % 10000 == 0) { printf("%li/%li\n", jentry, nentries); }
    int64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    fChain->GetEntry(jentry);

    //! (2.1) Event selections
    if (!isPP) {
      if (hiBin < centmin || hiBin >= centmax) continue;
    }
    // if (nPho != 1) continue;
    if (phoNoise == 0) continue;
    bool signal = (phoSigmaIEtaIEta_2012 < 0.010);
    bool sideband = (phoSigmaIEtaIEta_2012 > 0.011 && phoSigmaIEtaIEta_2012 < 0.017);
    if (phoEt / phoCorr < phoetmin || phoEt / phoCorr > phoetmax) continue;
    if (signal) {
      phoetsignal->Fill(phoEtCorrected);
    }
    if (sideband) {
      phoetsideband->Fill(phoEtCorrected);
    }

    // isMC = (weight != 0);
    // if (isMC) weight = weight * hvzweight->GetBinContent(hvzweight->FindBin(vz));
    // if (isMC && !isPP) weight = weight * hcentweight->GetBinContent(hcentweight->FindBin(hiBin));

    hvz->Fill(vz, weight);
    hcent->Fill(hiBin, weight);

    int njets_perevent = 0;
    int njets_permixevent = 0;

    if (jet_type_is("reco", jet_part) || jet_type_is("sreco", jet_part) || jet_type_is("idreco", jet_part) || jet_type_is("sidreco", jet_part)) {
      nij = njet;
      j_pt = *jetptCorr;
      j_eta = *jeteta;
      j_phi = *jetphi;
      nij_mix = njet_mix;
      j_pt_mix = *jetptCorr_mix;
      j_eta_mix = *jeteta_mix;
      j_phi_mix = *jetphi_mix;
      j_ev_mix = *nmixEv_mix;
    } else if (jet_type_is("zreco", jet_part)) {
      nij = njet;
      j_pt = *jetptCorr_zjet;
      j_eta = *jeteta;
      j_phi = *jetphi;
      nij_mix = njet_mix;
      j_pt_mix = *jetptCorr_zjet_mix;
      j_eta_mix = *jeteta_mix;
      j_phi_mix = *jetphi_mix;
      j_ev_mix = *nmixEv_mix;
    } else {
      nij = ngen;
      j_pt = *genpt;
      j_eta = *geneta;
      j_phi = *genphi;
      nij_mix = ngen_mix;
      j_pt_mix = *genpt_mix;
      j_eta_mix = *geneta_mix;
      j_phi_mix = *genphi_mix;
      j_ev_mix = *genev_mix;
    }

    if (part_type_is("reco", jet_part)) {
      nip = nTrk;
      p_pt = *trkPt;
      p_eta = *trkEta;
      p_phi = *trkPhi;
      nip_mix = nTrk_mix;
      p_pt_mix = *trkPt_mix;
      p_eta_mix = *trkEta_mix;
      p_phi_mix = *trkPhi_mix;
      p_ev_mix = *trkFromEv_mix;
    } else {
      nip = mult;
      p_pt = *pt;
      p_eta = *eta;
      p_phi = *phi;
      nip_mix = mult_mix;
      p_pt_mix = *pt_mix;
      p_eta_mix = *eta_mix;
      p_phi_mix = *phi_mix;
      p_ev_mix = *nev_mix;
    }

    //! Jet loop
    for (ij = 0; ij < nij; ij++) {
      if (jet_type_is("gen0", jet_part)) {
        if ((*gensubid)[ij] != 0) continue;
      }
      if (jet_type_is("bkg", jet_part) || jet_type_is("subbkg", jet_part)) {
        if ((*gensubid)[ij] == 0) continue;
      }
      if (jet_type_is("idreco", jet_part)) {
        if (!(*jetID)[ij]) continue;
      }
      if (jet_type_is("sidreco", jet_part)) {
        if ((*subid)[ij]) continue;
      }

      float tmpjetpt = j_pt[ij];
      float tmpjeteta = j_eta[ij];
      float tmpjetphi = j_phi[ij];

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      if (!isPP) {
        if (jet_type_is("sgen", jet_part)) {
          int resolutionBin = getResolutionBin(centmin);
          res_pt = getResolutionHI(tmpjetpt, resolutionBin);
          res_phi = getPhiResolutionHI(tmpjetpt, resolutionBin);
          nsmear = _NSMEAR;
        }
      }

      //! apply smearing if pp
      if (isPP) {
        if (jet_type_is("sreco", jet_part)) {
          res_pt = getSigmaRelPt(centmin, tmpjetpt);
          res_phi = getSigmaRelPhi(centmin, tmpjetpt);
          nsmear = _NSMEAR;
        } else if (jet_type_is("sgen", jet_part)) {
          res_pt = getResolutionPP(tmpjetpt);
          res_phi = getPhiResolutionPP(tmpjetpt);
          nsmear = _NSMEAR;
        }
      }

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = j_pt[ij] * smear_rand.Gaus(1, res_pt);
        tmpjetphi = j_phi[ij] + smear_rand.Gaus(0, res_phi);

        //! jet selections
        if (tmpjetpt < jetptcut) continue;
        if (fabs(tmpjeteta) > 1.6) continue;
        if (acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8) continue;

        if (signal) {
          hjetpt->Fill(tmpjetpt, smear_weight);
          njets_perevent++;
          xjgsignal->Fill(tmpjetpt / phoEtCorrected, smear_weight);
        }
        if (sideband) {
          hjetptsideband->Fill(tmpjetpt, smear_weight);
          xjgsideband->Fill(tmpjetpt / phoEtCorrected, smear_weight);
        }
        hphoSigmaIEtaIEta_2012->Fill(phoSigmaIEtaIEta_2012, smear_weight);

        // raw jet
        for (ip = 0; ip < nip; ++ip) {
          if (part_type_is("gen0", jet_part)) {
            if ((*sube)[ip] != 0) continue;
            if ((*chg)[ip] == 0) continue;
          }
          if (part_type_is("gen", jet_part)) {
            if ((*chg)[ip] == 0) continue;
          }

          if (p_pt[ip] < trkptmin) continue;
          float dphi = acos(cos(tmpjetphi - p_phi[ip]));
          float deta = fabs(tmpjeteta - p_eta[ip]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
            if (signal) { hgammaffxi->Fill(deltar, p_pt[ip] / refpt * weight * getTrkWeight(ip, trkWeight, jet_part) * smear_weight); }
            if (sideband) { hgammaffxisideband->Fill(deltar, p_pt[ip] / refpt * weight * getTrkWeight(ip, trkWeight, jet_part) * smear_weight); }
          }
        }

        if (isPP) continue;
        if (part_type_is("gen0", jet_part)) continue;

        // raw jet ue
        float nmixedUEevents = (nmix + 1) / 2;
        for (ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if ((p_ev_mix[ip_mix]) % 2 != 0) continue;
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
            if (signal) { hgammaffxiuemix->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedUEevents); }
            if (sideband) { hgammaffxiuemixsideband->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedUEevents); }
          }
        }
      }
    }

    if (isPP) continue;
    if (jet_type_is("gen0", jet_part)) continue;
    if (jet_type_is("bkg", jet_part)) continue;
    if (part_type_is("gen0", jet_part)) continue;

    //! (2.4) Mix jet loop
    float nmixedjetevents = nmix / 2;
    for (ij_mix = 0; ij_mix < nij_mix; ij_mix++) {
      if (j_ev_mix[ij_mix] % 2 != 1) continue;

      if (jet_type_is("idreco", jet_part)) {
        if (!(*jetID_mix)[ij_mix]) continue;
      }
      if (jet_type_is("sidreco", jet_part)) {
        if ((*subid_mix)[ij_mix]) continue;
      }

      float tmpjetpt = j_pt_mix[ij_mix];
      float tmpjeteta = j_eta_mix[ij_mix];
      float tmpjetphi = j_phi_mix[ij_mix];

      int nsmear = 1;
      float res_pt = 0;
      float res_phi = 0;

      if (jet_type_is("sgen", jet_part)) {
        int resolutionBin = getResolutionBin(centmin);
        res_pt = getResolutionHI(tmpjetpt, resolutionBin);
        res_phi = getPhiResolutionHI(tmpjetpt, resolutionBin);
        nsmear = _NSMEAR;
      }

      float smear_weight = 1. / nsmear;
      for (int is = 0; is < nsmear; ++is) {
        tmpjetpt = j_pt_mix[ij_mix] * smear_rand.Gaus(1, res_pt);
        tmpjetphi = j_phi_mix[ij_mix] + smear_rand.Gaus(0, res_phi);

        if (tmpjetpt < jetptcut) continue;
        if (fabs(tmpjeteta) > 1.6) continue;
        if (acos(cos(tmpjetphi - phoPhi)) < 7 * pi / 8) continue;
        if (signal) {
          hjetptjetmix->Fill(tmpjetpt, smear_weight / nmixedjetevents);
          njets_permixevent++;
          hnmixsignal->Fill(1, smear_weight);
          xjgmixsignal->Fill(tmpjetpt / phoEtCorrected, smear_weight / nmixedjetevents);
        }
        if (sideband) {
          hjetptjetmixsideband->Fill(tmpjetpt, smear_weight / nmixedjetevents);
          hnmixsideband->Fill(1, smear_weight);
          xjgmixsideband->Fill(tmpjetpt / phoEtCorrected, smear_weight / nmixedjetevents);
        }

        // mix jet
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen0", jet_part)) {
            if ((*sube)[ip_mix] != 0) continue;
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (j_ev_mix[ij_mix] != p_ev_mix[ip_mix]) continue; // tracks and jet come from same mixed event
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
            if (signal) {
              hgammaffxijetmix->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
            }
            if (sideband) {
              hgammaffxijetmixsideband->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
            }
          }
        }

        if (part_type_is("gen0", jet_part)) continue;

        // mix jet ue
        for (int ip_mix = 0; ip_mix < nip_mix; ++ip_mix) {
          if (part_type_is("gen", jet_part)) {
            if ((*chg_mix)[ip_mix] == 0) continue;
          }
          if (j_ev_mix[ij_mix] != (p_ev_mix[ip_mix] + 1)) continue;
          if (p_pt_mix[ip_mix] < trkptmin) continue;

          float dphi = acos(cos(tmpjetphi - p_phi_mix[ip_mix]));
          float deta = fabs(tmpjeteta - p_eta_mix[ip_mix]);
          float deltar = sqrt((dphi * dphi) + (deta * deta));
          if (deltar < 1) {
            float refpt = gammaxi ? phoEtCorrected : tmpjetpt;
            if (signal) {
              hgammaffxijetmixue->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
            }
            if (sideband) {
              hgammaffxijetmixuesideband->Fill(deltar, p_pt_mix[ip_mix] / refpt * weight * getTrkWeight(ip_mix, trkWeight_mix, jet_part) * smear_weight / nmixedjetevents);
            }
          }
        }
      }
    }
  }

  fout->Write();
  fout->Close();
}

int main(int argc, char* argv[]) {
  if (argc > 12 || argc < 3) {
    printf("usage: ./jetshape <input> <label> [centmin centmax] [phoetmin] [phoetmax] [jetptcut] [jet_part] [trkptmin] [gammaxi]\n");
    return 1;
  }

  photonjettrack* t = new photonjettrack(argv[1]);
  if (argc == 3)
    t->jetshape(argv[2]);
  else if (argc == 5)
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

  return 0;
}
