/*
 *  rest_duration.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "rest_duration.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_rest_duration_state() {
  return new rest_duration();
}
// Define the identifier
const std::string rest_duration_state_id("_rest_duration");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    rest_duration_state_id, create_rest_duration_state);

}

boost::logic::tribool rest_duration::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data duration = tokens[0];
  if (duration.empty()) return false;

  if (is_number(duration)) {
    // append to command data
    append_command_data(handler, duration);
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // return true (complete)
    return true;
  }
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_cmderr")));
  return handled_but_incomplete;      
}

} // end namespace command_input_state
} // end namespace iTrek
