# include <Python.h>
# include <map>
# include <string>
using namespace std;

static PyObject* map_to_dict(map<string, int> db) {
	PyObject* dict = PyDict_New();
	
	for (const auto& pair : db) {
		dict.setitem(PyUnicode_FromString(pair.first), PyInt_FromLong(pair.second));
	}

	return dict;
}

static PyObject* string_to_str(string c_str) {
	return PyUnicode_FromString(c_str.c_str());
}

const char* str_to_string(PyObject* python_string) {
	return PyUnicode_AsUTF8(python_string);
}

map<string, int> dict_to_map(PyObject* dict) {
	map<string, int> db;

	PyObject* key = NULL;
    PyObject* value = NULL;
    Py_ssize_t pos = 0;

    while (PyDict_Next(dict, &pos, &key, &value)) {
        string keyStr = PyString_AsString(key);
        int valueStr = PyInt_AsLong(value);

        db[keyStr] = valueStr;
    }
    return db;
}