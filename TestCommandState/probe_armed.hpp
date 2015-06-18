/*
 *  probe_armed.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_probe_armed_hpp
#define iTrek_probe_armed_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class probe_armed : public command_state {
 public:
  /** This method adds "armed" to the command, clears the queue, and 
   *  transitions the command state to move_mode if the response to the query 
   *  is "yes". If the response is "no", then this method just clears the queue 
   *  and transitions the command state to move_mode. This method does not 
   *  prompt the use to answer only yes or no as in the original sst. If the 
   *  response cannot be matched to "yes" or "no", then the command is deemed 
   *  an error. In all cases, this method returns handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Arm NOVAMAX warhead? ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
