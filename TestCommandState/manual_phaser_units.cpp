/*
 *  manual_phaser_units.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/23/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "manual_phaser_units.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "CommandStateFactory.hpp"
#include "GlobalState.hpp"

namespace iTrek { 
namespace CommandInputState {
  
// @todo: tgt_energy_ computation is more complex than this
manual_phaser_units::manual_phaser_units(unsigned i_tgt, unsigned n_tgts)
    : i_tgt_(i_tgt), n_tgts_(n_tgts),
      loc_(target_location(kx[i_tgt_], ky[i_tgt_])), 
      tgt_energy_(compute_phaser_kill_energy(i_tgt_)),
      tgt_type_(get_object_type(quad[loc_.first][loc_.second])) {
}
    
void manual_phaser_units::executeAction(CommandInputHandler * handler) {
  // Pop a value from the queue
  CommandInputs tokens;
  getCommandInputs(1, tokens);
  // try to cast it to double
  try {
    double value = boost::lexical_cast<double>(tokens[0]);
    // if value is positive, append it to the command data
    if (value > 0.) {
      CommandState::appendCommandData(handler, tokens[0]);
      if (i_tgt_ == n_tgts_) {
        CommandState::changeState(handler, CommandStateFactory::instance().createCommandState("_execmd"));
      } else {
        CommandState::changeState(handler, boost::shared_ptr<manual_phaser_units>(new manual_phaser_units(++i_tgt_, n_tgts_)));        
      }
    } else {
      // else transition back to this state to try again
      CommandState::changeState(handler, boost::shared_ptr<manual_phaser_units>(new manual_phaser_units(*this)));
    }
  } catch (boost::bad_lexical_cast &) {
    // If fail, catch exception and transition back to this state to try again
    CommandState::changeState(handler, boost::shared_ptr<manual_phaser_units>(new manual_phaser_units(*this)));
  }
}

std::string manual_phaser_units::getPrompt() const {
  std::ostringstream PromptStr;
  PromptStr << "(" << tgt_energy_ << ")  units to fire at " << tgt_type_ << " at Sector " << loc_.first << " - " << loc_.second << "- ";
  return PromptStr.str();
}
  
} // end namespace CommandInputState
} // end namespace iTrek
