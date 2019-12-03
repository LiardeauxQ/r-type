//
// Created by alex on 11/8/19.
//

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <stdint.h>

#ifdef WIN32
    #define U128 uint64_t
    #define I128 uint64_t
#else
    #define U128 __uint128_t
    #define I128 __uint128_t
#endif /* WIN32 */

template<typename  T>
using Box = std::unique_ptr<T>;

template<typename  T>
using Rc = std::shared_ptr<T>;

template<typename T>
using Vec = std::vector<T>;

using String = std::string;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = U128;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = I128;

using f32 = float;
using f64 = double;

template<typename T, typename U>
using Map = std::map<T, U>;

template<typename T, typename U>
using HashMap = std::unordered_map<T, U>;