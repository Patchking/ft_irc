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
	m_operators.insert(
			std::lower_bound(m_operators.begin(), m_operators.end(), id)
			, id);
}

void Channel::addSpeaker(int id){
	m_operators.insert(
			std::lower_bound(m_speakers.begin(), m_speakers.end(), id)
			, id);
}

void Channel::addCreep(int id){
	m_operators.insert(
			std::lower_bound(m_creeps.begin(), m_creeps.end(), id)
			, id);
}

void Channel::removeOperator(int id) {
	iterator it = std::lower_bound(m_operators.begin(), m_operators.end(), id);
	if (it != m_operators.end() && *it == id)
		m_operators.erase(it);
}

void Channel::removeSpeaker(int id) {
	iterator it = std::lower_bound(m_speakers.begin(), m_speakers.end(), id);
	if (it != m_speakers.end() && *it == id)
		m_speakers.erase(it);
}

void Channel::removeCreep(int id) {
	iterator it = std::lower_bound(m_creeps.begin(), m_creeps.end(), id);
	if (it != m_creeps.end() && *it == id)
		m_creeps.erase(it);
}

}
