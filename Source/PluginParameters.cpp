/*
  ==============================================================================

    PluginParameters.cpp
    Created: 23 May 2024 5:29:14pm
    Author:  arjbah

  ==============================================================================
*/

#include "PluginParameters.h"

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(SELECT_NETWORK1_ID,
                                                                SELECT_NETWORK1_NAME,
                                                                false));
    params.push_back(std::make_unique<juce::AudioParameterBool>(SELECT_NETWORK2_ID,
                                                                SELECT_NETWORK2_NAME,
                                                                false));
    for (const auto & param : params) {
        parameterList.add(param->getParameterID());
    }

    return { params.begin(), params.end() };
}

juce::ValueTree PluginParameters::createNotAutomatableParameterLayout()
{
    juce::ValueTree notAutomatableParameters = juce::ValueTree("Settings");
    notAutomatableParameters.setProperty(NETWORK1_NAME_NAME, juce::var("Funk"), nullptr);
    notAutomatableParameters.setProperty(NETWORK2_NAME_NAME, juce::var("Djembe"), nullptr);
    return notAutomatableParameters;
}

juce::StringArray PluginParameters::getPluginParameterList() {
    return parameterList;
}