#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Morphotron9000AudioProcessor::Morphotron9000AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters (*this, nullptr, juce::Identifier ("Scyclone"), PluginParameters::createParameterLayout()),
        onnxProcessor1(parameters, 1),//, FunkDrum),
        onnxProcessor2(parameters, 2)//, Djembe)  since raveModel is not added in onnxProcessor constructor       
#endif
{
    network1Name = "Funk";
    network2Name = "Djembe";

    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
        parameters.addParameterListener(parameterID, this);
    }

    parameters.state.addChild(PluginParameters::createNotAutomatableParameterLayout(), 0, nullptr);

}

Morphotron9000AudioProcessor::~Morphotron9000AudioProcessor()
{    
    for (auto & parameterID : PluginParameters::getPluginParameterList()) {
        parameters.removeParameterListener(parameterID, this);
    }
}

//==============================================================================
const juce::String Morphotron9000AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Morphotron9000AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Morphotron9000AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Morphotron9000AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Morphotron9000AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Morphotron9000AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Morphotron9000AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Morphotron9000AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Morphotron9000AudioProcessor::getProgramName (int index)
{
    return {};
}

void Morphotron9000AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Morphotron9000AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Morphotron9000AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Morphotron9000AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Morphotron9000AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Morphotron9000AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Morphotron9000AudioProcessor::createEditor()
{
    return new Morphotron9000AudioProcessorEditor (*this, parameters);
}

//==============================================================================

//parameter state management: store in and restore from the memory block
void Morphotron9000AudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void Morphotron9000AudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName(parameters.state.getType())) {
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            network1Name.referTo(parameters.state.getChildWithName("Settings")
                                                            .getPropertyAsValue(PluginParameters::NETWORK1_NAME_NAME, nullptr));
            network2Name.referTo(parameters.state.getChildWithName("Settings")
                                                            .getPropertyAsValue(PluginParameters::NETWORK2_NAME_NAME, nullptr));
        }
}

void Morphotron9000AudioProcessor::parameterChanged(const juce::String &parameterID, float newValue) {
    onnxProcessor1.parameterChanged(parameterID, newValue);
    onnxProcessor2.parameterChanged(parameterID, newValue);
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Morphotron9000AudioProcessor();
}
