#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Logger
{
private:
	std::ofstream logfile;
	bool logging = true;
	bool has_error_occurred = false;
public:
	Logger();
	Logger(const std::string &log_file);
	void open(const std::string &log_file);
	void log(const std::string err);
	void elog(const std::string err);
	bool is_logging();
	void dont_log();
	void do_log();
	~Logger();
};

