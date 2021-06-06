#include "OutputNode.h"
#include "../LookAndFeel/Themes.h"
#include "Graphs/NodeGraphProcessor.h"

OutputNode::OutputNode() : Node(1) {

}
void OutputNode::process(int numSamples) {
	int simd_idx = 0;
	if (IS_INPUT_CONNECTED(0))
		for (int s = 0; s < numSamples; s += 4, simd_idx++)
			buffer[simd_idx] = inputs[0]->buffer[simd_idx];
	else
		for (int s = 0; s < numSamples; s += 4, simd_idx++)
			buffer[simd_idx] = SIMDFloat(0.0f);
}

OutputNodeEditor::OutputNodeEditor(NodeGraphEditor* nge) : NodeEditor(new OutputNode(), nge, "Out", Theme::getRandomMainColor(), 50, 50) {
	processor->editor = this;
	configureInput(0, 0, 25);
	configureOuput(0, 0, false);
}
void OutputNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setFont(boldFont);
	g.setFont(20);
	g.setColour(Theme::current->headerColor);
	g.drawText("Out", 20, 20, 30, 30, Justification::centred, 1);
}