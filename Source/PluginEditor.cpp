#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginParameters.h"

//==============================================================================
Morphotron9000AudioProcessorEditor::Morphotron9000AudioProcessorEditor (Morphotron9000AudioProcessor& p, juce::AudioProcessorValueTreeState& parameters)
    : AudioProcessorEditor (&p), processorRef (p), apvts(parameters)//, parameterControl(parameters)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
        parameters.addParameterListener(parameterID, this);
    }

    
}

Morphotron9000AudioProcessorEditor::~Morphotron9000AudioProcessorEditor()
{
    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
    apvts.removeParameterListener(parameterID, this);
}
}

//==============================================================================
void Morphotron9000AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Morphotron9000AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void Morphotron9000AudioProcessorEditor::parameterChanged(const juce::String &parameterID, float newValue) {
    //parameterControl.parameterChanged(parameterID, newValue);
    if (parameterID == PluginParameters::SELECT_NETWORK1_ID.getParamID() && newValue == 1.f) {
        openFileChooser(1);
    } else if (parameterID == PluginParameters::SELECT_NETWORK2_ID.getParamID() && newValue == 1.f) {
        openFileChooser(2);
    }
}

void Morphotron9000AudioProcessorEditor::openFileChooser(int networkID) {
    fc = std::make_unique<juce::FileChooser> ("Choose a file to open...", juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory),
                                              "*.ort", true);

    fc->launchAsync (juce::FileBrowserComponent::openMode
                     | juce::FileBrowserComponent::canSelectFiles,
                     [this, networkID] (const juce::FileChooser& chooser)
                     {
                         juce::File chosen;
                         auto results = chooser.getURLResults();

                         for (const auto& result : results) {
                             if (result.isLocalFile()) {
                                 chosen = result.getLocalFile();
                             }
                             else
                             {
                                 return;
                             }

                         }

                         if (chosen.getSize() != 0) {
                             processorRef.loadExternalModel(chosen.getFullPathName(), networkID);
                         } else {
                             auto param = (networkID == 1) ? PluginParameters::SELECT_NETWORK1_ID.getParamID() : PluginParameters::SELECT_NETWORK2_ID.getParamID();
                             apvts.getParameter(param)->setValueNotifyingHost(0.f);
                         }

                     });
}