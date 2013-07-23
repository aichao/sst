/*
 *  ignore_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_ignore_command_hpp
#define iTrek_ignore_command_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   
  
/** 
 */
class ignore_command : public command_state {
 public:
  /** This method clears the token queue and the command data  and then 
   *  transition to the get_command state. This method always return 
   *  handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
