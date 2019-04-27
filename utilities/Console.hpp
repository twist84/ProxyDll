#pragma once
#include <windows.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Utils.hpp"

#pragma warning(disable:4273)
BOOL WINAPI MoveWindow(_In_ HWND hWnd, _In_ int NewWidth, _In_ int NewHeight, _In_ int WindowWidth, _In_ int WindowHeight, _In_ BOOL bRepaint);

namespace Console
{
	// Base class for objects which handle console output.
	class ConsoleOutputHandler
	{
	public:
		virtual ~ConsoleOutputHandler() {}

		// Writes a line to the output.
		virtual void WriteLine(const std::string &line) = 0;
		virtual void WriteLines(std::vector<std::string> lines) = 0;
	};

	// Get the consoles allocation.
	bool IsAllocated();

	// Initializes the console.
	void Init(const std::string& initLine);

	// Writes one or more lines to the console.
	void WriteLine(const std::string &line);

	// Writes lines in a vector to the console.
	void WriteLines(const std::vector<std::string> lines);

	// Registers an output handler.
	void RegisterHandler(std::shared_ptr<ConsoleOutputHandler> handler);


	std::vector<std::shared_ptr<ConsoleOutputHandler>> Handlers;

	class LogConsoleOutputHandler : public ConsoleOutputHandler
	{
	public:
		void WriteLine(const std::string &line) override;
		void WriteLines(const std::vector<std::string> lines) override;
	};

	bool is_allocated = false;

	bool IsAllocated()
	{
		return is_allocated;
	}

	inline void Init(const std::string &initLine)
	{
		is_allocated = AllocConsole();

		// Register a log output by default
		RegisterHandler(std::make_shared<LogConsoleOutputHandler>());

		WriteLine(initLine);
	}

	inline void WriteLine(const std::string &line)
	{
		// Split the string into lines and send each line to each handler
		// This makes things easy for all of the handlers
		auto lines = Utils::String::SplitString(line, '\n');
		for (auto &&lineToPrint : lines)
		{
			for (auto &&handler : Handlers)
				handler->WriteLine(lineToPrint);
		}
	}
	inline void WriteLines(const std::vector<std::string> lines)
	{
		for (auto&& lineToPrint : lines)
		{
			for (auto&& handler : Handlers)
				handler->WriteLine(lineToPrint);
		}
	}

	inline void RegisterHandler(std::shared_ptr<ConsoleOutputHandler> handler)
	{
		Handlers.push_back(handler);
	}

	inline void LogConsoleOutputHandler::WriteLine(const std::string &line)
	{
		std::stringstream ss;
		ss << line << std::endl;
		Utils::Con(ss.str());
		//Utils::Log(ss.str(), (".\\bin\\" + ProxyManager.Name + ".txt"));
	}

	inline void LogConsoleOutputHandler::WriteLines(const std::vector<std::string> lines)
	{
		for (auto&& lineToLog : lines)
		{
			std::stringstream ss;
			ss << lineToLog << std::endl;
			Utils::Con(ss.str());
			//Utils::Log(ss.str(), (".\\bin\\" + ProxyManager.Name + ".txt"));
		}
	}

	bool Resize(int nWidth, int nHeight, int cOffX = 0, int cOffY = 0)
	{
		return MoveWindow(GetConsoleWindow(), ((GetSystemMetrics(SM_CXSCREEN) - nWidth)) / 2 - cOffX, ((GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2) + cOffY, nWidth, nHeight, TRUE);
	}
}
