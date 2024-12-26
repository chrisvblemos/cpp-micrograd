#include "MLP.h"

MLP::MLP(int _nin, std::vector<int> _nouts)
{
	sizes.push_back(_nin);
	sizes.insert(sizes.end(), _nouts.begin(), _nouts.end());

	for (int i = 0; i < _nouts.size(); i++)
	{
		layers.push_back(Layer(sizes[i], sizes[i + 1]));
	}
}

std::vector<std::shared_ptr<Scalar>> MLP::Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const
{
	std::vector<std::shared_ptr<Scalar>> out = x;
	for (auto layer : layers)
	{
		out = layer.Evaluate(out);
	}

	return out;
}

std::vector<std::shared_ptr<Scalar>> MLP::GetParameters() const
{
	std::vector<std::shared_ptr<Scalar>> params;

	for (auto layer : layers)
	{
		for (auto neuron : layer.GetNeurons())
		{
			std::vector<std::shared_ptr<Scalar>> neuronParams = neuron.GetParameters();
			params.insert(params.end(), neuronParams.begin(), neuronParams.end());
		}
	}

	return params;
}