// #include "ParameterControl.h"

// ParameterControl::ParameterControl(juce::AudioProcessorValueTreeState &parameters) : parameters(parameters) 
// {}

// void ParameterControl::parameterChanged(const juce::String &parameterID, float newValue) {
//     juce::ignoreUnused(parameterID, newValue);
//     /*
//      *  Greys fade slider out when one network is disabled. This functionality is currently disabled and might be enabled and brought to other sliders as well in the future...
//      *
//     if (parameterID == PluginParameters::ON_OFF_NETWORK1_ID || parameterID == PluginParameters::ON_OFF_NETWORK2_ID) {
//         handleNetworkEnablementChange();
//     }
//      */
// }