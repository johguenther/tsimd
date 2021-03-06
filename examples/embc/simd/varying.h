// ======================================================================== //
// Copyright 2009-2017 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "../sys/platform.h"

namespace embree
{
  /* Varying numeric types */
  template<int N>
  struct vfloat
  {
    union { float f[N]; int i[N]; };
    __forceinline const float& operator [](size_t index) const { assert(index < N); return f[index]; }
    __forceinline       float& operator [](size_t index)       { assert(index < N); return f[index]; }

    using value_type = float;
    static constexpr int static_size = N;
  };

  template<int N>
  struct vdouble
  {
    union { double f[N]; long long i[N]; };
    __forceinline const double& operator [](size_t index) const { assert(index < N); return f[index]; }
    __forceinline       double& operator [](size_t index)       { assert(index < N); return f[index]; }

    using value_type = double;
    static constexpr int static_size = N;
  };

  template<int N>
  struct vint
  {
    int i[N];
    __forceinline const int& operator [](size_t index) const { assert(index < N); return i[index]; }
    __forceinline       int& operator [](size_t index)       { assert(index < N); return i[index]; }

    using value_type = int;
    static constexpr int static_size = N;
  };

  template<int N>
  struct vuint
  {
    unsigned int i[N];
    __forceinline const unsigned int& operator [](size_t index) const { assert(index < N); return i[index]; }
    __forceinline       unsigned int& operator [](size_t index)       { assert(index < N); return i[index]; }

    using value_type = unsigned int;
    static constexpr int static_size = N;
  };

  template<int N>
  struct vllong
  {
    long long i[N];
    __forceinline const long long& operator [](size_t index) const { assert(index < N); return i[index]; }
    __forceinline       long long& operator [](size_t index)       { assert(index < N); return i[index]; }

    using value_type = long long;
    static constexpr int static_size = N;
  };

  /* Varying bool types */
  template<int N> struct vboolf
  {
    int       i[N];
    using value_type = int;
    static constexpr int static_size = N;
  }; // for float/int

  template<int N> struct vboold
  {
    long long i[N];
    using value_type = long long;
    static constexpr int static_size = N;
  }; // for double/long long

  /* Aliases to default types */
  template<int N> using vreal = vfloat<N>;
  template<int N> using vbool = vboolf<N>;

  /* Maximum supported varying size */
#if defined(__AVX512F__)
  const int VSIZEX = 16;
#elif defined(__AVX__)
  const int VSIZEX = 8;
#else
  const int VSIZEX = 4;
#endif

  /* Extends varying size N to optimal or up to max(N, N2) */
  template<int N, int N2 = VSIZEX>
  struct vextend
  {
#if defined(__AVX512F__) && !defined(__AVX512VL__) // KNL
    /* use 16-wide SIMD calculations on KNL even for 4 and 8 wide SIMD */
    static const int size = (N2 == VSIZEX) ? VSIZEX : N;
    #define SIMD_MODE(N) N, 16
#else
    /* calculate with same SIMD width otherwise */
    static const int size = N;
    #define SIMD_MODE(N) N, N
#endif
  };

  /* 4-wide shortcuts */
  typedef vfloat<4>  vfloat4;
  typedef vdouble<4> vdouble4;
  typedef vreal<4>   vreal4;
  typedef vint<4>    vint4;
  typedef vuint<4>  vuint4;
  typedef vllong<4>  vllong4;
  typedef vbool<4>   vbool4;
  typedef vboolf<4>  vboolf4;
  typedef vboold<4>  vboold4;

  /* 8-wide shortcuts */
  typedef vfloat<8>  vfloat8;
  typedef vdouble<8> vdouble8;
  typedef vreal<8>   vreal8;
  typedef vint<8>    vint8;
  typedef vllong<8>  vllong8;
  typedef vbool<8>   vbool8;
  typedef vboolf<8>  vboolf8;
  typedef vboold<8>  vboold8;

  /* 16-wide shortcuts */
  typedef vfloat<16>  vfloat16;
  typedef vdouble<16> vdouble16;
  typedef vreal<16>   vreal16;
  typedef vint<16>    vint16;
  typedef vuint<16>   vuint16;
  typedef vllong<16>  vllong16;
  typedef vbool<16>   vbool16;
  typedef vboolf<16>  vboolf16;
  typedef vboold<16>  vboold16;

  /* Maximum shortcuts */
  typedef vfloat<VSIZEX>  vfloatx;
  typedef vdouble<VSIZEX> vdoublex;
  typedef vreal<VSIZEX>   vrealx;
  typedef vint<VSIZEX>    vintx;
  typedef vllong<VSIZEX>  vllongx;
  typedef vbool<VSIZEX>   vboolx;
  typedef vboolf<VSIZEX>  vboolfx;
  typedef vboold<VSIZEX>  vbooldx;
}
