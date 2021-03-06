## ========================================================================== ##
## The MIT License (MIT)                                                      ##
##                                                                            ##
## Copyright (c) 2017 Jefferson Amstutz                                       ##
##                                                                            ##
## Permission is hereby granted, free of charge, to any person obtaining a    ##
## copy of this software and associated documentation files (the "Software"), ##
## to deal in the Software without restriction, including without limitation  ##
## the rights to use, copy, modify, merge, publish, distribute, sublicense,   ##
## and/or sell copies of the Software, and to permit persons to whom the      ##
## Software is furnished to do so, subject to the following conditions:       ##
##                                                                            ##
## The above copyright notice and this permission notice shall be included in ##
## in all copies or substantial portions of the Software.                     ##
##                                                                            ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    ##
## THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER ##
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    ##
## FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        ##
## DEALINGS IN THE SOFTWARE.                                                  ##
## ========================================================================== ##

set(FLAGS_SSE42  "-xsse4.2")
set(FLAGS_AVX    "-xAVX")
set(FLAGS_AVX2   "-xCORE-AVX2")
set(FLAGS_AVX512KNL "-xMIC-AVX512")
set(FLAGS_AVX512SKX "-xCORE-AVX512")

if (TSIMD_BUILD_ISA STREQUAL "AVX512SKX")
  set (ISA_FLAGS ${FLAGS_AVX512SKX})
elseif (TSIMD_BUILD_ISA STREQUAL "AVX512KNL")
  set (ISA_FLAGS ${FLAGS_AVX512KNL})
elseif (TSIMD_BUILD_ISA STREQUAL "AVX2")
  set (ISA_FLAGS ${FLAGS_AVX2})
elseif (TSIMD_BUILD_ISA STREQUAL "AVX")
  set (ISA_FLAGS ${FLAGS_AVX})
else()
  set (ISA_FLAGS ${FLAGS_SSE42})
endif()

set(CMAKE_CXX_FLAGS "-std=c++11 ${ISA_FLAGS} ${CMAKE_CXX_FLAGS}")

if (APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} -dynamiclib)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") # link against C++11 stdlib
endif()
