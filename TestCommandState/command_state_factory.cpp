/*
 *  command_state_factory.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "command_state_factory.hpp"

namespace iTrek {
  
bool command_state_factory_impl::register_command_state(
    std::string const& id, command_state_creator create_fcn) {
  return map_.insert(state_map::value_type(id, create_fcn)).second != 0;
}

void command_state_factory_impl::unregister_command_state(std::string const& id) {
//    state_map::iterator pos = map_.find(id);
//    if (pos != map_.end()) map_.erase_return_void(pos);
  map_.erase(id);
}

command_state* command_state_factory_impl::create_command_state(std::string const& id) {
//    state_map::iterator pos = map_.find(id);
//    return pos == map_.end() ? 0 : (pos->second)();
  state_map::const_iterator pos = map_.lower_bound(id);
  if (pos != map_.end() && (pos->first).compare(0, id.length(), id) == 0)
    return (pos->second)();
  // if not found, return NULL
  return NULL;
}

} // end namespace iTrek
