#ifndef BAER_STRING_HPP
#define BAER_STRING_HPP

#include <boost/range.hpp>
#include <sstream>
#include <string>

namespace baer {
    namespace string {
        template<
            class Iterator,
            class Sep,
            class Str = std::basic_string< typename boost::range_value< Sep >::type >
        >
        auto join(Iterator begin, Iterator end, const Sep &delimiter) {
            using char_type          = typename Str::value_type;
            using traits_type        = typename Str::traits_type;
            using allocator_type     = typename Str::allocator_type;
            using ostringstream_type = std::basic_ostringstream< char_type, traits_type, allocator_type >;

            ostringstream_type result;

            if(begin != end) {
                result << *begin++;
            }

            while(begin != end) {
                result << delimiter << *begin++;
            }

            return result.str();
        }
    }  // namespace string
}  // namespace baer

#endif