#ifndef CWCSV_MISC_H
#define CWCSV_MISC_H
#include <iterator>

namespace csv {

	template<typename It>
	using Char = typename std::iterator_traits<It>::value_type;

	template<typename T>
	using Val = typename T::value_type;

}

#endif
