#pragma once

#include "Module.h"
#include "Neuron.h"
#include <vector>

class Layer : public Module {
private:
	std::vector<Neuron> neurons;

public:
	inline std::vector<Neuron> GetNeurons() const { return neurons; }

	Layer(int nin, int nout);

	std::vector<std::shared_ptr<Scalar>> Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const;

	virtual std::vector<std::shared_ptr<Scalar>> GetParameters() const override;
};
