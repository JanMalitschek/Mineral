#include "DummyNode.h"

DummyNode::DummyNode() : Node(2) {

}
void DummyNode::process(int numSamples) {

}

DummyNodeEditor::DummyNodeEditor(NodeGraphEditor* nge) : NodeEditor(new DummyNode(), nge, "DUMMY NODE", 100, 80) {
	processor->editor = this;
}
void DummyNodeEditor::paint(Graphics& g) {
	NodeEditor::paint(g);
	g.setFont(boldFont);
	g.setColour(HEADER_COLOR);
	g.drawFittedText("It does nothing!", 20, 20, width - 40, height - 20, Justification::centred, 1);
}