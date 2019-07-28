/*
 *  move_mode.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_move_mode_hpp
#define iTrek_move_mode_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class move_mode : public command_state {
public:
  /** This method processes the next command in the queue and transitions the 
   *  state in accordance to the input movement mode "manual" or "automatic". 
   *  If the input does not match these, then the state is tranitioned to the 
   *  command error state. If the command queue is empty, then this method 
   *  returns false and the prompt is triggered. Otherwise, this method returns 
   *  handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Manual or automatic? ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
