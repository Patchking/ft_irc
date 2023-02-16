#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <map>
#include <vector>

namespace ft_irc {

class Channel {
public:
	typedef std::vector<int> container_type;
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
	enum Status {
		SUCCESS
		, SUCCESS_REMOVED
		, FAIL_IS_CREEP
		, FAIL_ALREADY_JOINED
		, FAIL_NOT_A_CREEP
		, FAIL_NOT_A_SPEAKER
		, FAIL_NOT_A_OPERATOR
		, FAIL_NOT_JOINED
		, REMOVED_SPEAKER
		, REMOVED_OPERATOR
	};
public:
	bool isOperator(int id) const;
	bool isSpeaker(int id) const;
	bool isCreep(int id) const;

	//does not check on speakers
	//may return SUCCESS FAIL_IS_CREEP FAIL_ALREADY_JOINED
	Status addOperator(int id);
	//does not check on operators
	//may return SUCCESS FAIL_IS_CREEP FAIL_ALREADY_JOINED
	Status addSpeaker(int id);
	//does check on speakers and operators
	//does remove a speaker or an operator if found
	//may return SUCCESS FAIL_IS_CREEP SUCCESS_REMOVED
	Status addCreep(int id);
	//make an existing speaker an operator
	Status op(int id);
	//make an existing operator a speaker
	Status deop(int id);

	//FAIL_NOT_JOINED REMOVED_SPEAKER REMOVED_OPERATOR
	Status remove(int id);

	bool removeOperator(int id);
	bool removeSpeaker(int id);
	bool removeCreep(int id);

	bool empty();

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


	container_type& getSpeakers();
	container_type& getOperators();
	const container_type& getSpeakers() const;
	const container_type& getOperators() const;
private:
	container_type m_speakers;
	container_type m_operators;
	container_type m_creeps;
};

}

#endif
