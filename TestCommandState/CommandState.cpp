/*
 *  CommandState.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "CommandState.hpp"
#include "CommandInputHandler.hpp"
#include "CommandQueue.hpp"
#include "EventQueue.hpp"
#include "DisplayEvent.hpp"

namespace iTrek
{
  
  void CommandState::changeState( CommandInputHandler * handler, boost::shared_ptr< CommandState > state ) const
  {
    // forwards state to handler
    handler->changeState( state );
  }
  
  CommandData const& CommandState::getCommandData( CommandInputHandler * handler ) const
  {
    return handler->commandData();
  }
  
  void CommandState::appendCommandData( CommandInputHandler * handler, CommandData const& data ) const
  {
    // forwards data to handler
    handler->commandData() += ( handler->commandData().length() == 0 ? data : ( std::string(" ") + data ) ); 
  }
  
  void CommandState::clearCommandData( CommandInputHandler * handler ) const
  {
    handler->commandData() = "";
  }
  
  void CommandState::clearCommandQueue() const
  {
    boost::lock_guard< CommandQueue::object_type > lock( CommandQueue::instance() );
    CommandQueue::instance().clear();    
  }
  
  CommandData CommandState::peekAtCommandQueue() const
  {
    // Lock the CommandQueue first to see if it is empty, if not return front
    boost::lock_guard< CommandQueue::object_type > lock( CommandQueue::instance() );
    if ( !CommandQueue::instance().empty() )
    {
      return CommandQueue::instance().front();
    }
    return CommandData("");
  }
  
  void CommandState::getCommandInputs( std::size_t n, CommandInputs & tokens ) const
  {
    tokens.clear();
    {
      CommandQueue::object_type::wait_lock_t lock( CommandQueue::instance().queueMutex );
      CommandQueue::instance().wait( lock );
      // loop over the n requested tokens or the number of available tokens, which ever is smaler
      n = n < CommandQueue::instance().size() ? n : CommandQueue::instance().size();
      for ( std::size_t i = 0; i < n; ++i )
      {
        tokens.push_back( CommandQueue::instance().front() );
        CommandQueue::instance().pop();
      }
    }
    // if tokens is still empty (queue is empty), insert an empty string
    if (tokens.empty()) tokens.push_back(CommandData(""));
  }
  
  void CommandState::addDisplayEvent( std::string const& msg ) const
  {
    // lock the EventQueue first
    {
      boost::lock_guard< EventQueue::object_type > lock( EventQueue::instance() );
      EventQueue::instance().push( boost::shared_ptr< Event >( new DisplayEvent( msg ) ) );
    }
    // Can be called outside scope of lock
    EventQueue::instance().signal();      
  }
  
} // end namespace iTrek
