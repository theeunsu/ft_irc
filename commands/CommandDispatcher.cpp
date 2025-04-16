/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandDispatcher.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:33:36 by eahn              #+#    #+#             */
/*   Updated: 2025/04/17 01:02:15 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandDispatcher.hpp"
#include "../utils/Logger.hpp"
#include <iostream>
#include <sys/socket.h> // for send()

CommandDispatcher::CommandDispatcher()
{
    addCommand("NICK", &CommandDispatcher::cmdNick);
    addCommand("USER", &CommandDispatcher::cmdUser);
    addCommand("JOIN", &CommandDispatcher::cmdJoin);
    addCommand("PRIVMSG", &CommandDispatcher::cmdMsg);
    addCommand("QUIT", &CommandDispatcher::cmdQuit);
    addCommand("PING", &CommandDispatcher::cmdPing);
    addCommand("PONG", &CommandDispatcher::cmdPong);
    addCommand("TOPIC", &CommandDispatcher::cmdTopic);
    addCommand("KICK", &CommandDispatcher::cmdKick);
    addCommand("INVITE", &CommandDispatcher::cmdInvite);
    addCommand("MODE", &CommandDispatcher::cmdMode);
    addCommand("PART", &CommandDispatcher::cmdPart);
}

CommandDispatcher::~CommandDispatcher() {}

void CommandDispatcher::addCommand(const std::string& name, CommandHandler handler)
{
    commandTable[name] = std::bind(handler, this, std::placeholders::_1, std::placeholders::_2);
}

void CommandDispatcher::dispatch(int clientFd, const ParsedCommand& cmd)
{
    if (cmd.command.empty()) {
        Logger::warning("Empty command received from fd=" + std::to_string(clientFd));
        return;
    }

    auto it = commandTable.find(cmd.command);
    if (it != commandTable.end()) {
        Logger::info("Dispatching command: " + cmd.command + " from fd=" + std::to_string(clientFd));
        it->second(clientFd, cmd.params);
    } else {
        Logger::warning("Unknown command: " + cmd.command + " from fd=" + std::to_string(clientFd));
    }
}

// To do by Siria : implement all command handlers

// Example: NICK command handler
void CommandDispatcher::cmdNick(int fd, const std::vector<std::string>& params)
{
    // Check if nickname was provided
    if (params.empty()) {
        Logger::warning("NICK: no nickname provided from fd=" + std::to_string(fd));
        std::string err = "431 :No nickname given\r\n";
        send(fd, err.c_str(), err.length(), 0);  // Send error message to client
        return;
    }

    std::string newNick = params[0];

    // TODO: Check if nickname is already in use (via ClientManager)
    // if (clientManager.nickExists(newNick)) {
    //     std::string err = "433 " + newNick + " :Nickname is already in use\r\n";
    //     send(fd, err.c_str(), err.length(), 0);
    //     return;
    // }

    // TODO: Set nickname in ClientManager
    // clientManager.setNickname(fd, newNick);

    Logger::info("NICK command accepted: " + newNick + " (fd=" + std::to_string(fd) + ")");

    std::string msg = ":" + newNick + " NICK " + newNick + "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);  // Send success response
}

/**
 * ✨ Tips for Siria
All handlers follow the same pattern:
	- Validate params
	- Possibly interact with ClientManager or ChannelManager
	- Respond with send(fd, message...)
All IRC responses must end with \r\n (per IRC protocol)
Use Logger::log(...) for colored, categorized logs (Info, Warning, Error, etc.)
 */


// To do
void CommandDispatcher::cmdUser(int fd, const std::vector<std::string>& params)
{

}
