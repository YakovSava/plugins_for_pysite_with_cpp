# include <Python.h>
# include <ctime>
# include <cstdlib>
using namespace std;

int Crandint(int range_min, int range_max) {
	return ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
}

static PyObject *randint(PyObject *self, PyObject *args) {
    int range_min, range_max;

    if (!PyArg_ParseTuple(args, "ii", &range_min, &range_max)) {
        return NULL;
    }

    int result = Crandint(range_min, range_max);

    return Py_BuildValue("i", result);
}

static PyObject *choice(PyObject *self, PyObject *args) {
    PyObject* lst;

    if (!PyArg_ParseTuple(args, "O", &lst)) {
        return NULL;
    }

    if (!PyList_Check(lst)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list object.");
        return NULL;
    }

    int size = PyList_Size(lst);
    int index = Crandint(0, size);

    PyObject* item = PyList_GetItem(lst, index);

    Py_INCREF(item);

    return item;
}

static PyObject *_overclocking(PyObject *self, PyObject *args) {
    srand(time(NULL));

    return Py_None;
}

static PyMethodDef methods[] = {
    {"randint", randint, METH_VARARGS, "Return random integer"},
    {"choice", choice, METH_VARARGS, "Return random element from list"},
    {"_overclocking", _overclocking, METH_VARARGS, "Overclocking"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "random_c",
    "Random from C++",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_random_c(void) {
    return PyModule_Create(&module);
}