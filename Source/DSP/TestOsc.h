/*
  ==============================================================================

    TestOsc.h
    Created: 15 Oct 2022 10:11:36am
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
class TestOsc
{
public:
    TestOsc() = default;
    ~TestOsc() = default;

    void prepare(const juce::dsp::ProcessSpec& spec);
    void setFrequency(const float freq);
    void process(juce::dsp::ProcessContextReplacing<float> context);


private:
    void updateAngleDelta(const float freq);

    double sampleRate = 0.0;
    float angleDelta, currentAngle = 0.f;

};
} // namespace xynth