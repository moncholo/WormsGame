#ifndef LOG
#define LOG

//#define _CRT_SECURE_NO_WARNINGS 0
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include "Constantes.h"

class Log {
	public:
		std::string path;

		Log(std::string path);
		void escribirLog(std::string msg);
};

#endif