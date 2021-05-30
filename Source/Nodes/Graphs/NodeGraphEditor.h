#ifndef NODE_GRAPH_EDITOR
#define NODE_GRAPH_EDITOR

#include "../../LookAndFeel/Colors.h"
#include "../../LookAndFeel/LookAndFeel.h"
#include "../Node.h"
#include "../NodeEditor.h"
#include "../../CustomToolbar.h"
#include <JuceHeader.h>
#include <vector>

using namespace juce;

class NodeGraphEditor : public Component, public MouseListener {
public:
	NodeGraphEditor();
	NodeEditor* addNodeImmediate(NodeType type, int x, int y);
	void addNode(NodeType type);
	void beginConnecting(NodeEditor* source);
	NodeEditor* endConnecting();
private:
	std::vector<std::unique_ptr<NodeEditor>> nodeEditors;

	CustomToolbar toolbar;

	void paint(Graphics&) override;
	void paintOverChildren(Graphics&) override;
	void resized() override;

	enum EditingMode {
		kIdling,
		kPlacing,
		kConnecting,
		kNumEditingModes
	};
	EditingMode currentMode;
	NodeType currentPlacingNodeType = kDummy;
	NodeEditor* currentSource;

	void mouseDown(const MouseEvent& event) override;
};

#endif