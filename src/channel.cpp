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

static inline
Channel::Status add(Channel::container_type& container, int id) {
	Channel::iterator location
		= std::lower_bound(container.begin(), container.end(), id);
	if (container.end() == location) {
		container.push_back(id);
		return Channel::SUCCESS;
	}
	if (*location == id)
		return Channel::FAIL_ALREADY_JOINED;
	else
	container.insert(location, id);
	return Channel::SUCCESS;
}

Channel::Status Channel::addOperator(int id) {
	if (isCreep(id))
		return FAIL_IS_CREEP;
	return add(m_operators, id);
}

Channel::Status Channel::addSpeaker(int id) {
	if (isCreep(id))
		return FAIL_IS_CREEP;
	return add(m_speakers, id);
}

Channel::Status Channel::addCreep(int id) {
	Channel::Status status = add(m_creeps, id);
	if (SUCCESS == status)
		return Channel::Status(removeOperator(id) or removeSpeaker(id));
	else
		return FAIL_IS_CREEP;
	return SUCCESS;
}

Channel::Status Channel::op(int id) {
	const bool removed = removeSpeaker(id);
	if (not removed)
		return FAIL_NOT_A_SPEAKER;
	return add(m_operators, id);
}

Channel::Status Channel::deop(int id) {
	const bool removed = removeOperator(id);
	if (not removed) {
		return FAIL_NOT_A_OPERATOR;
	}
	return add(m_speakers, id);
}

Channel::Status Channel::remove(int id) {
	if (removeOperator(id))
		return REMOVED_OPERATOR;
	if (removeSpeaker(id))
		return REMOVED_SPEAKER;
	return FAIL_NOT_JOINED;
}

bool Channel::removeOperator(int id) {
	if (m_operators.empty())
		return false;
	iterator it = std::lower_bound(m_operators.begin(), m_operators.end(), id);
	if (it != m_operators.end() && *it == id) {
		m_operators.erase(it);
		return true;
	}
	return false;
}

bool Channel::removeSpeaker(int id) {
	if (m_speakers.empty())
		return false;
	iterator it = std::lower_bound(m_speakers.begin(), m_speakers.end(), id);
	if (it != m_speakers.end() && *it == id) {
		m_speakers.erase(it);
		return true;
	}
	return false;
}

bool Channel::removeCreep(int id) {
	if (m_creeps.empty())
		return false;
	iterator it = std::lower_bound(m_creeps.begin(), m_creeps.end(), id);
	if (it != m_creeps.end() && *it == id) {
		m_creeps.erase(it);
		return true;
	}
	return false;
}

bool Channel::empty() {
	return m_operators.empty() && m_speakers.empty();
}

Channel::container_type& Channel::getSpeakers() {
	return m_speakers;
}
Channel::container_type& Channel::getOperators() {
	return m_operators;
}
const Channel::container_type& Channel::getSpeakers() const {
	return m_speakers;
}
const Channel::container_type& Channel::getOperators() const {
	return m_operators;
}

}
