// -*- C++ -*-
//
// Package:    Primtester/Primtest
// Class:      Primtest
// 
/**\class Primtest Primtest.cc Primtester/Primtest/plugins/Primtest.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
 */
//
// Original Author:  Zachary Lesko
//         Created:  Tue, 03 Mar 2015 02:58:32 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class declaration
//
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/Common/interface/Handle.h"



#include <memory>

// user include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"
#include "DataFormats/HcalDetId/interface/HcalTrigTowerDetId.h"

#include "CalibCalorimetry/CaloTPG/src/CaloTPGTranscoderULUT.h"
#include "CalibFormats/HcalObjects/interface/HcalTPGRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalTPGCoder.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"

//#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"

#include <iostream>
using namespace std;


class Primtest : public edm::EDAnalyzer {
public:
  explicit Primtest(const edm::ParameterSet&);
  ~Primtest();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

Primtest::Primtest(const edm::ParameterSet& iConfig) {
  //now do what ever initialization is needed

}

Primtest::~Primtest() {

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------

void
Primtest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  //using namespace edm;

  edm::Handle<HcalTrigPrimDigiCollection> hfpr_digi;
  iEvent.getByLabel("simHcalTriggerPrimitiveDigis", hfpr_digi);

  edm::ESHandle<CaloTPGTranscoder> outTranscoder;
  iSetup.get<CaloTPGRecord>().get(outTranscoder);
  outTranscoder->setup(iSetup, CaloTPGTranscoder::HcalTPG);
  for (HcalTrigPrimDigiCollection::const_iterator tp = hfpr_digi->begin(); tp != hfpr_digi->end(); ++tp) {
double RealEt= outTranscoder->hcaletValue(tp->id(), (*tp)[1]);
cout<<"Real Et? "<<RealEt<<endl;
  }

}


// ------------ method called once each job just before starting event loop  ------------

void
Primtest::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------

void
Primtest::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void 
Primtest::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when ending the processing of a run  ------------
/*
void 
Primtest::endRun(edm::Run const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
Primtest::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
 */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
Primtest::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
 */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------

void
Primtest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Primtest);
