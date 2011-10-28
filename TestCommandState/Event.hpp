/*
 *  Event.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/5/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef EVENT_HPP
#define EVENT_HPP

namespace iTrek 
{   
  
  /** 
   */
  class Event
  {
  public:
      
    /** base class needs a virtual destructor
      */
    virtual ~Event() {}
      
    /** Interface to execute the event. The base Event does nothing.
      */
    virtual void operator()() {}
      
  };
  
} // end namesoace iTrek

#endif
