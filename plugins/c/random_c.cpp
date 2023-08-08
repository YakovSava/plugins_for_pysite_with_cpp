# include <Python.h>
# include <ctime>
# include <cstdlib>
# include <random>
# include <string>
using namespace std;

string char_to_string(char ch) {
    string str(1, ch);
    return str;
}

string get_ascii() {
    string ascii_letters;
    for (int i = 65; i < 90; i++) {
        ascii_letters += char_to_string(static_cast<char>(i));
    }
    for (int i = 0; i < 10; i++) {
        ascii_letters += to_string(i);
    }
    return ascii_letters;
}

int Crandint(int range_min, int range_max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);
	return dist(gen);
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

static PyObject *get_code(PyObject *self, PyObject *args) {
    int blocks;
    int chars;

    if (!PyArg_ParseTuple(args, "ii", &blocks, &chars)) {
        return NULL;
    }

    string chr = "";
    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < chars; j++) {
            string letter = get_ascii();
            chr += letter[letter.length()];
        }
        chr += "-";
    }
    return PyUnicode_FromString(chr.c_str());
}

static PyMethodDef methods[] = {
    {"randint", randint, METH_VARARGS, "Return random integer"},
    {"choice", choice, METH_VARARGS, "Return random element from list"},
    {"get_code", get_code, METH_VARARGS, "Return articul code"},
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