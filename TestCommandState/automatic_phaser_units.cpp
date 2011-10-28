/*
 *  automatic_phaser_units.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "automatic_phaser_units.hpp"

#include "CommandStateFactory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { 
namespace CommandInputState {
  
namespace {
// Factory method to create the ConcreteCommandState object
boost::shared_ptr<CommandState> create_automatic_phaser_units_state() {
  return boost::shared_ptr<CommandState>(new automatic_phaser_units());
}
// Define the identifier
const std::string automatic_phaser_units_state_id("_automatic_phaser_units");
// Register
const bool registered = CommandStateFactory::instance().registerCommandState(
  automatic_phaser_units_state_id, create_automatic_phaser_units_state);
}

void automatic_phaser_units::executeAction(CommandInputHandler * handler) {
  // peek at next command on queue to see if it is the optional no
  CommandData next_cmd = CommandState::peekAtCommandQueue();
  // if nextCmd is no, then get this command and add to command data
  if (is_partial_match("no", next_cmd)) {
    CommandInputs tokens;
    getCommandInputs(1, tokens);
    CommandState::appendCommandData(handler, tokens[0]);
  }
  // we can still have two tokens on the queue since it can be: value 'no'
  CommandInputs tokens;
  getCommandInputs(2, tokens);
  if (is_number(tokens[0])) {
    CommandState::appendCommandData(handler, tokens[0]);
    // see if we have another token and it is 'no'
    if (tokens.size() == 2 && is_partial_match("no", tokens[1])) {
      CommandState::appendCommandData(handler, tokens[1]);
    }
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_execmd"));    
  } else {
    // clear the CommandQueue and go back to this state
    CommandState::clearCommandQueue();
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_automatic_phaser_units"));
  }
}

std::string automatic_phaser_units::getPrompt() const {
  return "Units to fire= ";
}
  
} // end namespace CommandInputState
} // end namespace iTrek
