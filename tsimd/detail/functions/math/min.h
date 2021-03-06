// ========================================================================== //
// The MIT License (MIT)                                                      //
//                                                                            //
// Copyright (c) 2017 Jefferson Amstutz                                       //
//                                                                            //
// Permission is hereby granted, free of charge, to any person obtaining a    //
// copy of this software and associated documentation files (the "Software"), //
// to deal in the Software without restriction, including without limitation  //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   //
// and/or sell copies of the Software, and to permit persons to whom the      //
// Software is furnished to do so, subject to the following conditions:       //
//                                                                            //
// The above copyright notice and this permission notice shall be included in //
// in all copies or substantial portions of the Software.                     //
//                                                                            //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        //
// DEALINGS IN THE SOFTWARE.                                                  //
// ========================================================================== //

#pragma once

#include <algorithm>

#include "../../pack.h"

namespace tsimd {

  // 1-wide //

  template <typename T>
  TSIMD_INLINE pack<T, 1> min(const pack<T, 1> &p1, const pack<T, 1> &p2)
  {
    return pack<T, 1>(std::min(p1[0], p2[0]));
  }

  // 4-wide //

  TSIMD_INLINE vfloat4 min(const vfloat4 &p1, const vfloat4 &p2)
  {
#if defined(__SSE__)
    return _mm_min_ps(p1, p2);
#else
    vfloat4 result;

    for (int i = 0; i < 4; ++i)
      result[i] = std::min(p1[i], p2[i]);

    return result;
#endif
  }

  TSIMD_INLINE vint4 min(const vint4 &p1, const vint4 &p2)
  {
#if defined(__SSE__)
    return _mm_min_epi32(p1, p2);
#else
    vint4 result;

    for (int i = 0; i < 4; ++i)
      result[i] = std::min(p1[i], p2[i]);

    return result;
#endif
  }

  // 8-wide //

  TSIMD_INLINE vfloat8 min(const vfloat8 &p1, const vfloat8 &p2)
  {
#if defined(__AVX2__) || defined(__AVX__)
    return _mm256_min_ps(p1, p2);
#else
    return vfloat8(min(vfloat4(p1.vl), vfloat4(p2.vl)),
                   min(vfloat4(p1.vh), vfloat4(p2.vh)));
#endif
  }

  TSIMD_INLINE vint8 min(const vint8 &p1, const vint8 &p2)
  {
#if defined(__AVX2__)
    return _mm256_min_epi32(p1, p2);
#elif defined(__AVX__)
    return vint8(_mm_min_epi32(p1.vl, p2.vl), _mm_min_epi32(p1.vh, p2.vh));
#else
    return vint8(min(vint4(p1.vl), vint4(p2.vl)),
                 min(vint4(p1.vh), vint4(p2.vh)));
#endif
  }

  // 16-wide //

  TSIMD_INLINE vfloat16 min(const vfloat16 &p1, const vfloat16 &p2)
  {
#if defined(__AVX512F__)
    return _mm512_min_ps(p1, p2);
#else
    return vfloat16(min(vfloat8(p1.vl), vfloat8(p2.vl)),
                    min(vfloat8(p1.vh), vfloat8(p2.vh)));
#endif
  }

  TSIMD_INLINE vint16 min(const vint16 &p1, const vint16 &p2)
  {
#if defined(__AVX512F__)
    return _mm512_min_epi32(p1, p2);
#else
    return vint16(min(vint8(p1.vl), vint8(p2.vl)),
                  min(vint8(p1.vh), vint8(p2.vh)));
#endif
  }

}  // namespace tsimd