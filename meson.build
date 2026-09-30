project(
  'folio',
  'cpp',
  default_options: ['cpp_std=c++23']
)

curl_dep = dependency('libcurl')

inc = include_directories('include')

executable(
  'folio',
  'main.cpp',
  dependencies: [curl_dep],
  include_directories: inc,
)
