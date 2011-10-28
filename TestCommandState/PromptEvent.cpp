/*
 *  PromptEvent.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/13/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "PromptEvent.hpp"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>

#include "CommandInputEvent.hpp"
#include "CommandData.hpp"
#include "CommandQueue.hpp"

namespace iTrek 
{
  
  PromptEvent::PromptEvent( std::string const& prompt )
    : prompt_(prompt)
  {}
  
  void PromptEvent::operator()()
  {
    // Send the prompt message to std::cout
    std::cout << prompt_ << std::flush;
    // Get command input event: for this simulation this is just
    // a line from std::cin. as in sst.c, the length of the line is
    // bound by 127 chars. According to scan(), the line is parsed 
    // as either string of at most 9 chars (with \0 at end) or 
    // as a number of type double. Spaces are delimiters in the parsing.
    // The string is converted to lower case.
    const unsigned N = 128;
    char cmd_cstr[ N ];
    std::cin.getline( cmd_cstr, N );
    CommandInputEvent command( cmd_cstr );
    // convert to lower case
    boost::to_lower(command);
    // tokenize with space delimiter
    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > tokens(command, sep);
    // Insert command tokens into CommandQueue
    {
      boost::lock_guard< CommandQueue::object_type > lock( CommandQueue::instance() );
      std::size_t i = 0;
      for( boost::tokenizer< boost::char_separator<char> >::iterator beg = tokens.begin(); beg != tokens.end(); ++beg, ++i )
      {
        CommandQueue::instance().push( *beg );
      }
      // insert "NULL" command into commandQueue if there are no valid tokens
      if ( i == 0 ) CommandQueue::instance().push( CommandData("") );
    }
    // Can be called outside scope of lock
    CommandQueue::instance().signal();
  }
  
} // end namespace iTrek
