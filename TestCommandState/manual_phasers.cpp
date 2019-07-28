/*
 *  manual_phasers.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "manual_phasers.hpp"

#include "command_state_factory.hpp"
#include "global_state.hpp"
#include "command_input_utilities.hpp"
#include "manual_phaser_units.hpp"

#include <iostream>

namespace iTrek { 
namespace command_input_state {
    
namespace {

// Factory method to create the concrete command_state object
command_state* create_manual_phasers_state() {
  return new manual_phasers();
}
// Define the identifier
const std::string manual_phasers_state_id("_manual_phasers");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    manual_phasers_state_id, create_manual_phasers_state);

}
  
// @todo: need to understand different command options (especially "no")
boost::logic::tribool manual_phasers::handle(command_input_handler* handler) const {
  if (nenhere == 0) {
    // if no enemies, transition to automatic_phasers
    // clear the command token queue first
    clear_token_queue(handler);
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_automatic_phasers")));
  } else {
    // peek at next command on queue to see if it is the optional no
    command_data next_cmd = peek_at_token_queue(handler);
    // if next_cmd is no, then get this command and add to command data
    if (is_partial_match("no", next_cmd)) {
      command_inputs tokens;
      get_command_inputs(handler, 1, tokens);
      append_command_data(handler, tokens[0]);
    }    
    change_state(handler, boost::shared_ptr<manual_phaser_units>(
      new manual_phaser_units(1, nenhere)));
  }
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;  
}
  
} // end namespace command_input_state
} // end namespace iTrek
