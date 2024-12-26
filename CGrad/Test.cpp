#include <cassert>

#include "Scalar.h"
#include "Neuron.h"
#include "Layer.h"
#include "MLP.h"

int main() {
	// Opnames test
	
	std::printf("Testing Scalars...\n");

	std::shared_ptr<Scalar> x1 = std::make_shared<Scalar>(1);
	std::shared_ptr<Scalar> x2 = std::make_shared<Scalar>(3);
	std::shared_ptr<Scalar> x3 = x1 + x2;
	std::shared_ptr<Scalar> x4 = x3 * x1;

	assert(("x1 OP name should be empty.", (x1->GetOpName() == "")));
	assert(("x2 OP name should be empty.", (x2->GetOpName() == "")));
	assert(("x3 OP name should be +.", (x3->GetOpName() == "+")));
	assert(("x4 OP name should be *.", (x4->GetOpName() == "*")));

	assert(("x1 value should be 1.", x1->GetValue() == 1));
	assert(("x2 value should be 3.", x2->GetValue() == 3));
	assert(("x3 value should be 4.", x3->GetValue() == 4));
	assert(("x4 value should be 4.", x4->GetValue() == 4));

	std::printf("Scalars test passed!\n\n");

	// Backward propagation test

	std::printf("Testing backward propagation...\n");

	x4->Backward();

	assert(("x1 grad value should be 5.", x1->GetGrad() == 5));
	assert(("x2 grad value should be 1.", x2->GetGrad() == 1));
	assert(("x3 grad value should be 1.", x3->GetGrad() == 1));
	assert(("x4 grad value should be 1.", x4->GetGrad() == 1));

	std::printf("Backward propagation test passed!\n\n");

	// Neuron test

	std::printf("Testing single neuron...\n");

	Neuron TestNeuron(1);
	std::vector<std::shared_ptr<Scalar>> x = { std::make_shared<Scalar>(5) };
	std::shared_ptr<Scalar> NeuronResult = TestNeuron.Evaluate(x);

	assert(("Neuron result should be 5.", NeuronResult->GetValue() == 5));

	std::printf("Single neuron test passed!\n\n");

	// Neuron layer test

	std::printf("Testing neuron layer...\n");
	Layer TestLayer(1, 4);
	std::vector<std::shared_ptr<Scalar>> TestLayerResult = TestLayer.Evaluate(x);

	for (auto v : TestLayerResult)
	{
		assert(("Neuron output should be 5.", v->GetValue() == 5));
	}

	std::printf("Neuron layer test passed!\n\n");

	std::vector<int> MLP_nouts = { 5, 5, 2, 2 };

	// MLP test

	std::printf("Testing MLP...\n");

	MLP TestMLP(1, MLP_nouts);
	std::vector<std::shared_ptr<Scalar>> MLPTestResult = TestMLP.Evaluate(x);
	for (auto v : MLPTestResult)
	{
		assert(("Layer output should be 250.", v->GetValue() == 250));
	}

	std::printf("MLP test passed!\n\n");
}