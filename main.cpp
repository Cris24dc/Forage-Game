#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string loadShader(const std::string &filename) {
    std::ifstream file(filename);
    std::stringstream stream;
    
    stream << file.rdbuf();

    file.close();
    return stream.str();
}

int main() {
    // vertex data
    GLfloat vertices[] = {
        // positions          // colors                   // tex coords
        -0.20f, -0.20f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f,     0.0f,
        0.20f, -0.20f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,   1.0f / 4, 0.0f,
        0.20f,  0.20f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,   1.0f / 4, 1.0f / 3,
        -0.20f,  0.20f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,     1.0f / 3
    };

    GLuint indices[] = 
    {
        0, 1, 2,
        1, 2, 3,
        2, 3, 4,
        3, 4, 5,
        4, 5, 6,
        5, 6, 7,
        6, 7, 0,
        7, 0, 1,
    };

    // glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "My first OpenGL Program", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    // transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // shaders
    std::string vert_shader_string, frag_shader_string;
    vert_shader_string = loadShader("./assets/shaders/default.vert");
    const char* shaderSource_vert = vert_shader_string.c_str();
    frag_shader_string = loadShader("./assets/shaders/default.frag");
    const char* shaderSource_frag = frag_shader_string.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &shaderSource_vert, nullptr);
    glShaderSource(fragmentShader, 1, &shaderSource_frag, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // now shaders can be freed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // textures
    int width;
    int height;
    int nrChannels;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // param pixeli
    // Filtrare la mărire (zoom in)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // margini corecte (poți pune și CLAMP_TO_EDGE dacă nu vrei artefacte)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // end param pixeli


    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("./assets/textures/Player/Idle.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);  



    // buffers
    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position (x, y, z, w)
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color (r, g, b, a)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coords (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Now we can unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // main loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.95f, 0.76f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use this specific shader and VAO (you can change them)
        glUseProgram(program);
        glBindVertexArray(VAO);

        // texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(program, "uTexture"), 0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
        // glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Delete all the object
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(program);

    // clear window and 
    glfwDestroyWindow(window);
    // clear glfw
    glfwTerminate();

    return 0;
}