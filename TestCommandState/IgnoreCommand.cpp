/*
 *  IgnoreCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "IgnoreCommand.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek { namespace CommandInputState
{
  
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createIgnoreCommandState()
    {
      return boost::shared_ptr< CommandState >( new IgnoreCommand() );
    }
    // Define the identifier
    const std::string IgnoreCommandStateID( "_ignorecmd" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( IgnoreCommandStateID, createIgnoreCommandState );
  }
  
  void IgnoreCommand::executeAction( CommandInputHandler * handler )
  {
    // clear command data
    CommandState::clearCommandData( handler );
    // clear command queue
    CommandState::clearCommandQueue();
    // transition the command state back to getcmd
    CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_getcmd" ) );
  }
  
} } // end namespace iTrek::CommandInputState
