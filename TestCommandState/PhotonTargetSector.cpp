/*
 *  PhotonTargetSector.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "PhotonTargetSector.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "CommandStateFactory.hpp"
#include "GlobalState.hpp"

namespace iTrek { namespace CommandInputState
{
  PhotonTargetSector::PhotonTargetSector( unsigned iTgt, unsigned nTgts )
    : iTgt_(iTgt), nTgts_(nTgts)
  {}
  
  void PhotonTargetSector::executeAction( CommandInputHandler * handler )
  {
    // Pop sector coordinate input from the CommandQueue
    CommandInputs tokens;
    getCommandInputs( 2, tokens );
    
    // If there is only one token, then we transition to command error state and return immediately
    if ( tokens.size() < 2U )
    {
      // see if single token is empty. If it is and iTgt_ is 2, then transition to _execmd (all torpedoes targeted
      // to same sector coordinates
      if ( tokens[0].empty() && iTgt_ == 2 )
      {
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_execmd" ) );
        // subtract the number requested from the number available, note this is for simulation only
        // @todo: remove this later.
        torps -= nTgts_;
      }
      else
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_cmderr" ) );
      return;
    }
    
    try
    {
      // lexical_cast each token to double.
      double ySect = boost::lexical_cast< double >( tokens[0] );
      double xSect = boost::lexical_cast< double >( tokens[1] );
      // if success, see if target sector is in range [ 1, 10 ].
      if ( xSect < MIN_SECTOR_X || xSect > MAX_SECTOR_X || ySect < MIN_SECTOR_Y || ySect > MAX_SECTOR_Y )
      {
        // If not, transition to ignore command state
        CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_ignorecmd" ) );
      }
      else 
      {
        // if coordinates are valid, add the coordinates to command data
        CommandState::appendCommandData( handler, tokens[0] + " " + tokens[1] );
        // if iTgt_ is equal to nTgts_, transition the command state to execmd
        if ( iTgt_ == nTgts_ )
        {
          CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_execmd" ) );
          // subtract the number requested from the number available, note this is for simulation only
          // @todo: remove this later.
          torps -= nTgts_;
        }
        else
          // else transition to photon target sector state initialized to ++iTgt_, and nTgts_.
          CommandState::changeState( handler, boost::shared_ptr<PhotonTargetSector>( new PhotonTargetSector( ++iTgt_, nTgts_ ) ) );
      }
    }
    catch ( boost::bad_lexical_cast & )
    {
      // If fail, catch exception and transition to command error state
      CommandState::changeState( handler, CommandStateFactory::instance().createCommandState( "_cmderr" ) );
    }
  }
  
  std::string PhotonTargetSector::getPrompt() const
  {
    std::ostringstream PromptStr;
    PromptStr << "Target sector for torpedo number " << iTgt_ << "- ";
    return PromptStr.str();
  }
  
} } // end namespace iTrek::CommandInputState
