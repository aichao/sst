/*
 *  command_error.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_command_error_hpp
#define iTrek_command_error_hpp

#include "command_state.hpp"

namespace iTrek { 

// forward declaration of command_input_handler
class command_input_handler;

namespace command_input_state {   

/** 
  */
class command_error : public command_state {
 public:
  /** This method adds an error message to the display event indicating
   *  that the input command is in error and then transition to the 
   *  ignore_command state. This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
