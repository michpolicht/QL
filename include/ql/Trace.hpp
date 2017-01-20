#ifndef QL_TRACE_HPP
#define QL_TRACE_HPP

#include <ostream>
#include <iomanip>
#include <ctime>

namespace ql {

/**
 * Trace.
 */
struct Trace
{
	enum flag_t {
		FILE = 1,
		LINE = 2,
		FUNCTION = 4,
		DATE = 8
	};

	Trace(int flags, const char * file, std::size_t line, const char * function);

	int flags;
	const char * file;
	std::size_t line;
	const char * function;
};

inline
Trace::Trace(int p_flags, const char * p_file, std::size_t p_line, const char * p_function):
    flags(p_flags),
    file(p_file),
    line(p_line),
    function(p_function)
{
}

}

inline
std::ostream & operator <<(std::ostream & s, const ql::Trace & trace)
{
	if (trace.flags != 0) {
		s << " ";
		char sep = '[';
		if (trace.flags & ql::Trace::FILE) {
			s << sep << "file: " << trace.file;
			sep = ' ';
		}
		if (trace.flags & ql::Trace::LINE) {
			s << sep << "line: " << trace.line;
			sep = ' ';
		}
		if (trace.flags & ql::Trace::FUNCTION) {
			s << sep << "function: " << trace.function;
			sep = ' ';
		}
		if (trace.flags & ql::Trace::DATE) {
			std::time_t t = std::time(0);
#ifdef QL_NO_STD_PUT_TIME
			char buff[128];	// 20 chars would be enough, but let's set it to paranoic size and avoid adaptative calls.
			std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(& t));
			s << sep << "date: " << buff;
#else
			s << sep << "date: " << std::put_time(std::localtime(& t), "%Y-%m-%d %H:%M:%S");
#endif
			sep = ' ';
		}
		s << "]";
	}
	return s;
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
