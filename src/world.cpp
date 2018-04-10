#include "world.h"

float getHeight(float x, float z) {return 1;}
Vec4 getHeightColor(float y) { return Vec4(1,1,1,1); }
Vec3 getNormal(float x, float z) { return Vec3(0,1,0); } 

TTile::TTile(const Vec2& position, float size, unsigned int subdiv)
{
    CreateSurface(position, size, subdiv);
    LoadTile();
    ClearMemory();
    
}

TTile::~TTile()
{
    
}

void TTile::Draw()
{

}

void TTile::CreateSurface(Vec2 position, float size, unsigned int subdiv)
{
    float halfsize = size/2.0;
    for(int i = 0; i < subdiv+1; i++) {
	float x = position.x - halfsize + i*size/subdiv;
	for(int j = 0; j < subdiv+1; j++) {
	    float z = position.y - halfsize + j*size/subdiv;
	    float y = getHeight(x, z);
	    positions.push_back( Vec3(x, y, z) );
	    texcoords.push_back( Vec2(x, z) );
	    normals.push_back( getNormal(x,z) );
	    colors.push_back( getHeightColor(y) );
	    if(i != 0 && j != 0) {
		int p0 = i*(subdiv+1) + j;
		int p1 = p0 - 1;
		int p2 = p1 - (subdiv+1);
		int p3 = p2 + 1;
		if( i%2 == j%2 ) {
		    indices.push_back(p0);
		    indices.push_back(p1);
		    indices.push_back(p2);
		    indices.push_back(p0);
		    indices.push_back(p2);
		    indices.push_back(p3);
		} else {
		    indices.push_back(p1);
		    indices.push_back(p2);
		    indices.push_back(p3);
		    indices.push_back(p1);
		    indices.push_back(p3);
		    indices.push_back(p0);
		}
	    }
	}
    }
    for(auto& n : normals)
	n = glm::normalize(n);
    
}

void TTile::LoadTile()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(NUM_BUFFERS, VABs);
    
    glBindBuffer(GL_ARRAY_BUFFER ,VABs[vabPOSITION]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER ,VABs[vabTEXCOORD]);
	glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER ,VABs[vabCOLOR]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER ,VABs[vabNORMAL]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,VABs[vabINDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
	
    glBindVertexArray(0);
}

void TTile::ClearMemory()
{
    float mem = 0;
    char p = '\0';
    mem += positions.size() * sizeof(positions[0]);
    positions.clear();
    positions.shrink_to_fit();
    mem += texcoords.size() * sizeof(texcoords[0]);
    texcoords.clear();
    texcoords.shrink_to_fit();
    mem += colors.size() * sizeof(colors[0]);
    colors.clear();
    colors.shrink_to_fit();
    mem += normals.size() * sizeof(normals[0]);
    normals.clear();
    normals.shrink_to_fit();
    mem += indices.size() * sizeof(indices[0]);
    indices.clear();
    indices.shrink_to_fit();
    while(mem > 1024) {
	mem /= 1024;
	if(p == 'G') p = 'T';
	if(p == 'M') p = 'G';
	if(p == 'K') p = 'M';
	if(p == '\0') p = 'K';
    }
    std::cout << "Cleaned up " << mem << " " << p << "B." << std::endl;
}

