/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AdditiveSynthAudioProcessor::AdditiveSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, "PARAMETER", { createParameterLayout() })
#endif
{
}

AdditiveSynthAudioProcessor::~AdditiveSynthAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout AdditiveSynthAudioProcessor::createParameterLayout()
{
    // Add parameters to the paramater tree. Allows for saving/loading and automating of paramaters

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //// Combobox: switch oscillators
    //auto oscParam = std::make_unique<juce::AudioParameterChoice>(OSC_ID, "Oscillator", oscVoices, 0);
    //params.push_back(std::move(oscParam));

    //// ADSR for synth voice
    //auto attackParam = std::make_unique<juce::AudioParameterFloat>(ATTACK_ID, "Attack", 0.001f, 1.f, 0.001f);
    //params.push_back(std::move(attackParam));
    //auto decayParam = std::make_unique<juce::AudioParameterFloat>(DECAY_ID, "Decay", 0.01f, 1.f, 0.4f);
    //params.push_back(std::move(decayParam));
    //auto sustainParam = std::make_unique<juce::AudioParameterFloat>(SUSTAIN_ID, "Sustain", 0.f, 1.f, 0.4f);
    //params.push_back(std::move(sustainParam));
    //auto releaseParam = std::make_unique<juce::AudioParameterFloat>(RELEASE_ID, "Release", 0.01f, 3.f, 0.04f);
    //params.push_back(std::move(releaseParam));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String AdditiveSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AdditiveSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AdditiveSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AdditiveSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AdditiveSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AdditiveSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AdditiveSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AdditiveSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AdditiveSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void AdditiveSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AdditiveSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec = {sampleRate, samplesPerBlock, getNumOutputChannels()};

    synthProcessor.prepare(spec);
}

void AdditiveSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AdditiveSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AdditiveSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    /*for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    }*/

    synthProcessor.process(buffer, midiMessages);
}

//==============================================================================
bool AdditiveSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AdditiveSynthAudioProcessor::createEditor()
{
    return new AdditiveSynthAudioProcessorEditor (*this);
}

//==============================================================================
void AdditiveSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AdditiveSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AdditiveSynthAudioProcessor();
}
