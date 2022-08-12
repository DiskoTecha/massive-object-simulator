#include "Visualizer3D.h"

namespace dw
{
	// Protected Constructor
	Visualizer3D::Visualizer3D(const char* title) : title(title) {}

	// Static private fields
	Visualizer3D* Visualizer3D::instance = nullptr;
	std::mutex Visualizer3D::mutex;

	// Static method, create a new instance (if not yet created) and return it
	Visualizer3D* Visualizer3D::getInstance(const char* title)
	{
		// Lock the mutex to stop data racing in multithread uses
		std::lock_guard<std::mutex> lock(mutex);
		if (instance == nullptr)
		{
			instance = new Visualizer3D(title);
		}

		return instance;
	}

	// Open a framework and a window from it, and store the window, framework, and camera in variables for use later
	void Visualizer3D::init(int& argc, char**& argv)
	{
		// Open a new window framework
		this->frame = new PandaFramework();
		frame->open_framework(argc, argv);

		// Set the window title and open the window
		frame->set_window_title(title);
		window = frame->open_window();

		// Set the background black because the natural grey is gross
		window->set_background_type(WindowFramework::BackgroundType::BT_black);

		// Store camera in variable
		camera = window->get_camera_group();
	}

	// Run the main loop of the framework
	void Visualizer3D::run()
	{
		frame->main_loop();
	}

	// Close the framework
	void Visualizer3D::shutdown()
	{
		frame->close_framework();
	}

	NodePath Visualizer3D::loadModel(const char* path, Vector3 scale, Vector3 pos, Vector3 color)
	{
		NodePath model = window->load_model(frame->get_models(), path);
		model.reparent_to(window->get_render());
		model.set_pos(pos.x, pos.y, pos.z);
		model.set_scale(scale.x, scale.y, scale.z);
		model.set_color(color.x, color.y, color.z);
		return model;
	}

	void Visualizer3D::addTask(const char* name, GenericAsyncTask::TaskFunc* taskFunc, void* userData)
	{
		dw_visualizer_3d_task_manager->add(new GenericAsyncTask(name, taskFunc, userData));
	}

	// Getters: Unwrap the panda framework
	NodePath Visualizer3D::getCamera()
	{
		return camera;
	}

	PandaFramework* Visualizer3D::getFrame()
	{
		return frame;
	}

	WindowFramework* Visualizer3D::getWindow()
	{
		return window;
	}
}