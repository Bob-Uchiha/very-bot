project('veryyes', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20','build.cpp_std=c++20'])
dpp = dependency('dpp')
exe = executable('veryyes', 'veryyes.cpp',cpp_args : '--std=c++20',dependencies: [dpp],
  install : true,native: true)

test('basic', exe)
