/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          http://www.mrpt.org/                          |
   |                                                                        |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file     |
   | See: http://www.mrpt.org/Authors - All rights reserved.                |
   | Released under BSD License. See details in http://www.mrpt.org/License |
   +------------------------------------------------------------------------+ */
#pragma once

#include <mrpt/typemeta/TTypeName.h>
#include <mrpt/typemeta/num_to_string.h>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <array>

/** \file This file extends TTypeName.h for STL C++ types. */

namespace mrpt
{
namespace typemeta
{
/** @name Conversion of type to string at compile time
@{ */

MRPT_DECLARE_TTYPENAME(std::string)

#define MRPT_DECLARE_TTYPENAME_CONTAINER(_CONTAINER)                    \
	template <typename V>                                               \
	struct TTypeName<_CONTAINER<V>>                                     \
	{                                                                   \
		constexpr static std::string get()                              \
		{                                                               \
			return std::string(#_CONTAINER) + std::string("<") +        \
				   std::string(TTypeName<V>::get()) + std::string(">"); \
		}                                                               \
	};

MRPT_DECLARE_TTYPENAME_CONTAINER(std::vector)
MRPT_DECLARE_TTYPENAME_CONTAINER(std::deque)
MRPT_DECLARE_TTYPENAME_CONTAINER(std::list)
MRPT_DECLARE_TTYPENAME_CONTAINER(std::set)

// array<T,N>
#define MRPT_DECLARE_TTYPENAME_CONTAINER_FIX_SIZE(_CONTAINER)           \
	template <typename V,std::size_t N>                                 \
	struct TTypeName<_CONTAINER<V,N>>                                   \
	{                                                                   \
		static std::string get()                                        \
		{                                                               \
			return std::string(#_CONTAINER) + std::string("<") +        \
				   std::string(TTypeName<V>::get()) + std::string(",")+ \
				   std::string(num_to_string<N>::value) + std::string(">"); \
		}                                                               \
	};

MRPT_DECLARE_TTYPENAME_CONTAINER_FIX_SIZE(std::array)

#define MRPT_DECLARE_TTYPENAME_CONTAINER_ASSOC(_CONTAINER)               \
	template <typename K, typename V>                                    \
	struct TTypeName<_CONTAINER<K, V>>                                   \
	{                                                                    \
		static std::string get()                                         \
		{                                                                \
			return std::string(#_CONTAINER) + std::string("<") +         \
				   std::string(TTypeName<K>::get()) + std::string(",") + \
				   std::string(TTypeName<V>::get()) + std::string(">");  \
		}                                                                \
	};

MRPT_DECLARE_TTYPENAME_CONTAINER_ASSOC(std::map)
MRPT_DECLARE_TTYPENAME_CONTAINER_ASSOC(std::multimap)

template <typename T1, typename T2>
struct TTypeName<std::pair<T1, T2>>
{
	static std::string get()
	{
		return std::string("std::pair<") + std::string(TTypeName<T1>::get()) +
			   std::string(",") + std::string(TTypeName<T2>::get()) +
			   std::string(">");
	}
};

/** @} */

}  // End of namespace
}  // End of namespace