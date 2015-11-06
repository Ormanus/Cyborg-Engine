#include "Renderer.h"
#include "common\shader.hpp"


namespace {
	GLuint programID;
	GLuint textureProgramID;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint indexbuffer;
	GLFWwindow* window; 
	glm::mat4 MVP(1.0);
	GLuint MVP_MatrixID;
	GLuint TextureID;
	GLuint uvbuffer;
	GLuint colorbuffer;
	GLuint Texture;
	glm::mat4 VP;
	glm::vec4 DefaultColor;
	int N_shapes;
	TextureManager* TM;
};

void Renderer::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Renderer::initDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Tyhjennetään ruutu
	// Koordinaatisto / Viewport
	glm::vec3 x_axis(1.0, 0.0, 0.0);
	glm::vec3 y_axis(0.0, 1.0, 0.0);
	glm::vec3 z_axis(0.0, 0.0, 1.0);

	glm::vec3 cam_pos(0, 0, 0);
	glm::vec3 cam_up = y_axis;
	glm::vec3 cam_right = x_axis;
	glm::vec3 cam_front = -z_axis; //oikeakatinen koordinaatisto
	glm::mat4 P = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glm::mat4 V = glm::ortho(-1.0f, 1.0f, -1.0f*height / width, 1.0f*height / width);
	VP = V*P;

	glUseProgram(programID);
	// ---------------------------
}


void Renderer::render()
{
	glfwSwapBuffers(window);
}

void Renderer::initRender(GLFWwindow* w)
{
	window = w;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Taustaväri - musta

	//asetetaan piirtoväri oranssiksi
	DefaultColor.r = 1.0f;
	DefaultColor.g = 0.4f;
	DefaultColor.b = 0.0f;
	DefaultColor.a = 1.0f;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	TM = new TextureManager;
	TM->loadTexture("testi", "./textures/default.png");

	//Ladataan shaderit
	//valmiissa ohjelmassa bool setShaders() -funktio ajonaikaiseen shaderien vaihtoon?
	programID = LoadShaders("shaders/VertexShader.vertexshader", "shaders/FragmentShader.fragmentshader");
	textureProgramID = LoadShaders("shaders/TextureVertexShader.txt", "shaders/TextureFragmentShader.txt");
	//----------------

	//luodaan väribufferi. 
	//TODO: siirrä muualle myöhemmin?

	static const GLfloat g_color_buffer_data[] = {
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
	};

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	//MVP näkyy shadereille
	MVP_MatrixID = glGetUniformLocation(programID, "MVP");

	//glEnable(jotain)
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::uninitRender()
{
	// ???
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
	glDeleteBuffers(1, &colorbuffer);
}

void Renderer::drawRectangle(float x1, float y1, float x2, float y2)
{
	drawTriangle(x1, y1, x1, y2, x2, y2);
	drawTriangle(x1, y1, x2, y1, x2, y2);
}

void Renderer::drawCircle(float x, float y, float r)
{
	float angle = 2.0*3.14159265 / 64;
	for (int i = 0; i < 64; i++)
	{
		drawTriangle(x, y, x + cos(angle * i)*r, y + sin(angle * i)*r, x + cos(angle * (i + 1))*r, y + sin(angle * (i + 1))*r);
	}
}

void Renderer::drawPie(float x, float y, float r,float a)
{
	float angle = 2.0*3.14159265 / 64 * a;
	for (int i = 0; i < 64; i++)
	{
		drawTriangle(x, y, x + cos(angle * i)*r, y + sin(angle * i)*r, x + cos(angle * (i + 1))*r, y + sin(angle * (i + 1))*r);
	}
}

void Renderer::drawPolygon(Polygon* p, const float x, const float y)
{
	std::vector<glm::vec2>* pp = p->getPoints();
	glm::vec2 c = pp->at(0);
	unsigned const N_points = pp->size();
	for (unsigned i = 1; i < N_points-1; i++) //aloita 1:stä, koska ensimmäinen vec2 on kuvion keskipiste
	{
	drawTriangle(x + c.x, y + c.y, x + pp->at(i).x, y + pp->at(i).y, x + pp->at(i + 1).x, y + pp->at(i + 1).y);
	}
	drawTriangle(x + c.x, y + c.y, x + pp->at(N_points - 1).x, y + pp->at(N_points - 1).y, x + pp->at(1).x, y + pp->at(1).y);
}

void Renderer::drawPolygonTextured(Polygon* p, const float x, const float y, std::string textureName)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//get points from polygon
	std::vector<glm::vec2>* points = p->getPoints();

	GLuint vertexBuffer, indexBuffer, uvBuffer;

	GLfloat* vertexData = new GLfloat[points->size() * 3];

	//save points to an array
	/*vertexBufferData[0] = points->at(0).x;
	vertexBufferData[1] = points->at(0).y;*/

	glm::mat4 MVP_temp = MVP;

	//MVP_temp = MVP_temp*glm::translate(glm::vec3(0, 0, 1));

	for (int i = 0; i < points->size(); i++)
	{
		/*vertexData[i * 3 + 0] = points->at(i).x + 1;
		vertexData[i * 3 + 1] = points->at(i).y + 1;
		vertexData[i * 3 + 2] = 1.0f;*/

		vertexData[i * 3 + 0] = 1.0f;
		vertexData[i * 3 + 1] = 1.0f;
		vertexData[i * 3 + 2] = 1.0f;
	}



	//enable texture2D
	glEnable(GL_TEXTURE_2D);

	//use texture shader
	glUseProgram(textureProgramID);
	TextureID = glGetUniformLocation(textureProgramID, "myTextureSampler");

	//generate VBO
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*points->size() * 3, vertexData, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
	//get texture
	GLuint texture = TM->getTexture(textureName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//send texture to GPU
	glUniform1i(TextureID, 0);

	//create uv buffer
	float width = p->getMax().x - p->getMin().x;
	float height = p->getMax().y - p->getMin().y;

	GLfloat* uvData = new GLfloat[points->size()*3];

	uvData[0] = points->at(0).x;
	uvData[0] = points->at(0).y;

	for (int i = 1; i < points->size(); i++)
	{
		uvData[i * 2 + 2] = points->at(i).x;
		uvData[i * 2 + 3] = points->at(i).y;
	}

	//generate buffer
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*(points->size()) * 2, uvData, GL_DYNAMIC_DRAW);

	//do some magic to set correct point order
	GLubyte* indexData = new GLubyte[points->size()*3];
	for (int i = 0; i < points->size()-1; i++)
	{
		indexData[i * 3 + 0] = 0;
		indexData[i * 3 + 1] = i;
		indexData[i * 3 + 2] = i+1;
	}
	indexData[(points->size()-1) * 3 + 0] = 0;
	indexData[(points->size()-1) * 3 + 1] = points->size()-1;
	indexData[(points->size()-1) * 3 + 2] = 1;

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*points->size() * 3, indexData, GL_DYNAMIC_DRAW);

	//send the Most Valuable Player of Matrix to GPU
	glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP_temp[0][0]);

	//draw
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size (x, y, z)
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		1,                  // attribute 1
		2,                  // size (u & v)
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	//glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
	//glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

	glDrawElements(GL_TRIANGLES, (points->size())*3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &uvBuffer);
}

//void Renderer::drawPolygonTextured(Polygon* p, const float x, const float y, std::string textureName)
//{
//	//get points from polygon
//	std::vector<glm::vec2>* points = p->getPoints();
//
//	GLuint vertexBuffer, indexBuffer, uvBuffer;
//
//	float width = p->getMax().x - p->getMin().x;
//	float height = p->getMax().y - p->getMin().y;
//
//	//enable texture2D
//	glEnable(GL_TEXTURE_2D);
//
//	//use texture shader
//	glUseProgram(textureProgramID);
//	TextureID = glGetUniformLocation(textureProgramID, "myTextureSampler");
//
//	//get texture
//	GLuint texture = TM->getTexture(textureName);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	//send texture to GPU
//	glUniform1i(TextureID, 0);
//
//	for (int i = 1; i < points->size(); i++)
//	{
//		glm::vec2 next = ((i == points->size() - 1) ? points->at(0) : points->at(i + 1));
//
//		//VBO
//		GLfloat vertexData[] = 
//		{
//			points->at(0).x , points->at(0).y , 1.0f, 
//			points->at(i).x , points->at(i).y , 1.0f,
//			next.x , next.y , 1.0f,
//		};
//		glGenBuffers(1, &vertexBuffer);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
//
//		//uv buffer
//		GLfloat uvData[] = 
//		{
//			points->at(0).x / width, points->at(0).y / height,
//			points->at(i).x / width, points->at(i).y / height,
//			next.x / width, next.y / height,
//		};
//		glGenBuffers(1, &uvBuffer);
//		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_DYNAMIC_DRAW);
//
//		//index buffer
//		GLubyte indexData[] = 
//		{
//			 0, 1, 2
//		};
//		glGenBuffers(1, &indexBuffer);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_DYNAMIC_DRAW);
//
//		//send the Most Valuable Player of Matrix to GPU
//		glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//		//draw
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(
//			0,                  // attribute 0
//			3,                  // size (x, y, z)
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//			);
//
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
//		glVertexAttribPointer(
//			1,                  // attribute 1
//			2,                  // size (u & v)
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//			);
//
//		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
//		glDisableVertexAttribArray(0);
//		glDisableVertexAttribArray(1);
//	}
//
//	glDeleteBuffers(1, &vertexBuffer);
//	glDeleteBuffers(1, &indexBuffer);
//	glDeleteBuffers(1, &uvBuffer);
//}

void Renderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	GLuint vb, ib;

	GLfloat g_vertex_buffer_data[] = {
		x1, y1, 1.0f,
		x2, y2, 1.0f,
		x3, y3, 1.0f,
	};

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
	
	/*static const */GLubyte g_indices[] =
	{
		0, 1, 2,
	};
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glVertexAttribPointer(
		0,                  // attribute 
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 1
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
}

void Renderer::drawTexturedTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::string textureName)
{
	//way too experimental:
	glEnable(GL_TEXTURE_2D);

	glUseProgram(textureProgramID);
	TextureID = glGetUniformLocation(textureProgramID, "myTextureSampler");
	
	
	//GLuint texture = loadBMP_custom("textures/default.bmp");
	//glGenTextures(1, &texture);

	GLuint texture = TM->getTexture(textureName);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1i(TextureID, 0);

	static const GLfloat g_uv_buffer_data[] =
	{
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
	};

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_DYNAMIC_DRAW);

	GLuint vb, ib;

	GLfloat g_vertex_buffer_data[] = {
		x1, y1, 1.0f,
		x2, y2, 1.0f,
		x3, y3, 1.0f,
	};

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

	GLubyte g_indices[] =
	{
		0, 1, 2,
	};
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                  // attribute 1
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);


	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
	glDeleteBuffers(1, &uvbuffer);
}

void Renderer::setColor(float r, float g, float b, float a)
{
	DefaultColor.r = r;
	DefaultColor.g = g;
	DefaultColor.b = b;
	DefaultColor.a = a;

	GLfloat g_color_buffer_data[] = {
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
		DefaultColor.r, DefaultColor.g, DefaultColor.b,
	};
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}