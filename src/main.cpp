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
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    unsigned int VAO, VBO; //Usar unsigned int por que o OpenGL define IDs como inteiros sem sinal comaçando em 1

    glGenBuffers(1, &VBO); //"Gere 1 ID de buffer e coloque em VBO, temos que passar o endereço da variável &VBO para escrever dentro dela
    cout << VBO << endl;
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO); //Começa a gravar oque vem em seguida

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Linka o VBO ao GL_ARRAY_BUFFER, o qual é o buffer para vértices, temos que declarar esse antes de BUFFERDATA
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Age sobre o buffer vinculado GL_ARRAY_BUFFER que está linkado a VBO, sizeof diz quanto
    //exatamente reservar na VRAM, vertices é um ponteiro para o ínicio dos dados na RAM, GL_STATIC_DRAW é dica de uso para o driver.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Passsamos como é para ele ler, indice 0, é o canal 0, oque  o VS vai ler com layout
    //tamanho 3 por vertice, cada valor é float
    //não normalizar, o tamanho da stride o tamanho de onde começa e termina  o vértice, e o offset
    glEnableVertexAttribArray(0); //Liga o canal 0

    //Código em GLSL, linguagem utilizada para escrever shaders, version 330 core é obrigatório, versão do OpenGL, layout (location = 0) in vec 3 aPos
    //Receba um vec3, 3 floats, e as chame de aPos, location 0 é o mesmo 0 que o do VertexAttribPointer, void main roda uma vez por vértice, 3 vezes no triângulo
    //gl_position diz este vértice fica nessa posição, aqui só passamos vec3, e criamos um vec4 com outra posição 1.0
    const char* vertexShaderSource = R"(#version 330 core
        layout (location = 0) in vec3 aPos;

        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    //out saída, a cor final do pixel, main roda uma vez para cada pixel dentro do triângulo, fragColor diz a cor que vai ser preenchido
    const char* fragmentShaderSource = R"(#version 330 core
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";

    int success;
    char infoLog[512];


    //Aqui temos que compilar nossos shaders, criamos um unsigned int com o nome que quisermos, aqui vertexShader, que recebe um glCreateShader, com o tipo de
    //Vertex shader, então o ID do nosso objeto é guardado em vertexShader, Unsigned int por que os ID de opengl são inteiros positivos, GLUINT, depois
    //da primeira linha temos um objeto vazio criado pelo driver, 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    cout << vertexShader << endl;
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); //Vertex shader, diz em qual shader colocar o contexto, 1 quantas strings está entregando
    //&vertexShaderSource é o texto em si, nullptr é o tamanho de cada string.
    glCompileShader(vertexShader); //compilando o Source que acabamos de por em vertexShader, driver pega o texto GLSL, e transforma em código de máquina
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //Retorno de erro
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Erro no vertex shader:\n" << infoLog << "\n";
    }


    //Mesma lógica
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Erro no fragment shader:\n" << infoLog << "\n";
    }


    unsigned int shaderProgram = glCreateProgram();//Pede ao driver um programa vazio e devolva o ID dele, não precisa de parâmetros, neste ponto, caixa vazia
    glAttachShader(shaderProgram, vertexShader); //Attachshader anexa no shaderPogram o nosso shader que acabamos de criar
    glAttachShader(shaderProgram, fragmentShader); //Mesma coisa
    glLinkProgram(shaderProgram); //Aqui o link acontece de verdade, junta os shaders anexados em um único pipeline, faz verificações.
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Erro ao linkar o programa:\n" << infoLog << "\n";
    }

    //Depois do programa compilado e linkado o programa já tem a própria cópia dos shaders, ai deletamos para não virar lixo de memória.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) { //verifica se tem chamada para fechar a janela
        glClearColor(0.25f, 0.80f, 0.85f, 1.0f); //configura um estado do OpenGL informando qual cor será usada na limpeza
        glClear(GL_COLOR_BUFFER_BIT); //Limpeza do buffer

        //Denovo máquina de estados, a partir de agora todo desenho obedece shaderProgram, usa estes shaders, 
        glUseProgram(shaderProgram);
        //Ativa o VAO, ao ativa-lo resgatamos qual VBO usar, e como usar
        glBindVertexArray(VAO);
        //Como montar a forma, cada grupo de 3 vértices vira um triângulo, 0 por qual vértice começar no buffer, 3 quantos vértices usar
        glDrawArrays(GL_TRIANGLES, 0, 3);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate();
            return 0;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
