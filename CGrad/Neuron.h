#pragma once

#include "Module.h"
#include <vector>

class Neuron : public Module {

public:
	int N = 1;
	bool IsNonLinear = false;

	std::vector<std::shared_ptr<Scalar>> w;
	std::shared_ptr<Scalar> b = std::make_shared<Scalar>(0);

	Neuron(int nin, bool _isNonLinear = false);

	std::shared_ptr<Scalar> Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const;

	virtual std::vector<std::shared_ptr<Scalar>> GetParameters() const override;
};
