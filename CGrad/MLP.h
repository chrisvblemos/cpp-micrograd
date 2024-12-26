#pragma once

#include "Module.h"
#include "Layer.h"
#include <vector>

class MLP : public Module {
private:
	std::vector<int> nouts;
	std::vector<int> sizes;
	std::vector<Layer> layers;

public:
	inline std::vector<Layer> GetLayers() const { return layers; }

	MLP(int _nin, std::vector<int> _nouts);

	std::vector<std::shared_ptr<Scalar>> Evaluate(const std::vector<std::shared_ptr<Scalar>>& x) const;

	virtual std::vector<std::shared_ptr<Scalar>> GetParameters() const override;
};