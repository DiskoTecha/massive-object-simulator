#ifndef DW_VISUALIZER_3D
#define DW_VISUALIZER_3D

#define DW_VISUALIZER_3D_VERSION "1.0.2"

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"
#include <mutex>

namespace dw
{
	// Singleton class wrapping Panda3D's commonly used functionality
	class Visualizer3D
	{
		static std::mutex mutex;
		static Visualizer3D* instance;

		const char* title;
		NodePath camera;
		PandaFramework* frame;
		WindowFramework* window;
		
		Visualizer3D();
		
	protected:
		Visualizer3D(const char*);
		~Visualizer3D();

	public:
		// Delete copy constructor and = operator
		Visualizer3D(Visualizer3D&) = delete;
		void operator = (const Visualizer3D&) = delete;

		static Visualizer3D* getInstance(const char*);

		void init(int&, char**&);
		void run();
		void shutdown();

		NodePath getCamera();
		PandaFramework* getFrame();
		WindowFramework* getWindow();

	};
}


#endif