'''
Example output of running this program:

  [2, 9, 1, 4, 1, 7]
  |  [2, 9, 1]
  |  .  [2]
  |  .  [2] => [2]
  |  .  [9, 1]
  |  .  .  [9]
  |  .  .  [9] => [9]
  |  .  .  [1]
  |  .  .  [1] => [1]
  |  .  [9, 1] => [1, 9]
  |  [2, 9, 1] => [1, 2, 9]
  |  [4, 1, 7]
  |  .  [4]
  |  .  [4] => [4]
  |  .  [1, 7]
  |  .  .  [1]
  |  .  .  [1] => [1]
  |  .  .  [7]
  |  .  .  [7] => [7]
  |  .  [1, 7] => [1, 7]
  |  [4, 1, 7] => [1, 4, 7]
  [2, 9, 1, 4, 1, 7] => [1, 1, 2, 4, 7, 9]
'''

import random


def main():
    random.seed(1, version=2)
    xs = [random.randrange(10) for _ in range(6)]
    merge_sort(xs)


def trace(f):
    MAJOR_INDENT = 3  # every MAJOR_INDENT tick marks, use a major tick mark instead of a regular one
    recursion_depth = 0

    def traced(*args, **kwargs):
        nonlocal recursion_depth
        indent = get_indent(recursion_depth)
        print(indent, *args)

        recursion_depth += 1
        result = f(*args, **kwargs)
        recursion_depth -= 1

        print(indent, *args, '=>', result)
        return result

    def get_indent(depth):
        indent = ''
        for i in range(depth):
            if i % MAJOR_INDENT == 0:
                indent += '  |'
            else:
                indent += '  .'
        return indent + ' '

    return traced


@trace
def merge_sort(xs):
    if len(xs) <= 1:
        return xs

    midpoint = len(xs) // 2
    return merge(
        merge_sort(xs[:midpoint]),
        merge_sort(xs[midpoint:])
    )


def merge(xs, ys):
    result = []
    while xs and ys:
        if xs[0] < ys[0]:
            result.append(xs.pop(0))
        else:
            result.append(ys.pop(0))
    result.extend(xs)
    result.extend(ys)
    return result


if __name__ == '__main__':
    main()
