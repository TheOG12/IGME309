#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// track all vertices
	std::vector<vector3> vertices;
	float theta = 0;
	float division = (PI * 2) / a_nSubdivisions; // change in theta for each set of vertices
	for (int i = 0; i < a_nSubdivisions; i++) {
		vertices.push_back(vector3((cos(theta) * a_fRadius), -(a_fHeight / 2), (sin(theta) * a_fRadius))); // track vertices for base
		theta += division;
	}

	// draw the shape
	for (int i = 0; i < a_nSubdivisions; i++) {
		AddTri(vertices[i], vertices[(i + 1) % a_nSubdivisions], vector3(0.0f, -a_fHeight / 2, 0.0f)); // draw the base
		AddTri(vertices[(i + 1) % a_nSubdivisions], vertices[i], vector3(0.0f, a_fHeight / 2, 0.0f)); // draw the sides
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// track all vertices
	std::vector<vector3> topVertices;
	std::vector<vector3> bottomVertices;
	GLfloat theta = 0;
	GLfloat division = (PI * 2) / a_nSubdivisions; // change in theta for each set of vertices
	for (int i = 0; i < a_nSubdivisions; i++) {
		topVertices.push_back(vector3((cos(theta) * a_fRadius), (a_fHeight / 2),(sin(theta) * a_fRadius))); //track vertices for top face
		bottomVertices.push_back(vector3((cos(theta) * a_fRadius), -(a_fHeight / 2), (sin(theta) * a_fRadius))); //track vertices for bottom face
		theta += division;
	}

	// draw the shape
	for (int i = 0; i < a_nSubdivisions; i++) {
		AddTri(topVertices[(i + 1) % a_nSubdivisions], topVertices[i], vector3(0.0f, a_fHeight / 2,0.0f)); // draw the top face
		AddTri(bottomVertices[i], bottomVertices[(i + 1) % a_nSubdivisions], vector3(0.0f, -a_fHeight / 2, 0.0f)); // draw the bottom face
		AddQuad(topVertices[i], topVertices[(i + 1) % a_nSubdivisions], bottomVertices[i], bottomVertices[(i + 1) % a_nSubdivisions]); // draw the sides of the cylinder
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// track all vertices
	std::vector<vector3> topVerticesOuter;
	std::vector<vector3> bottomVerticesOuter;
	std::vector<vector3> topVerticesInner;
	std::vector<vector3> bottomVerticesInner;
	GLfloat theta = 0;
	GLfloat division = (PI * 2) / a_nSubdivisions; // change in theta for each set of vertices
	for (int i = 0; i < a_nSubdivisions; i++) {
		topVerticesOuter.push_back(vector3((cos(theta) * a_fOuterRadius), (a_fHeight / 2), (sin(theta) * a_fOuterRadius))); // track vertices for outer ring of the top face
		topVerticesInner.push_back(vector3((cos(theta) * a_fInnerRadius), (a_fHeight / 2), (sin(theta) * a_fInnerRadius))); // track vertices for inner ring of the top face

		bottomVerticesOuter.push_back(vector3((cos(theta) * a_fOuterRadius), -(a_fHeight / 2), (sin(theta) * a_fOuterRadius))); // track vertices for outer ring of the bottom face
		bottomVerticesInner.push_back(vector3((cos(theta) * a_fInnerRadius), -(a_fHeight / 2), (sin(theta) * a_fInnerRadius))); // track vertices for inner ring of the bottom face

		theta += division;
	}

	// draw the shape
	for (int i = 0; i < a_nSubdivisions; i++) {
		AddQuad(topVerticesOuter[(i + 1) % a_nSubdivisions], topVerticesOuter[i], topVerticesInner[(i + 1) % a_nSubdivisions], topVerticesInner[i]); // draw the top face of the tube
		AddQuad(bottomVerticesOuter[i], bottomVerticesOuter[(i + 1) % a_nSubdivisions], bottomVerticesInner[i], bottomVerticesInner[(i + 1) % a_nSubdivisions]); // draw the bottom face of the tube
		
		AddQuad(topVerticesOuter[i], topVerticesOuter[(i + 1) % a_nSubdivisions], bottomVerticesOuter[i], bottomVerticesOuter[(i + 1) % a_nSubdivisions]); // draw the outer sides of the tube
		AddQuad(bottomVerticesInner[i], bottomVerticesInner[(i + 1) % a_nSubdivisions], topVerticesInner[i], topVerticesInner[(i + 1) % a_nSubdivisions]); // draw the inner sides of the tube
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	// GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// got the math for determining the vertices of a torus from here
	// https://gamedev.stackexchange.com/questions/16845/how-do-i-generate-a-torus-mesh

	float torRadius = (a_fOuterRadius + a_fInnerRadius) / 2; // radius for the torus
	float tubeRadius = (a_fOuterRadius - a_fInnerRadius) / 2; // radius for the "tube" of the torus

	// track all the vertices
	std::vector<std::vector<vector3>> torusVertices; // all of the vertices of the torus
	GLfloat theta = 0; // theta for the circle at each subdivision
	GLfloat phi = 0; // phi for the torus
	GLfloat divisionHeight = (PI * 2) / a_nSubdivisionsA; // change in theta for each set of vertices
	GLfloat divisionRing = (PI * 2) / a_nSubdivisionsB; // change in phi for each set of vertices

	// adds the corresponding vertices for the torus to a vector for each circle created and then adds that vector to a vector for the whole torus
	for (int i = 0; i < a_nSubdivisionsB; i++) {

		// determine the center point for the circle at the current angle
		vector3 centerPoint = vector3(torRadius * cos(phi), 0, (torRadius * sin(phi)));

		// determine the vertices for the circle at the current angle
		std::vector<vector3> circleVertices; // new list of vertices for each subdivision of the torus
		for (int i = 0; i < (a_nSubdivisionsA); i++) {
			vector3 circleVertex; // = centerPoint + tubeRadius * cos(theta) * vector3(cos(phi), 0, sin(phi)) + vector3(0, (tubeRadius * sin(theta)), 0);
			// separated the above comment into x, y, and z for readability
			circleVertex.x = centerPoint.x + (tubeRadius * cos(theta) * cos(phi));
			circleVertex.y = centerPoint.y + (tubeRadius * sin(theta));
			circleVertex.z = centerPoint.z + (tubeRadius * cos(theta) * sin(phi));

			circleVertices.push_back(circleVertex);
			theta += divisionHeight;
		}
		torusVertices.push_back(circleVertices);
		theta = 0; // reset theta to zero for the next circle
		phi += divisionRing;
	}

	// draw the shape
	for (int i = 0; i < a_nSubdivisionsB; i++) {
		for (int j = 0; j < a_nSubdivisionsA; j++) {
			vector3 A = torusVertices[(i + 1) % a_nSubdivisionsB][j];
			vector3 B = torusVertices[i][j];
			vector3 C = torusVertices[(i + 1) % a_nSubdivisionsB][(j + 1) % a_nSubdivisionsA];
			vector3 D = torusVertices[i][(j + 1) % a_nSubdivisionsA];
			AddQuad(A, B, C, D); // separated so that it was easier to move things around if vertices were added in the wrong order
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// trying to understand spherical coordinates to apply them here
	// https://mathinsight.org/spherical_coordinates
	
	// track all vertices
	std::vector<std::vector<vector3>> sphereVertices;
	GLfloat phi = 0; // theta for each sphere vertices
	GLfloat theta = 0; // theta for the circle vertices
	GLfloat angleChange = (2 * PI) / a_nSubdivisions; // angle change for drawing the each next set of quads

	// adds the corresponding vertices for the sphere to a vector for each circle created and then adds that vector to a vector for the whole sphere
	for (int i = 0; i <= a_nSubdivisions; i++) { // needed to do extra loop because using % for the last i makes the top of the sphere cave in back to the first point
		theta = 0;
		std::vector<vector3>circleVertices;
		for (int j = 0; j < (a_nSubdivisions); j++) {
			vector3 circleVertex;
			circleVertex.x = a_fRadius * sin(phi) * cos(theta);
			circleVertex.y = a_fRadius * cos(phi); // switched y and z from original formula for the sake of orientation
			circleVertex.z = a_fRadius * sin(phi) * sin(theta);
			theta += angleChange;
			circleVertices.push_back(circleVertex);
		}
		sphereVertices.push_back(circleVertices);
		phi += angleChange / 2; // restrict phi to only going up to PI rather than 2 * PI
	}

	// draw the shape
	for (int i = 0; i < a_nSubdivisions; i++) {
		for (int j = 0; j < (a_nSubdivisions); j++) {
			vector3 A = sphereVertices[(i + 1)][j];
			vector3 B = sphereVertices[i][j];
			vector3 C = sphereVertices[(i + 1)][(j + 1) % (a_nSubdivisions)];
			vector3 D = sphereVertices[i][(j + 1) % (a_nSubdivisions)];
			AddQuad(A, B, C, D); // separated so that it was easier to move things around if vertices were added in the wrong order
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}