/*
 *  ExecuteCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "ExecuteCommand.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek { namespace CommandInputState
{
    
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createExecuteCommandState()
    {
      return boost::shared_ptr< CommandState >( new ExecuteCommand() );
    }
    // Define the identifier
    const std::string ExecuteCommandStateID( "_execmd" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( ExecuteCommandStateID, createExecuteCommandState );
  }
  
  void ExecuteCommand::executeAction( CommandInputHandler * handler )
  {
    // construct display message stating command execution
    std::string displayMsg( std::string("Executing command: ") + CommandState::getCommandData( handler ) + '\n' );
    // insert DisplayEvent onto EventQueue
    CommandState::addDisplayEvent( displayMsg );
    // clear command data
    CommandState::clearCommandData( handler );
    // clear command queue
    CommandState::clearCommandQueue();
    // transition the command state back to getcmd
    CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_getcmd" ) );
  }
    
} } // end namespace iTrek::CommandInputState
