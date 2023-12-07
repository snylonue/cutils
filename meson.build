project('cutils', 'c', version: '0.1', default_options: ['warning_level=3'])

vec = library('vec', 'vec/vec.c', 'vec/iter.c', 'vec/slice.c')

math = library('math', 'math/bigint.c', 'math/prime.c', link_with: [vec])

math_test = executable(
    'math_test',
    'math/test.c',
    link_with: [math],
    install: true,
)

test('math', math_test)
