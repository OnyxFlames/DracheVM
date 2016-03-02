#include "Logger.hpp"

Logger::Logger()
{/*Intentioonally empty*/}

Logger::Logger(std::string log_file)
{
	open(log_file);
}

void Logger::open(std::string log_file)
{
	logfile.open(log_file);
	if (!logfile.is_open())
	{
		std::cerr << "logger error: failed to create log file. Errors will not be logged." << std::endl;
		logging = false;
	}
}

void Logger::log(const std::string err)
{
	if (!logging)
		return;
	logfile  << err << "\n";
}

void Logger::elog(const std::string err)
{
	if (!logging)
		return;
	has_error_occurred = true;
	logfile << err << "\n";
}

bool Logger::is_logging()
{
	return logging;
}

void Logger::dont_log()
{
	logging = false;
}

void Logger::do_log()
{
	logging = true;
}

Logger::~Logger()
{
	logfile << "Done logging. Exiting." << std::endl;
	logfile.close();
	if (has_error_occurred)
		std::cerr << "Errors have occurred during runtime, please check the log." << std::endl;
}
