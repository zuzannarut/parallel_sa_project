# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-src"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-build"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/tmp"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/src/parlaylib-populate-stamp"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/src"
  "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/src/parlaylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/src/parlaylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/zuzia/Desktop/CMSC858N/parallel_sa/build/_deps/parlaylib-subbuild/parlaylib-populate-prefix/src/parlaylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
