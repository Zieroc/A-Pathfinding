#ifndef PATHNODE_H
#define PATHNODE_H

class Tile; //Forward Declaration

class PathNode
{
public:
	PathNode(Tile* tile);
	~PathNode();
	PathNode* GetParent();
	void SetParent(PathNode* parent);
	int GetF();
	void SetF(int h);
	Tile* GetTile();
	int GetG();
	void SetG(int g);
private:
	PathNode* m_p_Parent;
	int m_G;
	int m_F;
	Tile* m_p_Tile;
};

#endif