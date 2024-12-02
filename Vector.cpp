#include <Python.h>
#include "Vector.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "memory.h"

Vector::Vector()
{
	vector = NULL;
	number_of_elements = 0;
}

Vector::Vector(const int size)
{
	number_of_elements = size;
	vector = new double[size];
	for (int n = size; --n >= 0;)
	{
		vector[n] = 0;
	}
}

Vector::~Vector()
{
	// printf("Releasing vector of size %d\n", number_of_elements);
	if (vector != NULL)
	{
		delete vector;
	}
}

Vector *Vector::plus(const Vector *other)
{
	if (other->number_of_elements != number_of_elements)
	{
		throw "Vector sizes does not match";
	}
	Vector *result = new Vector(number_of_elements);
	for (int n = 0; n < number_of_elements; ++n)
	{
		result->vector[n] = vector[n] + other->vector[n];
	}
	return result;
}

Vector *Vector::multiplyScalar(const double scalar)
{
	Vector *result = new Vector(number_of_elements);
	for (int n = 0; n < number_of_elements; ++n)
	{
		result->vector[n] = scalar * vector[n];
	}
	return result;
}

double Vector::l2()
{
	double sum = 0;
	for (int n = 0; n < number_of_elements; ++n)
	{
		sum += vector[n] * vector[n];
	}
	return sqrt(sum);
}

double Vector::l1()
{
	double sum = 0;
	for (int n = 0; n < number_of_elements; ++n)
	{
		sum += abs(vector[n]);
	}
	return sum;
}

double Vector::dot(const Vector *other)
{
	if (other->number_of_elements != number_of_elements)
	{
		throw "Vector sizes does not match";
	}
	double sum = 0;
	for (int n = 0; n < number_of_elements; ++n)
	{
		sum += vector[n] * other->vector[n];
	}
	return sum;
}

Vector::Vector(const double *vector, const int size)
{
	this->vector = (double *)malloc(size * sizeof(double));
	memcpy(this->vector, vector, size * sizeof(double));
	this->number_of_elements = size;
}

int Vector::size()
{
	return this->number_of_elements;
}

double Vector::get(const int index)
{
	if (index < 0 || index >= this->number_of_elements)
	{
		throw "Index out of bounds";
	}
	return this->vector[index];
}

void Vector::set(const int index, const double value)
{
	if (index < 0 || index >= this->number_of_elements)
	{
		throw "Index out of bounds";
	}
	this->vector[index] = value;
}
