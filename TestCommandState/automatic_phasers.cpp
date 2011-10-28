/*
 *  automatic_phasers.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "automatic_phasers.hpp"

#include "CommandStateFactory.hpp"
#include "GlobalState.hpp"

namespace iTrek { 
namespace CommandInputState {
    
namespace {
// Factory method to create the ConcreteCommandState object
boost::shared_ptr<CommandState> create_automatic_phasers_state() {
  return boost::shared_ptr<CommandState>(new automatic_phasers());
}
// Define the identifier
const std::string automatic_phasers_state_id("_automatic_phasers");
// Register
const bool registered = CommandStateFactory::instance().registerCommandState(automatic_phasers_state_id, create_automatic_phasers_state);
}

void automatic_phasers::executeAction(CommandInputHandler * handler) {
  if ((damage[DCOMPTR] == 0 && damage[DSRSENS] == 0) || nenhere == 0) {
    // if no damage or no enemies, transition to automatic_phaser_units
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_automatic_phaser_units"));      
  } else if (nenhere > 0 && (damage[DCOMPTR] != 0 || damage[DSRSENS] != 0)) {
    // else if enemies and damage to computers or sensors, transition to forced manual_phasers
    // clear CommandQueue first
    CommandState::clearCommandQueue();
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_manual_phasers"));      
  } else {
    // else we have an error in the input, this should never happen
    CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_cmderr"));      
  }
}
    
} // end namespace CommandInputState
} // end namespace iTrek
