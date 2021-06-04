#include "NodeGraphEditor.h"
#include "../../LookAndFeel/Themes.h"

NodeGraphEditor::NodeGraphEditor() : toolbar(this) {
	addAndMakeVisible(toolbar);
}
NodeEditor* NodeGraphEditor::addNodeImmediate(node_type type, int x, int y) {
	NodeFactory::createNodeInstance(type, nodeEditors, this);
	NodeEditor* addedNode = nodeEditors[nodeEditors.size() - 1].get();
	addedNode->setPosition(x, y);
	addAndMakeVisible(*addedNode);
	updateNodeTransforms();
	setMouseCursor(MouseCursor::NormalCursor);
	currentMode = kIdling;
	return addedNode;
}
void NodeGraphEditor::addNode(node_type type) {
	currentMode = kPlacing;
	currentPlacingNodeType = type;
	setMouseCursor(MouseCursor::CrosshairCursor);
}
void NodeGraphEditor::removeNode(NodeEditor* node) {
	node->processor->disconnectAll();
	for (int i = 0; i < nodeEditors.size(); i++)
		if (nodeEditors[i].get() != node)
			nodeEditors[i]->processor->disconnectInput(node->processor);
	for (int i = 0; i < nodeEditors.size(); i++)
		if (nodeEditors[i].get() == node) {
			removeChildComponent(node);
			nodeEditors.erase(nodeEditors.begin() + i);
		}
	repaint();
}
void NodeGraphEditor::beginConnecting(NodeEditor* source) {
	currentMode = kConnecting;
	currentSource = source;
	setMouseCursor(MouseCursor::DraggingHandCursor);
}
NodeEditor* NodeGraphEditor::endConnecting() {
	if (currentMode == kConnecting) {
		setMouseCursor(MouseCursor::NormalCursor);
		currentMode = kIdling;
		return currentSource;
	}
	return nullptr;
}
void NodeGraphEditor::updateNodeTransforms() {
	for (int i = 0; i < nodeEditors.size(); i++) {
		
	}
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
	if (currentMode == kConnecting) {
		Point<int> startPos = currentSource->getPosition() + currentSource->getOutputPosition();
		Point<int> startPos2 = startPos + Point<int>(20, 0);
		Point<int> endPos = currentMousePos;
		Path connection;
		connection.startNewSubPath(startPos.toFloat());
		connection.lineTo(startPos2.toFloat());
		connection.lineTo(endPos.toFloat());
		PathStrokeType stroke = PathStrokeType(6, PathStrokeType::JointStyle::beveled, PathStrokeType::EndCapStyle::rounded);
		g.setColour(currentSource->getMainColor());
		g.strokePath(connection, stroke);
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
	if (!movingNodes && event.mods.isLeftButtonDown()) {
		movingNodes = true;
		previousMousePos = event.position.toInt();
	}
}
void NodeGraphEditor::mouseMove(const MouseEvent& event) {
	currentMousePos = event.position.toInt();
	if (currentMode == kConnecting)
		repaint();
}
void NodeGraphEditor::mouseDrag(const MouseEvent& event) {
	currentMousePos = event.position.toInt();
	if (movingNodes) {
		Point<int> offset = currentMousePos - previousMousePos;
		previousMousePos = currentMousePos;
		for (int i = 0; i < nodeEditors.size(); i++) {
			nodeEditors[i]->translate(offset);
		}
		repaint();
	}
}
void NodeGraphEditor::mouseUp(const MouseEvent& event) {
	if (movingNodes) {
		movingNodes = false;
	}
}
void NodeGraphEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) {
	zoomFactor = jlimit<float>(0.2f, 3.0f, zoomFactor + wheel.deltaY);
	DBG(zoomFactor);
}