/*
 *  CommandInputHandler.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef COMMAND_INPUT_HANDLER_HPP
#define COMMAND_INPUT_HANDLER_HPP

#include <boost/shared_ptr.hpp>

#include "CommandInputEvent.hpp"
#include "CommandData.hpp"

namespace iTrek 
{   
  
  // forward declaration of CommandState
  class CommandState;
  
  /** 
   */
  class CommandInputHandler
  {
  public:
    
    /** Initializes the command state and command data. 
     */
    CommandInputHandler();
    
    /** Handles command input events using the command state machine.
     *  The current state is responsible for transitioning the state after
     *  processing the command input. After the command input in the
     *  event has been exhausted, a PromptEvent corresponding to the 
     *  command prompt for the resulting state is posted to the 
     *  EventQueue. While processing the command input, a state may
     *  also post events to the EventQueue.
     */
    void operator()();
    
  private:
    
    /** CommandState is a friend of this class so that it
     *  can call changeState() to change the state.
     */
    friend class CommandState;
    
    /// change the CommandState to state
    void changeState( boost::shared_ptr< CommandState > state ) { state_ = state; }
    
    /// acessaor for command data
    CommandData & commandData() { return commandData_; }
    
    /// const accessor for command data
    CommandData const& commandData() const { return commandData_; }
    
    /** CommandInputHandler has pointer to the current CommandState
     *  object. This should be a smart pointer (or we must explicitly
     *  manage its destruction on transitions) if the states are not
     *  Singletons.
     */
    boost::shared_ptr< CommandState > state_;
    
    /// maintain the command data
    CommandData commandData_;
  };
  
} // end namesoace iTrek

#endif
