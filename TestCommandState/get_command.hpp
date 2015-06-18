/*
 *  get_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_get_command_hpp
#define iTrek_get_command_hpp

#include "command_state.hpp"

namespace iTrek { 
  
// forward declaration of command_input_handler
class command_input_handler;
  
namespace command_input_state {   
  
/** 
 */
class get_command : public command_state {
 public:
  /** Process command inputs to get the command name. This method pops
   *  the first element from the command token queue and checks to see if 
   *  it is a valid command name. If the command name is empty, then this 
   *  method returns false to indicate that more user input is needed. If 
   *  the command names is valid, the command data is appended with the 
   *  command name and the state is transitioned to the corresponding state 
   *  for that command name. If the command name is not empty and not valid, 
   *  the state is transitiond to the command_error state. In both the 
   *  latter two cases, this method returns handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
    
  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("COMMAND> ");
  }  
};
  
} // end namespace command_input_state
} // end namespace iTrek

#endif
