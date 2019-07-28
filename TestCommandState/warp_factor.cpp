/*
 *  warp_factor.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "warp_factor.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_warp_factor_state() {
  return new warp_factor();
}
// Define the identifier
const std::string warp_factor_state_id("_warp_factor");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    warp_factor_state_id, create_warp_factor_state);

}

boost::logic::tribool warp_factor::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data factor = tokens[0];
  if (factor.empty()) return false;

  if (is_number(factor)) {
    // append to command data
    append_command_data(handler, factor);
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
