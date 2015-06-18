/*
 *  help_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "help_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_help_command_state() {
  return new help_command();
}
// Define the identifier
const std::string help_command_state_id("help");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    help_command_state_id, create_help_command_state);

}

boost::logic::tribool help_command::handle(command_input_handler* handler) const {
  // add the command name "help" to command data
  append_command_data(handler, "help");
  // transition to the _help_item state
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_help_item")));
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
