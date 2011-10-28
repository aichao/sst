/*
 *  PromptCommandState.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef PROMPT_COMMAND_STATE_HPP
#define PROMPT_COMMAND_STATE_HPP

#include "CommandState.hpp"

namespace iTrek 
{   
  
  /** 
   */
  class PromptCommandState : public CommandState
  {
  public:
    
    /** base class needs a virtual destructor
     */
    virtual ~PromptCommandState() {}
    
    /** Interface to execute the state action. State specific processing
     *  is implemented in the derived class. This method is responsible 
     *  for transitioning the state after executing the state action. 
     *  While executing the state action, this method may also post 
     *  events to the EventQueue.
     */
    virtual void executeAction( CommandInputHandler * handler ) = 0;
    
    /** Interface to return the prompt corresponding to the state. State 
     *  specific prompt is implemented in the derived class.
     */
    virtual std::string getPrompt() const = 0;
    
  protected:
        
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
    
  };
  
} // end namesoace iTrek

#endif
