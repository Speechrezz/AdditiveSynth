/*
  ==============================================================================

    TestOsc.cpp
    Created: 15 Oct 2022 10:11:36am
    Author:  thesp

  ==============================================================================
*/

#include "TestOsc.h"

namespace xynth
{
void TestOsc::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
}

void TestOsc::setFrequency(const float freq)
{
    updateAngleDelta(freq);
}

void TestOsc::process(juce::dsp::ProcessContextReplacing<float> context)
{
    auto left = context.getOutputBlock().getChannelPointer(0);
    auto right = context.getOutputBlock().getChannelPointer(1);
    const auto numSamples = context.getOutputBlock().getNumSamples();

    for (int i = 0; i < numSamples; ++i)
    {
        const float currentSample = std::sin(currentAngle) * 0.1f;
        left[i] = currentSample;
        right[i] = currentSample;
        currentAngle += angleDelta;
    }

    currentAngle = fmod(currentAngle, juce::MathConstants<float>::twoPi);
}

void TestOsc::updateAngleDelta(const float freq)
{
    jassert(sampleRate != 0.0);

    const float cyclesPerSample = freq / float(sampleRate);
    angleDelta = cyclesPerSample * juce::MathConstants<float>::twoPi;
}
} // namespace xynth