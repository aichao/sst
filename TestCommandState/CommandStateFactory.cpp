/*
 *  CommandStateFactory.cpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "CommandStateFactory.hpp"

namespace iTrek
{
  bool CommandStateFactoryImpl::registerCommandState( std::string const& id, CommandStateCreator createFcn )
  {
    return associations_.insert( AssocMap::value_type( id, createFcn ) ).second != 0;
  }

  bool CommandStateFactoryImpl::unregisterCommandState( std::string const& id )
  {
    return associations_.erase(id) != 0;
  }

  boost::shared_ptr< CommandState > CommandStateFactoryImpl::createCommandState( std::string const& id )
  {
    // First check partial match using upper bound from map and substring comparison
    AssocMap::const_iterator i = associations_.upper_bound( id );
    if ( i != associations_.end() && (i->first).compare( 0, id.length(), id ) == 0 )
      return (i->second)();
    else // now we need to check for equality using lower bound
    {
      i = associations_.find( id );
      if ( i != associations_.end() )
        return (i->second)();
    }
    
    // this returns NULL for pointer
    return boost::shared_ptr< CommandState >();
  }

} // end namespace iTrek
