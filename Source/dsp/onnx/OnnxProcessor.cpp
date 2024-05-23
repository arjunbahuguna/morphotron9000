/*
  ==============================================================================

    OnnxProcessor.cpp
    Created: 23 May 2024 5:31:46pm
    Author:  arjbah

  ==============================================================================
*/

#include "OnnxProcessor.h"

//constructor
OnnxProcessor::OnnxProcessor(juce::AudioProcessorValueTreeState &apvts, int no): parameters(apvts), number(no)
{

}

void OnnxProcessor::parameterChanged(const juce::String &parameterID, float newValue) {
    if (parameterID == PluginParameters::SELECT_NETWORK1_ID.getParamID() && number == 1) {
        auto newValueBool = (bool) newValue;
        if (!newValueBool) {
            onOnnxModelLoad(true, "");
            //inferenceThread.setInternalModel();
        }
    } else if (parameterID == PluginParameters::SELECT_NETWORK2_ID.getParamID() && number == 2) {
        auto newValueBool = (bool) newValue;
        if (!newValueBool) {
            onOnnxModelLoad(true, "");
            //inferenceThread.setInternalModel();
        }
//     } else if (parameterID == PluginParameters::ON_OFF_NETWORK1_ID.getParamID() && number == 1) {
// //        setMuted(!(bool) newValue);
//     } else if (parameterID == PluginParameters::ON_OFF_NETWORK2_ID.getParamID() && number == 2) {
// //        setMuted(!(bool)newValue);
    }
}

void OnnxProcessor::loadExternalModel(juce::File file) {
    onOnnxModelLoad(true, file.getFileNameWithoutExtension());
    //inferenceThread.setExternalModel(file);
}
