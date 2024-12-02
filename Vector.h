#ifndef VECTOR_H_
#define VECTOR_H_

class Vector
{
	double *vector;
	int number_of_elements;

public:
	Vector();
	Vector(const int n);
	Vector(double const *vector, int const size);
	virtual ~Vector();
	Vector *plus(Vector const *other);
	Vector *multiplyScalar(double const scalar);
	double dot(Vector const *other);
	int size();
	double get(int const index);
	void set(int const index, double const value);
	double l2();
	double l1();
};

#endif /* VECTOR_H_ */
