/*
 *  warp_factor.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/17/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_warp_factor_hpp
#define iTrek_warp_factor_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class warp_factor : public command_state {
 public:
  /** This method processes the next command in the queue and checks if it is 
   *  numeric. If it is, then the command is complete and this method returns 
   *  true. If it is not, then the state is tranitioned to the command error 
   *  state and this method returns handled_but_incomplete. If the command 
   *  queue is empty, then this method returns false and the prompt is 
   *  triggered.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Warp factor- ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
