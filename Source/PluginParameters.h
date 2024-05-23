/*
  ==============================================================================

    PluginParameters.h
    Created: 23 May 2024 5:29:14pm
    Author:  arjbah

  ==============================================================================
*/
#pragma once

#ifndef PLUGINPARAMETERS_H
#define PLUGINPARAMETERS_H //these are added to avoid "Error: Redefition of PluginParameters"

#include <JuceHeader.h>

class PluginParameters {
public:
    
    inline static const juce::ParameterID
            SELECT_NETWORK1_ID = {"select_network1", 1},
            SELECT_NETWORK2_ID = {"select_network2", 1};

    inline static const juce::String
            SELECT_NETWORK1_NAME = "Select Network 1",
            SELECT_NETWORK2_NAME = "Select Network 2",
            
            // not automatable parameters
            NETWORK1_NAME_NAME = "network1_name",
            NETWORK2_NAME_NAME = "network2_name";

    static juce::StringArray getPluginParameterList(); // called by both editor & processor
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); //called by processor
    static juce::ValueTree createNotAutomatableParameterLayout(); //called by processor

private:
    inline static juce::StringArray parameterList;    
};

#endif //AUDIO_PLUGIN_EXAMPLE_PLUGINPARAMETERS_H