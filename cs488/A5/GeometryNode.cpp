// Winter 2019

#include "GeometryNode.hpp"

//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
		const std::string & meshId,
		const std::string & name,
		const int & textureId
)
	: SceneNode(name),
	  meshId(meshId),
	  textureId(textureId)
{
	m_nodeType = NodeType::GeometryNode;
}

/* GeometryNode::GeometryNode(
		const std::string & meshId,
		const std::string & name
)
	: SceneNode(name),
	  meshId(meshId)
{
	m_nodeType = NodeType::GeometryNode;
	textureId = 0;
}
 */