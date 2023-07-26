# include <Python.h>
# include "definitor.hpp"
# include "c_database.hpp"
# include "getter.hpp"
# include "searcher.hpp"

static PyObject* write(PyObject *self, PyObject *args) {
	PyObject *filename_obj, *data_obj;

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

	bool result = exists(filename);

	return result ? Py_True : Py_False;
}

static PyObject* longest_common_subsequence(PyObject* self, PyObject* args) {
	PyObject* first, second;

	if (!PyArg_ParseTuple(args, "OO", &first, &second)) {
		return NULL;
	}

	int result = longestCommonSubsequence(list_to_vector(first), list_to_vector(second));

	return Py_BuildValue("i", result);
}

static PyObject* mass_search(PyObject* self, PyObject* args);