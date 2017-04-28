#include <iostream>	// std::cout
#include <string.h>	// strcpy
#include <vector>	// vectors
#include <iomanip>	//set precision

#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Intersection.hpp"
#include "Loader.hpp"
#include "Scene.hpp"

Renderer renderer;
Loader loader;
Scene scene;

/* Flags for different arguments
 0 - render
 1 - sceneinfo
 2 - pixelray
 3 - firsthit
 4 - pixelcolor
*/
int arg_flags[4] = {0};

using namespace std;

int main(int args, char **argv) {
	
	// Catch empty line args
	if (args == 1) {
		return 1;
	}

	// Store command line arguments
	arg_flags[0] = !strcmp(argv[1], "render");
	arg_flags[1] = !strcmp(argv[1], "sceneinfo");
	arg_flags[2] = !strcmp(argv[1], "pixelray");
	arg_flags[3] = !strcmp(argv[1], "firsthit");
	arg_flags[4] = !strcmp(argv[1], "pixelcolor");
	renderer.BRDF_flag = !strcmp(argv[args-1], "-altbrdf");

	cout << setprecision(4);

	// Parse file + create scene
	loader.parse(argv[2], scene);


 	// Render
	if (arg_flags[0]) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		renderer.render(scene, window_width, window_height);
	}

	// Sceneinfo
	if (arg_flags[1]) {
		scene.print();
	}

	// Pixelray 
	if (arg_flags[2] || arg_flags[3] || arg_flags[4]) {
		int window_width = atoi(argv[3]);
		int window_height = atoi(argv[4]);
		int pixel_x = atoi(argv[5]);
		int pixel_y = atoi(argv[6]);
		Ray ray = scene.createCameraRay(window_width, window_height, pixel_x, pixel_y);
		Intersection in(&scene, ray);
		cout << "Pixel: [" << pixel_x << ", " << pixel_y << "] ";
		ray.print();
		// Firsthit or Pixelcolor
		if (arg_flags[3] || arg_flags[4]) {
			in.print();
			renderer.print();
			glm::vec3 color = renderer.calculateColor(scene, glm::ivec2(window_width, window_height), pixel_x, pixel_y, renderer.BRDF_flag);
		   cout << "Color: (" << color.x << " " << color.y  << " " << color.z << ")" << endl;
		}
 	}

	return 0;
	}
