#include "Solar/Shapes/Mesh.hxx"
#include "Solar/Utils.hxx"

// Raw:
glm::mat4 Solar::Shapes::MeshAttributes::GetMeshMatrix()
{
    glm::mat4 __model_matrix = glm::mat4(1.0f);
    __model_matrix = glm::translate(__model_matrix, this->position.ToGLM());
    __model_matrix = glm::scale(__model_matrix, this->size.ToGLM());
    __model_matrix = glm::rotate(__model_matrix, glm::radians((float)this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    __model_matrix = glm::rotate(__model_matrix, glm::radians((float)this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    __model_matrix = glm::rotate(__model_matrix, glm::radians((float)this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    return __model_matrix;
}

Solar::Types::U32 Solar::Shapes::MeshAttributes::GetPackedColor4()
{
    return this->color.ConvertToRGBA();
}

// GetMeshAttribute:
Solar::Types::U8 Solar::Shapes::GetMeshAttribute(Solar::Types::Boolean Shape, Solar::Types::Boolean HasElementBuffer)
{
    Solar::Types::U8 value = (1 << 1) + Shape;
    value = (value << 1) + HasElementBuffer;
    value = value << 6;
    return value;
}

// Mesh:
void Solar::Shapes::Mesh::LoadMesh(
    const Solar::Shapes::MeshVertices      vertices,
    const Solar::Shapes::MeshColors        colors,
    const Solar::Shapes::MeshTextureMap    texture_map,
    const Solar::Shapes::MeshIndices       indices
)
{
    bool has_colors         = colors.size() > 0;
    bool has_texture_map    = texture_map.size() > 0;
    bool has_indices        = indices.size() > 0;

    // begin constructing the buffer but first check if there is enough color & texture map for each vertice.
    if(has_colors)      { MAKESURE(vertices.size() == colors.size(),        GENERROR("error while building Mesh, vertices.size() != colors.size();")); }
    if(has_texture_map) { MAKESURE(vertices.size() == texture_map.size(),   GENERROR("error while building Mesh, vertices.size() != colors.size();")); }
    
    // here construct the buffer containing the object!
    std::vector<Solar::Types::D32> buffer;
    #define ADD_ELEMENT3(element) { buffer.push_back(element.at(index).x); buffer.push_back(element.at(index).y); buffer.push_back(element.at(index).z); }
    #define ADD_ELEMENT2(element) { buffer.push_back(element.at(index).x); buffer.push_back(element.at(index).y); }
    for(std::size_t index = 0; index < vertices.size(); index++)
    {
        ADD_ELEMENT3(vertices);
        if(has_colors)      ADD_ELEMENT3(colors);
        if(has_texture_map) ADD_ELEMENT2(texture_map);
    }

    // Begin constructing the OpenGL buffers:
    GENDEBUG("buffer has been created an takes " << buffer.size() * sizeof(Solar::Types::D32) << " bytes!");
    
    // Build the VBO & VAO, those are required even if we don't use an EBO:
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);

    // Bind the VBO & VAO to the current context:
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    // Copy the buffer into the memory:
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(Solar::Types::D32), buffer.data(), GL_STATIC_DRAW);

    // Set the attributes, the layout 0 is always the position of the vertices though!
    const Solar::Types::U8 layout_size = 3 + (has_colors ? 3 : 0) + (has_texture_map ? 2 : 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, layout_size * sizeof(Solar::Types::D32), (void*)0);
    glEnableVertexAttribArray(0);

    // enable the other layouts in case it is enabled:
    if(has_colors)
    {
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            layout_size * sizeof(Solar::Types::D32), (void*)(3 * sizeof(Solar::Types::D32))
        );
        glEnableVertexAttribArray(1);
    }

    // NOTE: due we not knowin' if color is on the stride, we must decide this runtime.
    if(has_texture_map)
    {
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            layout_size * sizeof(Solar::Types::D32),
            (has_colors ? (void*)(6 * sizeof(Solar::Types::D32)) : (void*)(3 * sizeof(Solar::Types::D32)))
        );
        glEnableVertexAttribArray(has_colors ? 2 : 1);
    }

    // Now copy the indice to the memory:
    if(has_indices)
    {
        glGenBuffers(1, &this->ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Solar::Types::Integer), indices.data(), GL_STATIC_DRAW);
    }

    this->attributes    = Solar::Shapes::GetMeshAttribute(0, has_indices);
    this->indices       = indices.size();
    this->buffer_size   = buffer.size();
}

#define GetFromAttributesIsQuad(attribute) (attribute & 0b100000000) >> 7
#define GetFromAttributesHasEBO(attribute) (attribute & 0b010000000) >> 6
void Solar::Shapes::Mesh::Draw(Solar::Core::Storage::Shader *using_shader)
{
    // Pass to the shader the Mesh matrix:
    using_shader->SetMatrixFourUniform("SE_MeshMatrix", this->GetMeshMatrix());
    using_shader->SetIntegerUniform("SE_CurrentColor", this->GetPackedColor4());
    using_shader->Use();

    // Decide the type of object:
    Solar::Types::Boolean is_quad                   = GetFromAttributesIsQuad(this->attributes);
    Solar::Types::Boolean has_element_buffer_object = GetFromAttributesHasEBO(this->attributes);

    // bind the buffer + the vertex attribute:
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    if(has_element_buffer_object)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glDrawElements(is_quad ? GL_QUADS : GL_TRIANGLES, this->indices, GL_UNSIGNED_INT, 0);
    }
    else glDrawArrays(GL_TRIANGLES, 0, this->buffer_size);
}

void Solar::Shapes::Mesh::UnloadMesh()
{
    if(this->attributes != 0)
    {
        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
        if(GetFromAttributesHasEBO(this->attributes) == 1)
            glDeleteBuffers(1, &this->ebo);
        // reset values:
        this->attributes = 0;
        this->indices = 0, this->buffer_size = 0;
    }
}
