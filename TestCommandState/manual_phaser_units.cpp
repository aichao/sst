/*
 *  manual_phaser_units.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/23/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "manual_phaser_units.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "command_state_factory.hpp"
#include "global_state.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { 
namespace command_input_state {
  
// @todo: tgt_energy_ computation is more complex than this
manual_phaser_units::manual_phaser_units(unsigned i_tgt, unsigned n_tgts)
    : i_tgt_(i_tgt), n_tgts_(n_tgts),
      loc_(target_location(kx[i_tgt_], ky[i_tgt_])), 
      tgt_energy_(compute_phaser_kill_energy(i_tgt_)),
      tgt_type_(get_object_type(quad[loc_.first][loc_.second])) {
}
    
boost::logic::tribool manual_phaser_units::handle(command_input_handler* handler) const {
  // Pop a value from the token queue
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data value = tokens[0];
  // if value is empty, not a number or a number <= 0,
  // return false to signal that input cannot be handled
  if (value.empty() || !is_number(value) || 
      boost::lexical_cast<double>(value) <= 0.) {
    clear_token_queue(handler);
    return false;    
  }
  append_command_data(handler, value);
  // check to see if all targets have been handled
  if (i_tgt_ == n_tgts_) {
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // return true (complete)
    return true;    
  }
  // if not, go to the next target
  change_state(handler, boost::shared_ptr<manual_phaser_units>(
      new manual_phaser_units(++i_tgt_, n_tgts_)));
  return handled_but_incomplete;
}

boost::optional<std::string> manual_phaser_units::prompt() const {
  std::ostringstream prompt_sstrm;
  prompt_sstrm << "(" << tgt_energy_ << ")  units to fire at " 
               << tgt_type_ << " at Sector " << loc_.first 
               << " - " << loc_.second << "- ";
  return boost::optional<std::string>(prompt_sstrm.str());
}
  
} // end namespace command_input_state
} // end namespace iTrek
