/*
 *  NumberOfPhotons.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "NumberOfPhotons.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "GlobalState.hpp"
#include "CommandStateFactory.hpp"
#include "PhotonTargetSector.hpp"

namespace iTrek { namespace CommandInputState
{
  
  namespace
  {
    // Factory method to create the ConcreteCommandState object
    boost::shared_ptr< CommandState > createNumberOfPhotonsState()
    {
      return boost::shared_ptr< CommandState >( new NumberOfPhotons() );
    }
    // Define the identifier
    const std::string NumberOfPhotonsStateID( "_num_photons" );
    // Register
    const bool registered = CommandStateFactory::instance().registerCommandState( NumberOfPhotonsStateID, createNumberOfPhotonsState );
  }
  
  void NumberOfPhotons::executeAction( CommandInputHandler * handler )
  {
    // Pop number of photo torpedoes input from the CommandQueue
    CommandInputs tokens;
    getCommandInputs( 1, tokens );
    CommandData numPhotonsStr = tokens[0];

    try
    {
      // lexical_cast to unsigned.
      unsigned numPhotons = boost::lexical_cast< unsigned >( numPhotonsStr );
      if ( numPhotons == 0 )
      {
        // if request is zero torpedoes, ignore the command
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      }
      // else see if number requested is less than or equal min( 3, number available ).
      else if ( numPhotons <= std::min( 3, torps ) )
      {
        // if request is valid, add the number requested to command data
        CommandState::appendCommandData( handler, numPhotonsStr );
        // transition the command state to PhotoTargetSector initialized to first torpedo out of numPhotons
        CommandState::changeState( handler, boost::shared_ptr<PhotonTargetSector>( new PhotonTargetSector( 1, numPhotons ) ) );
      }
      else 
      {
        // if not and if request is more than 3, then send message of "Maximum of 3 torpedoes per burst.\n"
        if ( numPhotons > 3U )
          CommandState::addDisplayEvent( "Maximum of 3 torpedoes per burst.\n" );
        else
        {
          std::ostringstream NumPhotonsAvailStr;
          NumPhotonsAvailStr << "Uh, Captain...  we only have " << torps 
                             << " " << ( ( torps == 1 ) ? "torpedo" : "torpedoes" ) << " left.\n";
          CommandState::addDisplayEvent( NumPhotonsAvailStr.str() );          
        }
        // clear command queue but not the command data to try again (same state)
        CommandState::clearCommandQueue();
      }
    }
    catch ( boost::bad_lexical_cast & )
    {
      // If fail, catch exception and transition to command error state
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_cmderr" ) );
    }
  }
  
  std::string NumberOfPhotons::getPrompt() const
  {
    return "Number of torpedoes to fire- ";
  }
  
} } // end namespace iTrek::CommandInputState
