#include <vector>
#include <iostream>
#include <string>

using namespace std;

// We want to have shapes that we can interact with (move, resize), but we also want to be
// able to select multiple shapes, and then apply the same operations to them all at once

namespace Composite {
	struct GraphicObject {
		virtual void Draw() = 0;
	};

	struct Circle :GraphicObject {
		virtual void Draw() override
		{
			cout << "Drawing a circle" << endl;
		}
	};

	struct Group :GraphicObject {

		string m_name;
		vector<GraphicObject*> objects;

		Group(string name) : m_name(name) {}

		virtual void Draw() override
		{
			cout << "Group name: " << m_name << " with containing objects: " << endl;
			for (auto&& o : objects) {
				o->Draw();
			}
		}
	};
}

void CompositeExample() {
	using namespace Composite;

	Group group{ "Group 1" };
	Circle circle1{};
	Circle circle2{};

	// the cool part is that we can create a subgroup, and add it to a group!
	Group subgroup{ "Subgroup 1" };
	subgroup.objects.push_back(&circle2);

	group.objects.push_back(&circle1);
	group.objects.push_back(&subgroup);

	group.Draw();
}