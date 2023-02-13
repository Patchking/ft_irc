#pragma once
#include <map>
#include <vector>

namespace ft_irc {

class Channel {
public:
	typedef std::vector<int> container_type;
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
public:
	bool isOperator(int id) const;
	bool isSpeaker(int id) const;
	bool isCreep(int id) const;

	void addOperator(int id);
	void addSpeaker(int id);
	void removeOperator(int id);
	void removeSpeaker(int id);
	void removeCreep(int id);

	void addCreep(int id);

	template<class Object, class Ret>
	void for_each(Object& object, Ret (Object::*const function)(int)) const {
		for (container_type::const_iterator it = m_operators.begin()
				, end = m_operators.end()
				; it != end; ++it) {
			(object.*function)(*it);
		}
		for (container_type::const_iterator it = m_speakers.begin()
				, end = m_speakers.end()
				; it != end; ++it) {
			(object.*function)(*it);
		}
	}
private:
	container_type m_speakers;
	container_type m_operators;
	container_type m_creeps;
};

}
