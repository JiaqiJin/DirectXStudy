#include "BaseApplication.h"

int Kawaii::BaseApplication::Initialize()
{
	m_bQuit = false;

	return 0;
}

void Kawaii::BaseApplication::Finalize()
{

}

void Kawaii::BaseApplication::Tick()
{
}

bool Kawaii::BaseApplication::IsQuit()
{
	return m_bQuit;
}