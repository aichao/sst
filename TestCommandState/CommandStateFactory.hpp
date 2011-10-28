/*
 *  CommandStateFactory.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef COMMAND_STATE_FACTORY_HPP
#define COMMAND_STATE_FACTORY_HPP

#include <string>

#include <boost/pool/detail/singleton.hpp>
#include <boost/shared_ptr.hpp>

#include "AssocVector.hpp"

namespace iTrek
{
  
  class CommandState;

  /**
   *
   *  In implementation of concrete CommandState class, register the factory method
   *  for that class to the CommandStateFactory in an empty namespace
   *  \code
   *  namespace
   *  {
   *    // Factory method to create the ConcreteCommandState object
   *    CommandState* createConcreteCommandState()
   *    {
   *      return new ConcreteCommandState;
   *    }
   *    // Define the identifier
   *    const std::string ConcreteCommandStateID( "ConcreteCommandState" );
   *    // Register the factory method in the CommandStateFactory
   *    const bool registered = CommandStateFactory::instance().registerCommandState( ConcreteCommandStateID, createConcreteCommandState );
   *  }
   *  \code
   */
  class CommandStateFactoryImpl
  {
  public:

    // Define CommandStateCreator as a pointer to a function with no arguments and returns CommandState*
    // The typename for CommandStateCreator is CommandState* (*)()
    typedef boost::shared_ptr< CommandState > (*CommandStateCreator)();
  
    bool registerCommandState( std::string const& id, CommandStateCreator createFcn );
  
    bool unregisterCommandState( std::string const& id );
  
    boost::shared_ptr< CommandState > createCommandState( std::string const& id );
  
  private:
  
    typedef AssocVector< std::string, CommandStateCreator > AssocMap;
  
    AssocMap associations_;
  };
  
  /// The CommandStateFactory is a singleton
  typedef boost::details::pool::singleton_default< CommandStateFactoryImpl > CommandStateFactory;

} // end namespace iTrek

#endif
