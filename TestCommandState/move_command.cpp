/*
 *  move_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "move_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_move_command_state() {
  return new move_command();
}
// Define the identifier
const std::string move_command_state_id("move");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    move_command_state_id, create_move_command_state);

}

boost::logic::tribool move_command::handle(command_input_handler* handler) const {
  // add the command name "move" to command data
  append_command_data(handler, "move");
  // transition to the _move_mode state
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_move_mode")));
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
