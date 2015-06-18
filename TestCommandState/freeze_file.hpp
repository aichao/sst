/*
 *  freeze_file.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_freeze_file_hpp
#define iTrek_freeze_file_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class freeze_file : public command_state {
 public:
  /** This method processes the next token in the queue and adds it to the 
   *  command as the freeze filename. The command is then complete and this 
   *  method returns true. If there is no token, then this method returns false 
   *  and the prompt is triggered.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("File name: ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
