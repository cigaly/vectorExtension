# Python Vector Extension

This is sample Python extension written in C++. It exposes type Vector with some basic vector operations. Some of those operations are simply delegated to methods of simplified Vector C++ class, other are combination of two or more methods.

## Build & installation

To build extension just run :

`python setup.py build`

Result will be in `build/lib.xxxxx` directory

To install extension run :

`python -m pip install .`

If you are not running as root user, result will be installed under your home directory as `.local/lib/python3.10/site-packages/vectorxxxxx`.To remove it just run

`pip uninstall -y vector`

## Usage

To use extension from Python:

```
>>> from vector import Vector
>>> a=Vector([1,2,3])
>>> b=Vector([1,-2,-2])
>>> c=a.plus(b)
>>> c.asList()
[2.0, 0.0, 1.0]
```

## Available methods

### Constructors

- `v = Vector(n)`  n is integer number, create null vector with n elements
- `v = Vector([a, b, c, ...])`  create vector and initialize it with elements of Python list

### Methods

- `v.norm()`  returns L2 norm of vector as Python float
- `v.normalized()`  returns L2 normalized vector as Vector
- `v.l1_norm()  returns L1 norm of vector as Python float
- `v.asList()`  converts Vector to Python list
- `v.dot(other)`  returns vector dot product of vectors v and other, return Python float
- `v.cosine(other)`  return cosine distance between Vectors v and other, return Python float
- `v.plus(plus)`  add vector other to v, returns Vector
- `v.minus(plus)`  subtract vector other from v, returns Vector
- `v.times(scalar)`  multiply vector v by scalar, return Vector
- `v.get(n)`  return n-th element of v, return Python float
- `v.set(n, value)`  set n-th element of Vector to value

  
