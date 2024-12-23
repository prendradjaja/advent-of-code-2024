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
    find_cliques(g)


def find_cliques(g):
    '''
    Adapted from https://github.com/prendradjaja/euler100/blob/master/060--prime-pair-sets/find_cliques.py

    There is one key optimization from find_cliques.py. (Compare b.slow.py and b.py; b.slow.py and
    find_cliques.py have a much slower find_larger_cliques() compared to b.py.)
    '''

    def find_larger_cliques(g, prev_cliques):
        result = set()
        for c1 in prev_cliques:
            for v in g.vertices():
                if extends_clique(c1, v, g):
                    result.add(tuple(sorted([*c1] + [v])))
        return result

    def extends_clique(clique, node, graph):
        if node in clique:
            return False
        return all(
            graph.has_edge(node, other_node)
            for other_node in clique
        )

    cliques_by_size = { 2: g.edges() }
    print(2, len(cliques_by_size[2]))
    for n in itertools.count(3):
        cliques_by_size[n] = find_larger_cliques(g, cliques_by_size[n - 1])
        print(n, len(cliques_by_size[n]))
        if len(cliques_by_size[n]) == 1:
            (clique,) = cliques_by_size[n]
            print(f'Answer: (clique of size {n})')
            print(','.join(sorted(clique)))
            return


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

    def vertices(self):
        return list(self.neighbors)


if __name__ == '__main__':
    main()
