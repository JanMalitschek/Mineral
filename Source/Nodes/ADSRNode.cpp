#include "ADSRNode.h"
#include "../LookAndFeel/Themes.h"
#include "Graphs/NodeGraphProcessor.h"

ADSRNode::ADSRNode() : Node(1) {

}
void ADSRNode::process(int numSamples) {
	int simd_idx = 0;
	if (IS_INPUT_CONNECTED(0))
		for (int s = 0; s < numSamples; s += 4, simd_idx++)
			buffer[simd_idx] = inputs[0]->buffer[simd_idx];
	else
		for (int s = 0; s < numSamples; s += 4, simd_idx++)
			buffer[simd_idx] = SIMDFloat(0.0f);
}

ADSRNodeEditor::ADSRNodeEditor(NodeGraphEditor* nge) : NodeEditor(new ADSRNode(), nge, "ADSR Envelope", Theme::getRandomMainColor(), 280, 120) {
	processor->editor = this;
	configureInput(0, 0, 60);
	configureOuput(260, 60);
}
void ADSRNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setFont(boldFont);
	g.setFont(20);
	g.setColour(Theme::current->headerColor);
	g.drawText("ATTACK", 20, 100, 60, 20, Justification::centred, 1);
	g.drawText("DECAY", 80, 100, 60, 20, Justification::centred, 1);
	g.drawText("SUSTAIN", 140, 100, 60, 20, Justification::centred, 1);
	g.drawText("RELEASE", 200, 100, 60, 20, Justification::centred, 1);
}