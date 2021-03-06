#include <TLatex.h>

//const int   nptBins  =   9;
//double xbins_pt[nptBins+1] = {0.0, 7.5, 12.5, 17.5, 24,30,40,50,70,110,150,190,250,600};

void drawDifference(TH1* iH0,TH1 *iH1) {
  std::string lName = std::string(iH0->GetName());
  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),50,0,300); lHDiff->Sumw2();
//  TH1F *lHDiff  = new TH1F((lName+"Diff").c_str(),(lName+"Diff").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax()); lHDiff->Sumw2();
  lHDiff->SetFillColor(kViolet); lHDiff->SetFillStyle(1001); lHDiff->SetLineWidth(1);
  TH1F *lXHDiff1 = new TH1F((lName+"XDiff1").c_str(),(lName+"XDiff1").c_str(),iH0->GetNbinsX(),iH0->GetXaxis()->GetXmin(),iH0->GetXaxis()->GetXmax());
  int i1 = 0;
  lXHDiff1->SetLineStyle(2); lXHDiff1->SetLineWidth(2); lXHDiff1->SetLineColor(kRed);

  lHDiff->GetYaxis()->SetRangeUser(0,2);
  lHDiff->GetYaxis()->SetTitleOffset(0.6);
  lHDiff->GetYaxis()->SetTitleSize(0.08);
  lHDiff->GetYaxis()->SetLabelSize(0.08);
  lHDiff->GetYaxis()->CenterTitle();
  lHDiff->GetXaxis()->SetTitleOffset(1.2);
  lHDiff->GetXaxis()->SetTitleSize(0.10);
  lHDiff->GetXaxis()->SetLabelSize(0.08);
  lHDiff->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
//  lHDiff->GetXaxis()->CenterTitle();
  lHDiff->GetYaxis()->SetTitle("MET/NoPuMEt");

  for(int i0 = 0; i0 < lHDiff->GetNbinsX()+1; i0++) {
    double lXCenter = lHDiff->GetBinCenter(i0);
    double lXVal     = iH0   ->GetBinContent(i0);
    lXHDiff1->SetBinContent(i0, 1.0);
    while(iH1->GetBinCenter(i1) < lXCenter) {i1++;}
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinContent(i0,lXVal      /(iH1->GetBinContent(i0)));
    if(iH1->GetBinContent(i0) > 0) lHDiff->SetBinError  (i0,iH0->GetBinError(i0)/(iH1->GetBinContent(i0)));
  }
  lHDiff->SetMarkerStyle(kFullCircle); lHDiff->SetLineColor(kBlack); lHDiff->SetMarkerColor(kBlack);
  lHDiff->Draw("E1");
  lXHDiff1->Draw("hist sames");
}

void CompMvaNoPuMEt()
{
//  InpFile = new TFile("ElectronHighPU/Ele_WToENu_S10_NoPUMEt.root");
//  InpFile = new TFile("ElectronHighPU/Ele_WJets_S10_MVAnoPUMEt.root");
//  InpFile = new TFile("ElectronHighPU/Ele_TTJets_S10_MVAnoPUMEt.root");
//  InpFile = new TFile("ElectronHighPU/Ele_ZG_Incl_S10_MVAnoPUMEt.root");
//  InpFile = new TFile("ElectronHighPU/Ele_ZGToNuNuG_S10_MVAnoPUMEt.root");
  InpFile = new TFile("ElectronHighPU/Ele_DYJetsToLL_S10_MVAnoPUMEt.root");

  char ylabel[100];

  TH1D *met;
  TH1D *NoPUmet;

  met =(TH1D*)InpFile->Get("h1_W_Met")->Clone();
  NoPUmet =(TH1D*)InpFile->Get("h1_W_NoPU_Met")->Clone();
  MVAmet =(TH1D*)InpFile->Get("h1_W_MVA_Met")->Clone();
  GENmet =(TH1D*)InpFile->Get("h1_W_Gen_Met")->Clone();

//  met =(TH1D*)InpFile->Get("h1_Z_Met")->Clone();
//  NoPUmet =(TH1D*)InpFile->Get("h1_Z_NoPU_Met")->Clone();
//  MVAmet =(TH1D*)InpFile->Get("h1_Z_MVA_Met")->Clone();

  met->SetLineColor(kBlack);
  NoPUmet->SetLineColor(kRed);
  MVAmet->SetLineColor(kBlue);
  GENmet->SetLineColor(kCyan);
  
//  sprintf(ylabel,"Events / %.1f GeV",NoPUmet->GetBinWidth(1));
//  NoPUmet->GetYaxis()->SetTitle(ylabel);
//  NoPUmet->GetYaxis()->SetTitleOffset(1.2);
//  NoPUmet->GetYaxis()->SetTitleSize(0.04);
//  NoPUmet->GetYaxis()->SetLabelSize(0.04);

  sprintf(ylabel,"Events / %.1f GeV",MVAmet->GetBinWidth(1));
  MVAmet->GetYaxis()->SetTitle(ylabel);
  MVAmet->GetYaxis()->SetTitleOffset(1.2);
  MVAmet->GetYaxis()->SetTitleSize(0.04);
  MVAmet->GetYaxis()->SetLabelSize(0.04);

//  sprintf(ylabel,"Events / %.1f GeV",GENmet->GetBinWidth(1));
//  GENmet->GetYaxis()->SetTitle(ylabel);
//  GENmet->GetYaxis()->SetTitleOffset(1.2);
//  GENmet->GetYaxis()->SetTitleSize(0.04);
//  GENmet->GetYaxis()->SetLabelSize(0.04);

  TLegend *lL =new TLegend(0.7,0.7,0.9,0.85);
  lL->SetFillColor(0); lL->SetBorderSize(0);
  lL->AddEntry(MVAmet,"MVA Met","L");
//  lL->AddEntry(GENmet,"Gen Met","L");
  lL->AddEntry(NoPUmet,"No PU Met","L");
  lL->AddEntry(met,"Met","L");
  TCanvas *lC0 = new TCanvas("Can","Can",800,800); lC0->cd(); lC0->SetLogy();
  lC0->Divide(1,2,0,0);
  lC0->cd(1)->SetPad(0,0.35,0.95,1.0);
  lC0->cd(1)->SetTopMargin(0.1);
  lC0->cd(1)->SetBottomMargin(0.01);
  lC0->cd(1)->SetLeftMargin(0.15);
  lC0->cd(1)->SetRightMargin(0.07);
  lC0->cd(1)->SetTickx(1);
  lC0->cd(1)->SetTicky(1);
  gStyle->SetTitleOffset(1.100,"Y");
  gStyle->SetLineWidth(2.);
  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.08,"xy");
  gStyle->SetTitleSize(0.08,"xy");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.0,"y");
  gStyle->SetOptTitle(0);
  TGaxis::SetMaxDigits(3);

//  gPad->SetLogy(1);
//  GENmet->Draw("hist");
  MVAmet->Draw("hist");
//  NoPUmet->Draw("hist");
  NoPUmet->Draw("hist same");
  MVAmet->Draw("hist same");
//  GENmet->Draw("hist same");
  met->Draw("hist same");
  lL->Draw();
  
  lC0->cd(2)->SetPad(0,0,0.95,0.35);
  lC0->cd(2)->SetTopMargin(0.025);
  lC0->cd(2)->SetBottomMargin(0.3);
  lC0->cd(2)->SetLeftMargin(0.15);
  lC0->cd(2)->SetRightMargin(0.07);
  lC0->cd(2)->SetTickx(1);
  lC0->cd(2)->SetTicky(1);
  drawDifference(met,NoPUmet);
//  lC0->SaveAs("WMetComp_TTJets.png");
//  lC0->SaveAs("ZMetComp_TTJets.png");
//  lC0->SaveAs("WMetComp_Z_Incl.png");
//  lC0->SaveAs("ZMetComp_Z_Incl.png");
//  lC0->SaveAs("WMetComp_WJetsToLNu.png");
//  lC0->SaveAs("ZMetComp_WJetsToLNu.png");
//  lC0->SaveAs("WMetComp_ZGToNuNuG.png");
//  lC0->SaveAs("ZMetComp_ZGToNuNuG.png");
  lC0->SaveAs("WMetComp_DYJets.png");
}
