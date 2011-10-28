/*
 *  PhotonsCommand.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "PhotonsCommand.hpp"

#include <sstream>

#include "GlobalState.hpp"
#include "CommandStateFactory.hpp"

namespace iTrek { namespace CommandInputState
{
  
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createPhotonsCommandState()
    {
      return boost::shared_ptr< CommandState >( new PhotonsCommand() );
    }
    // Define the identifier
    const std::string PhotonsCommandStateID( "photons" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( PhotonsCommandStateID, createPhotonsCommandState );
  }
  
  void PhotonsCommand::executeAction( CommandInputHandler * handler )
  {
    // if photons are damaged, say so and ignore the command
    if ( damage[DPHOTON] ) 
    {
      CommandState::addDisplayEvent( "Photon tubes damaged.\n" );
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      return;
    }
    // if there are no torpedoes left, say so and ignore command
    if ( torps == 0 ) 
    {
      CommandState::addDisplayEvent( "No torpedoes left.\n" );
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      return;
    }
    // display number of torpedoes left.
    std::ostringstream NumPhotonsAvailStr;
    NumPhotonsAvailStr << torps << " torpedoes left.\n";
    CommandState::addDisplayEvent( NumPhotonsAvailStr.str() );          
    // add the command name "Photons" to command data
    CommandState::appendCommandData( handler, "photons" );
    // transition the command state to _num_photons
    CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_num_photons" ) );
  }
  
} } // end namespace iTrek::CommandInputState
