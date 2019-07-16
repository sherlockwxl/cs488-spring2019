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
	Material material;

	// Mesh Identifier. This must correspond to an object name of
	// a loaded .obj file.
	std::string meshId;
	int textureId;
};
