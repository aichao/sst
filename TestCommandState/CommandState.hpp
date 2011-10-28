/*
 *  CommandState.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef COMMAND_STATE_HPP
#define COMMAND_STATE_HPP

#include <string>

#include <boost/shared_ptr.hpp>

#include "CommandData.hpp"
#include "CommandInputs.hpp"

namespace iTrek 
{   
  
  // forward declaration of CommandInputHandler
  class CommandInputHandler;
  
  /** 
   */
  class CommandState
  {
  public:
    
    /** base class needs a virtual destructor
     */
    virtual ~CommandState() {}
    
    /** Interface to execute the state action. State specific processing
     *  is implemented in the derived class. This method is responsible 
     *  for transitioning the state after executing the state action. 
     *  While executing the state action, this method may also post 
     *  events to the EventQueue.
     */
    virtual void executeAction( CommandInputHandler * handler ) = 0;
    
  protected:
      
    /** Change the CommandState to state. This is called by the subclass to transition 
     *  the state.
     */
    void changeState( CommandInputHandler * handler, boost::shared_ptr< CommandState > state ) const;
      
    /// Const accessor for the command data
    CommandData const& getCommandData( CommandInputHandler * handler ) const;
    
    /** Append the command data. This is called by the concrete state to append its processed 
     *  input data to the command data.
     */
    void appendCommandData( CommandInputHandler * handler, CommandData const& data ) const;
    
    /** Clear the command data. This is called by the concrete command stste to reset the 
     *  command data to empty.
     */
    void clearCommandData( CommandInputHandler * handler ) const;
    
    /// Clear the CommandQueue
    void clearCommandQueue() const;
    
    /** Peek at the next element in the CommandQueue. If the CommandQueue is empty, the
     *  returned CommandData is empty
     */
    CommandData peekAtCommandQueue() const;
    
    /** Get a specified number of command data tokens from the command queue. If the command
     *  queue is empty, this method first inserts a prompt event onto the event queue using 
     *  the state's prompt message. Then it waits on the cmomand queue for inputs. This method
     *  is guaranteed to return with at least one token, even if that token is an empty string.
     *  This method can return less than the requested number of tokens if the command queue 
     *  does not have the requested number of tokens. This usually results from an error in 
     *  comand input, which is to be handled by the concrete state. Furthermore, the command 
     *  queue can have more tokens than requested in the queue. In this case, only the specified
     *  number is popped from the queue and returned. This method should only be called by 
     *  concrete states that requires command data from the command queue.
     */
    virtual void getCommandInputs( std::size_t n, CommandInputs & tokens ) const;
    
    /// Add a DisplayEvent to the EventQueue with the message.
    void addDisplayEvent( std::string const& msg ) const;
    
  };
  
} // end namesoace iTrek

#endif
