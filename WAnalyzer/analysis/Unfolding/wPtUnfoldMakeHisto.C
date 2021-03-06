#include <iostream>
#include "../EventSelection/include/SetupTree.h"
#include "../Utils/const.h"
using namespace std;
#define	RealLumi	(18.977) //pb
void wPtUnfoldMakeHisto()
{
//======================================
// choose Mode and AnaChannel here  !!!
//======================================
//  TString Mode = "Unfold";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
//  TString AnaChannel = "MuonLowPU"; //ElectronLowPU

TString Mode = "Unfold";//Analysis,Recoil, RecoilMC, RecoilCorr, Unfold,
TString AnaChannelEle = "ElectronLowPU"; 
TString AnaChannelMu  = "MuonLowPU";

  gSystem->CompileMacro("../EventSelection/WLepNeu.C","k");
//====================
/////////// Muon LowPU
//====================
// For Muon analysis: use the lines FROM HERE
  //Luminosity weight
  double LumiW_WpToMuNu = LumiWeight_Muon_WpToMuNu_S8;
  double LumiW_WmToMuNu = LumiWeight_Muon_WmToMuNu_S8;
  //double LumiWeight_Muon_WpToMuNu_S8 = RealLumi*1*6702.0/935446;
  //double LumiWeight_Muon_WmToMuNu_S8 = RealLumi*1*4697.0/1.97346e6;
  LumiW_WpToMuNu = 1;
  LumiW_WmToMuNu = 1;



  //**********
//WpToMuNu========================================
  cout<<"WpToMuNu_S8===================="<<endl;
  TChain *TC_Muon_WpToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WpToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8);
  SetupTree("Muon_WpToMuNu_S8",TC_Muon_WpToMuNu_S8_Mu);
  TString Muon_WpToMuNuFile = "Muon_WpToMuNu_S8_"+Mode;
  WLepNeu WPt_WpMuNu(TC_Muon_WpToMuNu_S8,TC_Muon_WpToMuNu_S8_Mu,
  	LumiW_WpToMuNu, Muon_WpToMuNuFile,Mode,AnaChannelMu);
  WPt_WpMuNu.Loop();
 //***/ 
//WmToMuNu========================================
//***
  cout<<"WmToMuNu_S8========================"<<endl;
  TChain *TC_Muon_WmToMuNu_S8    = new TChain("WMuNeu/tree","");
  TChain *TC_Muon_WmToMuNu_S8_Mu = new TChain("Muons/tree","");
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8);
  SetupTree("Muon_WmToMuNu_S8",TC_Muon_WmToMuNu_S8_Mu);
  TString Muon_WmToMuNuFile = "Muon_WmToMuNu_S8_"+Mode;
  WLepNeu WPt_WmMuNu(TC_Muon_WmToMuNu_S8,TC_Muon_WmToMuNu_S8_Mu,
  	LumiW_WmToMuNu, Muon_WmToMuNuFile,Mode,AnaChannelMu);
  WPt_WmMuNu.Loop();
//***/

// For Muon analysis: TO HERE

//=========================
/////////// Electron LowPU
//=========================
// For Electron analysis: use the lines FROM HERE
//Luminosity weight
//***
  double LumiW_WpToElNu = LumiWeight_Ele_WpToEleNu_S8;
  double LumiW_WmToElNu = LumiWeight_Ele_WmToEleNu_S8;
  //double LumiWeight_Ele_WpToEleNu_S8= RealLumi*1*6702.0/2401905;
  //double LumiWeight_Ele_WmToEleNu_S8= RealLumi*1*4697.0/2127666;
  LumiW_WpToElNu = 1;
  LumiW_WmToElNu = 1;


  //***
  cout<<"Ele_WminusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WmToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WmToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8);
  SetupTree("Ele_WmToEleNu_S8",TC_Ele_WmToEleNu_S8_Ele);
  TString Ele_WmToEleNu_S8File = "Ele_WmToEleNu_S8_"+Mode;
  WLepNeu WPt_WmToEleNu_S8(TC_Ele_WmToEleNu_S8,TC_Ele_WmToEleNu_S8_Ele,
  	LumiW_WmToElNu, Ele_WmToEleNu_S8File,Mode,AnaChannelEle);
  WPt_WmToEleNu_S8.Loop();
  //***/

  //***
  cout<<"Ele_WplusToEleNu_S8==========================="<<endl;
  TChain *TC_Ele_WpToEleNu_S8    = new TChain("WEleNeu/tree","");
  TChain *TC_Ele_WpToEleNu_S8_Ele = new TChain("Electrons/tree","");
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8);
  SetupTree("Ele_WpToEleNu_S8",TC_Ele_WpToEleNu_S8_Ele);
  TString Ele_WpToEleNu_S8File = "Ele_WpToEleNu_S8_"+Mode;
  WLepNeu WPt_WpToEleNu_S8(TC_Ele_WpToEleNu_S8,TC_Ele_WpToEleNu_S8_Ele,
  	LumiW_WpToElNu, Ele_WpToEleNu_S8File,Mode,AnaChannelEle);
  WPt_WpToEleNu_S8.Loop();
  //***/

// For Electron analysis: TO HERE
}
