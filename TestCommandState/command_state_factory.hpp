/*
 *  command_state_factory.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/24/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_command_state_factory_hpp
#define iTrek_command_state_factory_hpp

#include <string>
//#include <unordered_map>

#include <prism/acip/boost_1_42_0_ext/pool/detail/singleton.hpp>
//#include <boost/shared_ptr.hpp>

#include <prism/acip/util/sorted_vector.hpp>

namespace iTrek {

/// forward declaration of command_state
class command_state;

/** In implementation of concrete command_state class, register the factory method
 *  for that class to the command_state_factory in an empty namespace
 *  \code
 *  namespace {
 *    // Factory method to create the ConcreteCommandState object
 *    command_state* create_concrete_command_state() {
 *      return new concrete_command_state;
 *    }
 *    // Define the identifier
 *    const std::string concrete_command_state_id("_concrete_state_name");
 *    // Register the factory method in the command_state_factory
 *    const bool registered = command_state_factory::instance().register_command_state( 
 *        concrete_command_state_id, create_oncrete_command_state);
 *  }
 *  \code
 */
class command_state_factory_impl {
 public:
  /// Define command_state_creator as a pointer to a function with no arguments and 
  /// returns command_state*. The typename for command_state_creator is 
  /// command_state* (*)()
  typedef command_state* (*command_state_creator)();

  bool register_command_state(std::string const& id, command_state_creator create_fcn);

  void unregister_command_state(std::string const& id);

  command_state* create_command_state(std::string const& id);

 private:
//  typedef std::tr1::unordered_map<std::string, command_state_creator> state_map;
  typedef prism::acip::util::sorted_vector<std::string, command_state_creator> state_map;

  state_map map_;
};

/// The command_state_factory is a singleton
typedef boost::details::pool::singleton_default<command_state_factory_impl> command_state_factory;

} // end namespace iTrek

#endif
