/*
 *  PromptCommandState.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "PromptCommandState.hpp"

#include "CommandInputHandler.hpp"
#include "CommandQueue.hpp"
#include "EventQueue.hpp"
#include "PromptEvent.hpp"

namespace iTrek
{
  
  void PromptCommandState::getCommandInputs( std::size_t n, CommandInputs & tokens ) const
  {
    // Check to see if CommandQueue is empty (get lock first). 
    bool commandQueueEmpty;
    // Lock the CommandQueue first
    {
      boost::lock_guard< CommandQueue::object_type > lock( CommandQueue::instance() );
      commandQueueEmpty = CommandQueue::instance().empty();
    }
    // If empty, then insert PromptEvent
    if ( commandQueueEmpty )
    {
      // get prompt from resulting state and insert PromptEvent onto EventQueue
      {
        boost::lock_guard< EventQueue::object_type > lock( EventQueue::instance() );
        EventQueue::instance().push( boost::shared_ptr< Event >( new PromptEvent( getPrompt() ) ) );
      }
      // Can be called outside scope of lock
      EventQueue::instance().signal();      
    }
    // Then wait on the CommandQueue and get inputs from the queue once it is filled. Note that if CommandQueue 
    // was not empty the wait will return immediately. 
    CommandState::getCommandInputs( n, tokens );
  }

} // end namespace iTrek
