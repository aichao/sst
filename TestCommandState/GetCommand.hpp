/*
 *  GetCommand.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef GET_COMMAND_HPP
#define GET_COMMAND_HPP

#include "PromptCommandState.hpp"

namespace iTrek { namespace CommandInputState
{   
  
  /** 
   */
  class GetCommand : public PromptCommandState
  {
  public:
      
    /** Process command inputs to get the command name. This method pops
     *  the first element from the CommandQueue and checks to see if it 
     *  is a valid command name. If it is a valid command name, the command
     *  data is appended with the command name and the state is transitioned 
     *  to the corresponding entry command processing state for that command
     *  name. If the first element is not a valid command name, the command
     *  inputs and the command data are both cleared and an error message is
     *  pushed onto the EventQueue.
     */
    virtual void executeAction( CommandInputHandler * handler );
      
    /// Return the prompt corresponding to the GetCommand state.
    virtual std::string getPrompt() const;
      
  };
  
} } // end namesoace iTrek::CommandInputState

#endif
