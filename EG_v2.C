/* 
   In this ROOT function, we generate a distribution of phi angles for multiple tracks within each event
   according to Eq. 1:
   f(ϕ) ∝ 1 + 2v2 cos[2(ϕ − Ψ2)]

   To run do:
   root 
   .L EG_v2.C 
   rootfuncgenerate(100, 1000, 0.1) // Example: 100 events, 1000 tracks in each event, v2 = 0.1
*/

// include C++ STL headers 
#include <iostream>

using namespace std;

// ROOT library objects
#include <TF1.h> // 1D function class
#include <TH1.h> // 1D histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRandom3.h> // Random number generator

void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t v2); // Updated ROOT method

//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t v2)
{
  cout << "Generating " << nEvents << " events with " << nTracks << " tracks per event and v2 = " << v2 << endl << endl;

  // Create histogram that we will fill with generated phi values
  TH1D* hPhi = new TH1D("hPhi", "Generated phi distribution; phi; Counts", 100, 0, 2 * TMath::Pi());

  // Initialize random number generator
  TRandom3 randgen;
// Loop over the number of events
  for (Int_t ne = 0; ne < nEvents; ne++) {

    // Temporary storage for phi angles for each track in the event
    Double_t phi[nTracks];

    // Generate phi angles for nTracks in the event
    for (Int_t nt = 0; nt < nTracks; nt++) {
      phi[nt] = 2 * TMath::Pi() * randgen.Rndm(); // Random phi between 0 and 2*pi
    }

    // Fill the histogram with phi values for this event
    for (Int_t i = 0; i < nTracks; i++) {
      // Calculate the function value according to Eq. 1
      Double_t cosTerm = TMath::Cos(2.0 * (phi[i] - 0)); // Assuming Ψ2 = 0
      Double_t funcValue = 1 + 2 * v2 * cosTerm;
      hPhi->Fill(phi[i], funcValue);
    }
  }
// Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // Create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "phi canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();

  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
}

