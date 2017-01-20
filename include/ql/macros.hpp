/**
 * @file
 * @brief .
 */

#ifndef QL_MACROS_HPP
#define QL_MACROS_HPP

#include "Log.hpp"

#ifdef QL_NO_LOG			///< Turns off QL_DEBUG, QL_NOTE and QL_WARN macros.
    #define QL_NO_DEBUG	///< Turns off QL_DEBUG macro.
    #define QL_NO_NOTE		///< Turns off QL_NOTE macro.
    #define QL_NO_WARN		///< Turns off QL_WARN macro.
#endif

/**
 * Debug message. This kind of messages are intended to be utilized during development.
 * This macro should be turned off for releases. It can be turned off by defining
 * QL_NO_DEBUG before including this file.
 * @param EXPR expression containing debug message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object or (void)0.
 */
#ifndef QL_NO_DEBUG
    #define QL_DEBUG(EXPR) ::ql::Log::Instance().debugStream() << "Debug message: " << EXPR << ::ql::Trace(::ql::Log::Instance().debugStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl
#else
	#define QL_DEBUG(EXPR) (void)0
#endif

/**
 * Notice. Indicate notable events, etc.
 * @param EXPR expression containing notice. Expression is injected into LogStream
 * object thus standard ostream syntax may be used. This macro can be turned off by
 * defining QL_NO_NOTE before including this file.
 * @return reference to LogStream object or (void)0.
 */
#ifndef QL_NO_NOTE
    #define QL_NOTE(EXPR) ::ql::Log::Instance().noteStream() << "Note: " << EXPR << ::ql::Trace(::ql::Log::Instance().noteStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl
#else
	#define QL_NOTE(EXPR) (void)0
#endif

/**
 * Warning. Indicate something serious that shouldn't be omitted. It is good idea not to
 * turn off QL_WARN macro completely and at least collect the data in the log file.
 * @param EXPR expression containing warning message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used. This macro can be turned off by defining
 * QL_NO_WARN before including this file.
 * @return reference to LogStream object or (void)0.
 */
#ifndef QL_NO_WARN
    #define QL_WARN(EXPR) ::ql::Log::Instance().warnStream() << "Warning: " << EXPR << ::ql::Trace(::ql::Log::Instance().warnStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl
#else
	#define QL_WARN(EXPR) (void)0
#endif

/**
 * Error. Denotes a very serious condition that requires user reaction. Program can
 * deal with it, but it will have an impact on its behaviour. QL_ERROR macro should never be turned off.
 * @param EXPR expression containing error message. Expression is injected into LogStream
 * object thus standard ostream syntax may be used. This macro can be turned off by defining
 * QL_NO_ERROR before including this file.
 * @return reference to LogStream object or (void)0.
 */
#ifndef QL_NO_ERROR
    #define QL_ERROR(EXPR) ::ql::Log::Instance().errorStream() << "Error: " << EXPR << ::ql::Trace(::ql::Log::Instance().errorStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl
#else
	#define QL_ERROR(EXPR) (void)0
#endif

/**
* Critical error. Sends critical error message to LogStream and exits with EXIT_FAILURE code.
* This macro should never be turned off, however it can be turned off by defining
* QL_NO_CRITICAL before including this file.
* @param EXPR expression containing critical error message. Expression is injected into LogStream
* object thus standard ostream syntax may be used.
* @return (void)0 or void.
 */
#ifndef QL_NO_CRITICAL
    #define QL_CRITICAL(EXPR) ::ql::Log::Instance().criticalStream() << "Critical error: " << EXPR << ::ql::Trace(::ql::Log::Instance().criticalStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl, std::exit(EXIT_FAILURE)
#else
	#define QL_CRITICAL(EXPR) (void)0
#endif

/**
* Fatal error. Sends fatal error message to LogStream and aborts execution.
* There are following differences between exit() (performed by QL_CRITICAL) and abort():
* 	- abort() sends SIGABRT signal.
* 	- abort() will dump core, if core dump is enabled.
* 	- abort() quits program without calling functions registered with atexit() function.
* 	- During exit() destructors of non-automatic objects are called. During abort()
* 		destructors	of neither objects are being called.
* 	.
* This macro should never be turned off, however it can be turned off by defining
* QL_NO_FATAL before including this file.
* @param EXPR expression containing fatal error message. Expression is injected into LogStream
* object thus standard ostream syntax may be used.
* @return (void)0 or void.
 */
#ifndef QL_NO_FATAL
    #define QL_FATAL(EXPR) ::ql::Log::Instance().fatalStream() << "Fatal error: " << EXPR << ::ql::Trace(::ql::Log::Instance().fatalStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl, std::abort()
#else
	#define QL_FATAL(EXPR) (void)0
#endif

/**
 * Information. Indicate informational data. Intended to operate at the same level of
 * importance as notice. In opposite to notice the output is clean by default - without prefix, file,
 * line or function name in it. Macro can be turned off by defining QL_NO_INFO.
 * @param EXPR expression containing information. Expression is injected into LogStream
 * object thus standard ostream syntax may be used.
 * @return reference to LogStream object or (void)0.
 */
#ifndef QL_NO_INFO
    #define QL_INFO(EXPR) ::ql::Log::Instance().infoStream() << EXPR << ::ql::Trace(::ql::Log::Instance().infoStream().traceFlags(), __FILE__, __LINE__, __FUNCTION__) << std::endl
#else
	#define QL_INFO(EXPR) (void)0
#endif

/**
 * Assertion. Usage of this macro is analogous to standard C assert. Expression is tested
 * and if it fails fatal error is triggered. In addition to standard C assert, description
 * message must be passed. Macro is turned off when NDEBUG is defined.
 * @param EXPR expression to test.
 * @param MSG descriptive message on assertion failure.
 * @return (void)0 or void.
 */
#ifndef NDEBUG
	#define QL_ASSERT(EXPR, MSG) ((EXPR) ? (void)0 : (QL_FATAL("assertion failed ("#EXPR"), " MSG)))
#else
	#define QL_ASSERT(EXPR, MSG) (void)0
#endif

#endif

//(c)MP: Copyright © 2017, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
