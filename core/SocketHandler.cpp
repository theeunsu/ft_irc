/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoklova <msoklova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:03:14 by eahn              #+#    #+#             */
/*   Updated: 2025/04/26 14:42:41 by msoklova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketHandler.hpp"

SocketHandler::SocketHandler(std::vector<struct pollfd>& pollFds, CommandHandler& handler, Server& server)
    : pollFds_(pollFds), commandHandler_(handler), server_(server) {}

SocketHandler::~SocketHandler() {}

void SocketHandler::acceptConnection(int listenFd)
{
	sockaddr_in clientAddr;
	socklen_t addrLen = sizeof(clientAddr);

	int clientFd = accept(listenFd, (struct sockaddr*)&clientAddr, &addrLen);
	if (clientFd < 0)
	{
		Logger::warning("accept() failed");
		return;
	}

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
	{
		Logger::warning("Failed to set non-blocking mode for client");
		close(clientFd);
		return;
	}
	std::string ipAddress = inet_ntoa(clientAddr.sin_addr);
	server_.getClients()[clientFd] = Client(ipAddress, clientFd);

	addClientSocket(clientFd);
	Logger::log(LogLevel::Connection, "New client connected: fd=" + std::to_string(clientFd));
}

void SocketHandler::receiveMessage(int clientFd)
{
	char buffer[1024] = {0};
	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead <= 0)
	{
		if (bytesRead == 0)
			Logger::log(LogLevel::Disconnection, "Client disconnected");
		else
			Logger::warning("recv() failed on fd = " + std::to_string(clientFd));
		disconnectClient(clientFd);
		return;
	}

	std::string message(buffer);
	//Logger::log(LogLevel::Privmsg, "Message from fd " + std::to_string(clientFd) + ": " + message);
	//Logger::log(LogLevel::Info, "Received message from fd " + std::to_string(clientFd) + ": " + message);

	std::stringstream ss(message);
    std::string line;
    while (std::getline(ss, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty()) continue;

        ParsedCommand parsed = InputParser::parse(line);
        commandHandler_.dispatch(clientFd, parsed);
    }
}

void SocketHandler::addClientSocket(int clientFd)
{
	struct pollfd clientPoll =
	{
		.fd = clientFd,
		.events = POLLIN,
		.revents = 0
	};
	pollFds_.push_back(clientPoll);
}


void SocketHandler::disconnectClient(int clientFd)
{
	close(clientFd);

	for (auto it = pollFds_.begin(); it != pollFds_.end(); ++it) {
		if (it->fd == clientFd) {
			pollFds_.erase(it);
			break;
		}
	}

	Logger::log(LogLevel::Disconnection, "Closed and removed client fd " + std::to_string(clientFd));
}
