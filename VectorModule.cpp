#include <Python.h>

#include "VectorExtension.h"

// A struct contains the definition of a module
PyModuleDef my_module = {
    PyModuleDef_HEAD_INIT,
    "Vector", // Module name
    "This is Vector's docstring",
    -1,   // Optional size of the module state memory
    NULL, // Optional module methods
    NULL, // Optional slot definitions
    NULL, // Optional traversal function
    NULL, // Optional clear function
    NULL  // Optional module deallocation function
};


PyMODINIT_FUNC 
PyInit_vector(void) {
    PyObject* module = PyModule_Create(&my_module);

    PyObject *vector = PyType_FromSpec(&spec_vector);
    if (vector == NULL){
        return NULL;
    }
    Py_INCREF(vector);

    if(PyModule_AddObject(module, "Vector", vector) < 0){
        Py_DECREF(vector);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}