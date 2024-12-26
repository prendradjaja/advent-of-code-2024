# Advent of Code 2024 solutions

Mostly in C this year.


## Python utilities

To do: Copy in sscanf.py (and give it a permanent home, maybe in toys repo)


## C notes

Reading files and parsing:
- [C template]: Read and parse a file line-by-line with `fopen()`, `fgets()`, `strcspn()`
- Day 3: Read a file character-by-character with `getc()`
- Day 5: Read a file with a fixed number of "paragraphs"
- Day 25: Read a file with an unknown number of "paragraphs"

Integer types:
- Throughout the month I used `int` and occasionally `long` when necessary
- Probably it is often (usually?) preferable to use fixed-width types e.g. `int64_t` and `uint64_t`
  - See e.g. day 24

Day 1: [01a] [01b]
- `qsort()` (part 1)
- Parsing ints with `fscanf()` (See also `sscanf()`, used in other days)
  - While scanf alone isn't suitable for reading a file line-by-line (it does not distinguish
    between e.g. `' '` and `'\n'`), see e.g. day 5 for using scanf together with `fgets()` for that
    purpose.
- Printing to stderr with `fprintf()`
  - See also `perror()` in [C template], which prints a human-readable error message based on the value of libc's global variable `errno`. (Use it after a function like `fopen()`, which writes to `errno` on error.)
  - `perror()` vs `fprintf(stderr, ...)`: https://stackoverflow.com/a/12102357

Day 2: [02a] [02b]
- `stdbool.h`: `true`, `false`, `bool`

Day 3: [03a] [03b]
- `struct`, `enum`, `typedef`
- Reading a file character-by-character with `getc()`
- `ctype.h`: `isdigit()`

Day 4: [04a] [04b]
- My own `struct Vector` (see day 8 [08a] for `Vector`, `Position`, `PositionDelta`)
  - And `add()`, `in_bounds()`
- `{ 0 }` initializes an array with all zeroes (even for multi-dimensional arrays: see day 5)

Day 5: [05a] [05b]
- `malloc()`
  - Of course in real code don't forget `free()`
- Jagged 2D array via own `struct ArrayWithSize`
- My own `consume()` and `consume_int()` first appear
  - But see day 14 for a better usage example
- Reading a file with a fixed number of "paragraphs"
- `assert.h`: `assert()`

Day 7: [07a] [07b]
- Jagged 2D array as 1D array with `END_OF_SUBARRAY` markers
  - I don't necessarily recommend this. See day 5 for another way of handling jagged arrays.

Day 10: [10a] [10b]
- Splitting a program into multiple files

Day 14: [14a]
- My own `consume()` and `consume_int()`

Day 24: [24a]
- Fixed-width types e.g. `uint64_t`
  - Q: How do you use these types with `printf()`?
    - A: With macros like `PRIu64`, e.g. `printf("%" PRIu64 "\n", answer)`
  - Q: What's the difference between `stdint.h` and `inttypes.h`?
    - A: https://stackoverflow.com/a/9162072

Day 25: [25a]
- Reading a file with a variable number of "paragraphs"


[c template]: ./c_template/s.c

[01a]: ./01/a.c
[01b]: ./01/b.c

[02a]: ./02/a.c
[02b]: ./02/b.c

[03a]: ./03/a.c
[03b]: ./03/b.c

[04a]: ./04/a.c
[04b]: ./04/b.c

[05a]: ./05/a.c
[05b]: ./05/b.c

[07a]: ./07/a.c
[07b]: ./07/b.c

[08a]: ./08/a.c

[10a]: ./10/a
[10b]: ./10/b

[14a]: ./14/a.c

[24a]: ./24/a.c

[25a]: ./25/a.c
