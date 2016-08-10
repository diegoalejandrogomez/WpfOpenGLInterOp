#pragma once
#include "SimpleObject.h"
#include <vector>
#include "SimpleCamera2D.h"
#include "SimpleLayer.h"
#include "SimpleAABB.h"

class SimpleScene {
	//Only 1 camera per scene
	SimpleCamera2D* _camera;
	std::vector<SimpleLayer*> _layers;

	//Scene queries (all the coords are in world space). The queries aren't reentrant
	//BTW We should implement a quadtree or somtheing like that... for now... O(n)
	const int _maxQueryResults = 10;
	std::vector<SimpleObject*> _queryResults;

public:

	SimpleScene();
	virtual ~SimpleScene();

	void Render(float dt);
	void Advance(float dt);
		
	inline SimpleCamera2D* GetCamera() { return _camera; };

	const std::vector<SimpleLayer*>& GetLayers() { return _layers; };
	
	void AddEntity(SimpleObject* sObj, SimpleLayer* sLayer);
	void AddEntity(SimpleObject* sObj, int nLayer);
	void AddEntity(SimpleObject* sObj, std::string layerName);

	void RemoveEntity(SimpleObject* sObj, SimpleLayer* sLayer);

	void AddLayer(SimpleLayer* sLayer);
	void RemoveLayer(SimpleLayer* sLayer);

	SimpleLayer* GetLayer(int nLayer);
	SimpleLayer* GetLayer(std::string layerName);
	inline std::vector<SimpleLayer*>& GetLayers(std::string layerName) { return _layers; }
	

	float GetLowerZIndex();

	float GetFPS(); 
	
	
	

	//Returns all the entities at point
	std::vector<SimpleObject*>& PickAll(glm::vec2 point);
	//Returns all the entities at point from a given layer
	std::vector<SimpleObject*>& SimpleScene::PickAll(glm::vec2 point, SimpleLayer* l);

	//Returns all the entities that overlap rect
	std::vector<SimpleObject*>& PickAll(SimpleAABB rect);
	//Returns all the entities that overlap rect from a given layer
	std::vector<SimpleObject*>& PickAll(SimpleAABB rect, SimpleLayer* l);

	//Returns the first entity at point
	SimpleObject* PickFirst(glm::vec2 point);
	SimpleObject* PickFirst(glm::vec2 point, SimpleLayer* l);

	//Returns the first entity that overlaps
	SimpleObject* PickFirst(SimpleAABB rect);
	//Returns the first entity that overlaps from a given layer
	SimpleObject* PickFirst(SimpleAABB rect, SimpleLayer* l);


};
