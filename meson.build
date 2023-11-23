project('cutils', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

math_test = executable('math_test',
            'math/test.c',
            'math/bigint.c',
            'vec/vec.c',
            'vec/slice.c',
           install : true)

test('math', math_test)
