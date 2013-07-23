/*
 *  automatic_phaser_units.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "automatic_phaser_units.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { 
namespace command_input_state {
  
namespace {

// Factory method to create the concrete command_state object
command_state* create_automatic_phaser_units_state() {
  return new automatic_phaser_units();
}
// Define the identifier
const std::string automatic_phaser_units_state_id("_automatic_phaser_units");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    automatic_phaser_units_state_id, create_automatic_phaser_units_state);

}

boost::logic::tribool automatic_phaser_units::handle(command_input_handler* handler) const {
  // peek at next command on queue to see if it is the optional no
  command_data next_cmd = peek_at_token_queue(handler);
  // if it is empty, return false to signal need for prompt
  if (next_cmd.empty()) return false;
  // if next_cmd is no, then get this command and add to command data
  if (is_partial_match("no", next_cmd)) {
    // @todo: need to handle the case where the user just enter 'no', which is an error case and should be ignored
    command_inputs tokens;
    get_command_inputs(handler, 1, tokens);
    append_command_data(handler, tokens[0]);
  }
  // we can still have two tokens on the queue since it can be: value 'no'
  command_inputs tokens;
  get_command_inputs(handler, 2, tokens);
  if (is_number(tokens[0])) {
    append_command_data(handler, tokens[0]);
    // see if we have another token and it is 'no'
    if (tokens.size() == 2 && is_partial_match("no", tokens[1])) {
      append_command_data(handler, tokens[1]);
    }
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // return true (complete)
    return true;    
  }
  // else, clear the command token queue and return false to signal need for prompt
  clear_token_queue(handler);
  return false;
}

} // end namespace command_input_state
} // end namespace iTrek
