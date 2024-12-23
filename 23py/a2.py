#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys
import collections
import itertools


def main():
    g = Graph()
    for line in open(sys.argv[1]).read().splitlines():
        l, r = line.split('-')
        g.add_edge(l, r)

    nodes = list(g.neighbors)
    triangles = find_cliques(g, 3)

    triangles_with_t = [
        tri
        for tri in triangles
        if any(node.startswith('t') for node in tri)
    ]
    print(len(triangles_with_t))


def find_cliques(g, size):
    ''' Adapted from https://github.com/prendradjaja/euler100/blob/master/060--prime-pair-sets/find_cliques.py '''

    def find_larger_cliques(g, prev_cliques):
        result = set()
        for c1, c2 in itertools.combinations(prev_cliques, 2):
            vertices = set(c1) ^ set(c2)
            if len(vertices) == 2 and g.has_edge(*vertices):
                result.add(tuple(sorted(set(c1) | vertices)))
        return result

    cliques_by_size = { 2: g.edges() }
    for n in range(3, size + 1):
        cliques_by_size[n] = find_larger_cliques(g, cliques_by_size[n - 1])
    return cliques_by_size[size]


class Graph:
    ''' Undirected graph '''

    def __init__(self):
        self.neighbors = collections.defaultdict(set)

    def add_edge(self, v, w):
        self.neighbors[v].add(w)
        self.neighbors[w].add(v)

    def has_edge(self, v, w):
        return w in self.neighbors[v]

    def edges(self):
        result = set()
        for v in self.neighbors:
            for w in self.neighbors[v]:
                result.add(tuple(sorted([v, w])))
        return result


if __name__ == '__main__':
    main()
