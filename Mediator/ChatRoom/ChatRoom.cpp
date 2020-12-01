#include <sstream>

#include "ChatRoom.h"
#include "ChatRoomPerson.h"

void ChatRoom::Join(ChatRoomPerson* person)
{
	auto joinMsg = person->m_name + " has joined the room!";
	BroadcastMsg("Room", joinMsg);

	person->m_chatRoom = this;
	m_personsInRoom.push_back(person);
}

void ChatRoom::BroadcastMsg(const string& origin, const string& msg)
{
	for (auto&& person : m_personsInRoom) {
		if (person->m_name == origin) {
			continue;
		}

		person->Receive(origin, msg);
	}
}

void ChatRoom::PrivateMessage(const ChatRoomPerson& sender, const string& receiverName, const string& msg)
{
	// looking for a person in the room with receiverName
	auto target = std::find_if(begin(m_personsInRoom), end(m_personsInRoom),
		// [&] means to implicitly capture the used automatic variables by reference instead of by copy
		[&](const ChatRoomPerson* p)
		{
			return p->m_name == receiverName;
		});

	// if a person was found, private message that person
	if (target != end(m_personsInRoom)) {
		(*target)->Receive(sender.m_name, msg);
	}
}
