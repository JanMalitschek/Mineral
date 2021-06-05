#include "NodeGraphProcessor.h"

NodeGraphProcessor::NodeGraphProcessor(){}
NodeGraphProcessor::~NodeGraphProcessor() {
	for (int i = 0; i < nodeProcessors.size(); i++)
		delete nodeProcessors[i];
	nodeProcessors.clear();
	processingQueue.clear();
}
void NodeGraphProcessor::addProcessor(Node* processor) {
	processor->initBuffer(maxSIMDBufferSize);
	processor->ngp = this;
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
	sizeof_buffer = sizeof(SIMDFloat) * maxSIMDBufferSize;
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
void NodeGraphProcessor::process(juce::AudioBuffer<float>& buffer, int numSamples) {
	for (int i = 0; i < processingQueue.size(); i++)
		processingQueue[i]->process(numSamples);
	//Unpack SIMD Buffer

}