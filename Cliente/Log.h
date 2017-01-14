#ifndef LOG
#define LOG

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#define PATH_LOG "log.txt"

class Log {
	public:
		std::string path;

		Log(std::string path);
		void escribirLog(std::string msg);
};

#endif