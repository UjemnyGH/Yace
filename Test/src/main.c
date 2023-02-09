#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <GL/gl.h>

int main(int argc, char **argv) {
    printf("\t\tHello world!\n");

	glfwInit();

	GLFWwindow *window = glfwCreateWindow(800, 600, "Window", NULL, NULL);

	if(!window) {
		exit(1);
	}

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}
