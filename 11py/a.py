#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys


def main():
    text = open(sys.argv[1]).read().strip()
    stones = [s for s in text.split(' ')]
    for _ in range(25):
        stones = blink(stones)
    ans = len(stones)
    print(ans)


def blink(stones):
    res = []
    for s in stones:
        if s == '0':
            res.append('1')
        elif len(s) % 2 == 0:
            h = len(s) // 2
            res.append(s[:h])
            res.append(str(int(s[h:])))
        else:
            res.append(str(int(s) * 2024))
    return res


if __name__ == '__main__':
    main()
