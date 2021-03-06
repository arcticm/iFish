#pragma once
#include "ofMain.h"

namespace iFish
{
	typedef shared_ptr<class Config> ConfigPtr;

	class Config
	{
	public:
		Config();

		ofEvent<void> loadCompleteEvent;
		ofEvent<void> loadErrorEvent;

		virtual void load();

		virtual ~Config();
	};
}

