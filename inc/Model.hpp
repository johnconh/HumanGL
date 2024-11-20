#ifndef MODEL_HPP
#define MODEL_HPP

#include "MatrixStack.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Model {
    private:
        void drawTorso(MatrixStack &m);
        void drawHead(MatrixStack &m);
        void drawArm(MatrixStack &m, bool left);
        void drawLeg(MatrixStack &m, bool left);
    public:
        Model();
        void draw(MatrixStack &m);
}; 
#endif