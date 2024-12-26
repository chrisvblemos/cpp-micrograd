#include "Layer.h"

Layer::Layer(int nin, int nout)
{
	for (int i = 0; i < nout; i++)
	{
		neurons.push_back(Neuron(nin));
	}
}

std::vector<std::shared_ptr<Scalar>> Layer::Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const
{
	std::vector<std::shared_ptr<Scalar>> out;
	for (auto neuron : neurons)
	{
		out.push_back(neuron.Evaluate(x));
	}

	return out;
}

std::vector<std::shared_ptr<Scalar>> Layer::GetParameters() const
{
	std::vector<std::shared_ptr<Scalar>> params;

	for (auto neuron : neurons)
	{
		std::vector<std::shared_ptr<Scalar>> neuronParams = neuron.GetParameters();
		params.insert(params.end(), neuronParams.begin(), neuronParams.end());
	}

	return params;
}