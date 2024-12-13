#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys
from findints import findints
from vector import Vector
import collections


Machine = collections.namedtuple('Machine', 'a b prize')


def main():
    text = open(sys.argv[1]).read()
    paragraphs = text.split('\n\n')
    paragraphs = [parse_paragraph(p) for p in paragraphs]

    answer = 0
    for each in paragraphs:
        answer += solve(each)
    print(answer)


def solve(machine):
    return min(
        (
            a * 3 + b
            for a in range(0, 101)
            for b in range(0, 101)
            if machine.a * a + machine.b * b == machine.prize
        ),
        default = 0
    )


def parse_paragraph(paragraph):
    a, b, prize = paragraph.split('\n')
    a = Vector(findints(a))
    b = Vector(findints(b))
    prize = Vector(findints(prize))
    return Machine(a, b, prize)


if __name__ == '__main__':
    main()
