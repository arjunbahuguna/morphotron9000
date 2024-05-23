#pragma once

#include "PluginProcessor.h"
#include "PluginParameters.h"
//#include "ui/CustomComponents/ParameterControl/ParameterControl.h"

//==============================================================================
/**
*/
class Morphotron9000AudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::AudioProcessorValueTreeState::Listener
{
public:

    explicit Morphotron9000AudioProcessorEditor (Morphotron9000AudioProcessor&, juce::AudioProcessorValueTreeState& parameters);
    ~Morphotron9000AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void parameterChanged (const juce::String& parameterID, float newValue) override;

private:
    void openFileChooser(int id);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Morphotron9000AudioProcessor& processorRef;

    juce::AudioProcessorValueTreeState& apvts;
    //ParameterControl parameterControl;

    std::unique_ptr<juce::FileChooser> fc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Morphotron9000AudioProcessorEditor)
};
