#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// build and compile shaders
// -------------------------
Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

// load models
// -----------
Model ourModel(".\\resources\\objects\\backpack\\backpack.obj");

//objectLoader knife = objectLoader(".\\resources\\objects\\knife\\knife.obj");
#define KNIFE_ZOOM 5.0f

//实现移动鼠标观察模型所需变量
#define PI 3.1415926f
static float c = PI / 180.0f;
static float r = 1.0f;
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;
static float zoom = 1.0f;
static float zoom_step = 0.5f;


//安置光源
void setLightResource() {
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

//初始化
void init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 960);
    glutCreateWindow("Texture Reflection");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightResource();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
}

void Texture()
{

}

void display()
{
    //glColor3f(1.0, 1.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -5.0f);
    //setLightResource();
    //glPushMatrix();

    //float eyex = r * cos((float)(c * degree));
    //float eyez = r * sin((float)(c * degree));
    //
    //gluLookAt(eyex, 1.0f, eyez, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    ////knife.Draw(KNIFE_ZOOM/zoom);
    //Texture();
    //glPopMatrix();
    //glutSwapBuffers();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // don't forget to enable shader before setting uniforms
    ourShader.use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    ourShader.setMat4("model", model);
    ourModel.Draw(ourShader);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

// 鼠标拖动
void mouseMove(int button, int state, int x, int y)
{
    //printf("mouse button %d, state %d, x %d, y %d\n", button, state, x, y);
    if (state == GLUT_DOWN) {
        oldPosX = x;
        oldPosY = y;
    }
}

void mouseWheel(int button, int state, int x, int y)
{
    //printf("wheel: button %d, state %d, x %d, y %d\n", button, state, x, y);
    if (zoom <= zoom_step && state == -1)
        return;
    zoom += state * zoom_step;
}

// 视角的切换
void changeViewPoint(int x, int y)
{
    int temp = x - oldPosX;
    degree += temp;
    oldPosX = x;
    oldPosY = y;
}

void myIdle()
{
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // 改变窗口大小
    glutMouseFunc(mouseMove);
    glutMouseWheelFunc(mouseWheel);
    glutMotionFunc(changeViewPoint); // 鼠标移动事件
    glutIdleFunc(myIdle); // 空闲时调用
    glutMainLoop();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
