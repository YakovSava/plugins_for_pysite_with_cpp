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

static PyObject* list_mass_search(PyObject* self, PyObject* args) {
	PyObject* first, second;

	if (!PyArg_ParseTuple(args, "OO", &first, &second)) {
		return NULL;
	}

	vector<vector<int>> lsts = {};
	Py_ssize_t listSize = PyList_Size(second);
	for (Py_ssize_t i = 0; i < listSize; ++i) {
		PyObject* pyElement = PyList_GetItem(pyList, i);

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
	PyObject* dict, filename;

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