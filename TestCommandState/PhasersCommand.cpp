/*
 *  PhasersCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "PhasersCommand.hpp"
#include "CommandStateFactory.hpp"
#include "GlobalState.hpp"
#include "command_input_utilities.hpp"

namespace iTrek { namespace CommandInputState
{
  
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createPhasersCommandState()
    {
      return boost::shared_ptr< CommandState >( new PhasersCommand() );
    }
    // Define the identifier
    const std::string PhasersCommandStateID( "phasers" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( PhasersCommandStateID, createPhasersCommandState );
  }
  
  // @todo: need to understand different command options (especially "no")
  void PhasersCommand::executeAction( CommandInputHandler * handler )
  {
    // @todo: this stuff is actually reactions to the command and should be part of
    // ship state, which is part of game state.
    // if docked, say so and ignore command
    if ( condit == IHDOCKED ) 
    {
      CommandState::addDisplayEvent( "Phasers can't be fired through base shields.\n" );
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      return;
    }
    // if phasers are damaged, say so and ignore command
    if ( damage[DPHASER] != 0 ) 
    {
      CommandState::addDisplayEvent( "Phaser control damaged.\n" );
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      return;
    }
    // if shields are up and shields are damaged or energy is insufficient to activate
    // high speed shield control, say so and ignore command
    if ( shldup ) 
    {
      if ( damage[DSHCTRL] ) 
      {
        CommandState::addDisplayEvent( "High speed shield control damaged.\n" );
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
        return;
      }
      if ( energy <= 200.0 ) 
      {
        CommandState::addDisplayEvent( "Insufficient energy to activate high-speed shield control.\n" );
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
        return;
      }
      // else display message for enabling high speed shield control
      CommandState::addDisplayEvent( "Weapons Officer Sulu-  \"High-speed shield control enabled, sir.\"\n" );
    }
    // add the command name "phasers" to command data
    CommandState::appendCommandData( handler, "phasers" );
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
    CommandData nextCmd = CommandState::peekAtCommandQueue();
    // if nextCmd is no, then get this command, add to command data, and peek at next command
    if ( is_partial_match( "no", nextCmd ) )
    {
      CommandInputs tokens;
      getCommandInputs( 1, tokens );
      CommandState::appendCommandData( handler, tokens[0] );
      nextCmd = CommandState::peekAtCommandQueue();
    }
    
    // if nextCmd is empty and enemies are present and there is no damage or
    //    nextCmd is manual or
    //    nextCmd is automatic, transition to manual or automatic
    if ( ( nextCmd.empty() && damage[DCOMPTR] == 0 && damage[DSRSENS] == 0 && nenhere > 0 ) ||
         is_partial_match( "manual", nextCmd ) ||
         is_partial_match( "automatic", nextCmd ) ) 
    {
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_phasers_mode" ) );      
    }
    // if nextCmd is empty and enemies are not present or
    //    nextCmd is a number, transition to automatic
    else if ( ( nextCmd.empty() && nenhere == 0 ) || is_number( nextCmd ) )
    {
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_automatic_phasers" ) );      
    }
    // if nextCmd is empty and enemies are present and there is damage, transition to manual
    else if ( nextCmd.empty() && nenhere > 0 && ( damage[DCOMPTR] != 0 || damage[DSRSENS] != 0 ) ) 
    {
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_manual_phasers" ) );
    }
    // else we have an error in the input
    else
    {
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_cmderr" ) );      
    }
  }
  
} } // end namespace iTrek::CommandInputState
