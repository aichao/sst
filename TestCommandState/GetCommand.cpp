/*
 *  GetCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "GetCommand.hpp"
#include "CommandData.hpp"
#include "CommandQueue.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek { namespace CommandInputState
{
  
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createGetCommandState()
    {
      return boost::shared_ptr< CommandState >( new GetCommand() );
    }
    // Define the identifier
    const std::string GetCommandStateID( "_getcmd" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( GetCommandStateID, createGetCommandState );
  }

  void GetCommand::executeAction( CommandInputHandler * handler )
  {
    // Pop command name input from the CommandQueue
    CommandInputs tokens;
    getCommandInputs( 1, tokens );
    CommandData commandName = tokens[0];
    
    // see if it is a valid command, match command name up to the number of characters in commandName, 
    // and returns the next state object corresponding to the command name.
    boost::shared_ptr< CommandState > nextState = CommandStateFactory::instance().createCommandState( commandName );
    // if invalid (return NULL pointer to CommandState), set the next state to the command error state
    if ( nextState.get() == NULL )
      nextState = CommandStateFactory::instance().createCommandState( "_cmderr" );
    // transition to the next state
    CommandState::changeState( handler, nextState );
  }
  
  std::string GetCommand::getPrompt() const
  {
    return "COMMAND> ";
  }

} } // end namespace iTrek::CommandInputState
