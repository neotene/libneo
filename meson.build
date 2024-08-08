project('libneo', 'cpp', version : '0.1',
  default_options : ['cpp_std=c++17'])

tests = dependency('gtest')
tests_main = dependency('gtest_main')

if host_machine.system() == 'windows'
  terminal = dependency('pdcursesmod')
else
  terminal = dependency('ncursesw')
endif

libneo_deps = [terminal]

if host_machine.system() == 'linux'
  libneo_deps += dependency('threads')
endif

libneo_deps += dependency('gainput')

libneo_src = [
  'src/uuid.cpp',
  'src/term/common.cpp',
  'src/ui/ascii.cpp',
  'src/ui/input.cpp',
  'src/term/buffer.cpp',
  'src/term/context.cpp',
]

libtype = get_option('default_library')

libneo_cpp_args = []
cpp_args = []

if libtype == 'static'
    cpp_args += ['-DNEO_STATIC']
else
    libneo_cpp_args += ['-DNEO_BUILDING_THE_LIB']
endif

tests_cpp_args = []

libneo_incs = include_directories(['include'])

libneo = library('neo',
  libneo_src,
  dependencies : libneo_deps,
  cpp_args: libneo_cpp_args + cpp_args,
  include_directories: libneo_incs
)

neo_dep = declare_dependency(
  include_directories : libneo_incs,
  link_with : libneo,
  dependencies : [terminal],
  compile_args: libneo_cpp_args + cpp_args,
)

 executable('demo1',
    ['demo1.cpp'],
    dependencies: [neo_dep],
    cpp_args: cpp_args,
  )

executable('demo2',
    ['demo2.cpp'],
    dependencies: [neo_dep],
    cpp_args: cpp_args,
  )

test('test_point',
  executable('test_point',
    ['test_point.cpp'],
    dependencies: [neo_dep, tests, tests_main],
    cpp_args: tests_cpp_args + cpp_args,
  ),
  args : ['--gtest_color=yes'])

test('test_attributes',
  executable('test_attributes',
    ['test_attributes.cpp'],
    dependencies: [neo_dep, tests, tests_main],
    cpp_args: tests_cpp_args + cpp_args,
  ),
  args : ['--gtest_color=yes'])

test('test_space',
  executable('test_space',
    ['test_space.cpp'],
    dependencies: [neo_dep, tests, tests_main],
    cpp_args: tests_cpp_args + cpp_args,
  ),
  args : ['--gtest_color=yes'])

test('test_term',
  executable('test_term',
    ['test_term.cpp'],
    dependencies: [neo_dep, tests, tests_main],
    cpp_args: tests_cpp_args + cpp_args,
  ),
  args : ['--gtest_color=yes'])
