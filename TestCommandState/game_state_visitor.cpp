/*
 *  game_state_visitor.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/28/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "game_state_visitor.hpp"

#include "global_state.hpp"
#include "command_input_handler.hpp"
#include "command_state_factory.hpp"
#include "command_state.hpp"
#include "phasers_command.hpp"

namespace iTrek {

boost::logic::tribool game_state_visitor::visit_phaser(
    command_input_state::phaser_command const& cmd,
    command_input_handler& handler) {
  // if docked, say so and ignore command
  if (condit == IHDOCKED) {
    handler.add_display_event("Phasers can't be fired through base shields.");
    handler.change_state(boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  }
  // if phasers are damaged, say so and ignore command
  if (damage[DPHASER] != 0) {
    handler.add_display_event("Phaser control damaged.");
    handler.change_state(boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  }
  // if shields are up and shields are damaged or energy is insufficient to
  // activiate high speed shield control, say so and ignore command
  if ( shldup ) {
    if ( damage[DSHCTRL] ) {
      handler.add_display_event("High speed shield control damaged.");
      handler.change_state(boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_ignorecmd")));
    }
    if ( energy <= 200.0 ) {
      handler.add_display_event(
          "Insufficient energy to activate high-speed shield control.");
      handler.change_state(boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_ignorecmd")));
    }
    // else display message for enabling high speed shield control
    handler.add_display_event(
        "Weapons Officer Sulu-  \"High-speed shield control enabled, sir.\"");
  }
  return handled_but_incomplete;
}

} // end namesoace iTrek
