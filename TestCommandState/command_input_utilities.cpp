/*
 *  command_input_utilities.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan Chao. All rights reserved.
 *
 */

#include "command_input_utilities.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace iTrek {
  
bool is_partial_match(std::string const& one, std::string const& oth) {
  unsigned N = (one.length() < oth.length()) ? one.length() : oth.length();
  if (N == 0) return false;
  return boost::algorithm::iequals(one.substr(0, N), oth.substr(0, N));
}

bool is_number(std::string const& in) {
  return boost::algorithm::all(in, boost::algorithm::is_digit() || boost::algorithm::is_any_of(".-+"));
}

bool is_integer(std::string const& in) {
  return boost::algorithm::all(in, boost::algorithm::is_digit() || boost::algorithm::is_any_of("-+"));
}

bool is_unsigned(std::string const& in) {
  return boost::algorithm::all(in, boost::algorithm::is_digit());
}
  
} // end namespace iTrek
