#include "Channel.hpp"

bool Channel::isSpeaker(int id) {
	for (size_t i = 0; i < speakers.size(); i++)
		if (speakers[i] == id)
			return true;
	return false;
}

bool Channel::isOperator(int id) {
	for (size_t i = 0; i < operators.size(); i++)
		if (operators[i] == id)
			return true;
	return false;
}

void Channel::addOperator(int id) {
    if (!isOperator(id))
        operators.push_back(id);
}

void	Channel::addSpeaker(int id){
    if (!isSpeaker(id))
        speakers.push_back(id);
}

void Channel::removeOperator(int id) {
    if (isOperator(id))
    {
        size_t  i;
        for (i = 0; i < operators.size(); i++)
            if (operators[i] == id)
                break;
        operators.erase(operators.begin() + i);
        if (operators.size() == 0 && users.size() > 0)
        {
            operators.push_back(users[0]);
            sendMessage("MODE " + this->name + " +o " + users[0]->getNickname() + "\n", user, true);
        }
    }
}

void Channel::removeSpeaker(int id) {
    if (isSpeaker(id))
    {
        size_t  i;
        for (i = 0; i < speakers.size(); i++)
            if (speakers[i] == id)
                break;
        speakers.erase(speakers.begin() + i);
    }
}

Channel::~Channel() {
}
