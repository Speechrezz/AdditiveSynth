/*
  ==============================================================================

    GuiData.h
    Created: 5 Sep 2022 3:56:01pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../CustomLooks/CustomLook.h"

namespace xynth
{
struct LookAndFeelStruct
{
    LookAndFeelStruct() { /*juce::LookAndFeel::setDefaultLookAndFeel(lnf);*/ }
    ~LookAndFeelStruct() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

    void updateLnf() { juce::LookAndFeel::setDefaultLookAndFeel(lnf); }

    juce::CustomLook customLook;

    // Change to desired LookAndFeel
    juce::CustomLook* lnf = &customLook;
};

struct GuiData
{
    GuiData(AdditiveSynthAudioProcessor& p, LookAndFeelStruct& defLnf, double& s, juce::ApplicationProperties& props);

    void updateLnf(int skin);

    AdditiveSynthAudioProcessor& audioProcessor;
    double& scale;
    LookAndFeelStruct& lnfStruct;
    juce::ApplicationProperties& properties;

    inline juce::CustomLook& getLnf() { return *lnfStruct.lnf; }
    std::function<void()> showAbout;

private:
    enum skinEnum { first };

};
} //namespace xynth