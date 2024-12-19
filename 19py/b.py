#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys
import functools


def main():
    # Parse
    text = open(sys.argv[1]).read()
    parts, designs = text.split('\n\n')
    parts = tuple(parts.split(', '))
    designs = designs.splitlines()

    # Solve
    answer = 0
    for d in designs:
        answer += count_arrangements(parts, d)
    print(answer)


@functools.cache
def count_arrangements(parts, design):
    if design == '':
        return 1
    else:
        result = 0
        for part in parts:
            if design.startswith(part):
                result += count_arrangements(parts, design[len(part):])
        return result


if __name__ == '__main__':
    main()
