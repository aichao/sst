/*
 *  move_automatic.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_move_automatic_hpp
#define iTrek_move_automatic_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class move_automatic : public command_state {
public:
  /** This method ....
   *  This method returns handled_but_incomplete if the mode is already in the
   *  queue; otherwise it returns false.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Destination sector or quadrant&sector- ");
  }
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
