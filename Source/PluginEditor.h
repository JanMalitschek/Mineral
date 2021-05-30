#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel/LookAndFeel.h"
#include "Nodes/Node.h"
#include "Nodes/Graphs/NodeGraphEditor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    LookAndFeelMain laFMain;
    Slider knob;

    NodeGraphEditor nge;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
