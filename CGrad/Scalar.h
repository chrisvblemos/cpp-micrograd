#pragma once
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <cstdio>
#include <memory>

class Scalar : public std::enable_shared_from_this<Scalar> {

private:
	/* Float value stored by this scalar. */
	float value = 0;

	/* Accumulated grad up to this value. */
	float grad = 0;

	/* Operation that created this scalar, if any. For debugging. */
	std::string opname;

	/* Stores how to apply backward to this scalar. */
	std::function<void()> backward;

	/* Stores childrens that produced this scalar. */
	std::set<std::shared_ptr<Scalar>> previous;

public:
	Scalar(float val, std::set<std::shared_ptr<Scalar>> children = {}, std::string opName = "");

	// Getters
	inline std::string GetOpName() { return opname; }
	inline std::set<std::shared_ptr<Scalar>>& GetPrev() { return previous; }
	inline float GetValue() { return value; }
	inline float GetGrad() { return grad; }

	// Setters
	inline void SetGrad(float val) { grad = val; }

	void Backward();

	std::shared_ptr<Scalar> operator*(const std::shared_ptr<Scalar>& Right);
	std::shared_ptr<Scalar> pow(const std::shared_ptr<Scalar>& Right);
	std::shared_ptr<Scalar> operator+(const std::shared_ptr<Scalar>& Right);
	std::shared_ptr<Scalar> operator/(const std::shared_ptr<Scalar>& Right);
	std::shared_ptr<Scalar> operator-();
	std::shared_ptr<Scalar> operator-(const std::shared_ptr<Scalar>& Right);

};

std::shared_ptr<Scalar> operator*(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right);
std::shared_ptr<Scalar> pow(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right);
std::shared_ptr<Scalar> operator+(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right);
std::shared_ptr<Scalar> operator/(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right);
std::shared_ptr<Scalar> operator-(const std::shared_ptr<Scalar>& Left, const std::shared_ptr<Scalar>& Right);

