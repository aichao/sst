/*
 *  move_automatic.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "move_automatic.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

  // Factory method to create the concrete command_state object
  command_state* create_move_automatic_state() {
    return new move_automatic();
  }
  // Define the identifier
  const std::string move_automatic_state_id("_move_automatic");
  // Register
  const bool registered = command_state_factory::instance().register_command_state(
      move_automatic_state_id, create_move_automatic_state);

}

boost::logic::tribool move_automatic::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 4, tokens);
  command_data dx = tokens[0];
  if (dx.empty()) return false;

  // check to see if there are four or two tokens, else transition to cmderr
  if (tokens.size() == 4) {
    if (is_integer(tokens[0]) &&
        is_integer(tokens[1]) &&
        is_integer(tokens[2]) &&
        is_integer(tokens[3])) {
      append_command_data(handler, tokens[0]);
      append_command_data(handler, tokens[1]);
      append_command_data(handler, tokens[2]);
      append_command_data(handler, tokens[3]);
      // clear token queue
      clear_token_queue(handler);
      // transition the command state to get_command
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_getcmd")));
      // return true (complete)
      return true;
    }
  } else if (tokens.size() == 2) {
    if (is_integer(tokens[0]) &&
        is_integer(tokens[1])) {
      append_command_data(handler, tokens[0]);
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
