
#include "config.h"
#include <string>
#include <utility>
#include <iostream>

namespace my_log {
#ifdef USE_BOOST_LOG


#else

#endif

	void log_it(std::size_t sender, std::string message);
}

