#ifndef CUSTOM_TOOLBAR
#define CUSTOM_TOOLBAR

#include "LookAndFeel/LookAndFeel.h"
#include <JuceHeader.h>

class NodeGraphEditor;

class CustomToolbar : public Component, public ButtonListener {
public:
	CustomToolbar();
	CustomToolbar(NodeGraphEditor* nge);
private:
	void paint(Graphics&) override;
	void resized() override;

	void buttonClicked(Button*) override;

	NodeGraphEditor* nge;

	TextButton addButton;
	LookAndFeelMain laF_Main;
};

#endif