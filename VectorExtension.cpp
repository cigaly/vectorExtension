#include <Python.h>
#include "stdio.h"
#include "stdlib.h"
#include "VectorExtension.h"

PyObject *Vector_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    int cardinality = PyTuple_GET_SIZE(args);

    VectorObject *self = (VectorObject *)type->tp_alloc(type, 0);
    if (cardinality == 0)
    {
        self->m_vector = new Vector();
    }
    else
    {
        PyObject *first = PyTuple_GET_ITEM(args, 0);
        if (Py_IS_TYPE(first, &PyLong_Type))
        {
            self->m_vector = new Vector((int)PyLong_AsLong(first));
        }
        else if (Py_IS_TYPE(first, &PyList_Type))
        {
            int size = (int)PyList_GET_SIZE(first);
            double *vector = (double *)malloc(size * sizeof(double));
            for (int n = 0; n < size; ++n)
            {
                PyObject *item = PyList_GetItem(first, n);
                double value;
                if (Py_IS_TYPE(item, &PyLong_Type))
                {
                    value = PyLong_AsDouble(item);
                    vector[n] = value;
                }
                else if (Py_IS_TYPE(item, &PyFloat_Type))
                {
                    value = PyFloat_AsDouble(item);
                    vector[n] = value;
                }
                else
                {
                    throw "Unexpected list item type";
                }
            }
            self->m_vector = new Vector(vector, size);
        }
        else
        {
            throw "Unknown parameter type";
        }
    }
    return (PyObject *)self;
}

void Vector_dealloc(VectorObject *self)
{
    // std::cout << "Vector_dealloc() called!" << std::endl;
    PyTypeObject *tp = Py_TYPE(self);

    VectorObject *m = reinterpret_cast<VectorObject *>(self);

    if (m->m_vector)
    {
        m->m_vector->~Vector();
        PyObject_Free(m->m_vector);
    }

    tp->tp_free(self);
    Py_DECREF(tp);
}

PyObject *Vector_norm(VectorObject *self)
{
    return PyFloat_FromDouble(self->m_vector->l2());
}

PyObject *Vector_normalized(VectorObject *self)
{
    PyTypeObject *type = Py_TYPE(self);
    VectorObject *normalized = (VectorObject *)type->tp_alloc(type, 0);

    Vector *vector = self->m_vector;
    normalized->m_vector = vector->multiplyScalar(1 / vector->l2());

    return (PyObject *)normalized;
}

PyObject *Vector_norm_l1(VectorObject *self)
{
    try
    {
        return PyFloat_FromDouble(self->m_vector->l1());
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}

PyObject *Vector_asList(VectorObject *self)
{
    Vector *vector = self->m_vector;
    int size = self->m_vector->size();
    PyObject *pyList = PyList_New(size);
    for (int n = 0; n < size; ++n)
    {
        PyList_SetItem(pyList, n, PyFloat_FromDouble(vector->get(n)));
    }
    return pyList;
}

PyObject *Vector_dot(VectorObject *self, PyObject *args)
{
    VectorObject *other = (VectorObject *)PyTuple_GET_ITEM(args, 0);
    try
    {
        double dot = self->m_vector->dot(other->m_vector);
        PyObject *result = PyFloat_FromDouble(dot);
        return result;
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}

PyObject *Vector_add(VectorObject *self, PyObject *args)
{
    PyTypeObject *type = Py_TYPE(self);
    VectorObject *result = (VectorObject *)type->tp_alloc(type, 0);

    VectorObject *other = (VectorObject *)PyTuple_GET_ITEM(args, 0);
    try
    {
        result->m_vector = self->m_vector->plus(other->m_vector);
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }

    return (PyObject *)result;
}

PyObject *Vector_subtract(VectorObject *self, PyObject *args)
{
    PyTypeObject *type = Py_TYPE(self);
    VectorObject *result = (VectorObject *)type->tp_alloc(type, 0);

    VectorObject *other = (VectorObject *)PyTuple_GET_ITEM(args, 0);
    try
    {
        Vector *otherNegative = other->m_vector->multiplyScalar(-1);
        result->m_vector = self->m_vector->plus(otherNegative);
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }

    return (PyObject *)result;
}

PyObject *Vector_multiplyScalar(VectorObject *self, PyObject *args)
{
    PyTypeObject *type = Py_TYPE(self);
    VectorObject *result = (VectorObject *)type->tp_alloc(type, 0);

    double scalar = PyFloat_AsDouble(PyTuple_GET_ITEM(args, 0));
    result->m_vector = self->m_vector->multiplyScalar(scalar);

    return (PyObject *)result;
}

PyObject *Vector_getItem(VectorObject *self, PyObject *args)
{
    int index = _PyLong_AsInt(PyTuple_GET_ITEM(args, 0));
    try
    {
        double value = self->m_vector->get(index);
        return PyFloat_FromDouble(value);
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}

PyObject *Vector_setItem(VectorObject *self, PyObject *args)
{
    int index = _PyLong_AsInt(PyTuple_GET_ITEM(args, 0));
    double value = PyFloat_AsDouble(PyTuple_GET_ITEM(args, 1));
    try
    {
        self->m_vector->set(index, value);
        return Py_None;
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}

PyObject *Vector_cosine(VectorObject *self, PyObject *args)
{
    VectorObject *other = (VectorObject *)PyTuple_GET_ITEM(args, 0);
    try
    {
        double dotProduct = self->m_vector->dot(other->m_vector);
        double normSelf = self->m_vector->l2();
        double normOther = other->m_vector->l2();
        double result = dotProduct / (normSelf * normOther);
        return PyFloat_FromDouble(1 - result);
    }
    catch (char const *err)
    {
        printf("Error %s\n", err);
        PyErr_SetString(PyExc_RuntimeError, err);
        return NULL;
    }
}
