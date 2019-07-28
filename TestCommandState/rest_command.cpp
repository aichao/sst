/*
 *  rest_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "rest_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_rest_command_state() {
  return new rest_command();
}
// Define the identifier
const std::string rest_command_state_id("rest");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    rest_command_state_id, create_rest_command_state);

}

boost::logic::tribool rest_command::handle(command_input_handler* handler) const {
  // add the command name "rest" to command data
  append_command_data(handler, "rest");
  // transition to the _rest_duration state
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_rest_duration")));
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
