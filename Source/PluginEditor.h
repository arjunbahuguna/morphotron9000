/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Morphotron9000AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Morphotron9000AudioProcessorEditor (Morphotron9000AudioProcessor&);
    ~Morphotron9000AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Morphotron9000AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Morphotron9000AudioProcessorEditor)
};
