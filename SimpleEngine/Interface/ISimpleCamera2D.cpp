#include "stdafx.h"
#include "ISimpleCamera2D.h"
#include "SimpleCamera2D.h"
#include "SimpleEngine.h"
#include "SimpleRenderer.h"
void SimpleCamera2D_SetPosition(float x, float y) {
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetPosition(x, y);
}

void SimpleCamera2D_SetZoom(float zoom) {
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetZoom(zoom);
}

void SimpleCamera2D_SetMaxVisibleArea(float x, float y, float width, float height) {
	SimpleAABB aabb;
	aabb.position = { x,y,0.0f };
	aabb.size = { width, height };
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetMaxVisibleArea(aabb);
}

void SimpleCamera2D_Move(float dx, float dy) {
	SimpleEngine::Instance()->GetScene()->GetCamera()->Move(dx, dy);
}

void SimpleCamera2D_DeltaZoom(float dz) {
	SimpleEngine::Instance()->GetScene()->GetCamera()->DeltaZoom(dz);

}

void SimpleCamera2D_ZoomToArea(float x, float y, float width, float height) {
	SimpleAABB aabb;
	aabb.position = { x,y,0.0f };
	aabb.size = { width, height };

	SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(aabb);
}

void SimpleCamera2D_SetViewportSize(float w, float h) {

	SimpleEngine::Instance()->GetScene()->GetCamera()->SetViewportSize(w, h);

}

float SimpleCamera2D_GetWidth() {

	return SimpleEngine::Instance()->GetScene()->GetCamera()->GetWidth();

}

float SimpleCamera2D_GetHeight() {
	return SimpleEngine::Instance()->GetScene()->GetCamera()->GetHeight();
}

float SimpleCamera2D_GetZoom() {

	return SimpleEngine::Instance()->GetScene()->GetCamera()->GetZoom();
}


float SimpleCamera2D_GetMaxZoom() {
	return SimpleEngine::Instance()->GetScene()->GetCamera()->GetMaxZoom();
}

void SimpleCamera2D_ScreenToWorld(int& x, int& y) {
	
	glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ x,y});
	x = ret.x;
	y = ret.y;
}

void SimpleCamera2D_ViewportToWorld(int& x, int& y) {

	glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->ViewportToWorld({ x,y });
	x = ret.x;
	y = ret.y;
}

void SimpleCamera2D_WorldToScreen(int& x, int& y) {

	glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToScreen({ x,y });
	x = ret.x;
	y = ret.y;

}

void SimpleCamera2D_WorldToViewport(int& x, int& y) {

	glm::vec2 ret = SimpleEngine::Instance()->GetScene()->GetCamera()->WorldToViewport({ x,y });
	x = ret.x;
	y = ret.y;

}