/*
 *  command_input_utilities.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef ITREK_COMMAND_INPUT_UTILITIES_HPP
#define ITREK_COMMAND_INPUT_UTILITIES_HPP

#include <string>

namespace iTrek {

/** Case insensitive partial matching of strings. The strings match and the
 *  function returns true if the first N characters between the strings
 *  match where N is the minimum of the lengths between the two strings. If
 *  one of the input strings is empty, the function returns false.
 */
bool is_partial_match(std::string const& one, std::string const& oth);
  
/** Function returning true if input string is a number. A number
 *  is defined as a string containing only [0-9] and "+-." in the 
 *  local locale.
 */
bool is_number(std::string const& in); 
  
} // end namespace iTrek

#endif
