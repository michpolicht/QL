/**
 * @file
 * @brief .
 */

#ifndef QL_LOG_HPP
#define QL_LOG_HPP

#include "LogStream.hpp"

namespace ql { class Log; }

/**
 * Log initialization function. No stream is being attached.
 * @param Log log instance.
 */
void ql_logInitFuncNone(ql::Log * log);

/**
 * Log initialization function. Attaches combined stream to std::cout.
 * @param Log log instance.
 */
void ql_logInitFuncCout(ql::Log * log);

/**
 * Log initialization function. In order to print the output, write to file etc., Log
 * streams must be attached to streams representing physical devices. To take into account
 * all the logs, attachments have to be made during Log instance construction. Function
 * defined by this macro will be called by the Log class constructor, giving the opportunity
 * to customize initial stream attachments. By default ql_logInitFuncCout() is used. User
 * function must be defined in global namespace, because for convenience it will be
 * forwardly declared, using given macro value.
 */
#ifndef QL_LOG_INIT_FUNC
	#define QL_LOG_INIT_FUNC ql_logInitFuncCout
#else
	/*
	 * For user convenience let's declare his initialization function so that (s)he will only
	 * need to define it later on. Otherwise (s)he would need to provide his lines every time
	 * before including QL log headers.
	 */
	void QL_LOG_INIT_FUNC(ql::Log * log);
#endif

namespace ql {

/**
 * Log. Main class of QL log facility.
 *
 * This class is a singleton and can not be instantiated directly. To obtain instance
 * use Instance() function. For convenient usage of this class seven macros are defined
 * (in separate header) for logging purposes (QL_DEBUG, QL_NOTE, QL_WARN, QL_ERROR,
 * QL_CRITICAL, QL_FATAL, QL_INFO).
 *
 * Log class defines seven streams which are instances of LogStream class. Each of them
 * may be attached to any number of other streams. For example, to bring debug output
 * to std::cout, attach std::cout to debug stream. seven basic streams are:
 * 	- debug stream - used by QL_DEBUG macro. Obtain it by calling debugStream().
 * 	- note stream - used by QL_NOTE macro. Obtain it by calling noteStream().
 * 	- warn stream - used by QL_WARN macro. Obtain it by calling warnStream().
 * 	- error stream - used by QL_ERROR macro. Obtain it by calling errorStream().
 * 	- critical stream - used by QL_CRITICAL macro. Obtain it by calling criticalStream().
 * 	- fatal stream - used by QL_FATAL macro. Obtain it by calling fatalStream().
 * 	- info stream - used by QL_INFO macro. Obtain it by calling infoStream().
 *  .
 * There is also special eighth stream which is not used directly by any macro:
 * 	- combined stream - obtain it by calling combinedStream().
 *  .
 * Combined stream is already attached to seven previously described streams. By attaching
 * std::cout to combined stream, all seven streams will put the output, through combined
 * stream, to std::cout. Default stream attachment is defined by QL_LOG_INIT_FUNC macro.
 */
class Log
{
	public:
		Log(const Log & other) = delete;

		Log & operator =(const Log & other) = delete;

		/**
		 * Get Log singleton instance.
		 * @return Log instance.
		 */
		static Log & Instance();

	public:
		/**
		 * Get debug stream.
		 * @return debug stream.
		 *
		 * @see QL_DEBUG.
		 */
		LogStream & debugStream();

		/**
		 * Get notice stream.
		 * @return notice stream.
		 *
		 * @see QL_NOTE.
		 */
		LogStream & noteStream();

		/**
		 * Get warn stream.
		 * @return warn stream.
		 *
		 * @see QL_WARN.
		 */
		LogStream & warnStream();

		/**
		 * Get error stream.
		 * @return error stream.
		 *
		 * @see QL_ERROR.
		 */
		LogStream & errorStream();

		/**
		 * Get critical stream.
		 * @return critical stream.
		 *
		 * @see QL_CRITICAL.
		 */
		LogStream & criticalStream();

		/**
		 * Get fatal stream.
		 * @return fatal stream.
		 *
		 * @see QL_FATAL.
		 */
		LogStream & fatalStream();

		/**
		 * Get info stream.
		 * @return info stream.
		 *
		 * @see QL_INFO.
		 */
		LogStream & infoStream();

		/**
		 * Get combined stream.
		 * @return combined stream.
		 */
		LogStream & combinedStream();

		/**
		 * Attach log. Attaches respectively seven streams (without combined) of other log to
		 * streams of this log.
		 * @param other other log.
		 *
		 * @note this function is useful when working with libraries.
		 *
		 * @see detachLog().
		 */
		void attachLog(Log & other);

		/**
		 * Detach log. Detaches respectively seven streams (without combined) of other log
		 * from streams of this log.
		 * @param other other log.
		 *
		 * @see attachLog().
		 */
		void detachLog(Log & other);

		/**
		 * Set trace flags. Sets specified trace flags on all streams except of combined stream
		 * and info stream.
		 * @param flags any combination of Trace::flag_t flags.
		 */
		void setTraceFlags(int flags);

	private:
		/**
		 * Default constructor. This class is a singleton and can not be instantiated
		 * directly. Use Instance() method instead.
		 */
		Log();

	private:
		LogStream m_combinedStream;
		LogStream m_debugStream;
		LogStream m_noteStream;
		LogStream m_warnStream;
		LogStream m_errorStream;
		LogStream m_criticalStream;
		LogStream m_fatalStream;
		LogStream m_infoStream;
};

inline
Log & Log::Instance()
{
	static Log instance;
	return instance;
}

inline
LogStream & Log::debugStream()
{
	return m_debugStream;
}

inline
LogStream & Log::noteStream()
{
	return m_noteStream;
}

inline
LogStream & Log::warnStream()
{
	return m_warnStream;
}

inline
LogStream & Log::errorStream()
{
	return m_errorStream;
}

inline
LogStream & Log::criticalStream()
{
	return m_criticalStream;
}

inline
LogStream & Log::fatalStream()
{
	return m_fatalStream;
}

inline
LogStream & Log::infoStream()
{
	return m_infoStream;
}

inline
LogStream & Log::combinedStream()
{
	return m_combinedStream;
}

inline
void Log::attachLog(Log & other)
{
	m_debugStream.attachStream(other.debugStream());
	m_noteStream.attachStream(other.noteStream());
	m_warnStream.attachStream(other.warnStream());
	m_errorStream.attachStream(other.errorStream());
	m_criticalStream.attachStream(other.criticalStream());
	m_fatalStream.attachStream(other.fatalStream());
	m_infoStream.attachStream(other.infoStream());
}

inline
void Log::detachLog(Log & other)
{
	m_debugStream.detachStream(other.debugStream());
	m_noteStream.detachStream(other.noteStream());
	m_warnStream.detachStream(other.warnStream());
	m_errorStream.detachStream(other.errorStream());
	m_criticalStream.detachStream(other.criticalStream());
	m_fatalStream.detachStream(other.fatalStream());
	m_infoStream.detachStream(other.infoStream());
}

inline
void Log::setTraceFlags(int flags)
{
	m_debugStream.setTraceFlags(flags);
	m_noteStream.setTraceFlags(flags);
	m_warnStream.setTraceFlags(flags);
	m_errorStream.setTraceFlags(flags);
	m_criticalStream.setTraceFlags(flags);
	m_fatalStream.setTraceFlags(flags);
}

inline
Log::Log()
{
	m_infoStream.setTraceFlags(0);
	m_combinedStream.setTraceFlags(0);
	m_debugStream.attachStream(m_combinedStream);
	m_noteStream.attachStream(m_combinedStream);
	m_warnStream.attachStream(m_combinedStream);
	m_errorStream.attachStream(m_combinedStream);
	m_criticalStream.attachStream(m_combinedStream);
	m_fatalStream.attachStream(m_combinedStream);
	m_infoStream.attachStream(m_combinedStream);
	QL_LOG_INIT_FUNC(this);
}

}


inline
void ql_logInitFuncNone(ql::Log * )
{
}

inline
void ql_logInitFuncCout(ql::Log * log)
{
	log->combinedStream().attachStream(std::cout);
}

#endif

//(c)MP: Copyright © 2016, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
