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

    class SVGObject {
        public:
            SVGObject(Color color, Shape shape);
            ~SVGObject() {};

            Shape get_form();

        protected:
            Color fill;
            Shape form;
    };

    class SVGRect : SVGObject {
        public:
            SVGRect(Color color, double width, double height, double x, double y);
            ~SVGRect() {}

            graphics::shapes::Cuboid cuboid();

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

            graphics::shapes::Cuboid cuboid();

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

        private:
            SVGObject* parseElement(tinyxml2::XMLElement * elem);
            std::vector<SVGObject*> objs;
    };
}