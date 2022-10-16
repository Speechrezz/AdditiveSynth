/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Oct 2022 10:04:28am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "TestOsc.h"
#include "Gain.h"

namespace xynth
{
class SynthVoice
{
public:
    SynthVoice() = default;
    ~SynthVoice() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);

    void setQueuePos(int newQueuePos);
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition);
    void stopNote(float velocity, bool allowTailOff);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);

    // For SynthProcessor
    inline bool isCurrentlyPlaying() const { return noteOn; }
    inline int getQueuePos() const { return queuePos; }
    inline int getMidiNoteNumber() const { return midiNoteNumber; }

private:
    double sampleRate = 0;
    TestOsc osc;
    bool noteOn = false;

    juce::AudioBuffer<float> voiceBuffer;

    // ADSR gain
    xynth::Gain gain;

    // For SynthProcessor
    int queuePos = 0, midiNoteNumber = 0;

};
} // namespace xynth