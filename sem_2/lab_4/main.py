def run_automaton(word):
    # Таблица переходов
    states = {
        'q0': {'a': 'q1', 'b': 'q0', 'c': 'q2', 'd': 'q2'},
        'q1': {'a': 'q1', 'b': 'q0', 'c': 'q2', 'd': 'q2'},
        'q2': {'a': 'q3', 'b': 'q2', 'c': 'q0', 'd': 'q0'},
        'q3': {'a': 'q3', 'b': 'q2', 'c': 'q0', 'd': 'q0'},
    }

    current_state = 'q0' # λ 

    for char in word:
        if char not in {'a', 'b', 'c', 'd'}:
            return False
        current_state = states[current_state][char]

    return current_state == 'q0'


print(run_automaton(""))
