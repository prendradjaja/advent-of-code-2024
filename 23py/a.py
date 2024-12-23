#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys
import collections


def main():
    g = Graph()
    for line in open(sys.argv[1]).read().splitlines():
        l, r = line.split('-')
        g.add_edge(l, r)

    nodes = list(g.neighbors)
    triangles = set()
    for node in nodes:
        for each in find_triangles_with_node(g, node):
            triangles.add(each)

    triangles_with_t = [
        tri
        for tri in triangles
        if any(node.startswith('t') for node in tri)
    ]
    print(len(triangles_with_t))


def find_triangles_with_node(g, node):
    ''' Via exhaustive depth-2 search '''
    a = node
    for b in g.neighbors[a]:
        for c in g.neighbors[b]:
            if a in g.neighbors[c]:
                yield normalize_triangle([a, b, c])


def normalize_triangle(triangle):
    return tuple(sorted(triangle))


class Graph:
    def __init__(self):
        self.neighbors = collections.defaultdict(set)

    def add_edge(self, v, w):
        self.neighbors[v].add(w)
        self.neighbors[w].add(v)


if __name__ == '__main__':
    main()
