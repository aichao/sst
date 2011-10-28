/*
 *  CommandInputHandler.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "CommandInputHandler.hpp"
#include "CommandState.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek
{

  CommandInputHandler::CommandInputHandler()
  : state_( CommandStateFactory::instance().createCommandState( "_getcmd" ) ),
    commandData_( "" )
  {}
  
  void CommandInputHandler::operator()()
  {
    // CommandInputHandler runs in its own thread (detached) and continuously handle 
    // inputs with respect to the command input state machine until the quit command 
    // is input. When the quit command is input, the resulting state will post an exit
    // event on the EventQueue which will call exit() on the main thread and then call
    // boost::thread_interrupted to break out of this infinite loop to terminate the
    // thread.
    while ( 1 )
    {
      // PostConditions: (i) CommandQueue is empty if error encountered for state
      // or full command is executed or all command data in queue has been handled,
      // (ii) state_ is transitioned to next state.
      state_->executeAction( this );
    }
  }
  
} // end namespace iTrek