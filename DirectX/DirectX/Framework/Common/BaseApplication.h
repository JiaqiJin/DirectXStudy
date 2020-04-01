#pragma once
#include "../Interface/IApplication.h"

namespace Kawaii
{
	class BaseApplication : implements IApplication
	{

	public:
		virtual int Initialize();
		virtual void Finalize();
		// One cycle of the main loop
		virtual void Tick();

		virtual bool IsQuit();

	protected:
		//flag if nned quiet main loop of application
		bool m_bQuit;
	};
}
