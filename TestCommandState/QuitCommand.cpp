/*
 *  QuitCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "QuitCommand.hpp"
#include "CommandStateFactory.hpp"
#include "CommandInputHandler.hpp"
#include "EventQueue.hpp"
#include "ExitEvent.hpp"

namespace iTrek { namespace CommandInputState
{
    
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createQuitCommandState()
    {
      return boost::shared_ptr< CommandState >( new QuitCommand() );
    }
    // Define the identifier
    const std::string QuitCommandStateID( "quit" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( QuitCommandStateID, createQuitCommandState );
  }
    
  void QuitCommand::executeAction( CommandInputHandler * handler )
  {
    // Insert an ExitEvent in the Event queue to terminate the program from the main thread.
    // lock the EventQueue first
    {
      boost::lock_guard< EventQueue::object_type > lock( EventQueue::instance() );
      EventQueue::instance().push( boost::shared_ptr< Event >( new ExitEvent() ) );
    }
    // Can be called outside scope of lock
    EventQueue::instance().signal();      
    // Throw boost::thread_interrupted to stop execution of this thread.
    throw boost::thread_interrupted();
  }
    
} } // end namespace iTrek::CommandInputState
