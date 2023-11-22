#include "TF1.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TStyle.h"

void diodoCal()
{
    gStyle->SetOptFit(1111);
    TCanvas *c = new TCanvas("Calibration");

    Float_t x[8] = {50, 100, 200, 300, 400, 500, 600, 800};            // Tensione Oscilloscopio
    Float_t y[8] = {48, 97.2, 195.4, 298.5, 385.6, 484.3, 581.1, 779}; // Tensione Multimentro
    Float_t ex[8] = {0};                                               // Errori su tensione oscilloscopio

    TGraphErrors *graph = new TGraphErrors(8, x, y, ex);
    graph->SetTitle("Retta di Calibrazione");
    graph->GetXaxis()->SetTitle("Oscilloscope Voltage (mv)");
    graph->GetYaxis()->SetTitle("Multimeter Voltage (mv)");
    graph->SetMarkerStyle(4);
    graph->Draw("APE");

    TF1 *f = new TF1("f", "[0]+x*[1]", 0, 850); // Fit retta di calibrazione
    f->SetParName(0, "offset");
    f->SetParameter(0, 0.7);
    f->SetParameter(1, 1);

    graph->Fit(f);
    TF1 *fit = graph->GetFunction("f");
}

void diodoSi()
{
    gStyle->SetOptFit(1111);
    TCanvas *c = new TCanvas("Silcio");
    c->SetLogy();

    Float_t x[15] = {380, 400, 420, 450, 480, 500, 520, 550, 580, 600, 620, 640, 680, 720, 760};             // Dati tensiome
    Float_t y[15] = {0.01, 0.01, 0.01, 0.02, 0.04, 0.06, 0.08, 0.14, 0.25, 0.4, 0.58, 0.9, 1.81, 3.49, 6.6}; // Dati corrente
    Float_t ex[15] = {0};                                                                                    // errori su tensione
    Float_t ey[15] = {0};                                                                                    // errori su corrente

    TGraphErrors *graph = new TGraphErrors(15, x, y, ex, ey);
    graph->SetTitle("Diodo al Si");
    graph->GetXaxis()->SetTitle("Voltage(mv)");
    graph->GetYaxis()->SetTitle("Current(mA)");
    graph->SetMarkerStyle(4);
    graph->Draw("APE");

    TF1 *f = new TF1("f", "[0]*(exp(x/[1]-1))", 350, 800); // fit caratteristica I-V
    f->SetParName(0, "I0");
    f->SetParName(1, "EtaVt");
    f->SetParameter(0, 1e-6);
    f->SetParameter(1, .50);

    graph->Fit("f");
    TF1 *fit = graph->GetFunction("f");

    /*TLegend *leg = new TLegend(.1,.7,.3,.9,"legenda");
    leg->AddEntry(graph,"punti sperimentali");
    leg->AddEntry(f,"curva di fit");
    leg->Draw("same");
    */
}