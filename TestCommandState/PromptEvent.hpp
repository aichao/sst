/*
 *  PromptEvent.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/13/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef PROMPT_EVENT_HPP
#define PROMPT_EVENT_HPP

#include <string>

#include "Event.hpp"

namespace iTrek 
{   
  
  /** 
   */
  class PromptEvent : public Event
  {
  public:
      
    /** Constructor sets the prompt message
     */
    PromptEvent( std::string const& prompt );
    
    /** A PromptEvent prompts the user for the next input, 
     *  tokenizes that input, and inserts the tokens into the 
     *  CommandQueue. This action block on the input channel
     *  waiting for input. This action guarantees at least one
     *  token is inserted into the CommandQueue. If the input
     *  contains no valid okens, then a special NULL token is 
     *  inserted into the CommandQueue.
     */
    void operator()();
  
  private:
    
    std::string prompt_;
  };
  
} // end namesoace iTrek

#endif
