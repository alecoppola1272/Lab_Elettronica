#include "TF1.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TLegend.h"

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

    Float_t x[15] = {380, 400, 420, 450, 480, 500, 520, 550, 580, 600, 620, 640, 680, 720, 760};                                // Dati tensiome
    Float_t y[15] = {0.01, 0.01, 0.01, 0.02, 0.04, 0.06, 0.08, 0.14, 0.25, 0.4, 0.58, 0.9, 1.81, 3.49, 6.6};                    // Dati corrente
    Float_t ex[15] = {15.84, 16.28, 16.73, 17.41, 18.12, 18.60, 19.09, 19.83, 20.59, 27.66, 28.05, 28.45, 29.28, 30.13, 31.00}; // errori su tensione
    Float_t ey[15] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.05, 0.07, 0.12};                // errori su corrente
    
    TGraphErrors *graph = new TGraphErrors(15, x, y, ex, ey);
    graph->SetTitle("Diodo al Si");
    graph->GetXaxis()->SetTitle("Voltage(mv)");
    graph->GetYaxis()->SetTitle("Current(mA)");
    graph->SetMarkerStyle(4);
    graph->Draw("APE");

    TF1 *f = new TF1("f", "[0]*(exp(x/[1]-1))", 350, 800); // fit caratteristica I-V
    f->SetParName(0, "I0");
    f->SetParName(1, "EtaVt");
    f->SetParameter(0, 1e-5);
    f->SetParameter(1, 50);

    graph->Fit("f");
    TF1 *fit = graph->GetFunction("f");
}

void diodoGe()
{
    gStyle->SetOptFit(1111);
    TCanvas *c2 = new TCanvas("Germanio");
    c2->SetLogy();

    Float_t x[15] = {60, 80, 100, 120, 140, 160, 180, 200, 220, 250, 270, 300, 320, 340, 360};                        // Dati tensiome
    Float_t y[15] = {0.01, 0.01, 0.03, 0.04, 0.07, 0.1, 0.16, 0.25, 0.36, 0.69, 1, 1.8, 2.35, 3.37, 4.83};            // Dati corrente
    Float_t ex[15] = {6.26, 6.46, 6.71, 7.00, 7.32, 7.68, 8.07, 8.49, 8.92, 9.60, 10.08, 10.82, 14.60, 15.00, 15.42}; // errori su tensione
    Float_t ey[15] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.04, 0.05, 0.06, 0.07, 0.09};      // errori su corrente

    TGraphErrors *graph2 = new TGraphErrors(15, x, y, ex, ey);
    graph2->SetTitle("Diodo al Ge");
    graph2->GetXaxis()->SetTitle("Voltage(mv)");
    graph2->GetYaxis()->SetTitle("Current(mA)");
    graph2->SetMarkerStyle(4);
    graph2->Draw("APE");

    TF1 *f2 = new TF1("f", "[0]*(exp(x/[1]-1))", 40, 400); // fit caratteristica I-V
    f2->SetParName(0, "I0");
    f2->SetParName(1, "EtaVt");
    f2->SetParameter(0, 1e-2);
    f2->SetParameter(1, 25);

    graph2->Fit("f");
    TF1 *fit2 = graph2->GetFunction("f");
}
