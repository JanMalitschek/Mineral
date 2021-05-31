/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LookAndFeel/Themes.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 600);
    Theme::createStandardThemes();

    addAndMakeVisible(nge);

    knob.setName("Knob");
    knob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob.setRotaryParameters(-2.35619f, 2.35619f, true);
    knob.setRange(0.0f, 1.0f);
    knob.setValue(0.5f);
    knob.setLookAndFeel(&laFMain);
    addAndMakeVisible(knob);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    Theme::deleteThemes();
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Theme::current->backgroundColor);
}

void NewProjectAudioProcessorEditor::resized()
{
    nge.setBounds(0, 0, getWidth(), getHeight());
    knob.setBounds(10, 50, 60, 60);
}
