/*
 *  game_state_visitor.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/28/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_game_state_visitor_hpp
#define iTrek_game_state_visitor_hpp

#include <boost/logic/tribool.hpp>

namespace iTrek {
namespace command_input_state {

class phaser_command;

} // end namespace command_input_state

class command_input_handler;

class game_state_visitor {
 public:
  // @todo_NOW: constructor should initialize the global state object

  boost::logic::tribool visit_phaser(
      command_input_state::phaser_command const& cmd,
      command_input_handler& handler);

 private:
  // @todo_NOW: add reference to global state object
};

} // end namesoace iTrek

#endif
