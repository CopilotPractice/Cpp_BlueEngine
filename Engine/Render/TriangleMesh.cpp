#include "TriangleMesh.h"
#include "Vertex.h"
#include "../Shader/Shader.h"

namespace Blue
{
	Blue::TriangleMesh::TriangleMesh()
	{
		std::vector<Vertex> vertices =
		{
			Vertex(Vector3(0.0f,0.5f,0.5f), Vector3(1.0f,0.0f,0.0f),Vector2(0.5f,0.0f)),
			Vertex(Vector3(0.5f, -0.5f,0.5f), Vector3(0.0f,1.0f,0.0f),Vector2(1.0f,1.0f)),
			Vertex(Vector3(-0.5f,-0.5f,0.5f), Vector3(0.0f,0.0f,1.0f),Vector2(0.0f,1.0f))
		};

		std::vector<uint32> indices = { 0,1,2 };
		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		shaders.emplace_back(std::make_shared<Shader>()); // 머티리얼 = shader
	}
}