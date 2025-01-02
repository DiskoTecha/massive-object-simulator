// Visualizer3D.h //
#ifndef DW_VISUALIZER_3D
#define DW_VISUALIZER_3D

#define DW_VISUALIZER_3D_VERSION "1.0.3"

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

#include <mutex>
#include <cstdlib>

#include "Vector3.h"

static PointerTo<AsyncTaskManager> dw_visualizer_3d_task_manager = AsyncTaskManager::get_global_ptr();
static PointerTo<ClockObject> dw_visualizer_3d_clock = ClockObject::get_global_clock();

namespace dw
{
	// Singleton class wrapping Panda3D's commonly used visual functionality for user with 3D data visualization
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

		NodePath loadModel(const char* path, Vector3 scale = Vector3(1, 1, 1), Vector3 pos = Vector3(), Vector3 color = Vector3(-1, -1, -1));
		void addTask(const char* name, GenericAsyncTask::TaskFunc* taskFunc, void* userData = nullptr);
		void addKeyEvent(const char* key, const char* name, EventHandler::EventCallbackFunction* eventFunction, void* userData = nullptr);
		NodePath* getCameraGroup();
		PandaFramework* getFrame();
		WindowFramework* getWindow();

	};
}


#endif