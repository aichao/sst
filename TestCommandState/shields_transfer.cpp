/*
 *  shields_transfer.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "shields_transfer.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_shields_transfer_state() {
  return new shields_transfer();
}
// Define the identifier
const std::string shields_transfer_state_id("_shields_transfer");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    shields_transfer_state_id, create_shields_transfer_state);

}

boost::logic::tribool shields_transfer::handle(command_input_handler* handler) const {
  // get the answer to the query
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data amount = tokens[0];
  if (amount.empty()) return false;

  if (is_number(amount)) {
    append_command_data(handler, amount);
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // return true (complete)
    return true;    
  }
  // else this is a command error
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_cmderr")));
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
