#!/usr/bin/env python3
'''
Usage:
    ./a.py PATH_TO_INPUT_FILE
    ./b.py PATH_TO_INPUT_FILE
'''

import sys


def main(filename):
    '''
    >>> main('ex_part1')
    4,6,3,5,6,3,5,2,1,0
    >>> main('in')
    1,4,6,1,6,4,3,0,3
    '''

    def eval_combo(operand):
        if 0 <= operand <= 3:
            return operand
        elif operand == 4:
            return registers['A']
        elif operand == 5:
            return registers['B']
        elif operand == 6:
            return registers['C']
        else:
            assert False, 'Unreachable case'

    # Parse
    text = open(filename).read()
    registers, program = text.split('\n\n')
    registers = [int(line.split(': ')[1]) for line in registers.splitlines()]
    registers = {ch: n for ch, n in zip('ABC', registers)}
    program = [int(n) for n in program.split(' ')[1].split(',')]

    # Run
    ip = 0
    output = []
    while ip < len(program):
        is_jump = False
        opcode = program[ip]
        operand = program[ip + 1]
        if opcode == 0:
            numer = registers['A']
            denom = 2**eval_combo(operand)
            registers['A'] = numer // denom
        elif opcode == 1:
            registers['B'] = registers['B'] ^ operand
        elif opcode == 2:
            registers['B'] = eval_combo(operand) % 8
        elif opcode == 3:
            if registers['A'] != 0:
                is_jump = True
                ip = operand
        elif opcode == 4:
            registers['B'] = registers['B'] ^ registers['C']
        elif opcode == 5:
            output.append(eval_combo(operand) % 8)
        elif opcode == 6:
            numer = registers['A']
            denom = 2**eval_combo(operand)
            registers['B'] = numer // denom
        elif opcode == 7:
            numer = registers['A']
            denom = 2**eval_combo(operand)
            registers['C'] = numer // denom
        else:
            assert False, 'Unreachable case'

        if not is_jump:
            ip += 2

    print(','.join(str(n) for n in output))


if __name__ == '__main__':
    main(sys.argv[1])
