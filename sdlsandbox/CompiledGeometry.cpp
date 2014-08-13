#include "CompiledGeometry.h"

CompiledGeometry::CompiledGeometry(Rocket::Core::Vertex* vertices, 
	int num_vertices, 
	int* indices, 
	int num_indices, 
	Rocket::Core::TextureHandle texture,
	GLuint program)
{
	_texture = (CTexture*)texture;
	_program = program;
	_num_indices = num_indices;
	std::vector<unsigned int> indexData;
	for (unsigned int i = 0; i < num_indices; i++)
	{
		indexData.push_back(indices[i]);
	}
	
	glGenBuffers(1, &_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), &indexData[0], GL_STATIC_DRAW);

	std::vector<float> vertexData;

	for (unsigned int i = 0; i < num_vertices; i++)
	{
		vertexData.push_back(vertices[i].position.x);
		vertexData.push_back(vertices[i].position.y);
		vertexData.push_back(0);
	}

	std::vector<float> uvData;

	for (unsigned int i = 0; i < num_vertices; i++)
	{
		uvData.push_back(vertices[i].tex_coord.x);
		uvData.push_back(vertices[i].tex_coord.y);
	}

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(float), &uvData[0], GL_STATIC_DRAW);
}

CompiledGeometry::~CompiledGeometry()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_elementBuffer);
}

void CompiledGeometry::render(const Rocket::Core::Vector2f& translation, int w_width, int w_height)
{
	glEnable(GL_BLEND);

	glUseProgram(_program);

	GLuint matrix_uniform = glGetUniformLocation(_program, "MVP");

	glm::mat4 MVP = glm::mat4(1.0f);
	MVP = glm::translate(MVP, glm::vec3(-1, 1, 0));
	MVP = glm::scale(MVP, glm::vec3(1.0f / (w_width/2), -1.0f / (w_height/2), 0.0f));
	MVP = glm::translate(MVP, glm::vec3(translation.x, translation.y,0));
	
	glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, &MVP[0][0]);

	GLuint texture_uniform = glGetUniformLocation(_program, "texSampler");

	glActiveTexture(GL_TEXTURE0);
	_texture->BindTexture();
	glUniform1i(texture_uniform, 0);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(
			1,                  // attribute
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	glDrawElements(
			GL_TRIANGLES,      // mode
			_num_indices,    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    
	glDisable(GL_BLEND);
}
