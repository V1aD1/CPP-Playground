#include <iostream>

#include "ChatRoomPerson.h"
#include "ChatRoom.h"

void ChatRoomPerson::Receive(const string& source, const string& msg){
	cout << "[" << source << "]: " << msg << endl;
}

void ChatRoomPerson::Say(const string& msg) const {
	m_chatRoom->BroadcastMsg(m_name, msg);
}

void ChatRoomPerson::PrivateMessage(const string& receiverName, const string& msg) const{
	m_chatRoom->PrivateMessage(*this, receiverName, msg);
}

bool ChatRoomPerson::operator==(const ChatRoomPerson& other) const{
	return other.m_name == m_name;
}

bool ChatRoomPerson::operator!=(const ChatRoomPerson& other) const {
	return !(other == *this);
}
