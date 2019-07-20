// Winter 2019

#pragma once

#include "SceneNode.hpp"

class GeometryNode : public SceneNode {
public:
	GeometryNode(
		const std::string & meshId,
		const std::string & name,
		const int & textureId
	);
/* 	GeometryNode(
		const std::string & meshId,
		const std::string & name
	); */
	bool isHit = false;
	int hitTimeCount = 0;
	bool particleTriggered = false;
	int status = 0;// 0 for fefault, -1 for attack, 1 for defence
	Material material;

	// Mesh Identifier. This must correspond to an object name of
	// a loaded .obj file.
	std::string meshId;
	int textureId;
};
