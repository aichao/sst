/*
 *  phasers_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "phasers_command.hpp"
#include "command_state_factory.hpp"
#include "global_state.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { 
namespace command_input_state {
  
namespace {
  
// Factory method to create the concrete command_state object
command_state* create_phasers_command_state() {
  return new phasers_command();
}
// Define the identifier
const std::string phasers_command_state_id("phasers");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    phasers_command_state_id, create_phasers_command_state);
  
}
  
boost::logic::tribool phasers_command::handle(command_input_handler* handler) const {
  // @todo: this stuff is actually reactions to the command and should be part of
  // ship state, which is part of game state.
  // if docked, say so and ignore command
  if (condit == IHDOCKED) {
    add_display_event(handler, "Phasers can't be fired through base shields.");
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
    return handled_but_incomplete;
  }
  // if phasers are damaged, say so and ignore command
  if (damage[DPHASER] != 0) {
    add_display_event(handler, "Phaser control damaged.");
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
    return handled_but_incomplete;
  }
  // if shields are up and shields are damaged or energy is insufficient to activate
  // high speed shield control, say so and ignore command
  if ( shldup ) {
    if ( damage[DSHCTRL] ) {
      add_display_event(handler, "High speed shield control damaged.");
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_ignorecmd")));
      return handled_but_incomplete;
    }
    if ( energy <= 200.0 ) {
      add_display_event(handler, "Insufficient energy to activate high-speed shield control.");
      change_state(handler, boost::shared_ptr<command_state>(
          command_state_factory::instance().create_command_state("_ignorecmd")));
      return handled_but_incomplete;
    }
    // else display message for enabling high speed shield control
    add_display_event(handler, "Weapons Officer Sulu-  \"High-speed shield control enabled, sir.\"");
  }
  // add the command name "phasers" to command data
  append_command_data(handler, "phasers");
  // transition the command state to execmd
  // @todo: handle case where queue is now empty vs there is more commands on queue
  // This state can look for one input token: The prompt is "Units to fire = "
  // If it is a number, add to command data and check if there is another token on queue that is "no". If there is then add this also. Transition to _execmd
  // If it is "automatic", check to see if there is damage. If not add to command data and maintain this state. If there is damage, go to forced manual
  // If it is "manual", check to see if there are enemies, if so add to command data and transition to _manual_phaser, otherwise display message and maintain this state
  // If it is "no", add to command data and maintain this state
  // Note:
  // mode selected  damage state  enemies  result
  //  automatic      computer     yes       ipoop = 0, forced manual, 
  //  automatic      sensors      yes       ipoop = 0, forced manual,
  //  automatic      both         yes       ipoop = 0, forced manual,
  //  automatic      none         yes      *ipoop = 1, set automatic, get next key
  //  manual         computer     yes       ipoop = 0, set manual, get next key
  //  manual         sensors      yes       ipoop = 0, set manual, get next key, cannot target commanders
  //  manual         both         yes       ipoop = 0, set manual, get next key
  //  manual         none         yes      *ipoop = 1, set manual, get next key
  //  automatic      computer     no        ipoop = 0, display "Energy will be expended into empty space", set automatic, get next key
  //  automatic      sensors      no        ipoop = 0, display "Energy will be expended into empty space", set automatic, get next key
  //  automatic      both         no        ipoop = 0, display "Energy will be expended into empty space", set automatic, get next key
  //  automatic      none         no        ipoop = 1, display "Energy will be expended into empty space", set automatic, get next key
  //  manual         computer     no        ipoop = 0, display "There is no enemy to select", clear queue, set key to EOL, set automatic
  //  manual         sensors      no        ipoop = 0, display "There is no enemy to select", clear queue, set key to EOL, set automatic
  //  manual         both         no        ipoop = 0, display "There is no enemy to select", clear queue, set key to EOL, set automatic
  //  manual         none         no        ipoop = 1, display "There is no enemy to select", clear queue, set key to EOL, set automatic
  //  value          computer     yes       ipoop = 0, forced manual
  //  value          sensors      yes       ipoop = 0, forced manual
  //  value          both         yes       ipoop = 0, forced manual
  //  value          none         yes      *ipoop = 1, set automatic
  //  value          computer     no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  value          sensors      no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  value          both         no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  value          none         no        ipoop = 1, display "Energy will be expended into empty space", set automatic
  //  EOL            computer     yes       ipoop = 0, forced manual
  //  EOL            sensors      yes       ipoop = 0, forced manual
  //  EOL            both         yes       ipoop = 0, forced manual
  //  EOL            none         yes      *ipoop = 1, prompt "Manual or automatic?"
  //  EOL            computer     no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  EOL            sensors      no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  EOL            both         no        ipoop = 0, display "Energy will be expended into empty space", set automatic
  //  EOL            none         no        ipoop = 1, display "Energy will be expended into empty space", set automatic
  //  no             computer     yes       set no, repeat
  //  no             sensors      yes       set no, repeat
  //  no             both         yes       set no, repeat
  //  no             none         yes       set no, repeat
  //  no             computer     no        set no, repeat
  //  no             sensors      no        set no, repeat
  //  no             both         no        set no, repeat
  //  no             none         no        set no, repeat
  //  junk string    computer     yes       command error
  //  junk string    sensors      yes       command error
  //  junk string    both         yes       command error
  //  junk string    none         yes       command error
  //  junk string    computer     no        command error
  //  junk string    sensors      no        command error
  //  junk string    both         no        command error
  //  junk string    none         no        command error
  //  
  // 2011-10-10:
  // Input: phaser <no> <value>
  // - peek at next token, 
  //   if "no", set state and pop token and peek at next token
  //   if value && no damage, transition to automatic
  //   if value && damage, transition to manual
  //   if "manual" or "automatic", transition to manual_or_automatic
  //   if EOL && enemies present && no damage, transition to "Manual or automatic?"
  //   if EOL && enemies present && damage, transition to manual"
  //   if EOL && enemies not present, transition to automatic with prompt "Units to fire"
  // _manual_or_auto_phaser
  // - prompt is "Manual or automatic?"
  // - pop token
  // - if "manual" transition to manual
  // - if "automatic" and no damage, transition to automatic, otherwise transition to manual
  // - else transition to _ignorecmd
  // _auto_phaser
  // - prompt is "Units to fire-"
  // - pop token
  // - if value, set state, pop next token, if "no", set state, else if EOL, transition to _execmd, else transition to _ignorecmd
  // - if "no", set state, pop next token, if value, set state and transition to _execmd, else transition to _ignorecmd
  // - else transition to _ignorecmd
  // _manual_phaser
  
  //  Enemies:                                   No Enemies
  //  nextCmd               damage                     damage
  //                   no           yes          no             yes
  //  empty            m_or_a       manual       auto           auto
  //  value            auto         manual       auto           manual
  //  manual           manual       manual       manual         manual
  //  auto             auto         auto         auto           auto
  //  no or junk       ???          ???          ???            ???
  //
  //  ??? is either m_or_a or an error state. If error state, then we need to take care of the case for 'no' separately
  //  if value and we are to transition to manual, this is forced manual so we should first clear the value from the Command Queue
  //
  //  Question: Is it more natural for a choice state to pop the next token (can be empty) or just peek? The
  //  choice state does not have a prompt.

  // AIC_NOTE: this bit of code is meant to retrieve an optional input that can
  // be inserted at this state. Should be able to abstract this as a member
  // of command_state
  command_data next_cmd = peek_at_token_queue(handler);
  // if next_cmd is no, then get this command, add to command data, and peek at next command
  if (is_partial_match("no", next_cmd)) {
    command_inputs tokens;
    get_command_inputs(handler, 1, tokens);
    append_command_data(handler, tokens[0]);
    next_cmd = peek_at_token_queue(handler);
  }

  // @todo: check command state wrt game state should use the visitor pattern.
  // The check should be a method of the game state or global function using
  // borh game state and handler as inputs. It is the game state's
  // responsibility to change the command state appropriately based on the game
  // state. If the game state does not impact the command state, the check
  // should return false, in which case this method should proceed as usual.
  // Otherwise, the chek should return true, in which case this method should
  // return handled_but_incomplete immediately.
  if ((next_cmd.empty() && damage[DCOMPTR] == 0 && damage[DSRSENS] == 0 && nenhere > 0) ||
      is_partial_match("manual", next_cmd) ||
      is_partial_match("automatic", next_cmd)) {
    // if next_cmd is empty and enemies are present and there is no damage or
    //    next_cmd is manual or
    //    next_cmd is automatic, transition to manual or automatic
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_phasers_mode")));      
  } else if ((next_cmd.empty() && nenhere == 0) || is_number(next_cmd)) {
    // if nextCmd is empty and enemies are not present or
    //    nextCmd is a number, transition to automatic
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_automatic_phasers")));      
  } else if (next_cmd.empty() && nenhere > 0 && 
             (damage[DCOMPTR] != 0 || damage[DSRSENS] != 0)) {
    // if nextCmd is empty and enemies are present and there is damage, transition to manual
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_manual_phasers")));
  } else {
    // else we have an error in the input
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
  }
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;  
}
  
} // end namespace command_input_state
} // end namespace iTrek
