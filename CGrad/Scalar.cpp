#include "Scalar.h"

Scalar::Scalar(float val, std::set<std::shared_ptr<Scalar>> children, std::string opName)
{
	this->value = val;
	this->opname = opName;
	this->previous = children;
	this->backward = [this] {
		for (const std::shared_ptr<Scalar> child : this->previous)
		{
			child->backward();
		}
	};
}

std::shared_ptr<Scalar> Scalar::operator*(const std::shared_ptr<Scalar>& Right)
{
	auto out_previous = std::set<std::shared_ptr<Scalar>>{ shared_from_this(), Right };
	auto out = std::make_shared<Scalar>(value * Right->value, out_previous, "*");
	
	out->backward = [this, Right, out] {
		grad += Right->value * out->grad;
		Right->grad += value * out->grad;
	};

	return out;
}

std::shared_ptr<Scalar> Scalar::pow(const std::shared_ptr<Scalar>& Right)
{
	auto out_previous = std::set<std::shared_ptr<Scalar>>{ shared_from_this(), Right };
	auto out = std::make_shared<Scalar>(std::pow(value, Right->value), out_previous, "^");

	out->backward = [this, Right, out] {
		grad += Right->value * std::pow(value, Right->value - 1) * out->grad;
		};

	return out;
}


std::shared_ptr<Scalar> Scalar::operator+(const std::shared_ptr<Scalar>& Right)
{
	auto out_previous = std::set<std::shared_ptr<Scalar>>{ shared_from_this(), Right };
	auto out = std::make_shared<Scalar>(value + Right->value, out_previous, "+");

	out->backward = [this, Right, out] {
		grad += out->grad;
		Right->grad += out->grad;
		};

	return out;
}

std::shared_ptr<Scalar> Scalar::operator/(const std::shared_ptr<Scalar>& Right)
{
	return shared_from_this() * Right->pow(std::make_shared<Scalar>(-1));
}

std::shared_ptr<Scalar> Scalar::operator-()
{
	return shared_from_this() * std::make_shared<Scalar>(-1);
}

std::shared_ptr<Scalar> Scalar::operator-(const std::shared_ptr<Scalar>& Right)
{
	return shared_from_this() + (Right->operator-());
}

std::shared_ptr<Scalar> operator*(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right) {
	return (*Left) * Right;
}

std::shared_ptr<Scalar> pow(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right) {
	return Left->pow(Right);
}

std::shared_ptr<Scalar> operator+(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right) {
	return (*Left) + Right;
}

std::shared_ptr<Scalar> operator/(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right) {
	return (*Left) / Right;
}

std::shared_ptr<Scalar> operator-(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right) {
	return (*Left) - Right;
}

/* Builds the topology for a given scalar to backward propagate. */
static std::vector<std::shared_ptr<Scalar>> BuildTopology(std::vector<std::shared_ptr<Scalar>>& Topology, std::set<std::shared_ptr<Scalar>>& Visited, std::shared_ptr<Scalar> Value)
{
	if (Visited.count(Value) == 0)
	{
		Visited.insert(Value);
		for (auto child : Value->GetPrev())
		{
			BuildTopology(Topology, Visited, child);
		}
		Topology.push_back(Value);
	}

	return Topology;
};

/* Applies backward gradient propagation. */
void Scalar::Backward()
{
	std::vector<std::shared_ptr<Scalar>> Topo;
	std::set<std::shared_ptr<Scalar>> Vis;

	BuildTopology(Topo, Vis, shared_from_this());
	this->grad = 1;

	for (auto it = Topo.rbegin(); it != Topo.rend(); ++it) {
		(*it)->backward();
	};
}