/*
 *  CommandError.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "CommandError.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek { namespace CommandInputState
{
    
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createCommandErrorState()
    {
      return boost::shared_ptr< CommandState >( new CommandError() );
    }
    // Define the identifier
    const std::string CommandErrorStateID( "_cmderr" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( CommandErrorStateID, createCommandErrorState );
  }
    
  void CommandError::executeAction( CommandInputHandler * handler )
  {
    // construct display message stating command execution
    std::string displayMsg( "Beg your pardon, Captain?\n" );
    // insert DisplayEvent onto EventQueue
    CommandState::addDisplayEvent( displayMsg );
    // transition the command state to _ignorecmd
    CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
  }
    
} } // end namespace iTrek::CommandInputState
