  #include "naive_dictionary.hpp"
#include "tools.hpp"
#include <iostream>



naive_dictionary::naive_dictionary(const std::initializer_list<std::string>& init)
  : m_set(init.begin(), init.end())
{
}


void naive_dictionary::init(const std::vector<std::string>& word_list)
{
  m_set = std::set<std::string>(word_list.begin(), word_list.end());
}


result_t naive_dictionary::search(const std::string& query) const
{
  std::lock_guard l(m);
  std::vector<std::string> v(m_set.begin(), m_set.end());
  std::cout << "here" << std::endl;

  size_t begin = 0;
  size_t end = v.size() - 1;

  int b_levenshtein = levenshtein(query, v.at(begin));
  int e_levenshtein = levenshtein(query, v.at(end));

  while(begin + 1 < end) {
    if(b_levenshtein >= e_levenshtein) {
      end = begin + (end - begin) / 2 ;
      e_levenshtein = levenshtein(query, v.at(end));
    }
    else {
      begin = begin + (end - begin) / 2 ;
      b_levenshtein = levenshtein(query, v.at(begin));
    }
  }

  if(e_levenshtein < b_levenshtein)
    return {v.at(end), e_levenshtein};
  else
    return {v.at(begin), b_levenshtein};
}


void naive_dictionary::insert(const std::string& w)
{
  std::lock_guard l(m);
  m_set.insert(w);
}

void naive_dictionary::erase(const std::string& w)
{
  std::lock_guard l(m);
  m_set.erase(w);
}
