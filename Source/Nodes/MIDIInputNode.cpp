#include "MIDIInputNode.h"
#include "../LookAndFeel/Themes.h"

MIDINoteInputNode::MIDINoteInputNode() : Node(0) {

}
void MIDINoteInputNode::process(int numSamples) {

}

MIDINoteInputNodeEditor::MIDINoteInputNodeEditor(NodeGraphEditor* nge) : NodeEditor(new MIDINoteInputNode(), nge, "Note In", Theme::getRandomMainColor(), 50, 50) {
	processor->editor = this;

	/*midiIcon = Drawable::createFromImageData(BinaryData::MIDI_Note_Icon_svg, BinaryData::MIDI_Note_Icon_svgSize);
	addAndMakeVisible(midiIcon);*/
}
void MIDINoteInputNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setColour(Theme::current->headerColor);
	g.setFont(boldFont);
	g.setFont(20);
	g.drawText("#", 0, 20, 30, 30, Justification::centred);
}
void MIDINoteInputNodeEditor::resized() {
	NodeEditor::resized();
	//midiIcon->setBounds(0, 20, 40, 40);
}

MIDIVelocityInputNode::MIDIVelocityInputNode() : Node(0) {

}
void MIDIVelocityInputNode::process(int numSamples) {

}

MIDIVelocityInputNodeEditor::MIDIVelocityInputNodeEditor(NodeGraphEditor* nge) : NodeEditor(new MIDIVelocityInputNode(), nge, "Vel In", Theme::getRandomMainColor(), 50, 50) {
	processor->editor = this;

	/*midiIcon = Drawable::createFromImageData(BinaryData::MIDI_Velocity_Icon_svg, BinaryData::MIDI_Velocity_Icon_svgSize);
	addAndMakeVisible(midiIcon);*/
}
void MIDIVelocityInputNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setColour(Theme::current->headerColor);
	g.setFont(boldFont);
	g.setFont(20);
	g.drawText("V", 0, 20, 30, 30, Justification::centred);
}
void MIDIVelocityInputNodeEditor::resized() {
	NodeEditor::resized();
	//midiIcon->setBounds(0, 20, 40, 40);
}