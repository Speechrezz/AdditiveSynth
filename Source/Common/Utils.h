/*
  ==============================================================================

    Utils.h
    Created: 30 Sep 2022 11:54:19pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
    juce::String frequencyAsText(float value, int maxLength = 2);
    juce::String msAsText(float value, int maxLength = 2);
    juce::String valueAsText(float value, int maxLength = 2);

    juce::NormalisableRange<float> createRange(const float minVal, const float maxVal, const float midVal);
    juce::NormalisableRange<float> createFrequencyRange(const float minFreq, const float maxFreq);
    juce::NormalisableRange<float> createRatioRange();

    std::array<juce::String, 3> generateIds(const std::array<juce::String, 3>& prefixes, const juce::String& suffix);
} // namespace xynth