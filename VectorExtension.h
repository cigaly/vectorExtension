#ifndef VECTOR_EXTENSION_H

#include <Python.h>
#include <Vector.h>

typedef struct
{
    PyObject_HEAD Vector *m_vector;
} VectorObject;

PyObject *Vector_new(PyTypeObject *subtype, PyObject *args, PyObject *kwds);
// int Vector_init(PyObject *self, PyObject *args, PyObject *kwds);
void Vector_dealloc(VectorObject *self);
PyObject *Vector_norm(VectorObject *self);
PyObject *Vector_normalized(VectorObject *self);
PyObject *Vector_norm_l1(VectorObject *self);
PyObject *Vector_asList(VectorObject *self);
PyObject *Vector_dot(VectorObject *self, PyObject *args);
PyObject *Vector_add(VectorObject *self, PyObject *args);
PyObject *Vector_subtract(VectorObject *self, PyObject *args);
PyObject *Vector_multiplyScalar(VectorObject *self, PyObject *args);
PyObject *Vector_getItem(VectorObject *self, PyObject *args);
PyObject *Vector_setItem(VectorObject *self, PyObject *args);
PyObject *Vector_cosine(VectorObject *self, PyObject *args);

static PyMethodDef Vector_methods[] = {
    {"norm", (PyCFunction)Vector_norm, METH_NOARGS, PyDoc_STR("Return L2 norm of vector")},
    {"normalized", (PyCFunction)Vector_normalized, METH_NOARGS, PyDoc_STR("Return L2 normalized vector")},
    {"l1_norm", (PyCFunction)Vector_norm_l1, METH_NOARGS, PyDoc_STR("Return L2 norm of vector")},
    {"asList", (PyCFunction)Vector_asList, METH_NOARGS, PyDoc_STR("Return vector as Python list")},
    {"dot", (PyCFunction)Vector_dot, METH_VARARGS, PyDoc_STR("Return dot product of two vectors")},
    {"plus", (PyCFunction)Vector_add, METH_VARARGS, PyDoc_STR("Return sum of two vectors")},
    {"minus", (PyCFunction)Vector_subtract, METH_VARARGS, PyDoc_STR("Return sum of two vectors")},
    {"times", (PyCFunction)Vector_multiplyScalar, METH_VARARGS, PyDoc_STR("Return product of scalar and vector")},
    {"get", (PyCFunction)Vector_getItem, METH_VARARGS, PyDoc_STR("Get vector element at specified index")},
    {"set", (PyCFunction)Vector_setItem, METH_VARARGS, PyDoc_STR("Set vector element at specified index to new value")},
    {"cosine", (PyCFunction)Vector_cosine, METH_VARARGS, PyDoc_STR("Cosine distance between two vectors")},
    {NULL, NULL} /* Sentinel */
};

// static struct PyMemberDef Vector_members[] = {
//     //{"value", T_INT, offsetof(VectorObject, m_value)},
//     {NULL} /* Sentinel */
// };

static PyType_Slot Vector_slots[] = {
    {Py_tp_new, (void *)Vector_new},
    // {Py_tp_init, (void*)Vector_init},
    {Py_tp_dealloc, (void *)Vector_dealloc},
    // {Py_tp_members,  Vector_members},
    {Py_tp_methods, Vector_methods},
    {0, 0}};

static PyType_Spec spec_vector = {
    "Vector",                                 // name
    sizeof(VectorObject) + sizeof(Vector),    // basicsize
    0,                                        // itemsize
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // flags
    Vector_slots                              // slots
};

#endif
