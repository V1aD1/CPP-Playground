#include <string>
#include <iostream>

using namespace std;

namespace VirtualProxy {
	struct Image {
		virtual void draw() = 0;
	};

	struct Bitmap : Image {

		Bitmap(const string& filename) {
			cout << "Loaded bitmap from file: " << filename << endl;
			
			// obviously the loading process would be more complicated
			// this is just an example
			m_bitmapData = filename;
		}

		virtual void draw() override
		{
			cout << "Drawing bitmap: " << m_bitmapData << endl;
		}

	private:
		string m_bitmapData;
	};

	// ok but requirements have changed!! We've realized loading a bitmap is SUPER demanding.
	// We've also realized that most bitmaps never end up getting drawn. So now we
	// want to load the bitmap ONLY if we actually end up drawing something. 
	// A lazy Bitmap, if you will.
	// 
	// BUT we can't go back and change Bitmap's implementation, because that would violate
	// the open-closed principle!!
	// Instead, let's create a virtual proxy object called LazyBitmap that fulfills our requirements

	struct LazyBitmap : Image {
		
		LazyBitmap(const string& filename): m_filename(filename){
			cout << "Initialized LazyBitmap" << endl;
		}

		virtual void draw() override
		{
			cout << "About to draw" << endl;
			if (!m_bmp)
				m_bmp = new Bitmap{ m_filename };
			m_bmp->draw();
		}

	private:
		string m_filename;
		Bitmap* m_bmp{ nullptr };
	};
}

void VirtualProxyExample() {
	using namespace VirtualProxy;

	// inneficient bit map since it's loaded regardless of whether it gets drawn
	Bitmap bitmap{ "someFile" };
	bitmap.draw();

	cout << endl;

	// efficient bit map since it only loads bitmap if it needs to draw
	LazyBitmap betterBitMap{ "someFile" };
	betterBitMap.draw();
}