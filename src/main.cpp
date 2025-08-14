
#include <cstdlib>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <print>


#include "buffers/vao.hpp"
#include "buffers/vbo.hpp"
#include "buffers/ebo.hpp"
#include "buffers/ssbo.hpp"
#include "buffers/vertex.hpp"
#include "buffers/mesh.hpp"
#include "defines.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "shader.hpp"
#include "util/resourcemanager.hpp"
#include "ecs/entitycomponentsystem.hpp"

// Callback-Funktion für Fenstergrößenänderungen
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Eingabe verarbeiten
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

template<class Type>
struct TransformComponent
{
    Type position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

template<class Type>
struct RenderableComponent
{
    Mesh<Type>& mesh;
    Material& material;
    bool render;
};

class TransformSystem2D : public ISystem
{
public:
    void update(ComponentManager& cm, float deltaTime) override
    {
        for(auto [id, pos] : LazyViewWithEntity<TransformComponent<glm::vec2>>(cm))
        {
            std::println("ID: [{}, index: {}, generation: {}], Pos: [{}, {}]", id, getEntityIndex(id), getEntityGeneration(id),pos.position.x, pos.position.y);
        }
    }
};

class AppleEntityCreateSystem : public IEntityCreateSystem
{
public:
    AppleEntityCreateSystem() = default;

    void create(ComponentManager &cm, EntityID id, glm::vec2 pos, glm::vec3 rot, glm::vec3 scale)
    {
        cm.addComponent(id, TransformComponent<glm::vec2>{pos, rot, scale});
    }
};

int main()
{
    EntityComponentSystem ecs;

    ecs.addSystem<TransformSystem2D>();
    ecs.addCreateSystem<AppleEntityCreateSystem>();
    ecs.createEntity<AppleEntityCreateSystem>(glm::vec2{1,2}, glm::vec3{3,4,5}, glm::vec3{6,7,8});
    auto id = ecs.createEntity<AppleEntityCreateSystem>(glm::vec2{2,3}, glm::vec3{3,4,5}, glm::vec3{6,7,8});
    ecs.removeEntity(id);
    ecs.createEntity<AppleEntityCreateSystem>(glm::vec2{3,4}, glm::vec3{3,4,5}, glm::vec3{6,7,8});
    ecs.updateSystem<TransformSystem2D>(1);

    // GLFW initialisieren
    if (!glfwInit()) {
        std::println("Fehler beim Initialisieren von GLFW");
        return -1;
    }

    // GLFW konfigurieren
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Fenster erstellen
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL C++23 Projekt", nullptr, nullptr);
    if (!window) {
        std::println("Fehler beim Erstellen des GLFW-Fensters");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD initialisieren
    if(!gladLoaderLoadGL()) {
        std::println("Fehler beim Initialisieren von GLAD");
        return -1;
    }

    if (GLAD_GL_ARB_bindless_texture) {
        std::println("GL_ARB_bindless_texture ist verfügbar!");
    } else {
        std::println("Fehler: GL_ARB_bindless_texture ist NICHT verfügbar.");
        return -1;
    }

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    Shader shader;
    shader.attach(GL_VERTEX_SHADER, "../data/shader/advanced/materialssbo.vert");
    shader.attach(GL_FRAGMENT_SHADER, "../data/shader/advanced/materialssbo.frag");
    shader.link();
    shader.bind();

    std::vector<Vertex2D> vertices =
    {
        Vertex2D{{-0.5f,  0.5f}, {0.0f, 1.0f}},  // Obere linke Ecke
        Vertex2D{{ 0.5f,  0.5f}, {1.0f, 1.0f}},  // Obere rechte Ecke
        Vertex2D{{ 0.5f, -0.5f}, {1.0f, 0.0f}},  // Untere rechte Ecke
        Vertex2D{{-0.5f, -0.5f}, {0.0f, 0.0f}},  // Untere linke Ecke
    };

    std::vector<GLuint> indices =
    {
        0, 1, 3,
        1, 2, 3
    };

    Mesh<Vertex2D> mesh(vertices, indices);

    VertexArrayObject vao;
    VertexBufferObject vbo;
    ElementBufferObject ebo;

    vao.bind();

    vbo.bind();
    vbo.data(mesh.getSizeVertices(), mesh.getVertices().data(), GL_STATIC_DRAW);
    vbo.addAttrib(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), offsetof(Vertex2D, position));
    vbo.addAttrib(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void*>(offsetof(Vertex2D, texCoords)));
    //vbo.addAttrib(2, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void*>(offsetof(Vertex2D, textureID)));
    //vbo.addAttrib(2, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex2D), reinterpret_cast<void*>(offsetof(Vertex2D, modelID)));

    ebo.bind();
    ebo.data(mesh.getSizeIndices(), mesh.getIndices().data(), GL_STATIC_DRAW);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    ResourceManager rManager;
    if(auto folder512 = rManager.loadTexture("folder512", "../data/texture/file-512.png"); !folder512) std::println("{}", folder512.error());
    if(auto folder50 = rManager.loadTexture("folder50", "../data/texture/file-50.png"); !folder50) std::println("{}", folder50.error());
    if(auto folder = rManager.createMaterial("folder", "folder512"); !folder) std::println("{}", folder.error());

    size_t primitiveCount = indices.size() / 3;
    std::vector<GLuint> primitivesToMaterial;
    primitivesToMaterial.reserve(primitiveCount);
    for(size_t i = 0; i < primitiveCount; i++)
        primitivesToMaterial.emplace_back(0);

    ShaderStorageBufferObject ssboPrimitiveToMaterial(0);
    ssboPrimitiveToMaterial.bind();
    ssboPrimitiveToMaterial.data(primitivesToMaterial.size() * sizeof(GLuint), primitivesToMaterial.data(), GL_STATIC_COPY_ARB);
    ssboPrimitiveToMaterial.bindBufferBase();

    auto& materials = rManager.getMaterials();

    ShaderStorageBufferObject ssboMaterials(1);
    ssboMaterials.bind();
    ssboMaterials.data(materials.size() * sizeof(Material), materials.data(), GL_STATIC_COPY_ARB);
    ssboMaterials.bindBufferBase();

    std::vector<GLuint> primitiveToModel;
    primitiveToModel.reserve(primitiveCount);
    for(size_t i = 0; i < primitiveCount; i++)
        primitiveToModel.emplace_back(0); // Alle Primitives gehören zu Model 0

    ShaderStorageBufferObject ssboPrimitiveToModel(2); // Binding 2 für Vertex Shader
    ssboPrimitiveToModel.bind();
    ssboPrimitiveToModel.data(primitiveToModel.size() * sizeof(GLuint), primitiveToModel.data(), GL_STATIC_COPY_ARB);
    ssboPrimitiveToModel.bindBufferBase();

    glm::mat4 model = glm::mat4(1);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));

    std::vector<glm::mat4> models;
    models.emplace_back(model);
    
    ShaderStorageBufferObject ssboModels(3);
    ssboModels.bind();
    ssboModels.data(models.size() * sizeof(glm::mat4), models.data(), GL_STATIC_COPY_ARB);
    ssboModels.bindBufferBase();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render-Schleife
    while (!glfwWindowShouldClose(window)) {
        // Eingabe verarbeiten
        processInput(window);

        // Rendern
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.unbind();

        // Puffer tauschen und Events abfragen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Ressourcen freigeben
    glfwTerminate();
    return 0;
}
