#pragma once

#include <vector>
#include "../ext/tinyxml2.hpp"
#include "../graphics/shapes/cuboid.hpp"

namespace game {
    enum Color {
        BLACK,
        RED,
        GREEN,
        BLUE
    };

    enum Shape {
        RECT,
        CIRCLE
    };

    enum SceneObjectType {
        HERO,
        ENEMY,
        OBSTACLE,
        BACKGROUND
    };

    struct SceneObject {
        graphics::shapes::Cuboid r;
        SceneObjectType t;
    };

    class SVGObject {
        public:
            SVGObject(Color color, Shape shape);
            ~SVGObject() {};

            Shape get_form();
            Color get_fill();

        protected:
            Color fill;
            Shape form;
    };

    class SVGRect : SVGObject {
        public:
            SVGRect(Color color, double width, double height, double x, double y);
            ~SVGRect() {}

            graphics::shapes::Cuboid cuboid(double x, double y);
            double get_x();
            double get_y();
            double get_width();
            double get_height();

        private:
            double width;
            double height;
            double x;
            double y;
    };

    class SVGCircle : SVGObject {
        public:
            SVGCircle(Color color, double radius, double cx, double cy);
            ~SVGCircle() {}

            graphics::shapes::Cuboid cuboid(double x, double y);

        private:
            double cx;
            double cy;
            double radius;
    };

    class SVGList {
        public:
            SVGList(const char* SVG_path);
            ~SVGList() {}

            std::vector<graphics::shapes::Cuboid> cuboids();
            std::vector<SceneObject> scene_objects();

        private:
            SVGObject* parseElement(tinyxml2::XMLElement * elem);
            std::vector<SVGObject*> objs;
            double x;
            double y;
            double width;
            double height;
    };
}