#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    python3 -m doctest -v a.py
'''

import sys
from collections import Counter


def main(filename):
    '''
    >>> main('ex')
    55312
    '''
    text = open(filename).read().strip()
    stones = Counter(s for s in text.split(' '))
    for _ in range(25):
        stones = blink(stones)
    answer = sum(int(n) for n in stones.values())
    print(answer)


def blink(stones):
    result = Counter()
    for engraving, count in stones.items():
        if engraving == '0':
            result['1'] += count
        elif len(engraving) % 2 == 0:
            half = len(engraving) // 2
            result[engraving[:half]] += count
            result[str(int(engraving[half:]))] += count
        else:
            result[str(int(engraving) * 2024)] += count
    return result


if __name__ == '__main__':
    main(sys.argv[1])
