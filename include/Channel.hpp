#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>

namespace ft_irc {

class Channel
{
private:
	std::vector<int>	speakers;
	std::vector<int>	operators;

	Channel();
	Channel(const Channel& copy);
	Channel	&operator=(const Channel& other);

public:
	virtual ~Channel();

	bool    isOperator(int id);
	bool    isSpeaker(int id);

	void    addOperator(int id);
	void	addSpeaker(int id);
	void    removeOperator(int id);
	void    removeSpeaker(int id);
};

}
