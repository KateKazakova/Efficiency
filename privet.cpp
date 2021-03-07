#include <bitset>
#include <iostream>
#include <cmath>

#include "TLine.h"
#include "TLatex.h"
#include "TMarker.h"
#include "TPave.h"
#include "TH1.h"
#include "TString.h"
#include <vector>
#include "AtlasUtils.C"
#include "AtlasLabels.C"
#include "AtlasStyle.C"
//#include "/home/katet/Programs/dfdg/2eff.C"

  void Func(double x, double y, double z){

  }


     TGraphAsymmErrors* DrawTwoEfficiencies(TString name, TString band1, TString band2, TH1F* hist1_before, TH1F* hist1_after,
                                            TH1F* hist2_before, TH1F* hist2_after, TString TitleX, TString TitleY, float setRangeA1_Y = 0., float setRangeA2_Y = 0.,
                                             bool drawSubPlot = false, TString TitleY_sub = "New/Old", float setRangeB1_Y = 0., float setRangeB2_Y = 0.)
{
  if(!hist1_before){
    cout<<"DrawRatioPlot:: Fatal error. Pointer hist1 before = 0x0"<<endl;
    exit(1);
  }
  if(!hist1_after){
    cout<<"DrawRatioPlot:: Fatal error. Pointer hist1 after = 0x0"<<endl;
    exit(1);
  }
  if(!hist2_before){
    cout<<"DrawRatioPlot:: Fatal error. Pointer hist2 before = 0x0"<<endl;
    exit(1);
  }
  if(!hist2_after){
    cout<<"DrawRatioPlot:: Fatal error. Pointer hist2 after = 0x0"<<endl;
    exit(1);
  }

  TCanvas *c1 = new TCanvas(name.Data(),name.Data(),0,0,800,600);
  TPad *c1_1 = new TPad("c1_1", "c1_1",0.007905138,0.2347107,0.9891304,0.9950413);
  TPad *c1_2 = new TPad("c1_2", "c1_2",0.008814887,0.006589786,0.9892262,0.2652389);

  if (drawSubPlot)
  {
    c1_1->Draw();
    c1_1->cd();
    c1_1->Range(-18.08743,-22.09887,32.57407,474.6759);
    c1_1->SetLeftMargin(0.1596366);
    c1_1->SetRightMargin(0.05080911);
    c1_1->SetTopMargin(0.04981374);
    c1_1->SetBottomMargin(0.04448469);
  }

  if (name.Contains("meeg")) c1->SetLogx();

    //hist1_before->Sumw2();
    //hist2_before->Sumw2();

    float minX = hist1_before->GetXaxis()->GetXmin();
    float maxX = hist1_before->GetXaxis()->GetXmax();
    float Nbins = hist1_before->GetNbinsX();
    TH1F *h = new TH1F("h", "h", Nbins, minX, maxX);
    TH1F *h1 = new TH1F("h1", "h1", Nbins, minX, maxX);

    TGraphAsymmErrors *eff1 = new TGraphAsymmErrors;
    eff1->Divide(hist1_after, hist1_before);

    TGraphAsymmErrors *eff2 = new TGraphAsymmErrors;
    eff2->Divide(hist2_after, hist2_before);

    eff1->SetLineWidth(3);
    eff1->SetMarkerSize(1.3);
    eff2->SetLineWidth(3);
    eff2->SetMarkerSize(1.3);
    //eff2->SetMarkerColor(kGreen+3);
    //xeff2->SetMarkerStyle(24);
    //eff2->SetLineColor(kGreen+3);
    eff2->SetMarkerColor(kRed);
    eff2->SetLineColor(kRed);

    h->GetXaxis()->SetTitle(TitleX.Data());
    h->GetYaxis()->SetTitle(TitleY.Data());

    if(setRangeA1_Y!=setRangeA2_Y) { // set specific range for Y axis
      h->SetMinimum(setRangeA1_Y);
      h->SetMaximum(setRangeA2_Y);
    }

    h->Draw();
    eff1->Draw("Psame");
    eff2->Draw("Psame");

    TLegend *leg = new TLegend(0.680306,0.7640643,0.8156797,0.9287524);
    leg->SetShadowColor(10);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.06404537);
    leg->SetFillStyle(1001);
    leg->SetFillColor(10);
    if (name.Contains("data18")) leg->AddEntry(eff1,"Z#rightarrowll#gamma Data18","");
    else if (name.Contains("data17")) leg->AddEntry(eff1,"Z#rightarrowll#gamma Data17","");
    else if (name.Contains("data16")) leg->AddEntry(eff1,"Z#rightarrowll#gamma Data16","");
    else if (name.Contains("mc")) leg->AddEntry(eff1,"Z#rightarrowll#gamma MC","");
    leg->AddEntry(eff1, Form("%s", band1.Data()),"lp");
    leg->AddEntry(eff2, Form("%s", band2.Data()),"lp");
    //leg->AddEntry(eff2,"35 < p_{T}^{#gamma} < 80 GeV","");
    leg->Draw();

    TLegend *leg3 = new TLegend(0.41339,0.2334027,0.4721371,0.3752174);
    leg3->SetShadowColor(10);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.06404537);
    leg3->SetFillStyle(1001);
    leg3->SetFillColor(10);
    ATLASLabel(0.22,0.88,"Internal");
    if (name.Contains("unc")) leg3->AddEntry(eff1,"Unconverted #gamma","");
    if (name.Contains("conv")) leg3->AddEntry(eff1,"Converted #gamma","");
    //leg3->AddEntry(data1,"Without bkg subtraction","");
    if (name.Contains("wptight")) leg3->AddEntry(eff1,"FixedCutTight","");
    if (name.Contains("wploose")) leg3->AddEntry(eff1,"FixedCutLoose","");
    if (name.Contains("wpcaloonly")) leg3->AddEntry(eff1,"FixedCutTightCaloOnly","");
    if (name.Contains("topoetcone20")) leg3->AddEntry(eff1,"E_{T}^{cone20} < 0.065 #times p_{T}","");
    if (name.Contains("ptcone20")) leg3->AddEntry(eff1,"p_{T}^{cone20}/p_{T} < 0.05","");
    if (name.Contains("tightid")) leg3->AddEntry(eff1,"Tight ID","");
    if (name.Contains("looseid")) leg3->AddEntry(eff1,"Loose ID","");
    leg3->Draw();

    TLegend *leg0 = new TLegend(0.3840164,0.1144613,0.541101,0.2265407);
    leg0->SetTextSize(0.06404537);
    leg0->SetShadowColor(10);
    leg0->SetBorderSize(0);
    leg0->SetFillStyle(1001);
    leg0->SetFillColor(10);
    if (name.Contains("eta0")) leg0->AddEntry(eff1, "0 < #cbar#eta^{#gamma}#cbar < 0.60","");
    else if (name.Contains("eta1")) leg0->AddEntry(eff1, "0.60 < #cbar#eta^{#gamma}#cbar < 1.37","");
    else if (name.Contains("eta3")) leg0->AddEntry(eff1, "1.52 < #cbar#eta^{#gamma}#cbar < 1.81","");
    else if (name.Contains("eta4")) leg0->AddEntry(eff1, "1.81 < #cbar#eta^{#gamma}#cbar < 2.37","");
    else leg0->AddEntry(h, "#cbar#eta^{#gamma}#cbar < 1.37, 1.52 < #cbar#eta^{#gamma}#cbar < 2.37","");
    leg0->Draw("same");

  if (drawSubPlot)
  {
    c1_1->Modified();
    c1->cd();

    c1_2->Draw();
    c1_2->cd();
    c1_2->Range(-18.10151,-1.965632,32.61929,2.637034);
    c1_2->SetLeftMargin(0.1597275);
    c1_2->SetRightMargin(0.05164129);
    c1_2->SetTopMargin(0.0437885);
    c1_2->SetBottomMargin(0.3645084);

    TGraphAsymmErrors *eff_sf = new TGraphAsymmErrors;
    eff_sf = myTGraphErrorsDivide(eff1, eff2);
    eff_sf->SetLineWidth(3);
    eff_sf->SetMarkerSize(1.2);

    h1->GetXaxis()->SetLabelSize(0.15);
    h1->GetYaxis()->SetLabelSize(0.15);
    h1->GetYaxis()->SetTitleOffset(0.46);
    h1->GetXaxis()->SetTitleOffset(1);
    h1->GetXaxis()->SetTitleSize(0.15);
    h1->GetYaxis()->SetTitleSize(0.15);
    h1->GetXaxis()->SetTickLength(0.1);

    h1->GetXaxis()->SetTitle(TitleX.Data());
    h1->GetYaxis()->SetTitle(TitleY_sub.Data());

    if(setRangeB1_Y!=setRangeB2_Y) { // set specific range for Y axis
      h1->SetMinimum(setRangeB1_Y);
      h1->SetMaximum(setRangeB2_Y);
    }

    h1->Draw();
    eff_sf->Draw("Psame");

    TLine *l=new TLine(minX, 1., maxX, 1.);
    l->SetLineColor(kBlack);
    l->SetLineStyle(9);
    l->SetLineWidth(2);
    l->Draw();
  }

    c1->SaveAs(Form("%s.pdf", name.Data()));
    return eff1;
}

 void privet(const char *fname2 = "/home/katet/Programs/dfdg/mc16e.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_Zy_Zll.deriv.DAOD_HIGG1D2.e5713_e5984_s3126_r10724_r10726_p4062.newmenu.root",
            const char *fname1= "/home/katet/Programs/dfdg/mc16e.PowhegPythia8EvtGen_NNLOPS_nnlo_30_ggH125_Zy_Zll.deriv.DAOD_HIGG1D2.e5713_e5984_s3126_r10724_r10726_p4062.oldmenu.root",
                           const char *fOutName = "/home/katet/GridRoot/moyaZadacha.root") {

    SetAtlasStyle();

    TFile *file1 = new TFile(fname1, "READ");
    TFile *file2 = new TFile(fname2, "READ");
    TFile *fOut = new TFile(fOutName, "RECREATE");


   // const int nBins = 100;
   // const float binLo = 0.0;
   // const float binHi = 50.0;


    TTree *tree1 =  (TTree*)file1->Get("HZG_Tree");
    TTree *tree2 =  (TTree*)file2->Get("HZG_Tree");

    Bool_t ph_isloose_old_menu = 0;
    Bool_t ph_isloose_new_menu = 0;
    Float_t llg_eta_old = 0;
    Float_t llg_eta_new = 0;


    tree1->SetBranchAddress("DR_ph_istruth", &llg_eta_old);
    tree2->SetBranchAddress("DR_ph_istruth", &llg_eta_new);
    tree1->SetBranchAddress("ph_isloose", &ph_isloose_old_menu);
    tree2->SetBranchAddress("ph_isloose", &ph_isloose_new_menu);


    unsigned int nEntries1 = tree1->GetEntries();
    unsigned int nEntries2 = tree2->GetEntries();

    const float binlow = 0;
    const float binhi = 6;

    TH1F *h_before_old = new TH1F("h_before_old","h_before_old",100,binlow,binhi);
    TH1F *h_after_old = new TH1F("h_after_old", "h_after_old", 100, binlow, binhi);
    TH1F *h_before_new = new TH1F("h_before_new", "h_before_new", 100, binlow, binhi);
    TH1F *h_after_new = new TH1F("h_after_new", "h_after_new", 100, binlow, binhi);



     for (unsigned int m = 0; m < nEntries1; m++) {
       tree1->GetEntry(m);

       h_before_old->Fill(llg_eta_old);

       if(ph_isloose_old_menu){
        h_after_old->Fill(llg_eta_old);
       }
     }

     for (unsigned int i = 0; i < nEntries2; i++) {
       tree2->GetEntry(i);

       h_before_new->Fill(llg_eta_new);

       if(ph_isloose_new_menu){
        h_after_new->Fill(llg_eta_new);
       }


     }



     /*TCanvas *c1 = new TCanvas("c1", "can", 0., 0., 600, 600);
     TCanvas *c2 = new TCanvas("c2", "canb", 0., 0., 600, 600);
      auto rp = new TRatioPlot( h_after_old, h_before_old);
      auto rp1 = new TRatioPlot(h_after_new, h_before_new);
      c1->cd();
      rp->Draw();
      c2->cd();
      rp1->Draw();*/

      //h_before_old, h_after_old, h_before_new, h_after_new

     DrawTwoEfficiencies("eff_m_menu","old menu","new menu", h_before_old, h_after_old, h_before_new, h_after_new, "dR GeV", "#varepsilon(ID)", -0.1, 1.5, true);
     cout<<"Bins in hist 1 before"<<h_before_old->GetNbinsX()<<endl;
     cout<<"Bins in hist 1 after"<<h_after_old->GetNbinsX()<<endl;
     cout<<"Bins in hist 2 after"<<h_before_new->GetNbinsX()<<endl;
     cout<<"Bins in hist 2 after"<<h_after_new->GetNbinsX()<<endl;


    fOut->cd();
}
