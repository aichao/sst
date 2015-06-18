/*
 *  help_item.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_help_item_hpp
#define iTrek_help_item_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/** @todo: in order to replicate the behavior in sst, the game needs to 
 *  transition the command state to this state in order to reprompt the user 
 *  if the input is not a valid command to get help on.
 */
class help_item : public command_state {
 public:
  /** This method processes the next token in the queue and adds it to the
   *  command as the help item. The command is then complete and this
   *  method returns true. If there is no token, then this method returns false
   *  and the prompt is triggered.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Help on what command? ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
