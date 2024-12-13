import re

def ints(strings, mixedstring='error'):
    """
    Parses a sequence of strings, some of which are ints. Usually, each should be either exactly
    a number or contain no digits at all. In these cases, just return the string or int.

    If a "mixed string" (contains digits and nondigits) is
    encountered, then the `mixedstring` param determines the behavior:

    - 'error' (default)
    - 'str': keep it as a string
    - 'int': take just the int part

    Example:
    >>> s = "red 1 2"
    >>> color, x, y = ints(s.split())
    >>> color, x, y
    ('red', 1, 2)
    """
    return [maybeint(s, mixedstring) for s in strings]

def maybeint(s, mixedstring='error'):
    """ See ints(...) """
    if re.search(r'[0-9]', s):
        try:
            return int(s)
        except ValueError:
            if mixedstring == 'error':
                raise
            elif mixedstring == 'str':
                return s
            elif mixedstring == 'int':
                return int(re.search(r'-?\d+', s).group(0))
            else:
                raise ValueError('Invalid value for mixedstring: ' + mixedstring)
    else:
        return s

def findint(s):
    return maybeint(s, 'int')

def findints(s):
    """
    >>> findints('1_-2__3.45')
    [1, -2, 3, 45]
    """
    return ints(re.findall(r'-?\d+', s))
