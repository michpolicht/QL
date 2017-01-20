# QL

A C++ header-only logger.

[![Build Status](https://travis-ci.org/michpolicht/QL.svg?branch=master)](https://travis-ci.org/michpolicht/QL)

Log class is a main component. Log class defines seven streams, which are instances
of LogStream class. Each of them may be attached to any number of other streams.

For example, to bring debug output to std::cerr, attach std::cerr to debug stream.

Seven basic streams are:
  - debug stream - used by QL_DEBUG macro. Obtain it by calling debugStream().
  - note stream - used by QL_NOTE macro. Obtain it by calling noteStream().
  - warn stream - used by QL_WARN macro. Obtain it by calling warnStream().
  - error stream - used by QL_ERROR macro. Obtain it by calling errorStream().
  - critical stream - used by QL_CRITICAL macro. Obtain it by calling criticalStream().
  - fatal stream - used by QL_FATAL macro. Obtain it by calling fatalStream().
  - info stream - used by QL_INFO macro. Obtain it by calling infoStream().

There is also special eighth stream, which is not used directly by any macro:
  - combined stream - obtain it by calling combinedStream().

Combined stream is already attached to seven previously described streams. By attaching
std::cerr to combined stream, all seven streams will put the output, through combined
stream, to std::cerr.
