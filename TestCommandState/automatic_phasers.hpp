/*
 *  automatic_phasers.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef AUTOMATIC_PHASERS_HPP
#define AUTOMATIC_PHASERS_HPP

#include "CommandState.hpp"

namespace iTrek { 
namespace CommandInputState {   
  
/** 
 */
class automatic_phasers : public CommandState {
 public:
  
  /** Interface to execute the state action. State specific processing
   *  is implemented in the derived class. This method is responsible 
   *  for transitioning the state after executing the state action. 
   *  While executing the state action, this method may also post 
   *  events to the EventQueue.
   */
  virtual void executeAction(CommandInputHandler * handler);
};
  
} // end namesoace CommandInputState
} // end namesoace iTrek

#endif
