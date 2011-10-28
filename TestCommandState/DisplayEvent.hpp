/*
 *  DisplayEvent.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/13/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef DISPLAY_EVENT_HPP
#define DISPLAY_EVENT_HPP

#include <string>

#include "Event.hpp"

namespace iTrek 
{   
  
  /** 
   */
  class DisplayEvent : public Event
  {
  public:
      
    /** Constructor sets the display message
     */
    DisplayEvent( std::string const& msg );
      
    /** A DisplayEvent sends its display message to the display. 
     */
    void operator()();
      
  private:
      
    std::string msg_;
  };
  
} // end namesoace iTrek

#endif
