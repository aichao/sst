/*
 *  DisplayEvent.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/13/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "DisplayEvent.hpp"
#include <iostream>

namespace iTrek 
{
  
  DisplayEvent::DisplayEvent( std::string const& msg )
  : msg_(msg)
  {}
  
  void DisplayEvent::operator()()
  {
    // Send the display message to std::cout
    std::cout << msg_ << std::flush;
  }
  
} // end namespace iTrek
