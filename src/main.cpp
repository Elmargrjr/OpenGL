#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define GLFW_KEY_ESCAPE   256

using namespace std;

int main() {

    if (!glfwInit()) { //biblioteca precisa ser inicilizada antes de começar a codar
        cerr << "Falha ao inicializar GLFW\n"; //cerr serve para exibir mensagens de erro, cerr é unbuffered, ao contrário do cout que armazena temporiamente
        return -1; //valor diferente de 0, para sinalizar erro
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //glfwWindowHint configura uma caracterítica que será considerada na próxima criação de janela
    //GLFW_CONTEXT_VERSION_MAJOR identifica a versão principal do contexto solicitado
    //3 define a versão
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Escolhe o perfil do OpenGL, CORE remove funcionalidades, API mais moderna

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - Etapa 0", nullptr, nullptr); //Criação da janela, int width, int height, título, monitor, e share

    if (!window) {
        cerr << "Falha ao criar janela GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //Ativa o contexto

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Falha ao inicializar GLAD\n";
        return -1;
    }

    float vertices[] = { //Definindo os vértices em (X,Y,Z)
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    unsigned int VBO; //Usar unsigned int por que o OpenGL define IDs como inteiros sem sinal comaçando em 1
    glGenBuffers(1, &VBO); //"Gere 1 ID de buffer e coloque em VBO, temos que passar o endereço da variável &VBO para escrever dentro dela
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Linka o VBO ao GL_ARRAY_BUFFER, o qual é o buffer para vértices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Age sobre o buffer vinculado GL_ARRAY_BUFFER que está linkado a VBO, sizeof diz quanto
    //exatamente reservar na VRAM, vertices é um ponteiro para o ínicio dos dados na RAM, GL_STATIC_DRAW é dica de uso para o driver.

    while (!glfwWindowShouldClose(window)) { //verifica se tem chamada para fechar a janela
        glClearColor(0.25f, 0.80f, 0.85f, 1.0f); //configura um estado do OpenGL informando qual cor será usada na limpeza
        glClear(GL_COLOR_BUFFER_BIT); //Limpeza do buffer

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate();
            return 0;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}