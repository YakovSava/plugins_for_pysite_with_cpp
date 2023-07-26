# include <iostream>
# include <map>
# include <string>
# include <sstream>
using namespace std;

int string_to_int(string word) {
    int integer = 0;
    for (int i = 0; i < word.length(); i++) {
        integer += static_cast<int>(word[i]);
    }
    return integer;
}

vector<string> get_all_indexes() {
    return {
        "ssd", "pc", "motherboard",
        "cable", "flash_USB", "power_unit",
        "hdd", "corpus", "processor",
        "ram", "nvme", "monitor",
        "laptop", "windows_activation", "windows_install"
    };
}

map<string, int> get_table() {
    vector<string> = get_all_indexes();
    map<string, int> table;

    for (int i = 0; i < indexes.size(); i++) {
        table[indexes[i]] = string_to_int(indexes[i]);
    }

    return table;
}

string dump_database(map<string, int> lines) {
    string dumper;
    for (const auto& pair : lines) {
        dumper += pair.first + "::" + to_string(pair.second);
    }
    return dumper;
}

vector<string> splitStringByNewLine(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string line;

    while (getline(ss, line, '\n')) {
        result.push_back(line);
    }

    return result;
}

map<string, int> load_database(string lines_str) {
    vector<string> lines_vector = splitStringByNewLine(lines_str);
    map<string, int> db;

    for (int i = 0; i < lines_vector.size(); i++) {
        string key, value;

        istringstream iss(input);
        getline(iss, key, "::");
        getline(iss, value);

        db[key] = stoi(value);
    }
    return db;
}