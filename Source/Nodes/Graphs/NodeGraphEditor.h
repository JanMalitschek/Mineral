#ifndef NODE_GRAPH_EDITOR
#define NODE_GRAPH_EDITOR

#include "../../LookAndFeel/Colors.h"
#include "../../LookAndFeel/LookAndFeel.h"
#include "../Node.h"
#include "../NodeEditor.h"
#include "../../CustomToolbar.h"
#include "../Utility/NodeFactory.h"
#include "NodeGraphProcessor.h"
#include <JuceHeader.h>
#include <vector>

using namespace juce;
using node_type = NodeFactory::NodeType;

class NodeGraphEditor : public Component, public MouseListener {
public:
	NodeGraphProcessor* ngp;
public:
	NodeGraphEditor();
	NodeEditor* addNodeImmediate(node_type type, int x, int y);
	void addNode(node_type type);
	void removeNode(NodeEditor* node);
	void beginConnecting(NodeEditor* source);
	NodeEditor* endConnecting();
private:
	std::vector<std::unique_ptr<NodeEditor>> nodeEditors;
	Point<int> previousMousePos;
	bool movingNodes;
	float zoomFactor = 1.0f;
	void updateNodeTransforms();

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
	node_type currentPlacingNodeType = node_type::kDummy;
	NodeEditor* currentSource;
	Point<int> currentMousePos;

	void mouseDown(const MouseEvent& event) override;
	void mouseDrag(const MouseEvent& event) override;
	void mouseMove(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;
	void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) override;
};

#endif