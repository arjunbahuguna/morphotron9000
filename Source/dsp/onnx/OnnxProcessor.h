/*
  ==============================================================================

    OnnxProcessor.h
    Created: 23 May 2024 5:31:46pm
    Author:  arjbah

  ==============================================================================
*/

#pragma once

#ifndef VAESYNTH_ONNXPROCESSOR_H
#define VAESYNTH_ONNXPROCESSOR_H

#include "JuceHeader.h"
#include "../../PluginParameters.h"


class OnnxProcessor{
public:
    OnnxProcessor(juce::AudioProcessorValueTreeState &apvts, int no);
    void parameterChanged(const juce::String &parameterID, float newValue);

    void loadExternalModel(juce::File path);

    std::function<void(bool initLoading, juce::String modelName)> onOnnxModelLoad;

private:
    juce::AudioProcessorValueTreeState& parameters;
    int number;
};

#endif