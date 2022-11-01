# cppLogger

A header-only C++17 logger.

It's thread-safe, and does not need to be instantiated.

## Basic Example

```cpp
#include <cppLogger.h>

int main()
{
  cppLogger::Logger::LogOpen("logs.txt");
  cppLogger::Logger::setPriority(cppLogger::LoggerPriority::Debug);

  DEBUGMSG("Hello World!");

  cppLogger::Logger::LogClose();
  return 0;
}
```

### Logger Priorities

```cpp
cppLogger::LoggerPriority::Error
cppLogger::LoggerPriority::Info
cppLogger::LoggerPriority::Debug
```
The default priority is Info.

### Details Printed

The logger prints the following details alongside the message:

* Date, in the format yyyy-mm-dd
* Time, in the format hh:mm:ss
* Thread ID
* Message Priority

### Sample Output

```
2022-11-02 01:48:17 [23372] [*] Log Opened.
2022-11-02 01:48:17 [23372] [DEBUG] Hello World!
2022-11-02 01:48:17 [23372] [*] Log Closed.
```
