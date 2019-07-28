/*
 *  move_mode.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "move_mode.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_move_mode_state() {
  return new move_mode();
}
// Define the identifier
const std::string move_mode_state_id("_move_mode");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    move_mode_state_id, create_move_mode_state);

}

boost::logic::tribool move_mode::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data mode = tokens[0];
  if (mode.empty()) return false;

  // append to command data, if error, command data will be cleared anyways
  append_command_data(handler, mode);

  if (is_partial_match("manual", mode)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_move_manual")));
  } else if (is_partial_match("automatic", mode)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_move_automatic")));
  } else {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
  }
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
