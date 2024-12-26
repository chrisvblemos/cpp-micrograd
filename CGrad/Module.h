#pragma once

#include "Scalar.h"

class Module {

public:
	virtual std::vector<std::shared_ptr<Scalar>> GetParameters() const = 0;

	virtual void ZeroGrad();

};