
#include "log.h"


#ifdef USE_BOOST_LOG

#else

#endif


void my_log::log_it(std::size_t sender, std::string message) {
	std::cout << "[" << sender << "] " << message << std::endl;
}


