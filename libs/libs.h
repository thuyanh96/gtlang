#ifndef LIBS_LIBS_H_
#define LIBS_LIBS_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
#include <variant>
#include <algorithm>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <csignal>
#include <boost/algorithm/string/replace.hpp>
#include <php2cpp.h>
#include <Mixed.h>

bool php_is_array(Mixed _mixed) {
	return (_mixed.type == "a");
}
#endif /* LIBS_LIBS_H_ */
