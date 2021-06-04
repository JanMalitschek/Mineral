#include "DummyNode.h"
#include "../LookAndFeel/Themes.h"

DummyNode::DummyNode() : Node(2) {

}
void DummyNode::process(int numSamples) {

}

DummyNodeEditor::DummyNodeEditor(NodeGraphEditor* nge) : NodeEditor(new DummyNode(), nge, "DUMMY NODE", Theme::getRandomMainColor(), 100, 80) {
	processor->editor = this;
	configureInput(0, 0, 30);
	configureInput(1, 0, 60);
}
void DummyNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setFont(boldFont);
	g.setColour(Theme::current->headerColor);
	g.drawFittedText("It does\nNOTHING!", 20, 20, width - 40, height - 20, Justification::centred, 2);
}