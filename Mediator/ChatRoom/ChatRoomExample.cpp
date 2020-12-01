#include "ChatRoomPerson.h"
#include "ChatRoom.h"

void ChatRoomExample() {
	ChatRoomPerson jane{ "Jane" };
	ChatRoomPerson john{ "John" };
	ChatRoom room{};

	// no message will be broadcast here because there is no one else
	// in the room to broadcast to
	room.Join(&jane);

	// John's arrival will be broadcast to Jane
	room.Join(&john);

	jane.Say("Hello John!");

	john.PrivateMessage("Jane", "Hey Jane, thanks for welcoming me!");
}