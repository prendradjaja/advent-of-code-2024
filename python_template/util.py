DIRECTIONS = [
    UP := (-1, 0),
    RIGHT := (0, 1),
    DOWN := (1, 0),
    LEFT := (0, -1),
]

# In clockwise order
EIGHT_DIRECTIONS = [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]

NINE_DIRECTIONS = [(0, 0), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]

def addvec(v, w):
    return tuple(a + b for a, b in zip(v, w))

def subvec(v, w):
    return tuple(a - b for a, b in zip(v, w))

def getitem(grid, pos):
    r, c = pos
    assert (0 <= r < len(grid) and 0 <= c < len(grid[0]))
    return grid[r][c]

def setitem(grid, pos, value):
    r, c = pos
    assert (0 <= r < len(grid) and 0 <= c < len(grid[0]))
    grid[r][c] = value

def in_bounds(grid, pos):
    r, c = pos
    return (
        0 <= r < len(grid) and
        0 <= c < len(grid[0])
    )

def enumerate2d(grid):
    for r, row in enumerate(grid):
        for c, value in enumerate(row):
            yield (r, c), value

def transpose(m):
    return [list(i) for i in zip(*m)]
