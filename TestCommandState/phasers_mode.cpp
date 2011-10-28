/*
 *  phasers_mode.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "phasers_mode.hpp"

#include "CommandStateFactory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { 
namespace CommandInputState {
  
namespace {
// Factory method to create the ConcreteCommandState object
boost::shared_ptr<CommandState> create_phasers_mode_state() {
  return boost::shared_ptr<CommandState>(new phasers_mode());
}
// Define the identifier
const std::string phasers_mode_state_id("_phasers_mode");
// Register
const bool registered = CommandStateFactory::instance().registerCommandState(phasers_mode_state_id, create_phasers_mode_state);
}
  
void phasers_mode::executeAction(CommandInputHandler * handler) {
  CommandInputs tokens;
  getCommandInputs(1, tokens);
  CommandData mode = tokens[0];
  // append to command data, if error, command data will be cleared anyways
  CommandState::appendCommandData(handler, mode);
  
  if (is_partial_match("manual", mode)) {
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_manual_phasers"));
  } else if (is_partial_match("automatic", mode)) {
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_automatic_phasers"));
  } else {
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_cmderr"));
  }
}

std::string phasers_mode::getPrompt() const {
  return "Manual or automatic? ";
}
  
} // end namespace CommandInputState
} // end namespace iTrek
