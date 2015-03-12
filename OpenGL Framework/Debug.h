#ifndef R_DEBUG_H_
#define R_DEBUG_H_
#include "RString.h"
namespace rb
{
	class Debug
	{
	public:
		static void Info(const string& infoText);
		static void Error(const string& errorText);
		static void Warning(const string& warningText);
	private:
		static void Log(const string& logText);
	};
}
#endif // !R_DEBUG_H_
