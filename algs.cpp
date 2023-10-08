# include <Python.h>
# include "definitor.hpp"
# include "c_database.hpp"
# include "getter.hpp"
# include "searcher.hpp"

static PyObject* write(PyObject *self, PyObject *args) {
	PyObject* filename_obj; 
	PyObject* data_obj;

	if (!PyArg_ParseTuple(args, "UU", &filename_obj, &data_obj)) {
		return NULL;
	}

	int result = Cwrite(str_to_string(filename_obj), str_to_string(data_obj));

	return Py_BuildValue("i", result);
}

static PyObject* read(PyObject* self, PyObject* args) {
	PyObject* filename;

	if (!PyArg_ParseTuple(args, "U", &filename)) {
		return NULL;
	}

	string result = Cread(str_to_string(filename));

	return string_to_str(result);
}

static PyObject* exists_file(PyObject* self, PyObject* args) {
	PyObject* filename;

	if (!PyArg_ParseTuple(args, "U", &filename)) {
		return NULL;
	}

	bool result = exists(str_to_string(filename));

	return result ? Py_True : Py_False;
}

static PyObject* longest_common_subsequence(PyObject* self, PyObject* args) {
	PyObject* first;
	PyObject* second;

	if (!PyArg_ParseTuple(args, "OO", &first, &second)) {
		return NULL;
	}

	int result = longestCommonSubsequence(list_to_vector(first), list_to_vector(second));

	return Py_BuildValue("i", result);
}

static PyObject* list_mass_search(PyObject* self, PyObject* args) {
	PyObject* first;
	PyObject* second;

	if (!PyArg_ParseTuple(args, "OO", &first, &second)) {
		return NULL;
	}

	vector<vector<int>> lsts = {};
	Py_ssize_t listSize = PyList_Size(second);
	for (Py_ssize_t i = 0; i < listSize; ++i) {
		PyObject* pyElement = PyList_GetItem(second, i);

		lsts.push_back(list_to_vector(pyElement));
	}

	vector<int> result = mass_search(list_to_vector(first), lsts);

	return vector_to_list(result);
}

static PyObject* dumps(PyObject* self, PyObject* args) {
	PyObject* dict;

	if (!PyArg_ParseTuple(args, "O", &dict)) {
		return NULL;
	}

	string dump_db = dump_database(dict_to_map(dict));

	return string_to_str(dump_db);
}

static PyObject* dump(PyObject* self, PyObject* args) {
	PyObject* dict;
	PyObject* filename;

	if (!PyArg_ParseTuple(args, "OU", &dict, &filename)) {
		return NULL;
	}

	string dump_db = dump_database(dict_to_map(dict));
	Cwrite(
		str_to_string(filename),
		dump_db.c_str()
	);

	return string_to_str(dump_db);
}

static PyObject* loads(PyObject* self, PyObject* args) {
	PyObject* db_str;

	if (!PyArg_ParseTuple(args, "U", &db_str)) {
		return NULL;
	}

	string db_string = str_to_string(db_str);
	map<string, int> result = load_database(db_string);

	return map_to_dict(result);
}

static PyObject* load(PyObject* self, PyObject* args) {
	PyObject* filename;

	if (!PyArg_ParseTuple(args, "U", &filename)) {
		return NULL;
	}

	string db_string = Cread(str_to_string(filename));
	map<string, int> result = load_database(db_string);

	return map_to_dict(result);
}

static PyObject* get_indexes_table(PyObject* self, PyObject* args) {
	return map_to_dict(
		get_table()
	);
}

static PyObject* get_all_name_indexes(PyObject* self, PyObject* args) {
	vector<string> lst = get_all_indexes();
	PyObject* pyList = PyList_New(0);
	for (int i = 0; i < lst.size(); i++) {
		PyList_Append(pyList, string_to_str(lst[i]));
	}

	return pyList;
}

static PyMethodDef methods[] = {
	{"read", read, METH_VARARGS, "Reading a file using the low-level C++ programming language"},
	{"write", write, METH_VARARGS, "Writing to file using the low-level C++ programming language"},
	{"exists_file", exists_file, METH_VARARGS, "Checking the existence of the file"},
	{"longest_common_subsequence", longest_common_subsequence, METH_VARARGS, "Algorithm for finding the smallest length between lists"},
	{"list_mass_search", list_mass_search, METH_VARARGS, "The algorithm of mass finding the smallest length between lists"},
	{"dumps", dumps, METH_VARARGS, "Creating a special graph database"},
	{"dump", dump, METH_VARARGS, "Creating and writing a special graph database to a file"},
	{"loads", loads, METH_VARARGS, "Reading a special database (reading into a dictionary)"},
	{"load", load, METH_VARARGS, "Reading from a special database file (reading into a dictionary)"},
	{"get_all_name_indexes", get_all_name_indexes, METH_VARARGS, "Getting all possible product names"},
	{"get_indexes_table", get_indexes_table, METH_VARARGS, "Getting all possible articles of goods"},
	{NULL, NULL, 0, NULL} 
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "algs",
    "All possible algorithms that can be useful for creating a website",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_algs(void) {
    return PyModule_Create(&module);
}