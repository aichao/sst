/*
 *  shields_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "shields_command.hpp"
#include "command_state_factory.hpp"
#include "global_state.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_shields_command_state() {
  return new shields_command();
}
// Define the identifier
const std::string shields_command_state_id("shields");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    shields_command_state_id, create_shields_command_state);

}

boost::logic::tribool shields_command::handle(command_input_handler* handler) const {
  // add the command name "phasers" to command data
  append_command_data(handler, "shields");
  // see if there is another token matching up or down or transfer
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data next_cmd = tokens[0];
  if (is_partial_match("up", next_cmd) || is_partial_match("down", next_cmd)) {
    append_command_data(handler, next_cmd);
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // AIC_DEBUG: simulate change in game state
    shldup = is_partial_match("up", next_cmd) ? 1 : 0;
    // command is complete so return true
    return true;
  } else if (is_partial_match("transfer", next_cmd)) {
    append_command_data(handler, next_cmd);
    // transition to the _shields_transfer state
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_shields_transfer")));
  } else {
    // clear token queue
    clear_token_queue(handler);
    // transition to the _shields_query state
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_shields_query")));
    return false;
  }
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
