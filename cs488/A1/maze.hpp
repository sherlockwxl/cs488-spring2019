// Winter 2019

#pragma once

class Maze
{
public:
	Maze( size_t dim );
	~Maze();

	void reset();

	size_t getDim() const;

	int getValue( int x, int y ) const;

	void setValue( int x, int y, int h );

	void digMaze();
	void printMaze(); // for debugging
	//
	int getStartY();
private:
	int startY;
	size_t m_dim;
	int *m_values;
	void recDigMaze(int r, int c);
	int numNeighbors(int r, int c);
};
