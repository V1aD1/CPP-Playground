#include <iostream>

using namespace std;

// Want to draw some circles, either through rasterization or vectors
// If we aren't careful, this could lead to many objects, which isn't scalable, like:
// RasterizedCircle, VectorizedCircle etc.

namespace Bridge{
	struct Renderer {
		virtual void DrawCircle(float x, float y, float radius) = 0;
	};

	struct RasterizerRenderer : Renderer {
		// Inherited via Renderer
		virtual void DrawCircle(float x, float y, float radius) override
		{
			cout << "Rasterizing circle with coords: " << x << ", " << y << " and radius " << radius << endl;
		}
	};

	struct VectorRenderer : Renderer {
		// Inherited via Renderer
		virtual void DrawCircle(float x, float y, float radius) override
		{
			cout << "Vectorizing circle with coords: " << x << ", " << y << " and radius " << radius << endl;
		}
	};

	struct Shape {
	public:
		Shape(Renderer& rend, float x, float y) : m_renderer(rend), m_x(x), m_y(y) {}
		virtual void Draw() = 0;

	protected:
		// this renderer reference is the actual bridge!
		Renderer& m_renderer;
		float m_x, m_y;
	};

	struct Circle : Shape {
		Circle(Renderer& rend, float x, float y, float radius) : m_radius(radius), Shape(rend, x, y) {}

		virtual void Draw() override
		{
			m_renderer.DrawCircle(m_x, m_y, m_radius);
		}

	private:
		float m_radius;
	};
}

void BridgeExample() {
	using namespace Bridge;
	
	// now we don't have to create separate VectorizedCircle or RasterizedCircle classes,
	// we can just create the objects we want through aggregation!

	RasterizerRenderer rasterizer{};
	VectorRenderer vectorizer{};

	auto rasterizedCircle = Circle(rasterizer, 5, 5, 5);
	auto vectorizedCircle = Circle(vectorizer, 1, 1, 1);

	rasterizedCircle.Draw();
	vectorizedCircle.Draw();
}
