#pragma once
#include <string>

using namespace std;

struct ChatRoom;

struct ChatRoomPerson {
	string m_name;
	ChatRoom* m_chatRoom{nullptr};

	ChatRoomPerson(const string& name) : m_name(name) {}

	void Receive(const string& source, const string& msg);
	void Say(const string& msg) const;
	void PrivateMessage(const string& receiverName, const string& msg) const;
	bool operator==(const ChatRoomPerson& other) const;
	bool operator!=(const ChatRoomPerson& other) const;
};