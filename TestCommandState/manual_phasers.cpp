/*
 *  manual_phasers.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "manual_phasers.hpp"

#include "CommandStateFactory.hpp"
#include "GlobalState.hpp"
#include "command_input_utilities.hpp"
#include "manual_phaser_units.hpp"

#include <iostream>

namespace iTrek { 
namespace CommandInputState {
    
namespace {
// Factory method to create the ConcreteCommandState object
boost::shared_ptr<CommandState> create_manual_phasers_state() {
  return boost::shared_ptr<CommandState>(new manual_phasers());
}
// Define the identifier
const std::string manual_phasers_state_id("_manual_phasers");
// Register
const bool registered = CommandStateFactory::instance().registerCommandState(manual_phasers_state_id, create_manual_phasers_state);
}
  
// @todo: need to understand different command options (especially "no")
void manual_phasers::executeAction(CommandInputHandler * handler) {
  if (nenhere == 0) {
    // if no enemies, transition to automatic_phasers
    // clear CommandQueue first
    CommandState::clearCommandQueue();
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_automatic_phasers"));          
  } else {
    // peek at next command on queue to see if it is the optional no
    CommandData next_cmd = CommandState::peekAtCommandQueue();
    // if nextCmd is no, then get this command and add to command data
    if (is_partial_match("no", next_cmd)) {
      CommandInputs tokens;
      getCommandInputs(1, tokens);
      CommandState::appendCommandData(handler, tokens[0]);
    }    
    CommandState::changeState(handler, boost::shared_ptr<manual_phaser_units>(
      new manual_phaser_units(1, nenhere)));
  }
}
  
} // end namespace CommandInputState
} // end namespace iTrek
