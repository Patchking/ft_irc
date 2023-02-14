#include <iostream>
#include <Channel.hpp>
#include <algorithm>

namespace ft_irc {

bool Channel::isSpeaker(int id) const {
	return std::binary_search(m_speakers.begin(), m_speakers.end(), id);
}

bool Channel::isCreep(int id) const {
	return std::binary_search(m_creeps.begin(), m_creeps.end(), id);
}

bool Channel::isOperator(int id) const {
	return std::binary_search(m_operators.begin(), m_operators.end(), id);
}

void Channel::addOperator(int id) {
	removeSpeaker(id);
	if (m_operators.empty())
		m_operators.push_back(id);
	else
	m_operators.insert(
			std::lower_bound(m_operators.begin(), m_operators.end(), id)
			, id);
}

void Channel::addSpeaker(int id) {
	removeOperator(id);
	if (m_speakers.empty())
		m_speakers.push_back(id);
	else
	m_operators.insert(
			std::lower_bound(m_speakers.begin(), m_speakers.end(), id)
			, id);
}

void Channel::addCreep(int id){
	if (m_creeps.empty())
		m_creeps.push_back(id);
	else
	m_operators.insert(
			std::lower_bound(m_creeps.begin(), m_creeps.end(), id)
			, id);
}

void Channel::removeOperator(int id) {
	if (m_operators.empty())
		return;
	iterator it = std::lower_bound(m_operators.begin(), m_operators.end(), id);
	if (it != m_operators.end() && *it == id)
		m_operators.erase(it);
}

void Channel::removeSpeaker(int id) {
	if (m_speakers.empty())
		return;
	iterator it = std::lower_bound(m_speakers.begin(), m_speakers.end(), id);
	if (it != m_speakers.end() && *it == id)
		m_speakers.erase(it);
}

void Channel::removeCreep(int id) {
	if (m_creeps.empty())
		return;
	iterator it = std::lower_bound(m_creeps.begin(), m_creeps.end(), id);
	if (it != m_creeps.end() && *it == id)
		m_creeps.erase(it);
}

}
