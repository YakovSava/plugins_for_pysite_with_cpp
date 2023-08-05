from plugins.wrapper import list_mass_search, sorting_by_frequency, get_indexes_table, get_all_indexes, damerau_levenshtein_distance

def _database():
    yield ...

def search(request:str) -> list:
    result = []
    for title in _database():
        if damerau_levenshtein_distance(title, request) * 0.8 < 25:
            result.append(title)
    return result