#include "tnahpch.h"
#include "Log.h"

namespace tnah
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		SetLoggerCoreMode();
		s_CoreLogger = spdlog::stdout_color_mt("TNAH Core");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("TNAH App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::SetLoggerDebugMode()
	{
		//Ref https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		//Inserts the path and line of the file calling the logger
		//
		// {12h Clock} Source:Line (FunctionName) LoggerName (LogLevel): Message
		spdlog::set_pattern("%^{%r} %s:%# (%!) %n (%l): %v%$");
	}

	void Log::SetLoggerCoreMode()
	{
		//Ref https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		//
		// {12h Clock} LoggerName (LogLevel): Message
		spdlog::set_pattern("%^{%r} %n (%l): %v%$");
	}

}
