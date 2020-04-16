#ifndef BAER_ALGORITHM_HPP
#define BAER_ALGORITHM_HPP

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

namespace baer {
    namespace algorithm {
        template<
            typename U,
            typename Lambda
        >
        auto slidingWindow(U container, int window, Lambda f) -> U {
            bool valid;
            U ret;

            for (auto it = container.begin(); std::distance(it, container.end()) >= window; it++) {
                auto item = f(it, it + window, valid);

                if(valid) {
                    ret.push_back(item);
                }
            }

            return ret;
        }

        template<
            typename U,
            typename Index = int,
            typename Value = double
        >
        auto topN_iv(U container, int N) -> std::vector<std::pair<Index, Value>> {
            std::vector<std::pair<Index, Value>> ret;

            assert(N <= container.size());

            for(int i = 0; i < container.size(); i++) {
                ret.push_back(std::make_pair(i,container.at(i)));
            }

            std::sort(ret.begin(), ret.end(),
                [=](std::pair<Index, Value>& a, std::pair<Index, Value>& b)
                {
                    return a.second > b.second;
                }
            );

            ret.erase(ret.begin() + N, ret.end());

            return ret;
        }
    }  // namespace algorithm
}  // namespace baer

#endif