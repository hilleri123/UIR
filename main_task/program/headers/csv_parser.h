
#pragma once

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <functional>

#include <iostream>

//#include "space/geometrics/point.h"
//#include "space/functions/velocity.h"
#include "point.h"
#include "velocity.h"


std::vector<std::pair<Point, Velocity>>& csv_parser_read(const char* file);
