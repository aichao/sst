/*
 *  photon_target_sector.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "photon_target_sector.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "command_state_factory.hpp"
#include "global_state.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

photon_target_sector::photon_target_sector(unsigned i_tgt, unsigned n_tgts)
    : i_tgt_(i_tgt), n_tgts_(n_tgts) {}

boost::logic::tribool photon_target_sector::handle(command_input_handler* handler) const {
  // Pop sector coordinate input from the command token queue
  command_inputs tokens;
  get_command_inputs(handler, 2, tokens);
  // If there is only one token, then check for error conditions
  if (tokens.size() < 2U) {
    // see if single token is empty.
    if (tokens[0].empty()) {
      // this is the case when the queue is empty, but we expect input
      // return false to signal need for prompt
      return false;
    } else {
      // this is the case when there is just an odd number of tokens, and this is an error
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_cmderr")));
      return handled_but_incomplete;
    }
  }
  // both tokens need to be numbers, if not this is an error
  if (!is_number(tokens[0]) || !is_number(tokens[1])) {
    // transition to command error state
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
    return handled_but_incomplete;
  }
  
  // lexical_cast each token to double. (this should always succeed)
  double ySect = boost::lexical_cast<double>(tokens[0]);
  double xSect = boost::lexical_cast<double>(tokens[1]);
  // see if target sector is in range [ 1, 10 ].
  if (xSect < MIN_SECTOR_X || xSect > MAX_SECTOR_X || 
      ySect < MIN_SECTOR_Y || ySect > MAX_SECTOR_Y) {
    // If not, transition to ignore command state
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  } else {
    append_command_data(handler, tokens[0] + " " + tokens[1]);
    // check to see if all targets have been handled
    if (i_tgt_ == n_tgts_) {
      // clear token queue
      clear_token_queue(handler);
      // transition the command state to get_command
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_getcmd")));
      // subtract the number requested from the number available, note this is for simulation only
      // @todo: remove this later.
      torps -= n_tgts_;
      // return true (complete)
      return true;    
    }
    // if not, go to the next target
    change_state(handler, boost::shared_ptr<photon_target_sector>(
        new photon_target_sector(++i_tgt_, n_tgts_)));
  }
  // return handled_but_incomplete unless complete
  return handled_but_incomplete;
}

boost::optional<std::string> photon_target_sector::prompt() const {
  std::ostringstream prompt_sstrm;
  prompt_sstrm << "Target sector for torpedo number " << i_tgt_ << "- ";
  return prompt_sstrm.str();
}

} // end namespace command_input_state
} // end namespace iTrek
