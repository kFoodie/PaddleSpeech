#ifndef DECODER_UTILS_H_
#define DECODER_UTILS_H_

#include <utility>
#include "path_trie.h"

const float NUM_FLT_INF = std::numeric_limits<float>::max();
const float NUM_FLT_MIN = std::numeric_limits<float>::min();

template <typename T1, typename T2>
bool pair_comp_first_rev(const std::pair<T1, T2> &a,
                         const std::pair<T1, T2> &b)
{
    return a.first > b.first;
}

template <typename T1, typename T2>
bool pair_comp_second_rev(const std::pair<T1, T2> &a,
                          const std::pair<T1, T2> &b)
{
    return a.second > b.second;
}

template <typename T>
T log_sum_exp(const T &x, const T &y)
{
    static T num_min = -std::numeric_limits<T>::max();
    if (x <= num_min) return y;
    if (y <= num_min) return x;
    T xmax = std::max(x, y);
    return std::log(std::exp(x-xmax) + std::exp(y-xmax)) + xmax;
}


// Functor for prefix comparsion
bool prefix_compare(const PathTrie* x,  const PathTrie* y);

// Get length of utf8 encoding string
// See: http://stackoverflow.com/a/4063229
size_t get_utf8_str_len(const std::string& str);

std::vector<std::string> split_str(const std::string &s,
                                   const std::string &delim);

std::vector<std::string> split_utf8_str(const std::string &str);

void add_word_to_fst(const std::vector<int>& word,
                     fst::StdVectorFst* dictionary);

bool add_word_to_dictionary(const std::string& word,
                         const std::unordered_map<std::string, int>& char_map,
                         bool add_space,
                         int SPACE,
                         fst::StdVectorFst* dictionary);
#endif // DECODER_UTILS_H
