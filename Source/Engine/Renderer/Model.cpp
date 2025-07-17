#include "Model.h"
#include "Renderer.h"

namespace viper {
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale){
		// check if points is empty, if so return
		if (m_points.empty()) return;

		renderer.SetColor(m_color.r, m_color.g, m_color.b);

		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i].Rotate(rotation) * scale) + position;
			vec2 p2 = (m_points[i + 1].Rotate(rotation) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// Draws the model using the specified renderer and transformation.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the model.</param>
	/// <param name="transform">The transformation to apply, including position, rotation, and scale.</param>
	void Model::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
}
