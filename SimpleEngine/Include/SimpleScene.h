#pragma once
#include "SimpleObject.h"
#include <vector>
#include "SimpleCamera2D.h"
#include "SimpleLayer.h"

class SimpleScene {
	//Only 1 camera per scene
	SimpleCamera2D* _camera;
	std::vector<SimpleLayer*> _layers;

public:

	SimpleScene();
	virtual ~SimpleScene();

	void Render(float dt);
	void Advance(float dt);
		
	inline SimpleCamera2D* GetCamera() { return _camera; };

	const std::vector<SimpleLayer*>& GetLayers() { return _layers; };
	
	void AddEntity(SimpleObject* sObj, SimpleLayer* sLayer);
	void RemoveEntity(SimpleObject* sObj, SimpleLayer* sLayer);

	void AddLayer(SimpleLayer* sLayer);
	void RemoveLayer(SimpleLayer* sLayer);
};
