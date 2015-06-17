/*
 *  srscan_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/17/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "srscan_command.hpp"
#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_srscan_command_state() {
  return new srscan_command();
}
// Define the identifier
const std::string srscan_command_state_id("srscan");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    srscan_command_state_id, create_srscan_command_state);

}

boost::logic::tribool srscan_command::handle(command_input_handler* handler) const {
  // add the command name "phasers" to command data
  append_command_data(handler, "srscan");
  // see if there is another token matching no or chart
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data next_cmd = tokens[0];
  if (is_partial_match("no", next_cmd) || is_partial_match("chart", next_cmd)) {
    // only add to command if "no" or "chart"; otherwise ignore
    append_command_data(handler, next_cmd);
  }
  // clear token queue
  clear_token_queue(handler);
  // transition the command state to get_command
  change_state(handler, boost::shared_ptr<command_state>(
     command_state_factory::instance().create_command_state("_getcmd")));
  // command is complete so return true
  return true;
}

} // end namespace command_input_state
} // end namespace iTrek
