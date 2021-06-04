#ifndef NODE_FACTORY
#define NODE_FACTORY

#include "../Node.h"
#include "../NodeEditor.h"
#include <JuceHeader.h>

class NodeGraphEditor;

class NodeFactory {
public:
	enum class NodeType {
		kDummy,
		kMIDINoteInput,
		kMIDIVelocityInput,
		kOutput,
		kNumNodeTypes
	};
	static void createNodeInstance(NodeType type, std::vector<std::unique_ptr<NodeEditor>>& nodeEditors, NodeGraphEditor* nge);
	static String nodeTypeToName(NodeType type);
	static void displayAddNodeMenu(NodeGraphEditor* nge);
};

#endif