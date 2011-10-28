#include <iostream>
#include <boost/thread/thread.hpp>
#include "CommandInputHandler.hpp"
#include "EventQueue.hpp"
#include "CommandQueue.hpp"

//#include "CommandInputEvent.hpp"
//#include <boost/tokenizer.hpp>
//#include <boost/algorithm/string/case_conv.hpp>
//#include <boost/lexical_cast.hpp>
#include <memory>
#include "GetCommand.hpp"

int main (int argc, char * const argv[]) 
{
  
  /*
  // test the boost::tokenizer
  // Send the prompt message to std::cout
  std::cout << "Test Input Tokenization> " << std::flush;
  // get line of input from std::cin
  const unsigned N = 128;
  char cmd_cstr[ N ];
  std::cin.getline( cmd_cstr, N );
  iTrek::CommandInputEvent command( cmd_cstr );
  // convert to lower case
  boost::to_lower(command);
  // tokenize with space delimiter
  boost::char_separator<char> sep(" ");
  boost::tokenizer< boost::char_separator<char> > tokens(command, sep);
  std::size_t i = 0;
  for( boost::tokenizer< boost::char_separator<char> >::iterator beg = tokens.begin(); beg != tokens.end(); ++beg, ++i )
  {
    try
    {
      std::cout << "Token " << i << ": " << boost::lexical_cast<double>(*beg) << " is a double" << std::endl;
    }
    catch ( boost::bad_lexical_cast & )
    {
      std::cout << "Token " << i << ": " << *beg << " is a string" << std::endl;
    }
  }
   */
  
  // construct CommandInputHandler and start it in its own thread
  iTrek::CommandInputHandler cmdHandler;
  boost::thread commandHandlerThread( cmdHandler );
  // detach the thread
  commandHandlerThread.detach();
  
  // simulate input event loop
  while (1)
  {
    // Pop Events from the EventQueue and execute them
    {
      iTrek::EventQueue::object_type::wait_lock_t lock( iTrek::EventQueue::instance().queueMutex );
      iTrek::EventQueue::instance().wait( lock );
      while ( !( iTrek::EventQueue::instance().empty() ) )
      {
        // Execute the Event at the front of the queue by calling operator()
        ( *iTrek::EventQueue::instance().front() )();
        iTrek::EventQueue::instance().pop();
      }
    }
  }
  
  return 0;
}
