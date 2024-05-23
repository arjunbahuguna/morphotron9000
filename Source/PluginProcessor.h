#pragma once

#include <JuceHeader.h>
#include "PluginParameters.h"
#include "dsp/onnx/OnnxProcessor.h"
//==============================================================================
/**
*/
class Morphotron9000AudioProcessor  : public juce::AudioProcessor, private juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    Morphotron9000AudioProcessor();
    ~Morphotron9000AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::Value network1Name;
    juce::Value network2Name;

    std::function<void(juce::String newName)>onNetwork1NameChange;
    std::function<void(juce::String newName)>onNetwork2NameChange;

public:
    //not strictly req yet: std::function<void(int modelID, juce::String& modelName)> setExternalModelName;
    void loadExternalModel(juce::File path, int id) {
        if (id == 1) onnxProcessor1.loadExternalModel(path);
        if (id == 2) onnxProcessor2.loadExternalModel(path);
    }

private:
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
private:
    juce::AudioProcessorValueTreeState parameters;   

    OnnxProcessor onnxProcessor1;
    OnnxProcessor onnxProcessor2;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Morphotron9000AudioProcessor)
};
