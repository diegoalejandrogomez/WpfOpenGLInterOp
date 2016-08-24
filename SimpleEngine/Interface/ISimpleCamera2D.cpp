#include "stdafx.h"
#include "ISimpleCamera2D.h"
#include "SimpleCamera2D.h"
#include "SimpleEngine.h"
#include "SimpleRenderer.h"

extern "C"
{
	SIMPLE_API void SimpleCamera2D_SetPosition(float x, float y) {
		SimpleEngine::Instance()->GetScene()->GetCamera()->SetPosition(x, y);
	}

	SIMPLE_API void SimpleCamera2D_SetZoom(float zoom) {
		SimpleEngine::Instance()->GetScene()->GetCamera()->SetZoom(zoom);
	}

	SIMPLE_API void SimpleCamera2D_SetMaxVisibleArea(float x, float y, float width, float height) {
		SimpleAABB aabb;
		aabb.position = { x,y,0.0f };
		aabb.size = { width, height };
		SimpleEngine::Instance()->GetScene()->GetCamera()->SetMaxVisibleArea(aabb);
	}

	SIMPLE_API void SimpleCamera2D_Move(float dx, float dy) {
		SimpleEngine::Instance()->GetScene()->GetCamera()->Move(dx, dy);
	}

	SIMPLE_API void SimpleCamera2D_DeltaZoom(float dz) {
		SimpleEngine::Instance()->GetScene()->GetCamera()->DeltaZoom(dz);

	}

	SIMPLE_API void SimpleCamera2D_ZoomToArea(float x, float y, float width, float height) {
		SimpleAABB aabb;
		aabb.position = { x,y,0.0f };
		aabb.size = { width, height };

		SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(aabb);
	}

	SIMPLE_API void SimpleCamera2D_SetViewportSize(float w, float h) {

		SimpleEngine::Instance()->GetScene()->GetCamera()->SetViewportSize(w, h);

	}

	SIMPLE_API float SimpleCamera2D_GetWidth() {

		return SimpleEngine::Instance()->GetScene()->GetCamera()->GetWidth();

	}

	SIMPLE_API float SimpleCamera2D_GetHeight() {
		return SimpleEngine::Instance()->GetScene()->GetCamera()->GetHeight();
	}

	SIMPLE_API float SimpleCamera2D_GetZoom() {

		return SimpleEngine::Instance()->GetScene()->GetCamera()->GetZoom();
	}


	SIMPLE_API float SimpleCamera2D_GetMaxZoom() {
		return SimpleEngine::Instance()->GetScene()->GetCamera()->GetMaxZoom();
	}

	SIMPLE_API void SimpleCamera2D_ScreenToWorld(float& x, float& y) {

		glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ x,y });
		x = ret.x;
		y = ret.y;
	}

	SIMPLE_API void SimpleCamera2D_ViewportToWorld(float& x, float& y) {

		glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->ViewportToWorld({ x,y });
		x = ret.x;
		y = ret.y;
	}

	SIMPLE_API void SimpleCamera2D_WorldToScreen(float& x, float& y) {

		glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToScreen({ x,y });
		x = ret.x;
		y = ret.y;

	}

	SIMPLE_API void SimpleCamera2D_WorldToViewport(float& x, float& y) {

		glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToViewport({ x,y });
		x = ret.x;
		y = ret.y;

	}
}