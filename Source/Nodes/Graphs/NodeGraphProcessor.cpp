#include "NodeGraphProcessor.h"

NodeGraphProcessor::NodeGraphProcessor(){}
NodeGraphProcessor::~NodeGraphProcessor() {
	for (int i = 0; i < nodeProcessors.size(); i++)
		delete nodeProcessors[i];
	processingQueue.clear();
	processingQueue.clear();
}
void NodeGraphProcessor::addProcessor(Node* processor) {
	nodeProcessors.push_back(processor);
}
void NodeGraphProcessor::removeProcessor(Node* processor) {
	for(int i = 0; i < nodeProcessors.size(); i++)
		if (nodeProcessors[i] == processor) {
			nodeProcessors.erase(nodeProcessors.begin() + i);
			return;
		}
}
void NodeGraphProcessor::setBufferSize(int numSamples) {
	maxSIMDBufferSize = (int)ceil((float)numSamples / 4.0f);
}
void NodeGraphProcessor::compile() { //Not super efficient but it does the job
	processingQueue.clear();
	int leftOverNodes = nodeProcessors.size();
	while (leftOverNodes > 0) {
		for (int i = 0; i < nodeProcessors.size(); i++) {
			if (nodeProcessors[i]->isMarked())
				continue;
			int numConnectedInputs, numMarkedInputs;
			nodeProcessors[i]->getInputInfo(numConnectedInputs, numMarkedInputs);
			if (numConnectedInputs == 0 || numConnectedInputs == numMarkedInputs) {
				processingQueue.push_back(nodeProcessors[i]);
				nodeProcessors[i]->mark();
				leftOverNodes--;
			}
		}
	}
	for (int i = 0; i < nodeProcessors.size(); i++)
		nodeProcessors[i]->mark(false);
}