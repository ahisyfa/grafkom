#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class Pendulum{
    private:
        bool pendulum1Move;
        bool pendulum2Move;
        bool pend1Balik;
        bool pend2Balik;
        double sudutPend1;
        double sudutPend2;

        void drawPendulum(){
            // Garis
            glColor3f(1.f, 0.f, 0.f);
            glLineWidth(3);
            glBegin(GL_LINES);
                glVertex2f(0, 0.0);
                glVertex2f(0, -0.6);
            glEnd();

            // Bandul pendulum
            glPushMatrix();
                glTranslatef(0, -0.6, 0);
                glBegin(GL_POLYGON);
                    for(int i=0;i<60;i++){
                        glVertex2f(sin(i*2*3.14/60) * 0.03,cos(i*2*3.14/60) * 0.03);
                    }
                glEnd();
            glPopMatrix();
        }

    public:
        Pendulum(){
            pendulum1Move  = true;
            sudutPend1 = 3;
            sudutPend2 = 0;
            pend1Balik = false;
            pend2Balik = false;
        }
        void setAnimate(){
            if(pendulum1Move){
                if(!pend1Balik){
                    sudutPend1 += 0.2;
                    if(sudutPend1 >= 20){
                        pend1Balik = true;
                    }
                }else{ // Kalo bailk
                    sudutPend1 -= 0.2;
                    if(sudutPend1 <= 5){
                        pendulum2Move = true;
                    }
                    if(sudutPend1 <= 0){
                        pend1Balik = false;
                        pendulum1Move = false;
                    }
                }
            }

            if(pendulum2Move){
                if(!pend2Balik){
                    sudutPend2 -= 0.2;
                    if(sudutPend2 <= -20){
                        pend2Balik = true;
                    }
                }else{ // Kalo bailk
                    sudutPend2 += 0.2;
                    if(sudutPend2 >= -5){
                        pendulum1Move = true;
                    }
                    if(sudutPend2 >= 0){
                        pend2Balik = false;
                        pendulum2Move = false;
                    }
                }
            }
        }
        void draw(){
            glPushMatrix();
                glRotatef(sudutPend1, 0.f, 0.f, 1.f);
                drawPendulum();
            glPopMatrix();

            glPushMatrix();
                glRotatef(sudutPend2, 0.f, 0.f, 1.f);
                drawPendulum();
            glPopMatrix();
        }
};

Pendulum pendulum;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    switch(action){
        case GLFW_PRESS:
            switch(key){
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                case GLFW_KEY_SPACE :

                    break;
            }
            break;
        case GLFW_RELEASE:
            switch(key){
                case GLFW_KEY_SPACE :

                    break;
            }
            break;
    }
}

void setup_viewport(GLFWwindow* window){
    // setting viewports size, projection etc
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(){
    pendulum.draw();
}

int main(void){
    GLFWwindow* window;
    if (!glfwInit()) exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Pendulum by Amin", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)){

        pendulum.setAnimate();

        setup_viewport(window);
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
