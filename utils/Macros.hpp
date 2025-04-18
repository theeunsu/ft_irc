/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:12:09 by smiranda          #+#    #+#             */
/*   Updated: 2025/04/17 15:01:43 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// colors
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_WHITE "\033[37m"
#define COLOR_BOLD "\033[1m"

// Errors
#define ERR_NOSUCHNICK(server, nick) (":" + server + " 401 " + nick + " :No such nick/channel")
#define ERR_NOSUCHCHANEL(server, channel) (":" + server + " 403 " + channel + " : No such channel")
#define ERR_CANNOTSENDTOCHAN(server, channel) (":" + server + " 404 " + channel + " :Cannot send to channel")
#define ERR_UNKNOWNCOMMAND(server, command) (":" + server + " 421 " + command + " :Unknown command")
#define ERR_NONICKNAMEGIVEN(server) (":" + server + " 431 * :No nickname given")
#define ERR_ERRONEUSNICKNAME(server, nick) (":" + server + " 432 " + nick + " :Erroneous nickname")
#define ERR_NICKNAMEINUSE(server, nick) (":" + server + " 433 " + nick + " :Nickname already in use")
#define ERR_USERNOTINCHANNEL(server, nick, channel) (":" + server + " 441 " + nick + channel " :They aren't on that channel")
#define ERR_NOTONCHANNEL(server, channel) (":" + server + " 442 " + channel + " :You're not on that channel")
#define ERR_NOTREGISTERED(server) (":" + server + " 451 :You have not registered")
#define ERR_NEEDMOREPARAMS(server, command) (":" + server + " 461 " + command + " :Not enough parameters")
#define ERR_ALREADYREGISTRED(server) (":" + server + " 462 :Unauthorized command (already registered)")
#define ERR_PASSWDMISMATCH(server) (":" + server + " 464 :Password incorrect")
#define ERR_CHANNELISFULL(server, channel) (":" + server + " 471 " + channel + " :Cannot join channel (+l)")
#define ERR_UNKNOWNMODE(server, char, channel) (":" + server + " 472 " + char + " :is unknown mode char to me for " + channel)
#define ERR_INVITEONLYCHAN(server, channel) (":" + server + " 473 " + channel + " :Cannot join channel (+i)")
#define ERR_BADCHANNELKEY(server, channel) (":" + server + " 475 " + channel + " :Cannot join channel (+k)")
#define ERR_CHANOPRIVISNEEDED(server, channel) (":" + server + " 482 " + channel + " :You're not channel operator")
#define ERR_UMODEUNKNOWNFLAG(server) (":" + server + " 501 :Unknown MODE flag")