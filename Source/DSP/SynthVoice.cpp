/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Oct 2022 10:04:28am
    Author:  thesp

  ==============================================================================
*/

#include "SynthVoice.h"

namespace xynth
{
void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    osc.prepare(spec);
    gain.prepare(spec);
    gain.updateDurationInSeconds(0.002);
    gain.resetGainLinear(0.f);

    voiceBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
}

void SynthVoice::setQueuePos(int newQueuePos)
{
    queuePos = newQueuePos;
}

void SynthVoice::startNote(int _midiNoteNumber, float velocity, int currentPitchWheelPosition)
{
    gain.setGainLinear(1.f);
    midiNoteNumber = _midiNoteNumber;
    osc.setFrequency((float)juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    noteOn = true;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    gain.setGainLinear(0.f);
    noteOn = false;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (gain.isSilent() || numSamples == 0) return;

    auto audioBlock = juce::dsp::AudioBlock<float>(voiceBuffer).getSubBlock(startSample, numSamples);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    osc.process(context);
    gain.process(context);

    for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++)
        outputBuffer.addFrom(ch, startSample, voiceBuffer, ch, startSample, numSamples);
}

} // namespace xynth