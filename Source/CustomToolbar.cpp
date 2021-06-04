#include "CustomToolbar.h"
#include "Nodes/Graphs/NodeGraphEditor.h"
#include "LookAndFeel/Themes.h"
#include "Nodes/Graphs/NodeFactory.h"

CustomToolbar::CustomToolbar() {}
CustomToolbar::CustomToolbar(NodeGraphEditor* nge) {
	this->nge = nge;

	addButton.setButtonText("Add Node");
	addButton.setLookAndFeel(&laF_Main);
	addButton.addListener(this);
	addAndMakeVisible(addButton);
}
void CustomToolbar::paint(Graphics& g) {
	int width = getWidth(), height = getHeight();
	g.setColour(Theme::current->headerColor);
	g.fillRect(0, 0, width, height);

	g.setColour(SHADOW);
	g.fillRect(0, height - 2, width, 2);

	g.setGradientFill(ColourGradient(SHADOW, 0, 30, CLEAR, 0, 40, false));
	g.fillRect(0, height, width, 10);
}
void CustomToolbar::resized() {
	addButton.setBounds(0, 0, 50, 30);
}
void CustomToolbar::buttonClicked(Button* button) {
	if (button == &addButton)
		NodeFactory::displayAddNodeMenu(nge);
}