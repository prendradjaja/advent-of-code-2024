#!/usr/bin/env python3
'''
Usage:
    ./b.py PATH_TO_INPUT_FILE
'''

import sys
from collections import Counter


def main(filename):
    text = open(filename).read().strip()
    stones = Counter(s for s in text.split(' '))
    for _ in range(75):
        stones = blink(stones)
    ans = sum(int(n) for n in stones.values())
    print(ans)


def blink(stones):
    res = Counter()
    for engraving, count in stones.items():
        if engraving == '0':
            n = '1'
            res[n] += count
        elif len(engraving) % 2 == 0:
            h = len(engraving) // 2
            n1 = engraving[:h]
            n2 = str(int(engraving[h:]))
            res[n1] += count
            res[n2] += count
        else:
            n = str(int(engraving) * 2024)
            res[n] += count
    return res


if __name__ == '__main__':
    main(sys.argv[1])
