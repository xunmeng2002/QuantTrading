#pragma once
#include "DB.h"
#include <string>


DB* CreateDB(const std::string& dbType, const std::string& dbHost, const std::string& dbUser = "", const std::string& dbPassword = "");

