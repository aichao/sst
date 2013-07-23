/*
 *  ignore_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "ignore_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek { 
namespace command_input_state {
  
namespace {

// Factory method to create the concrete command_state object
command_state* create_ignore_command_state() {
  return new ignore_command();
}
// Define the identifier
const std::string ignore_command_state_id("_ignorecmd");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    ignore_command_state_id, create_ignore_command_state);

}

boost::logic::tribool ignore_command::handle(command_input_handler* handler) const {
  // clear command data
  clear_command_data(handler);
  // clear token queue
  clear_token_queue(handler);
  // transition the command state to get_command
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_getcmd")));
  // this state always return handled_but_incomplete
  return handled_but_incomplete;
}
  
} // end namespace command_input_state
} // end namespace iTrek
