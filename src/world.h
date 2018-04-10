#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::ivec3 Tri;

typedef std::vector<Vec2> VecVec2;
typedef std::vector<Vec3> VecVec3;
typedef std::vector<Vec4> VecVec4;
typedef std::vector<Tri> VecTriInd;

enum vabBUFFERS { vabPOSITION, 
       vabTEXCOORD, 
       vabCOLOR, 
       vabNORMAL, 
       vabINDEX, 
       NUM_BUFFERS };

class TTile
{
public:
    TTile(const Vec2& position, float size, unsigned int subdiv);
    virtual ~TTile();
    void Draw();
private:
    void CreateSurface(Vec2 position, float size, unsigned int subdiv);
    void LoadTile();
    void ClearMemory();
    
    GLuint VAO;
    GLuint VABs[NUM_BUFFERS];
    
    VecVec3 positions;
    VecVec2 texcoords;
    VecVec4 colors;
    VecVec3 normals;
    std::vector<int> indices;
};

#endif