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
        if possible(parts, d):
            answer += 1
    print(answer)


@functools.cache
def possible(parts, design):
    if design == '':
        return True
    else:
        return any(
            design.startswith(part) and possible(parts, design[len(part):])
            for part in parts
        )


if __name__ == '__main__':
    main()
