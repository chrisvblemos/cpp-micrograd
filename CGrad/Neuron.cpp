#include "Neuron.h"

Neuron::Neuron(int nin, bool _isNonLinear) {
	N = nin;
	IsNonLinear = _isNonLinear;

	w = std::vector<std::shared_ptr<Scalar>>();
	for (int i = 0; i < N; i++)
	{
		w.push_back(std::make_shared<Scalar>(1));
	};

}

std::shared_ptr<Scalar> Neuron::Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const
{
	std::shared_ptr<Scalar> Sum = std::make_shared<Scalar>(0);
	for (int i = 0; i < N; i++)
	{
		Sum = Sum + x[i] * w[i];
	}

	Sum = Sum + b;
	return Sum;
}

std::vector<std::shared_ptr<Scalar>> Neuron::GetParameters() const
{
	std::vector<std::shared_ptr<Scalar>> Res;
	Res.insert(Res.end(), w.begin(), w.end());
	Res.insert(Res.end(), b);

	return Res;
}