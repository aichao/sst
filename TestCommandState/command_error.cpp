/*
 *  command_error.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "command_error.hpp"
#include "command_state_factory.hpp"

namespace iTrek { 
namespace command_input_state {
    
namespace {
  
// Factory method to create the concrete command_state object
command_state* create_command_error_state() {
  return new command_error();
}
// Define the identifier
const std::string command_error_state_id("_cmderr");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    command_error_state_id, create_command_error_state);
  
}
  
boost::logic::tribool command_error::handle(command_input_handler* handler) const {
  // construct display message stating command execution
  std::string display_msg("Beg your pardon, Captain?\n");
  // add display message as an event on the display queue
  add_display_event(handler, display_msg);
  // transition the command state to _ignorecmd
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_ignorecmd")));
  // this state always return handled_but_incomplete
  return handled_but_incomplete;
}
  
} // end namespace command_input_state
} // end namespace iTrek
