/*
 *  mine_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/14/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "mine_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek { 
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_mine_command_state() {
  return new mine_command();
}
// Define the identifier
const std::string mine_command_state_id("mine");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    mine_command_state_id, create_mine_command_state);

}

boost::logic::tribool mine_command::handle(command_input_handler* handler) const {
  // append the command "mine" to the command data
  append_command_data(handler, "mine");
  // clear token queue
  clear_token_queue(handler);
  // transition the command state to get_command
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_getcmd")));
  // this state always return true (complete)
  return true;
}

} // end namespace command_input_state
} // end namespace iTrek
