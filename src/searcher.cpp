#include "searcher.hpp"

#include <numeric>


Searcher::Searcher(std::vector<Option>& searchable) :
    cache({ "", {} }),
    previous(cache[""]),
    opts(searchable) {

    auto& prev = previous.get();
    prev.resize(searchable.size(), 0);
    std::iota(prev.begin(), prev.end(), 0);
}

std::vector<size_t> Searcher::search(const std::string& query) {

    const auto cached = cache.find(query);
    if (cached != cache.end()) {
        previous = cached->second;
        return previous;
    }

    auto [iter, _] = cache.emplace(query);
    auto& next = iter->second;

    for (size_t i : previous.get()) {
        auto& opt = opts[i].display;

        auto oiter = opt.cbegin();
        auto qiter = query.begin();

        while (true) {

            if (qiter == query.end()) {
                next.emplace_back(i);
                break;
            }
            if (*oiter == *qiter) {
                ++qiter;
            }
            if (oiter == opt.end()) {
                break;
            }

            ++oiter;
        }
    }

    previous = next;

    return previous;
}
