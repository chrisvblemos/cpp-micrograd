Small implementation of micrograd using C++. Code folder structure should be pretty clear. Trainning and learning loops have not been tested nor coded yet. This is just for fun and self learning.

# class Scalar

Wrapper for numeric values (`floats`, `ints`, etc). Contais `value` (the value stored), `grad` and `previous`, a set of references to other `Scalar`s that produced it through an operation.
The other classes should be self-explanatory to anyone who knows a little bit of machine learning.

# Test

`Test.cpp` contains some asserts for sanity testing. It also gives an idea for how the code works for now.

