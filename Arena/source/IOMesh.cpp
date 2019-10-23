#include <IOMesh.hpp>

IOMesh::IOMesh():Mesh()
{
	// Wrap init
	
}

IOMesh::IOMesh(const IOMesh & m):Mesh(m),
boundingBox(m.boundingBox)
{}

IOMesh::~IOMesh()
{
	vertexData_.clear();
	indexData_.clear();
	normalData_.clear();
}

// detection de collision
std::pair<collisionFace, float> IOMesh::hitTestObject(const IOMesh & m)
{
	return hitTestObject(m.getBoundingBox());
}

std::pair<collisionFace, float> IOMesh::hitTestObject(const Wrap & wrap)
{
	std::pair<collisionFace, float> face(NONE, 0.0);
	
	// verifie si wrap touche la boundingBox de IOMesh
	bool isTouched = (wrap.x >= boundingBox.x - (boundingBox.width + wrap.width)/2.0) &&
					 (wrap.x <= boundingBox.x + (boundingBox.width + wrap.width)/2.0) && 
					 (wrap.y >= boundingBox.y - (boundingBox.height + wrap.height)/2.0) && 
					 (wrap.y <= boundingBox.y + (boundingBox.height + wrap.height)/2.0);
	
	// recherche de la face de collision sur wrap		 
	if(isTouched)
	{
		if((wrap.y >= (boundingBox.y + boundingBox.height/2.0)) && ((wrap.x <= (boundingBox.x + boundingBox.width/2.0)) && (wrap.x >= (boundingBox.x - boundingBox.width/2.0))))
		{
			face.first = BOTTOM;
			face.second = boundingBox.y + boundingBox.height/2.0 /*+ wrap.height/2.0*/;
		}
		else if((wrap.y <= (boundingBox.y - boundingBox.height/2.0)) && ((wrap.x <= (boundingBox.x + boundingBox.width/2.0)) && (wrap.x >= (boundingBox.x - boundingBox.width/2.0))))
		{
			face.first = TOP;
			face.second = boundingBox.y - boundingBox.height/2.0 /*- wrap.height/2.0*/;
		}
		else if(type_ == WALL) // If it's a wall
		{
			if((wrap.x <= (boundingBox.x - boundingBox.width/2.0))/* && ((wrap.y <= (boundingBox.y + boundingBox.height/2.0)) && (wrap.y >= (boundingBox.y - boundingBox.height/2.0)))*/)
			{
				face.first = RIGHT;
				face.second = boundingBox.x - boundingBox.width/2.0 /*- wrap.width/2.0*/;
			}
			else if((wrap.x >= (boundingBox.x + boundingBox.width/2.0))/* && ((wrap.y <= (boundingBox.y + boundingBox.height/2.0)) && (wrap.y >= (boundingBox.y - boundingBox.height/2.0)))*/)
			{
				face.first = LEFT;
				face.second = boundingBox.x + boundingBox.width/2.0 /*+ wrap.width/2.0*/;
			}
		}
	}
	
	return face;
}
