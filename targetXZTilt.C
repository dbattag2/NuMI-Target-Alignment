/* targetXZTilt.C -- Plot the mean reconstructed X position vs Z positon of particles to get tilt from slope
   
    Language: C++
    
    Dominic Battaglia
    
    University of Notre Dame
    Written for NA61 NuMI target analysis                                                                                                                              
    Last modified February 10, 2023.                                                                                                                                   
    2/10/23 (mac):  
*/


#include<iostream>
#include <TCanvas.h>
#include <TF1Convolution.h>
#include <TF1.h>
#include <TH1F.h>

#include "TTree.h"

void targetXZTilt()
{
  TFile *targetVertexData = TFile::Open("/Users/dbattag/TargetTilt/recNOvA18DataAllTracks.root","READ");
  TFile *targetVertexDataVTPCMTPC = TFile::Open("/Users/dbattag/TargetTilt/recNOvA18DataVTPCMTPCTracks.root","READ");
  TFile *targetVertexMC = TFile::Open("/Users/dbattag/shineRootFiles/oldLongVertexingModuleMC.root","READ");
  
  TTree *recTreeData = (TTree*)targetVertexData->Get("Rec");
  TTree *recTreeDataVTPCMTPC = (TTree*)targetVertexDataVTPCMTPC->Get("Rec");
  TTree *recTreeMC = (TTree*)targetVertexMC->Get("Rec");
  
  TH2F* dataHisto = new TH2F("dataHisto","Reconstructed X vs Z;Z Vertex Position [cm]; X Vertex Position [cm]",31,-656,-532,500,-0.5,0.5);
  TH2F* dataHistoVTPCMTPC = new TH2F("dataHistoVTPCMTPC","Reconstructed X vs Z;Z Vertex Position [cm]; X Vertex Position [cm]",31,-656,-532,500,-0.5,0.5);
  TH2F* MCHisto = new TH2F("MCHisto","Reconstructed X vs Z;Z Vertex Position [cm];X Vertex Position [cm]",31,-656,-532,500,-0.5,0.5);
  
  recTreeData->Draw("recStartXPos:recStartZPos>>dataHisto","recStartYPos<0.5 && recStartYPos>-0.5","COLZ");
  recTreeDataVTPCMTPC->Draw("recStartXPos:recStartZPos>>dataHistoVTPCMTPC","recStartYPos<0.5 && recStartYPos>-0.5","COLZ");
  recTreeMC->Draw("recStartXPos:recStartZPos>>MCHisto","recStartYPos<0.5 && recStartYPos>-0.5","COLZ");

  TH1F* xMeanHistData = new TH1F("xMeanHistData","Mean Reconstructed X-Value vs Z Position;Z Vertex Position [cm];X Mean Value [cm]",31,-656,-532);
  TH1F* xMeanHistDataVTPCMTPC = new TH1F("xMeanHistDataVTPCMTPC","Mean Reconstructed X-Value vs Z Position;Z Vertex Position [cm];X Mean Value [cm]",31,-656,-532);
  TH1F* xMeanHistMC = new TH1F("xMeanHistMC","Mean Reconstructed X-Value vs Z Position;Z Vertex Position [cm];X Mean Value [cm]",31,-656,-532);
  
  for (int xBin = 1; xBin < dataHisto->GetNbinsX(); xBin++) {
    //xMeanHistData->Fill(-656+(xBin-1),dataHisto->ProjectionY("projY",xBin,xBin+1)->GetMean());
    xMeanHistData->SetBinContent(xBin,dataHisto->ProjectionY("projY",xBin,xBin+1)->GetMean());
    xMeanHistData->SetBinError(xBin,dataHisto->ProjectionY("projY",xBin,xBin+1)->GetMeanError());
    xMeanHistDataVTPCMTPC->SetBinContent(xBin,dataHistoVTPCMTPC->ProjectionY("projY",xBin,xBin+1)->GetMean());
    xMeanHistDataVTPCMTPC->SetBinError(xBin,dataHistoVTPCMTPC->ProjectionY("projY",xBin,xBin+1)->GetMeanError());
    xMeanHistMC->SetBinContent(xBin,MCHisto->ProjectionY("projY",xBin,xBin+1)->GetMean());
    xMeanHistMC->SetBinError(xBin,MCHisto->ProjectionY("projY",xBin,xBin+1)->GetMeanError());
  }
  xMeanHistData->Draw("E");
  xMeanHistDataVTPCMTPC->Draw("E SAME");
  xMeanHistMC->Draw("E SAME");
  //xMeanHistData->GetYaxis()->SetRangeUser(-0.1,0.1);
  //xMeanHistMC->GetYaxis()->SetRangeUser(-0.1,0.1);

  xMeanHistData->SetLineColor(kRed);
  xMeanHistMC->SetLineColor(kBlue);
  
  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->SetHeader("Histogram Legend","C");
  legend->AddEntry(xMeanHistData,"NuMI Reconstructed Data All Tracks","lep");
  legend->AddEntry(xMeanHistDataVTPCMTPC,"NuMI Reconstructed Data Only VTPC & MTPC Tracks","lep");
  legend->AddEntry(xMeanHistMC,"NuMI Reconstructed MC","lep");
  legend->Draw("same");

  //double numiUpstreamFace = -656;
  //double numiDownstreamFace = -532;
  //int binsMax = 124;
  //double zStep = (numiDownstreamFace - numiUpstreamFace)/binsMax;
  
  //for (int zBins = 0; zBins<binsMax; zBins++) {
    
  //}
  //TH1F* hist1 = new TH1F();
}
