/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Morphotron9000AudioProcessorEditor::Morphotron9000AudioProcessorEditor (Morphotron9000AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Morphotron9000AudioProcessorEditor::~Morphotron9000AudioProcessorEditor()
{
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


void AudioPluginAudioProcessorEditor::openFileChooser(int networkID) {
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