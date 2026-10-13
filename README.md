# OpenGL Curso

Repositório de estudos de OpenGL e processamento gráfico em C++, com o código acompanhando a cada etapa do aprendizado. Serve como diário de estudo e como material de consulta.

## Tecnologias

| Item | Uso |
|---|---|
| C++17 | Linguagem |
| OpenGL [3.3 Core] | API gráfica |
| [GLFW](https://www.glfw.org/) | Criação de janela, contexto OpenGL e entrada (teclado/mouse) |
| [GLAD](https://github.com/Dav1dde/glad) | Carregamento das funções do OpenGL |
| [GLM](https://github.com/g-truc/glm) | Matemática (vetores, matrizes, transformações) |
| CMake + vcpkg | Build e gerenciamento de dependências |

## Pré-requisitos

- **Windows 10/11**
- **Visual Studio 2026 Community** com a carga de trabalho *Desenvolvimento para desktop com C++* (já inclui compilador MSVC, Windows SDK, CMake e vcpkg)
- **Git**
- Placa de vídeo com suporte a OpenGL 3.3 ou superior (drivers atualizados)

Não é necessário instalar GLFW, GLAD ou GLM manualmente: o vcpkg baixa e compila tudo automaticamente (veja `vcpkg.json`).

## Como compilar e rodar

1. Clone o repositório:
```
   git clone https://github.com/SEU-USUARIO/opengl-estudos.git
```
2. No Visual Studio: **Arquivo → Abrir → Pasta** e selecione a pasta clonada.
3. Aguarde a configuração do CMake terminar (na primeira vez demora alguns minutos, pois as bibliotecas são compiladas). Acompanhe em **Exibir → Saída → CMake**.
4. No menu ao lado do botão ▶, selecione o executável `opengl-curso.exe`.
5. Pressione **F5**.

### Usando outro vcpkg

Se preferir um vcpkg próprio, defina a variável de ambiente `VCPKG_ROOT` com o caminho dele antes de abrir o Visual Studio.

### Pela linha de comando

```
cmake --preset default
cmake --build build --config Debug
```

## Estrutura

```
.
├── CMakeLists.txt       # Configuração do build
├── CMakePresets.json    # Preset de configuração (gerador e toolchain do vcpkg)
├── vcpkg.json           # Dependências do projeto
└── src/
    └── main.cpp
```

## Progresso

- [x] Criação de janela com GLFW
- [x] Fechar a janela com ESC
- [x] Primeiro VBO
- [ ] Shaders
- [ ] Texturas
- [ ] Transformações
- [ ] Câmera
- [ ] Iluminação

## Problemas comuns

**Erro ao configurar o CMake:** confira se a carga de trabalho de C++ está instalada e se a variável `VCPKG_ROOT` aponta para um vcpkg válido.

## Referências

- [LearnOpenGL](https://learnopengl.com/)
- [Documentação do GLFW](https://www.glfw.org/documentation.html)
- [Documentação do vcpkg](https://learn.microsoft.com/vcpkg/)