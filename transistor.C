#include "TF1.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TString.h"

void transistor()
{
  gStyle->SetOptFit(111);
  TCanvas *c = new TCanvas("Caratteristica di Uscita Transistor BJT");
  c->SetGrid();
  gStyle->SetErrorX(0);

  TGraphErrors *g100 = new TGraphErrors("100micro.dat");
  //g100->SetPointError(); check error X
  // g100->SetMarkerStyle(2);
  // g100->SetMarkerColor(kRed);
  // g100->SetLineColor(kRed);

  TGraphErrors *g50 = new TGraphErrors("50micro.dat");
  // g50->SetMarkerStyle(2);
  // g50->SetMarkerColor(kBlue);
  // g50->SetLineColor(kBlue);

  TLegend *leg = new TLegend(.1, .7, .3, .9, "Punti Sperimentali");
  leg->AddEntry(g100, "I_{C}=-100mA");
  leg->AddEntry(g50, "I_{C}=-50mA");

  TMultiGraph *g = new TMultiGraph();
  g->SetTitle("Caratteristica di Uscita Transistor;Voltage |V_{CE}| (V);Current |I_{C}| (mA)");
  g->Add(g100);
  g->Add(g50);

  g->Draw("APE");
//controllare parametri
  TF1 *f100 = new TF1("f100", "[0]+[1]*x", 0.4, 4.2);
  f100->SetRange(0, 4.2);
  f100->SetParameter(0,10);
  f100->SetParName(0, "Tensione di Early");
  f100->SetParName(1, "Resistance");
  f100->SetLineColor(kBlue);

  TF1 *f50 = new TF1("f50", "[0]+[1]*x", 0.4, 4.2);
  f50->SetParameter(0,10);
  f50->SetRange(0, 4.2);
  f50->SetParName(0, "Tensione di Early");
  f50->SetParName(1, "Resistance");
  f50->SetLineColor(kRed);

  g100->Fit(f100);
  TF1 *fit100 = g100->GetFunction("f100");

  g50->Fit(f50);
  TF1 *fit50 = g50->GetFunction("f100");

  leg->Draw("SAME");

  c->Print("transistorBJT.pdf");
}
