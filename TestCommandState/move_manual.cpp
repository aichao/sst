/*
 *  move_manual.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "move_manual.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_move_manual_state() {
  return new move_manual();
}
// Define the identifier
const std::string move_manual_state_id("_move_manual");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    move_manual_state_id, create_move_manual_state);

}

boost::logic::tribool move_manual::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 2, tokens);
  command_data dx = tokens[0];
  if (dx.empty()) return false;

  // check to see if dx is a number, if it is, then append dx to the command
  // data, else transition to cmderr
  if (is_number(dx)) {
    append_command_data(handler, dx);
    if (tokens.size() < 2) {
      command_data dy("0.0");
      append_command_data(handler, dy);
      // clear token queue
      clear_token_queue(handler);
      // transition the command state to get_command
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_getcmd")));
      // return true (complete)
      return true;    
    } else if (is_number(tokens[1])) {
      append_command_data(handler, tokens[1]);
      // clear token queue
      clear_token_queue(handler);
      // transition the command state to get_command
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_getcmd")));
      // return true (complete)
      return true;
    }
  }
  // else we have an error in the input
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_cmderr")));
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
