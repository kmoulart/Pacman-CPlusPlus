// DisplayListPool.h
#pragma once

class DisplayListPool
{
private:
	static DisplayListPool *instance;
	int idLists;

	// Constructeur
	DisplayListPool();

public:
	// Singleton
	static DisplayListPool *getInstance();

	// Getter
	int getList(int nomList);
};

