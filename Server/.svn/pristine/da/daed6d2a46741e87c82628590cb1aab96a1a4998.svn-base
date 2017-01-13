#include "Log.h"

Log::Log(std::string path_) {
	path = path_;
	std::fstream fs(path, std::fstream::app);

	if (!fs){

		std::fstream fs(path, std::fstream::out);
	}

	fs.close();
}

void Log::escribirLog(std::string msg){
	time_t rawtime;
    time (&rawtime);

	std::fstream fs(path.c_str(), std::fstream::app);
	fs << "--------------------" << std::endl;
//	fs << ctime (&rawtime) << std::endl;
	fs << msg << std::endl;
	fs << "--------------------" << std::endl;
	fs.close();
}
