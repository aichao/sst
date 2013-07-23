/*
 *  command_input_utilities.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_command_input_utilities_hpp
#define iTrek_command_input_utilities_hpp

#include <string>

namespace iTrek {

/** Case insensitive partial matching of strings. The strings match and the
 *  function returns true if the first N characters between the strings
 *  match where N is the minimum of the lengths between the two strings. If
 *  one of the input strings is empty, the function returns false.
 */
bool is_partial_match(std::string const& one, std::string const& oth);
  
/** Predicate returning true if input string is a number. A number
 *  is defined as a string containing only [0-9] and "+-." in the 
 *  local locale.
 */
bool is_number(std::string const& in);
  
/** Predicate returning true if input string is an integer. An integer
 *  is defined as a string containing only [0-9] and "+-" in the 
 *  local locale.
 */
bool is_integer(std::string const& in); 
  
/** Predicate returning true if input string is an unsigned integer. An 
 *  unsigned integer is defined as a string containing only [0-9] in the 
 *  local locale.
 */
bool is_unsigned(std::string const& in); 

} // end namespace iTrek

#endif
