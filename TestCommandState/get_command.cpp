/*
 *  get_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "get_command.hpp"
#include "command_data.hpp"
#include "command_state_factory.hpp"

namespace iTrek { 
namespace command_input_state {
  
namespace {
  
// Factory method to create the concrete command_state object
command_state* create_get_command_state() {
  return new get_command();
}
// Define the identifier
const std::string get_command_state_id("_getcmd");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    get_command_state_id, create_get_command_state);
  
}

boost::logic::tribool get_command::handle(command_input_handler* handler) const {
  // Pop command name input from the CommandQueue
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data command_name = tokens[0];
  // if command_name is the eempty string, then the token queue was empty,
  // therefore return false to indicate the need for more user input
  if (command_name.empty()) return false;
  // see if it is a valid command, match command name up to the number of characters 
  // in command_name, and returns the next state object corresponding to the command 
  // name.
  boost::shared_ptr<command_state> next_state(
      command_state_factory::instance().create_command_state(command_name));
  // if invalid (return NULL pointer to CommandState), set the next state to the 
  // command error state
  if (next_state.get() == NULL) {
    next_state = boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr"));
  }
  // transition to the next state
  change_state(handler, next_state);
  // return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
