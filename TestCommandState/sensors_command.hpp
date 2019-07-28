/*
 *  sensors_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_sensors_command_hpp
#define iTrek_sensors_command_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   

/** 
 */
class sensors_command : public command_state {
 public:
  /** This method adds the input token to the command data, clears the token 
   *  queue, and transitions to the get_command state. This method always 
   *  return true because the input token is the completed command.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
