#ifndef NODE_EDITOR
#define NODE_EDITOR

#include "../Utility/simdFloat.h"
#include "../Utility/simdInt.h"
#include "../LookAndFeel/LookAndFeel.h"
#include <JuceHeader.h>
#include <vector>
#include "Node.h"

class NodeGraphEditor;

class NodeEditor : public Component, public MouseListener, public ButtonListener {
public:
	NodeEditor();
	NodeEditor(Node* processor, NodeGraphEditor* nge, String title, int x, int y);
	~NodeEditor();
	virtual void paint(Graphics&) override;
	virtual void resized() override;
	void mouseDown(const MouseEvent&) override;
	void mouseUp(const MouseEvent&) override;
	void mouseDrag(const MouseEvent&) override;
	void buttonClicked(Button*) override;
	void setPosition(int x, int y);
	Point<int> getOutputPosition();
	Point<int> getInputPosition(int index);
	Node* processor;
protected:
	NodeGraphEditor* nge;
	Font boldFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bebas_ttf, (size_t)BinaryData::Bebas_ttfSize));
	Font titleFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bahnschrift_ttf, (size_t)BinaryData::Bahnschrift_ttfSize));
	String title;
	int width, height;
private:
	ComponentDragger dragger;

	LookAndFeelHeader laF_Header;
	TextButton header;

	LookAndFeelInputs laF_Inputs;
	std::vector<std::unique_ptr<TextButton>> inputSockets;
	LookAndFeelOuputs laF_Ouputs;
	TextButton outputSocket;
};

#endif