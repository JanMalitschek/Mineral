#include "NodeEditor.h"
#include "Graphs/NodeGraphEditor.h"
#include "../LookAndFeel/Themes.h"

NodeEditor::NodeEditor() {
	this->processor = nullptr;
	this->title = "Empty";
	this->width = 100;
	this->height = 80;
}
NodeEditor::NodeEditor(Node* processor, NodeGraphEditor* nge, String title, Colour mainColor, int width, int height) {
	this->processor = processor;
	this->nge = nge;
	this->title = title;
	this->mainColor = mainColor;
	this->width = width;
	this->height = height;

	header.setButtonText(this->title);
	header.setLookAndFeel(&laF_Header);
	header.addMouseListener(this, true);
	header.setColour(TextButton::ColourIds::buttonColourId, this->mainColor);
	addAndMakeVisible(header);

	for (int i = 0; i < this->processor->getNumInputs(); i++) {
		inputSockets.push_back(std::unique_ptr<TextButton>(new TextButton()));
		inputSockets[i]->setButtonText("");
		inputSockets[i]->setLookAndFeel(&laF_Inputs);
		inputSockets[i]->setColour(TextButton::ColourIds::buttonColourId, this->mainColor);
		inputSockets[i]->addListener(this);
		addAndMakeVisible(inputSockets[i].get());
	}
	outputSocket.setButtonText("");
	outputSocket.setLookAndFeel(&laF_Outputs);
	outputSocket.setColour(TextButton::ColourIds::buttonColourId, this->mainColor);
	outputSocket.addListener(this);
	outputSocket.setBounds(width - 20, 20 + (height - 20) / 2 - 10, 20, 20);
	addAndMakeVisible(outputSocket);
}
NodeEditor::~NodeEditor() {
	delete processor;
}
void NodeEditor::paint(Graphics& g) {
	Path background;
	background.addRoundedRectangle(0, 0, width, height, 5, 5, true, true, true, true);
	g.setColour(Theme::current->nodeBackgroundColor);
	g.fillPath(background);

	g.setGradientFill(ColourGradient(SHADOW, 0, 20, CLEAR, 0, 30, false));
	g.fillRect(0, 20, width, 10);
}
void NodeEditor::resized() {
	header.setBounds(0, 0, width, 20);

	/*FlexBox fb;
	fb.flexDirection = FlexBox::Direction::column;
	fb.justifyContent = FlexBox::JustifyContent::spaceBetween;
	for (int i = 0; i < inputSockets.size(); i++)
		fb.items.add(FlexItem(*inputSockets[i].get()).withFlex(1.0f));
	fb.performLayout(Rectangle<int>(0, 20, 20, height - 20));*/
}
void NodeEditor::mouseDown(const MouseEvent& event) {
	if (event.mods.isLeftButtonDown()) {
		if (event.originalComponent == &header) {
			dragger.startDraggingComponent(this, event);
			header.setMouseCursor(MouseCursor::DraggingHandCursor);
		}
	}
	else if (event.mods.isRightButtonDown()) {
		PopupMenu menu;
		menu.addItem(1, "Remove");
		switch (menu.show()) {
		case 1:
			nge->removeNode(this);
			break;
		}
	}
}
void NodeEditor::mouseUp(const MouseEvent& event) {
	header.setMouseCursor(MouseCursor::NormalCursor);
}
void NodeEditor::mouseDrag(const MouseEvent& event) {
	if (event.originalComponent == &header) {
		dragger.dragComponent(this, event, nullptr);
		nge->repaint();
	}
}
void NodeEditor::buttonClicked(Button* button) {
	if (button == &outputSocket) {
		nge->beginConnecting(this);
	}
	else {
		for (int i = 0; i < inputSockets.size(); i++) {
			if (button == inputSockets[i].get()) {
				NodeEditor* sourceNode = nge->endConnecting();
				if (sourceNode)
					processor->connectInput(i, sourceNode->processor);
				else
					processor->disconnectInput(i);
				nge->repaint();
			}
		}
	}
}
void NodeEditor::configureInput(int inputIndex, int x, int y) {
	jassert(inputIndex < inputSockets.size());
	inputSockets[inputIndex]->setBounds(x, y, 20, 20);
	addAndMakeVisible(inputSockets[inputIndex].get());
}
void NodeEditor::configureOuput(int x, int y) {
	outputSocket.setBounds(x, y, 20, 20);
}
void NodeEditor::setPosition(int x, int y) {
	setBounds(x, y, width, height);
}
void NodeEditor::translate(Point<int> offset) {
	setBounds(getPosition().x + offset.x, getPosition().y + offset.y, width, height);
}
Point<int> NodeEditor::getOutputPosition() {
	return outputSocket.getPosition() + Point<int>(10, 10);
}
Point<int> NodeEditor::getInputPosition(int index) {
	jassert(index < inputSockets.size());
	return inputSockets[index]->getPosition() + Point<int>(inputSockets[index]->getWidth() / 2, inputSockets[index]->getHeight() / 2);
}
Colour NodeEditor::getMainColor() {
	return mainColor;
}