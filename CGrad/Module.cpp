#include "Module.h"

void Module::ZeroGrad() {
	for (auto v : GetParameters())
	{
		v->SetGrad(0);
	}
}