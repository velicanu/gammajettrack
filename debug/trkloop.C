#include "getTrkCorr.h"
#include <cstdlib>
#include <random>

int main(int argc, char *argv[])
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(1, 2);
  std::uniform_real_distribution<> trkpt(0.5, 300);
  std::uniform_real_distribution<> trketa(-2.4, 2.4);
  std::uniform_real_distribution<> trkphi(-3.14, 3.14);
  std::uniform_real_distribution<> rmin(0, 1);
  std::uniform_int_distribution<> hibin(0, 39);
  for (int n = 0; n < 10; ++n) {
    std::cout << dis(gen) << ' ';
  }
  std::cout << '\n';
  TrkCorr* trkCorr = new TrkCorr("TrkCorr_Mar15_Iterative_PbPb/");
  for(int i = 0 ; i < std::atoi(argv[1]) ; ++i)
  {
    float trkweight = 0;
    trkweight=trkCorr->getTrkCorr(trkpt(gen),trketa(gen),trkphi(gen),hibin(gen),rmin(gen), i);
    // trkweight=getTrkWeight(trkCorr,i,32,i);
    std::cout<<trkweight<<endl;
  }
  
  return 0;
}

