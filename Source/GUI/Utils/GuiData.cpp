/*
  ==============================================================================

    GuiData.cpp
    Created: 23 Sep 2022 11:14:25am
    Author:  thesp

  ==============================================================================
*/

#include "GuiData.h"

namespace xynth
{

GuiData::GuiData(AdditiveSynthAudioProcessor& p, LookAndFeelStruct& _lnfStruct, double& s, juce::ApplicationProperties& props)
    : audioProcessor(p), scale(s), lnfStruct(_lnfStruct), properties(props)
{
}

void GuiData::updateLnf(int skin)
{
    //if (skin == first)
    //    defaultLnf.lnf = &defaultLnf.hellLook;
    //else
    //    jassertfalse; // wrong index (too many items?)

    lnfStruct.updateLnf();

    properties.getUserSettings()->setValue("Skin", skin);
    properties.saveIfNeeded();
}

}