#ifndef BAER_ALGORITHM_HPP
#define BAER_ALGORITHM_HPP

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
    }  // namespace algorithm
}  // namespace baer

#endif