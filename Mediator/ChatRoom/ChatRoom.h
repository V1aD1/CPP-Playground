#pragma once
#include <vector>
#include <string>

using namespace std;

struct ChatRoomPerson;

struct ChatRoom
{
	vector<ChatRoomPerson*> m_personsInRoom;
	void Join(ChatRoomPerson* person);
	void PrivateMessage(const ChatRoomPerson& sender, const string& receiverName, const string& msg);
	void BroadcastMsg(const string& origin, const string& msg);
};

