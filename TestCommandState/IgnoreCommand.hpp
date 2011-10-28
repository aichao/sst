/*
 *  IgnoreCommand.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef IGNORE_COMMAND_HPP
#define IGNORE_COMMAND_HPP

#include "CommandState.hpp"

namespace iTrek { namespace CommandInputState
{   
  
  /** 
   */
  class IgnoreCommand : public CommandState
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
