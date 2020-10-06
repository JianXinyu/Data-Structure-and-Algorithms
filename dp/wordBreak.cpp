//
// Created by jianx on 10/5/2020.
//
#include "dp.h"
bool wordBreak::wordbreak(string s, vector<string>& wordDict) {
  // Mark evert word as breakable.
  for (const string& word : wordDict)
    mem_.emplace(word, true);

  // Query the answer of the original string.
  return wordbreak(s);
}

bool wordBreak::wordbreak(const string& s)
{
  // In memory, directly return.
  if (mem_.count(s)) return mem_[s];

  // Try every break point.
  for (int j = 1; j < s.length(); j++) {
    auto it = mem_.find(s.substr(j));
    // Find the solution for s.
    if (it != mem_.end() && it->second && wordbreak(s.substr(0, j)))
      return mem_[s] = true;
  }

  // No solution for s, memorize and return.
  return mem_[s] = false;
}