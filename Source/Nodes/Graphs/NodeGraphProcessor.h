#ifndef NODE_GRAPH_PROCESSOR
#define NODE_GRAPH_PROCESSOR

#include "../Node.h"
#include <JuceHeader.h>
#include <vector>

using namespace juce;

class NodeGraphProcessor {
public:
	NodeGraphProcessor();
	~NodeGraphProcessor();
	void addProcessor(Node* processor);
	void removeProcessor(Node* processor);
	void setBufferSize(int numSamples);
	void compile();
private:
	std::vector<Node*> nodeProcessors;
	std::vector<Node*> processingQueue;
	int maxSIMDBufferSize = 120;
};

#endif