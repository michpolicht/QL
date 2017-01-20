/**
 * @file
 * @brief .
 */

//following macros can be defined before including QL files
//#define QL_NO_DEBUG	///< Turns off QL_DEBUG macro.
//#define QL_NO_NOTE	///< Turns off QL_NOTE macro.
//#define QL_NO_WARN	///< Turns off QL_WARN macro.
//#define QL_NO_ERROR	///< Turns off QL_ERROR macro.
//#define QL_NO_INFO 	///< Turns off QL_INFO macro.
//#define QL_NO_FATAL 	///< Turns off QL_FATAL macro.
//#define QL_NO_LOG	///< Turns off all logging macros except QL_FATAL and QL_INFO

#define QL_NO_STD_PUT_TIME	// Define if C++11 std::put_time is not available.

#include "../include/ql.hpp"

#include <fstream>

int main(int, char * [])
{
	// Configure release mode logging style with date instead of file, line, function.
#ifndef EXAMPLE_DEBUG
	ql::Log::Instance().setTraceFlags(ql::Trace::DATE);
#endif

	// Initially std::cout is attached to combined stream.
	// All streams will print to std::cout, through combined stream.
#ifdef EXAMPLE_DEBUG
	QL_INFO("Compiled with EXAMPLE_DEBUG macro - using debug logging style.");
#else
	QL_INFO("Compiled without EXAMPLE_DEBUG macro - using release logging style.");
#endif
	QL_DEBUG("This kind of messages are intended to be utilized during development.");
	QL_NOTE("Indicating notable event.");
	QL_WARN("Something serious that shouldn't be omitted.");
	QL_ERROR("A very serious condition that requires user reaction.");

	// Standard ostream expressions can be used inside brackets.
	QL_NOTE("2+2 is " << (2+2));

	// Open a text file.
	std::ofstream logFile;
	logFile.open("log.txt", std::ofstream::out | std::ofstream::app);
	if (!logFile.is_open())
		QL_CRITICAL("Could not create a log file.");

	// Attach the text file stream to combined stream.
	ql::Log::Instance().combinedStream().attachStream(logFile);
	QL_WARN("Second warning.");
	QL_FATAL("Fatal exit, just to demonstrate the purpose of fatal stream.");

	// EXIT_SUCCESS is not reached due to previous fatal error.
	return EXIT_SUCCESS;
}
