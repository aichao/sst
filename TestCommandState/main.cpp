#include <iostream>
#include <string>

#include <boost/optional.hpp>

#include "command_input_event.hpp"
#include "command_input_handler.hpp"
#include "command_data.hpp"
#include "command_state.hpp"

int main (int argc, char * const argv[]) {
  // construct command_input_handler and enter into event loop
  iTrek::command_input_handler cmd_handler;
  iTrek::command_data complete_cmd;
  do {
    // get display events (if any) and send to std::cout
    std::string display_events = cmd_handler.get_display_events();
    if (!display_events.empty()) {
      std::cout << display_events << std::endl;
      cmd_handler.clear_display_events();
    }
    // get the prompt
    boost::optional<std::string> prompt = cmd_handler.current_state().prompt();
    iTrek::command_input_event cmd_inp;
    if (prompt) {
      std::cout << (*prompt);
      const unsigned N = 128;
      char cmd_cstr[ N ];
      std::cin.getline(cmd_cstr, N);
      cmd_inp = cmd_cstr;
    } else {
      std::cout << "Error: current state should return a prompt" << std::endl;
      exit(-1);
    }
    if (cmd_handler.handle(cmd_inp)) {
      complete_cmd = cmd_handler.get_command_data();
      std::cout << "Executing: " << complete_cmd << std::endl;
      cmd_handler.clear_command_data();
    }
  } while (complete_cmd != "quit");
  
  std::cout << "Quitting TestCommandState" << std::endl;
  
  return 0;
}
