#pragma once
#include "SimpleConfiguration.h"



//A 2D aabb living in a 3D world
struct SIMPLE_API SimpleAABB {

	enum ANCHOR_POINT {
		CENTER,
		LOWER_LEFT
	};

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(0.0f);
	ANCHOR_POINT anchor;

	SimpleAABB():anchor(CENTER) {
}
	SimpleAABB(glm::vec2 lowerLeft, glm::vec2 upperRight) :anchor(CENTER) {
		position.x = (upperRight.x + lowerLeft.x) * 0.5f;
		position.y = (upperRight.y + lowerLeft.y) * 0.5f;
		position.z = 0.0f ;
		size = (upperRight - lowerLeft);
	}

	const glm::vec3 LowerLeft() const{
		switch (anchor) {
		case LOWER_LEFT:
			return position;
			break;
		case CENTER:
		default:
			return{ position.x - 0.5f*size.x, position.y - 0.5f * size.y, 0.0f };
			break;
		}
	}

	const glm::vec3 Center() const {
		switch (anchor) {
		case LOWER_LEFT:
			return{ position.x + 0.5f*size.x, position.y + 0.5f * size.y, position.z };
			break;
		case CENTER:
		default:
			return position;
			break;
		}
	}

	const glm::vec3 UpperRight() const {
		switch (anchor) {
		case LOWER_LEFT:
			return{ position.x + size.x ,position.y + size.y, position.z };
			break;
		case CENTER:
		default:
			return{ position.x + 0.5f*size.x, position.y + 0.5f * size.y, position.z };
			break;
		}
	};
	void SetAnchor(ANCHOR_POINT anchor) { anchor = anchor; }

	bool Contains(float px, float py) const;
	bool Overlaps(const SimpleAABB &other) const;

	//Ok, we should have this in a separate class, but will keep them here for now... collision check using transformed AABB
	bool Contains(const glm::mat4& transform, float px, float py) const;
	bool Overlaps(const glm::mat4& transform, const SimpleAABB &other, const glm::mat4& otherTransform) const;
};
