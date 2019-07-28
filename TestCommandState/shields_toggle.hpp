/*
 *  shields_toggle.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_shields_toggle_hpp
#define iTrek_shields_toggle_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class shields_toggle : public command_state {
 public:
  /** This method toggles the shields game state if the command input is 
   *  "yes" and ignores the command if the command input is "no". If the 
   *  command input is "yes" this method completes the command and returns 
   *  true. This method does not prompt the use to answer only yes or no as 
   *  in the original sst. If the response cannot be matched to "yes" or 
   *  "no", then the command is deemed an error.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
