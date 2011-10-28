/*
 *  ExitEvent.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/15/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef EXIT_EVENT_HPP
#define EXIT_EVENT_HPP

#include <string>

#include "Event.hpp"

namespace iTrek 
{   
  
  /** 
   */
  class ExitEvent : public Event
  {
  public:
      
    /** An ExitEvent calls exit to terminate the program. 
     */
    void operator()();
  };
  
} // end namesoace iTrek

#endif
