#include <iostream.h>
#define Nbin 11
void trig_pt()
{
  TCanvas *myCan=new TCanvas("myCan","myCan");
  myCan->SetGrid();
  TFile *f_MC= new TFile("TnP_WptCutToTrig_MCptminus.root","read");
  RooDataSet *datasetMC = (RooDataSet*)f_MC->Get("tpTree/Tnp_WptCut_to_Mu15_eta2p1_pt/cnt_eff");
  cout<<"ntry: "<<datasetMC->numEntries()<<endl;
  double XMC[Nbin],XMCerrL[Nbin],XMCerrH[Nbin],YMC[Nbin],YMCerrLo[Nbin],YMCerrHi[Nbin];
  for(int i(0); i<datasetMC->numEntries();i++)
  {
    const RooArgSet &pointMC=*datasetMC->get(i);
    RooRealVar &ptMC=pointMC["pt"],&effMC = pointMC["efficiency"];
    XMC[i]=ptMC.getVal();
    XMCerrL[i]=-ptMC.getAsymErrorLo();
    XMCerrH[i]=ptMC.getAsymErrorHi();
    YMC[i]=effMC.getVal();
    YMCerrLo[i]=-effMC.getAsymErrorLo();
    YMCerrHi[i]=effMC.getAsymErrorHi();
  }
  grMC=new TGraphAsymmErrors(11,XMC,YMC,XMCerrL,XMCerrH,YMCerrLo,YMCerrHi);
  grMC->SetLineColor(kRed);
  grMC->SetMarkerColor(kRed);
  grMC->Draw("AP");
  //grMC->Draw("psame");
  myCan->SaveAs("trig_McMinus_pt.png");
  myCan->SaveAs("trig_McMinus_pt.eps");

}
