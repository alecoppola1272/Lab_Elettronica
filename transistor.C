#include "TF1.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include <iostream>
#include "TROOT.h"
#include "TString.h"

void transistor()
{
  gStyle->SetOptFit(0);
  TCanvas *c = new TCanvas("Caratteristica di Uscita Transistor BJT");
  c->SetGrid();

  TGraphErrors *g100 = new TGraphErrors("100micro.dat");
  g100->SetLineColor(12);

  TGraphErrors *g50 = new TGraphErrors("50micro.dat");
  g50->SetLineColor(12);

  g100->Fit("pol1", "Q", "", 0.5, 4.5);
  TF1 *fit100 = g100->GetFunction("pol1");
  fit100->SetRange(0, 5);
  fit100->SetParName(1, "g");
  fit100->SetLineColor(kRed);
  fit100->SetLineWidth(1);

  g50->Fit("pol1", "Q", "", 0.5, 4.5);
  TF1 *fit50 = g50->GetFunction("pol1");
  fit50->SetRange(0, 5);
  fit50->SetParName(1, "g");
  fit50->SetLineColor(kBlue);
  fit50->SetLineWidth(1);

  TLegend *leg = new TLegend(0.65, 0.13, 0.88, 0.28, "Corrente di Base");
  leg->AddEntry(fit100, "I_{B}=-100 microA");
  leg->AddEntry(fit50, "I_{B}=-50 microA");

  TMultiGraph *g = new TMultiGraph();
  g->SetTitle("Caratteristica di Uscita Transistor;Voltage |V_{CE}| (V);Current |I_{C}| (mA)");
  g->Add(g100);
  g->Add(g50);

  g->Draw("APE");
  leg->Draw("SAME");
  std::cout << "CORRENTE DI BASE I_b = 100 microA" << std::endl;
  std::cout << "p0 (intercetta) : " << fit100->GetParameter(0) << " +/- " << fit100->GetParError(0) << std::endl;
  std::cout << "p1 (slope) : " << fit100->GetParameter(0) << " +/- " << fit100->GetParError(0) << std::endl;
  std::cout << "---------------------------------------------------------------------------------" << std::endl;
  std::cout << "CORRENTE DI BASE I_b = 50 microA" << std::endl;
  std::cout << "p0 (intercetta) : " << fit50->GetParameter(0) << " +/- " << fit50->GetParError(0) << std::endl;
  std::cout << "p1 (slope) : " << fit50->GetParameter(0) << " +/- " << fit50->GetParError(0) << std::endl;

  c->Print("transistorBJT.pdf");
}
