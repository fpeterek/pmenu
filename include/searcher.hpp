#ifndef SEARCHER_HPP
#define SEARCHER_HPP


#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include "menu_option.hpp"


class Searcher {

    std::unordered_map<std::string, std::vector<size_t>> cache;

    std::reference_wrapper<std::vector<size_t>> previous;
    std::vector<Option>& opts;

public:

    Searcher(std::vector<Option>& searchable);

    std::vector<size_t> search(const std::string& query);

};


#endif // SEARCHER_HPP
