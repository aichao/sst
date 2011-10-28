/*
 *  PhasersCommand.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef PHASERS_COMMAND_HPP
#define PHASERS_COMMAND_HPP

#include "CommandState.hpp"

namespace iTrek { namespace CommandInputState
{   
  
  /** 
   */
  class PhasersCommand : public CommandState
  {
  public:
    
    /** Interface to execute the state action. State specific processing
     *  is implemented in the derived class. This method is responsible 
     *  for transitioning the state after executing the state action. 
     *  While executing the state action, this method may also post 
     *  events to the EventQueue.
     */
    virtual void executeAction( CommandInputHandler * handler );
    
  };
  
} } // end namesoace iTrek::CommandInputState

#endif