/*
 *  phasers_mode.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_phasers_mode_hpp
#define iTrek_phasers_mode_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   

/** 
 */
class phasers_mode : public command_state {
 public:
  /** This method .... 
   *  This method always return handled_but_incomplete.
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
