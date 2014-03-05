#include "TileDAO.h"

TileDAO::TileDAO()
{
}

TileDAO::~TileDAO()
{

}

std::vector<Tile*> TileDAO::Read(const char* file)
{
	std::vector<Tile*> tiles;

	tinyxml2::XMLDocument doc;

	if(doc.LoadFile(file) ==  tinyxml2::XML_SUCCESS)
	{
		//get the first story element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			int index = atoi(child->FirstChildElement()->GetText());
			bool passable = atoi(child->FirstChildElement("Passable")->GetText());
			int code = atoi(child->FirstChildElement("Code")->GetText());
			Tile* tile = new Tile(index, passable, 0, 0, code);

			tiles.push_back(tile);
		}
	}

	return tiles;
}