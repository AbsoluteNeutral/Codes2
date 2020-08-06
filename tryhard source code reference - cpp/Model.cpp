#include "stdafx.h"
#include "Model.h"
#include "MeshRenderer.h"

static std::map<size_t, Model*>	MODEL_POOL;

Model::Model()
	: VAO(0)
	, VBO(0)
	, EBO(0)
	, meshes{}
	, vertices{}
	, indices{}
	, filename{}
	, nodes{}
	, boneCount{0}
	, hasAnims(false)
	, animations{}
	, channelMap{}
	, boneMap{}
	, parentBones{}
	, boneOffsets{}
	, scalingMat{}
	, scalingFactor(0.01f)
{
	scalingMat = BuildScale4x4(zg::Vector3{ scalingFactor, scalingFactor, scalingFactor });
}

void DeleteAllNodes(INode* node)
{
	//for (auto &elem : node->childNodes)
	//	DeleteAllNodes(elem);
	//delete node;
}

Model::~Model(){
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	//DeleteAllNodes(nodes);
}

void Model::LoadCustomModel(const std::string & path) // Custom Model Format, requirement of GAM300
{
	//std::fstream file;
	FILE* file;
	fopen_s(&file, path.c_str(), "r");
	//file.open(path, std::ios::in);

	if (file != NULL)
	{
		const int bufSz = 1024;
		char buf[bufSz], str[bufSz];
		int n;
		//int size;
		zg::Matrix44 mat;
		bool loadTan = false;

		ZeroMemory(buf, bufSz);
		ZeroMemory(str, bufSz);
		fgets(buf, bufSz, file);
		//fgets(buf, bufSz, file);

		if (buf[0] == 'v')
		{
			loadTan = true;
		}

		fgets(buf, bufSz, file);

		int meshCount = 0;
		float getSize = scalingFactor;
		sscanf(buf, "%f %d", &getSize, &meshCount);

		scalingMat = BuildScale4x4(zg::Vector3{ getSize, getSize, getSize });
		scalingFactor = getSize;

		//printf("%s, %d\n", path.c_str(), size);
		fgets(buf, bufSz, file);

		for (int i = 0; i < meshCount; ++i)
		{
			meshes.emplace_back();
			sscanf(buf, "%d %d %d", &meshes.back().IndiceCount, &meshes.back().BaseVertex, &meshes.back().BaseIndex);
			fgets(buf, bufSz, file);
		}

		IVertex v;
		while (buf[0] != 'I')
		{
			//sscanf(buf, "\tV %f %f %f", &v.position.x, &v.position.y, &v.position.z);
			//fgets(buf, bufSz, file); //Normals
			//sscanf(buf, "\tN %f %f %f", &v.normal.x, &v.normal.y, &v.normal.z);
			//fgets(buf, bufSz, file); //UVs
			//sscanf(buf, "\tU %f %f", &v.uv.x, &v.uv.y);
			//fgets(buf, bufSz, file); //Weights
			//sscanf(buf, "\tW %f %f %f %f", &v.weights.x, &v.weights.y, &v.weights.z, &v.weights.w);
			//fgets(buf, bufSz, file); //Joints
			//sscanf(buf, "\tJ %f %f %f %f", &v.joints.x, &v.joints.y, &v.joints.z, &v.joints.w);
			//if (loadTan)
			//{
			//	fgets(buf, bufSz, file); //Tangents
			//	sscanf(buf, "\tT %f %f %f", &v.tangent.x, &v.tangent.y, &v.tangent.z);
			//}

			if (loadTan)
			{
				sscanf(buf, "\tV %f %f %f N %f %f %f U %f %f W %f %f %f %f J %f %f %f %f T %f %f %f"
					, &v.position.x, &v.position.y, &v.position.z
					, &v.normal.x, &v.normal.y, &v.normal.z
					, &v.uv.x, &v.uv.y
					, &v.weights.x, &v.weights.y, &v.weights.z, &v.weights.w
					, &v.joints.x, &v.joints.y, &v.joints.z, &v.joints.w
					, &v.tangent.x, &v.tangent.y, &v.tangent.z
				);
			}
			else {
				sscanf(buf, "\tV %f %f %f N %f %f %f U %f %f W %f %f %f %f J %f %f %f %f"
					, &v.position.x, &v.position.y, &v.position.z
					, &v.normal.x, &v.normal.y, &v.normal.z
					, &v.uv.x, &v.uv.y
					, &v.weights.x, &v.weights.y, &v.weights.z, &v.weights.w
					, &v.joints.x, &v.joints.y, &v.joints.z, &v.joints.w
				);
			}

			vertices.push_back(v);
			fgets(buf, bufSz, file); //Maybe Vertices
		} //Exits when read I #

		size_t indexSize = 0;
		sscanf(buf, "I %d", &indexSize);
		indices.reserve(indexSize);

		fgets(buf, bufSz, file); //Maybe Indices

		int n1 = 0, n2 = 0, n3 = 0;
		while (buf[0] != 'N')
		{
			sscanf(buf, "%d %d %d", &n1, &n2, &n3);
			indices.push_back(n1);
			indices.push_back(n2);
			indices.push_back(n3);
			fgets(buf, bufSz, file); //Maybe Indices
		} //Exits when read N START

		//nodes = new INode{};
		//nodes->parent = nullptr;
		AddNode(file, &nodes, buf, bufSz);


		animations.reserve(32);
		channelMap.reserve(2048);
		int id = 0;

		while (buf[0] == 'A')
		{
			animations.emplace_back();
			auto& currA = animations.back();
			currA.channels.reserve(128);

			//fgets(buf, bufSz, file);
			//sscanf_s(buf, "\t%s", str, bufSz);
			//currA.name = GetHashFromString2(str);
			//
			//fgets(buf, bufSz, file);
			//sscanf(buf, "\t%f", &currA.duration);
			//
			//fgets(buf, bufSz, file);
			//sscanf(buf, "\t%f", &currA.ticksPerSecond);
			sscanf_s(buf, "A START %f %f %s", &currA.duration, &currA.ticksPerSecond, str, bufSz);
			currA.name = GetHashFromString2(str);
			channelMap.emplace_back(std::map<size_t, AnimationChannel*>{});
			fgets(buf, bufSz, file);

			while (buf[0] != 'A' && buf[2] != 'E')
			{
				
				currA.channels.emplace_back();
				auto& currC = currA.channels.back();

				sscanf_s(buf, "%s", str, bufSz);
				currC.name = GetHashFromString2(str);

				fgets(buf, bufSz, file);
				sscanf(buf, "PK%d", &currC.posKeyCount);

				for (auto i = 0u; i < currC.posKeyCount; ++i)
				{
					currC.posKeys.emplace_back();

					fgets(buf, bufSz, file);
					sscanf(buf, "\t%f %f %f %f", &currC.posKeys[i].time, &currC.posKeys[i].value.x, &currC.posKeys[i].value.y, &currC.posKeys[i].value.z);
				}

				fgets(buf, bufSz, file);
				sscanf_s(buf, "SK%d", &currC.scaleKeyCount);

				for (auto i = 0u; i < currC.scaleKeyCount; ++i)
				{
					currC.scaleKeys.emplace_back();

					fgets(buf, bufSz, file);
					sscanf(buf, "\t%f %f %f %f", &currC.scaleKeys[i].time, &currC.scaleKeys[i].value.x, &currC.scaleKeys[i].value.y, &currC.scaleKeys[i].value.z);

				}

				fgets(buf, bufSz, file);
				sscanf_s(buf, "RK%d", &currC.rotKeyCount);

				for (auto i = 0u; i < currC.rotKeyCount; ++i)
				{
					currC.rotKeys.emplace_back();

					fgets(buf, bufSz, file);
					sscanf(buf, "\t%f %f %f %f %f", &currC.rotKeys[i].time, &currC.rotKeys[i].value.x, &currC.rotKeys[i].value.y, &currC.rotKeys[i].value.z, &currC.rotKeys[i].value.w);
				}

				fgets(buf, bufSz, file);

				channelMap[id][currC.name] = &currC;
			}
			++id;

			fgets(buf, bufSz, file);
			//printf("Channels: %d\n", currA.channels.size());
		}

		sscanf(buf, "B %d", &boneCount);

		for (auto i = 0u; i < boneCount; ++i)
		{
			fgets(buf, bufSz, file);
			sscanf_s(buf, "%d %s", &n, str, bufSz);
			boneMap[GetHashFromString2(str)] = n;
		}

		fgets(buf, bufSz, file);
		while (buf != NULL && buf[1] == 'O')
		{
			fgets(buf, bufSz, file);
			sscanf(buf, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f"
				, &mat.m[0], &mat.m[1], &mat.m[2], &mat.m[3]
				, &mat.m[4], &mat.m[5], &mat.m[6], &mat.m[7]
				, &mat.m[8], &mat.m[9], &mat.m[10], &mat.m[11]
				, &mat.m[12], &mat.m[13], &mat.m[14], &mat.m[15]
			);
			boneOffsets.push_back(mat);

			fgets(buf, bufSz, file);
		}

		fclose(file);
	}

	//printf("Anims: %d, ChannelMap: %d\n", animations.size(), channelMap.size());

	if (animations.size())
		hasAnims = true;

	FindParentBones(&nodes);
}

void Model::Init()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(IVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)offsetof(IVertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)offsetof(IVertex, uv));
	// weights
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)offsetof(IVertex, weights));
	// joint IDs
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)offsetof(IVertex, joints));
	// tangents
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(IVertex), (void*)offsetof(IVertex, tangent));

	glBindVertexArray(0);
}

//void Model::Draw(const Camera* cam, const MeshRenderer* s)
//{
//	UNREFERENCED_PARAMETER(cam);
//	//UNREFERENCED_PARAMETER(ls);
//	s->material->SendInt("anim", hasAnims ? 1 : 0);
//	s->material->SendBool("receiveShadows", s->receiveShadows);
//	s->material->SendBool("bloom", s->bloom);
//	s->material->SendMat4("modelScale", scalingMat);
//	s->material->SendMat4("model", s->owner->transform.worldMatrix);
//	s->material->SendVec4("color", s->color);
//
//	glBindVertexArray(VAO);
//
//	for (auto i = 0u; i < meshes.size(); ++i)
//		glDrawElementsBaseVertex(GL_TRIANGLES, meshes[i].IndiceCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * meshes[i].BaseIndex), meshes[i].BaseVertex);
//
//	glBindVertexArray(0);
//}

void Model::Draw()
{
	glBindVertexArray(VAO);
	for (auto i = 0u; i < meshes.size(); ++i)
		glDrawElementsBaseVertex(GL_TRIANGLES, meshes[i].IndiceCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * meshes[i].BaseIndex), meshes[i].BaseVertex);
	glBindVertexArray(0);
}

void Model::AddNode(FILE* file, INode* n, char* b, unsigned int sz)
{
	//N START
	if (b[2] == 'S')
	{
		const int bufSz = 1024;
		char str[bufSz];
		ZeroMemory(str, bufSz);
		zg::Matrix44 mat;
		//Name
		fgets(b, sz, file);
		sscanf_s(b, "\t%s", str, bufSz);

		//Matrix 4x4
		fgets(b, sz, file);
		sscanf(b, "\t%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f"
			, &mat.m[0], &mat.m[1], &mat.m[2], &mat.m[3]
			, &mat.m[4], &mat.m[5], &mat.m[6], &mat.m[7]
			, &mat.m[8], &mat.m[9], &mat.m[10], &mat.m[11]
			, &mat.m[12], &mat.m[13], &mat.m[14], &mat.m[15]
		);

		//Empty Line
		//fgets(b, sz, file);

		n->name = GetHashFromString2(str);
		n->transform = mat;

		fgets(b, sz, file);

		//N START
		if (b[2] == 'S')
		{
			n->childNodes.push_back(INode{});
			n->childNodes.back().parent = n;

			AddNode(file, &n->childNodes.back(), b, sz);
		}
	}

	//Add each child
	while (b[2] == 'S')
	{
		n->childNodes.push_back(INode{});
		n->childNodes.back().parent = n;

		AddNode(file, &n->childNodes.back(), b, sz);
	}

	fgets(b, sz, file);
}

void Model::FindParentBones(INode* node)
{
	auto name = GetStringFromHash2(node->name);
	auto idx = name.find("_$");
	if (idx != std::string::npos)
	{
		name[idx] = '\0';
		parentBones[node->name] = GetHashFromString2(name);
	}
}

void Model::ProcessMesh(unsigned meshID, aiMesh* mesh)
{
	//Process Each vertices
	for (auto i = 0u; i < mesh->mNumVertices; ++i)
	{
		IVertex v;
		zg::Vector3 vec;

		//local coordinates of VERTEX of current mesh[meshID] in scene
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		v.position = vec;

		//local NORMAL of current mesh[meshID] in scene
		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		v.normal = vec;

		//local TANGENTS of current mesh[meshID] in scene
		vec.x = mesh->mTangents[i].x;
		vec.y = mesh->mTangents[i].y;
		vec.z = mesh->mTangents[i].z;
		v.tangent = vec;

		//UV of current mesh[meshID] in scene
		if (mesh->HasTextureCoords(0))
		{
			zg::Vector2 uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			v.uv = uv;
		}
		else
			v.uv = zg::Vector2{};

		v.weights = zg::Vector4{};

		v.joints = zg::Vector4{};

		vertices.push_back(v);
	}

	//BONES of current mesh[meshID] in scene
	ProcessBones(meshID, mesh);
	//boneTransforms.resize(boneOffsets.size());

	for (auto i = 0u; i < mesh->mNumFaces; ++i)
	{
		const aiFace& face = mesh->mFaces[i];

		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
}

void Model::ProcessBones(unsigned meshID, aiMesh* mesh)
{
	for (unsigned int i = 0u; i < mesh->mNumBones; ++i)
	{
		unsigned int boneIndex = 0u;

		//Get bone name
		std::string boneName{ mesh->mBones[i]->mName.data };
		size_t getHash = GetHashFromString2(boneName);

		//printf("mesh[%d]: %s \n", meshID, boneName.c_str());

		//Slot into BoneMap of this Model
		if (boneMap.find(getHash) == boneMap.end())
		{
			boneIndex = boneCount;
			++boneCount;
			zg::Matrix44 tmp{
				mesh->mBones[i]->mOffsetMatrix.a1, mesh->mBones[i]->mOffsetMatrix.a2, mesh->mBones[i]->mOffsetMatrix.a3, mesh->mBones[i]->mOffsetMatrix.a4,
				mesh->mBones[i]->mOffsetMatrix.b1, mesh->mBones[i]->mOffsetMatrix.b2, mesh->mBones[i]->mOffsetMatrix.b3, mesh->mBones[i]->mOffsetMatrix.b4,
				mesh->mBones[i]->mOffsetMatrix.c1, mesh->mBones[i]->mOffsetMatrix.c2, mesh->mBones[i]->mOffsetMatrix.c3, mesh->mBones[i]->mOffsetMatrix.c4,
				mesh->mBones[i]->mOffsetMatrix.d1, mesh->mBones[i]->mOffsetMatrix.d2, mesh->mBones[i]->mOffsetMatrix.d3, mesh->mBones[i]->mOffsetMatrix.d4
			};
			boneOffsets.push_back(tmp);
			boneMap[getHash] = boneIndex;
		}
		else
			boneIndex = boneMap[getHash];

		for (auto j = 0u; j < mesh->mBones[i]->mNumWeights; ++j)
		{
			//Get the Real vertex Index of this model
			auto vertexID = meshes[meshID].BaseVertex + mesh->mBones[i]->mWeights[j].mVertexId;

			//Get the Vertex of this Model that have been init just now
			auto& vert = vertices[vertexID];
			float weight = mesh->mBones[i]->mWeights[j].mWeight;

			//Current Vertex is Affected by 4 joints only 
			for (int k = 0; k < 4; ++k)
			{
				if (weight > vert.weights[k] || vert.weights[k] == 0.0f)
				{
					vert.joints[k] = static_cast<float>(boneIndex);	//storing boneIndex
					vert.weights[k] = weight;							//storing the weight 
					break;
				}
			}
		}
	}
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, INode* n)
{
	n->name = GetHashFromString2(node->mName.C_Str());
	//printf("Node: %s \n", n.name.c_str());
	aiMatrix4x4 tmpp = node->mTransformation;
	n->transform = zg::Matrix44{
		tmpp.a1, tmpp.a2, tmpp.a3, tmpp.a4,
		tmpp.b1, tmpp.b2, tmpp.b3, tmpp.b4,
		tmpp.c1, tmpp.c2, tmpp.c3, tmpp.c4,
		tmpp.d1, tmpp.d2, tmpp.d3, tmpp.d4
	};

	for (unsigned int i = 0u; i < node->mNumChildren; ++i)
	{
		n->childNodes.push_back(INode{});
		n->childNodes.back().parent = n;
		ProcessNode(node->mChildren[i], scene, &n->childNodes[i] );
	}
	//printf("End Parent ");
}

void Model::LoadFBXModel(const std::string & path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		std::cout << "ASSIMP Error: " << importer.GetErrorString() << std::endl;
	
	//name = path.substr(0, path.find_last_of('.'));
	//GlobalInverseTransform = scene->mRootNode->mTransformation.Inverse();
	
	//Get Number Of Meshes In the scene
	meshes.resize(scene->mNumMeshes);
	printf("Number Of Meshes: %d\n", scene->mNumMeshes);
	
	unsigned int numVertices = 0u;
	unsigned int numIndices = 0u;
	
	for (unsigned int i = 0u; i < scene->mNumMeshes; ++i)
	{
		meshes[i].IndiceCount = scene->mMeshes[i]->mNumFaces * 3;
		meshes[i].BaseVertex = numVertices;
		meshes[i].BaseIndex = numIndices;
	
		numVertices += scene->mMeshes[i]->mNumVertices;
		numIndices += meshes[i].IndiceCount;
	}
	
	vertices.reserve(numVertices);	//Total Number Of Vertices in the model
	indices.reserve(numIndices);		//Total Number Of Indices in the model
	
	for (auto i = 0u; i < meshes.size(); ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];
		//std::string aaaa{ mesh->mName.data };
		//printf("Name Of Mesh[%d]: %s \n", i, aaaa.c_str());
		ProcessMesh(i, mesh);
	}
	
	ProcessNode(scene->mRootNode, scene, &nodes);
	
	//Port number of animation
	for (unsigned int i = 0u; i < scene->mNumAnimations; ++i)
	{
		//Name of the Animation
		animations.emplace_back(Animation{ scene->mAnimations[i]->mName.C_Str(), (float)scene->mAnimations[i]->mDuration, (float)scene->mAnimations[i]->mTicksPerSecond });
		channelMap.emplace_back(std::map<size_t, AnimationChannel*>{});

		double maxDuration = 0;
	
		//Number of Channels affected
		for (auto j = 0u; j < scene->mAnimations[i]->mNumChannels; ++j)
		{
			//Node Name Affected
			animations[i].channels.emplace_back(scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str());
			auto& currC = animations[i].channels.back();
			channelMap[i][GetHashFromString2(scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str())] = &currC;

			//Node Position Key 
			animations[i].channels[j].posKeyCount = scene->mAnimations[i]->mChannels[j]->mNumPositionKeys;
	
			for (auto k = 0u; k < animations[i].channels[j].posKeyCount; ++k)
			{
				const auto& key = scene->mAnimations[i]->mChannels[j]->mPositionKeys[k];
	
				animations[i].channels[j].posKeys.emplace_back(Vector3Key{ (float)key.mTime, zg::Vector3{ key.mValue.x,key.mValue.y, key.mValue.z} });
	
				if (key.mTime > maxDuration)
					maxDuration = key.mTime;
			}
			//Node Scale Key 
			animations[i].channels[j].scaleKeyCount = scene->mAnimations[i]->mChannels[j]->mNumScalingKeys;
			for (auto k = 0u; k < animations[i].channels[j].scaleKeyCount; ++k)
			{
				const auto& key = scene->mAnimations[i]->mChannels[j]->mScalingKeys[k];
				animations[i].channels[j].scaleKeys.emplace_back(Vector3Key{ (float)key.mTime, zg::Vector3{ key.mValue.x,key.mValue.y, key.mValue.z } });
				//animations[i].channels[j]..emplace_back(key.mTime, key.mValue);
	
				if (key.mTime > maxDuration)
					maxDuration = key.mTime;
			}
	
			//Node Rotation Key 
			animations[i].channels[j].rotKeyCount = scene->mAnimations[i]->mChannels[j]->mNumRotationKeys;
			for (auto k = 0u; k < animations[i].channels[j].rotKeyCount; ++k)
			{
				const auto& key = scene->mAnimations[i]->mChannels[j]->mRotationKeys[k];
				animations[i].channels[j].rotKeys.emplace_back(QuaternionKey{ (float)key.mTime, zg::Quaternion{ key.mValue.x,key.mValue.y, key.mValue.z, key.mValue.w } });
				//animations[i].channels[j].rotKeys.emplace_back(key.mTime, key.mValue);
	
				if (key.mTime > maxDuration)
					maxDuration = key.mTime;
			}
	
			//printf("Pos:%d SCA:%d Rot%d \n", animations[i].channels[j].posKeyCount, animations[i].channels[j].scaleKeyCount, animations[i].channels[j].rotKeyCount);
		}
		//Get the Max Total Duration of each Animation
		animations[i].duration = maxDuration;
	}

	if (animations.size())
		hasAnims = true;
}

void Model::ExportFile(const std::string& fileOut)
{
	std::fstream outFile;
	outFile.open(fileOut + filename, std::ios::out);

	outFile << "v2" << std::endl;
	outFile << scalingFactor << " " << meshes.size() << std::endl;

	for (const auto& mesh : meshes)
		outFile << mesh.IndiceCount << " " << mesh.BaseVertex << " " << mesh.BaseIndex << " " << std::endl;

	for (const auto& vert : vertices)
	{
		outFile << "\tV " << vert.position.x << " " << vert.position.y << " " << vert.position.z
			    << " N " << vert.normal.x << " " << vert.normal.y << " " << vert.normal.z
			    << " U " << vert.uv.x << " " << vert.uv.y
			    << " W " << vert.weights.x << " " << vert.weights.y << " " << vert.weights.z << " " << vert.weights.w
			    << " J " << vert.joints.x << " " << vert.joints.y << " " << vert.joints.z << " " << vert.joints.w
			    << " T " << vert.tangent.x << " " << vert.tangent.y << " " << vert.tangent.z << std::endl;
	}

	size_t tmpsz = indices.size();
	outFile << "I " << tmpsz << std::endl;
	for (size_t i = 2; i < tmpsz; i += 3) {

		outFile << indices[i - 2] << " " << indices[i - 1] << " " << indices[i] << std::endl;
	}

	ExportNodes(outFile, &nodes);

	for (const auto& anim : animations)
	{
		outFile << "A START " << anim.duration << " " << anim.ticksPerSecond << " " << GetStringFromHash2(anim.name) << std::endl;

		//outFile << "\t" << anim.name << std::endl;
		//outFile << "\t" << anim.duration << std::endl;
		//outFile << "\t" << anim.ticksPerSecond << std::endl;

		for (const auto& chn : anim.channels)
		{
			outFile << GetStringFromHash2(chn.name) << std::endl;

			outFile << "PK " << chn.posKeyCount << std::endl;
			for (const auto& key : chn.posKeys)
			{
				outFile << "\t" << key.time << " " << key.value.x << " " << key.value.y << " " << key.value.z << std::endl;
			}

			outFile << "SK " << chn.scaleKeyCount << std::endl;
			for (const auto& key : chn.scaleKeys)
			{
				outFile << "\t" << key.time << " " << key.value.x << " " << key.value.y << " " << key.value.z << std::endl;
			}

			outFile << "RK " << chn.rotKeyCount << std::endl;
			for (const auto& key : chn.rotKeys)
			{
				outFile << "\t" << key.time << " " << key.value.x << " " << key.value.y << " " << key.value.z << " " << key.value.w << std::endl;
			}
		}

		outFile << "A END" << std::endl;
	}

	outFile << "B " << boneCount << std::endl;
	for (const auto& pair : boneMap)
	{
		outFile << pair.second << " " << GetStringFromHash2(pair.first) << std::endl;
	}

	for (const auto& bo : boneOffsets)
	{
		outFile << "BO START" << std::endl;

		outFile << bo.m[0] << " " << bo.m[1] << " " << bo.m[2] << " " << bo.m[3]  << " "
			    << bo.m[4] << " " << bo.m[5] << " " << bo.m[6] << " " << bo.m[7]  << " "
			    << bo.m[8] << " " << bo.m[9] << " " << bo.m[10]<< " " << bo.m[11] << " "
			    << bo.m[12]<< " " << bo.m[13]<< " " << bo.m[14]<< " " << bo.m[15] << std::endl;
		//outFile << "\t" << bo.m[0] << " " << bo.m[4] << " " << bo.m[8] << " " << bo.m[12]
		//		<< " " << bo.m[1] << " " << bo.m[5] << " " << bo.m[9] << " " << bo.m[13]
		//		<< " " << bo.m[2] << " " << bo.m[6] << " " << bo.m[10] << " " << bo.m[14]
		//		<< " " << bo.m[3] << " " << bo.m[7] << " " << bo.m[11] << " " << bo.m[15] << std::endl;
		//outFile << "BO END" << std::endl;
	}
}

void Model::ExportNodes(std::fstream & outFile, const INode* node)
{
	outFile << "N START" << std::endl;
	outFile << "\t" << GetStringFromHash2(node->name) << std::endl;
	outFile << "\t" << node->transform.m[0] << " " << node->transform.m[1] << " " << node->transform.m[2] << " " << node->transform.m[3]  << " "
					<< node->transform.m[4] << " " << node->transform.m[5] << " " << node->transform.m[6] << " " << node->transform.m[7]  << " "
					<< node->transform.m[8] << " " << node->transform.m[9] << " " << node->transform.m[10]<< " " << node->transform.m[11] << " "
					<< node->transform.m[12]<< " " << node->transform.m[13]<< " " << node->transform.m[14]<< " " << node->transform.m[15] << std::endl;

	for (const auto& child : node->childNodes)
		ExportNodes(outFile, &child);

	outFile << "N END" << std::endl;
}

//function
void DestroyAllModels() {
	for (auto& elem : MODEL_POOL) delete elem.second;
}

void LoadModelFromDIR(const char* pathname_)
{
	DIR_itr&& directory = GetDirectory(pathname_);
	for (auto & p : directory) {
		std::string filename;
		bool found = GetFileNameWithExtensionAndCheckExtension(p.path().string(), filename, "models");

		if (found) {
			size_t hashnum = GenerateHash2(filename);
			Model* model = Allocate<Model>(1);

#ifdef USE_RAWNEW
			model->filename = filename;
			model->LoadCustomModel(p.path().string());
			MODEL_POOL[hashnum] = model;
#else
			new (get) Model{ filename };
			get->LoadCustomModel(p.path().string());
			MODEL_POOL[hashnum] = get;
#endif
		}
	}

	for (auto& mesh : MODEL_POOL)
		mesh.second->Init();
}

void LoadFBXModelAndConvertFromDIR(const char* fbx_pathname_, const char* models_pathname_) 
{
	DIR_itr&& directory = GetDirectory(models_pathname_);
	for (auto & p : directory) {
		std::string filename;
		bool found = GetFileNameWithExtensionAndCheckExtension(p.path().string(), filename, "models");

		if (found) {
			size_t hashnum = GenerateHash2(filename);
			Model* model = Allocate<Model>(1);

#ifdef USE_RAWNEW
			model->filename = filename;
			model->LoadCustomModel(p.path().string());
			MODEL_POOL[hashnum] = model;
#else
			new (get) Model{ filename };
			get->LoadCustomModel(p.path().string());
			MODEL_POOL[hashnum] = get;
#endif
		}
	}

	DIR_itr&& directory2 = GetDirectory(fbx_pathname_);
	for (auto& p : directory2) {
		std::string filename;

		bool found = GetFileNameWithExtensionAndCheckExtension(p.path().string(), filename, "fbx");
		
		if (found) {
			GetFileNameNoExtension(p.path().string(), filename);
			size_t hashnum = GenerateHash2(filename + ".models");

			bool findifModelExist = MODEL_POOL.find(hashnum) == MODEL_POOL.end();

			if (findifModelExist) {
				Model* model = Allocate<Model>(1);
#ifdef USE_RAWNEW
				model->filename = filename + ".models";
				model->LoadFBXModel(p.path().string());
				model->ExportFile(models_pathname_);
				MODEL_POOL[hashnum] = model;
#else
				new (get) Model{ filename };
				get->LoadCustomModel(p.path().string());
				MODEL_POOL[hashnum] = get;
#endif
			}
		}
	}

	for (auto& mesh : MODEL_POOL)
		mesh.second->Init();
}

Model*& FindModel(std::string&& filename_extension_) {
	return FindModel(GetHashFromString(filename_extension_));
}
Model*& FindModel(const std::string& filename_extension_) {
	return FindModel(GetHashFromString(filename_extension_));
}
Model *& FindModel(size_t hashnum) {
	auto find = MODEL_POOL.find(hashnum);
	bool found = find == MODEL_POOL.end();

#if defined(_DEBUG) || defined(_EDITOR_ON)
	if (found)
		PopUp_Warn(std::string{ "Models file Not Found: " + GetStringFromHash(hashnum) }.c_str());
	return found ? MODEL_POOL[GetHashFromString("null.models")] : find->second;
#else
	return SHADER_POOL[hashnum];
#endif
}

const std::map<size_t, Model*>& GetAllModel() {
	return MODEL_POOL;
}

std::vector<std::string> GetAllModelName() {
	std::vector<std::string> allname;
	for (auto& elem : MODEL_POOL) {
		allname.push_back(GetStringFromHash(elem.first));
	}
	return allname;
}
