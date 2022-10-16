/*
  ==============================================================================

    Utils.cpp
    Created: 30 Sep 2022 11:54:19pm
    Author:  thesp

  ==============================================================================
*/

#include "Utils.h"

namespace xynth
{
    juce::String frequencyAsText(float value, int)
    {
        if (value >= 1000.f) 
        {
            value = value / 1000.f;
            return juce::String(value, 2) + " kHz";
        }

        return juce::String(value, 2) + " Hz";
    }

    juce::String msAsText(float value, int maxLength)
    {
        if (value >= 1000.f)
        {
            value /= 1000.f;
            return juce::String(value, 2) + " s";
        }

        return juce::String(value, 2) + " ms";
    }

    juce::String valueAsText(float value, int)
    {
        return juce::String(value, 2);
    }

    juce::NormalisableRange<float> createRange(const float minVal, const float maxVal, const float midVal)
    {
        juce::NormalisableRange<float> range(minVal, maxVal);
        range.setSkewForCentre(midVal);
        return range;
    }

    juce::NormalisableRange<float> createFrequencyRange(const float minFreq, const float maxFreq)
    {
        return juce::NormalisableRange<float>(minFreq, maxFreq,
            // ---convertFrom0To1Func---
            [](float rangeStart, float rangeEnd, float valueToRemap) -> float 
            {
                return juce::mapToLog10<float>(valueToRemap, rangeStart, rangeEnd); 
            }, 
            // ---convertTo0To1Func---
            [](float rangeStart, float rangeEnd, float valueToRemap) -> float 
            {
                return juce::mapFromLog10<float>(valueToRemap, rangeStart, rangeEnd); 
            }, {}); 
    }

    juce::NormalisableRange<float> createRatioRange()
    {
        juce::NormalisableRange<float> range(1.f, 20.f);
        range.setSkewForCentre(4.f);
        return range;
    }

    std::array<juce::String, 3> generateIds(const std::array<juce::String, 3>& prefixes, const juce::String& suffix)
    {
        return { prefixes[0] + suffix, prefixes[1] + suffix , prefixes[2] + suffix };
    }
} // namespace xynth