/*
 *  ExitEvent.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/15/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "ExitEvent.hpp"
#include "EventQueue.hpp"

namespace iTrek 
{
  
  void ExitEvent::operator()()
  {
    // Unlock the EventQueue mutex since this thread is still holding it
    // to pop Events for execution. Otherwise, calling exit will result in
    // an assertion error in deleting the mutex because it is still held.
    EventQueue::instance().queueMutex.unlock();
    // Calls exit() to terminate the program
    exit(0);
  }
  
} // end namespace iTrek
