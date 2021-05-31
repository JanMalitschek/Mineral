#include "NodeGraphEditor.h"
#include "../DummyNode.h"
#include "../../LookAndFeel/Themes.h"

NodeGraphEditor::NodeGraphEditor() : toolbar(this) {
	addAndMakeVisible(toolbar);
}
NodeEditor* NodeGraphEditor::addNodeImmediate(NodeType type, int x, int y) {
	switch (type) {
	case kDummy:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new DummyNodeEditor(this)));
		break;
	}
	NodeEditor* addedNode = nodeEditors[nodeEditors.size() - 1].get();
	addedNode->setPosition(x, y);
	addAndMakeVisible(*addedNode);
	return addedNode;
}
void NodeGraphEditor::addNode(NodeType type) {
	currentMode = kPlacing;
	currentPlacingNodeType = type;
	setMouseCursor(MouseCursor::CrosshairCursor);
}
void NodeGraphEditor::beginConnecting(NodeEditor* source) {
	currentMode = kConnecting;
	currentSource = source;
	setMouseCursor(MouseCursor::DraggingHandCursor);
}
NodeEditor* NodeGraphEditor::endConnecting() {
	if (currentMode == kConnecting) {
		currentMode = kIdling;
		return currentSource;
	}
	return nullptr;
}
void NodeGraphEditor::paint(Graphics& g) {
	int width = getWidth(), height = getHeight();
	g.setColour(SHADOW);
	for(int x = 0; x <= width; x += 40)
		for (int y = 0; y <= height; y += 40) {
			g.drawLine(x - 5, y, x + 5, y, 2);
			g.drawLine(x, y - 5, x, y + 5, 2);
		}
}
void NodeGraphEditor::paintOverChildren(Graphics& g) {
	//Draw Connections
	for (int i = 0; i < nodeEditors.size(); i++) {
		std::vector<Node*>& inputs = nodeEditors[i]->processor->getInputs();
		for(int j = 0; j < inputs.size(); j++){
			if (inputs[j] != nullptr) {
				Point<int> startPos = inputs[j]->editor->getPosition() + inputs[j]->editor->getOutputPosition();
				Point<int> startPos2 = startPos + Point<int>(20, 0);
				Point<int> endPos2 = nodeEditors[i]->getPosition() + nodeEditors[i]->getInputPosition(j);
				Point<int> endPos = endPos2 - Point<int>(20, 0);
				Path connection;
				connection.startNewSubPath(startPos.toFloat());
				connection.lineTo(startPos2.toFloat());
				connection.lineTo(endPos.toFloat());
				connection.lineTo(endPos2.toFloat());
				PathStrokeType stroke = PathStrokeType(6, PathStrokeType::JointStyle::beveled, PathStrokeType::EndCapStyle::rounded);
				g.setGradientFill(ColourGradient(inputs[j]->editor->getMainColor(), startPos2.toFloat(), nodeEditors[i]->getMainColor(), endPos.toFloat(), false));
				g.strokePath(connection, stroke);
			}
		}
	}
}
void NodeGraphEditor::resized() {
	toolbar.setBounds(0, 0, getWidth(), 30);
}
void NodeGraphEditor::mouseDown(const MouseEvent& event) {
	switch (currentMode) {
	case kPlacing:
		if (event.mods.isRightButtonDown()) {
			setMouseCursor(MouseCursor::NormalCursor);
			currentMode = kIdling;
		}
		else if (event.mods.isLeftButtonDown()) {
			setMouseCursor(MouseCursor::NormalCursor);
			currentMode = kIdling;
			addNodeImmediate(currentPlacingNodeType, event.position.x, event.position.y);
		}
		break;
	case kConnecting:
		setMouseCursor(MouseCursor::NormalCursor);
		currentMode = kIdling;
		break;
	}	
}