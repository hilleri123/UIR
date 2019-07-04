
#pragma once

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <functional>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <cmath>

#include "point.h"
#include "velocity.h"


std::vector<std::pair<Point, Velocity>>& csv_parser_read(const char* file);
