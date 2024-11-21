#ifndef MODEL_HPP
#define MODEL_HPP

#include "Shader.hpp" 
#include "MatrixStack.hpp"
#include "checkGLError.hpp"
#include "Renderer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Model {
    private:
        void drawTorso(MatrixStack &m, Shader &shader);
        void drawHead(MatrixStack &m, Shader &shader);
        void drawArm(MatrixStack &m, Shader &shader ,bool left);
        void drawLeg(MatrixStack &m, Shader &shader ,bool left);
    public:
        Model();
        void draw(MatrixStack &m, Shader &shader);
};

#endif