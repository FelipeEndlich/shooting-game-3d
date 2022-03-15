#include <string>
#include <iostream>
#include "svg_reader.hpp"

using game::Color;
using game::Shape;
using game::SceneObjectType;
using game::SceneObject;
using game::SVGObject;
using game::SVGRect;
using game::SVGCircle;
using game::SVGList;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using ::graphics::shapes::Cuboid;

SVGObject::SVGObject(Color color, Shape shape) {
    fill = color;
    form = shape;
}

Shape SVGObject::get_form() {
    return form;
}

Color SVGObject::get_fill() {
    return fill;
}

SVGRect::SVGRect(Color color, double width, double height, double x, double y) :
          SVGObject(color, Shape::RECT)
{
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
}

Cuboid SVGRect::cuboid(double x_off, double y_off) {
    Cuboid rect(width, height, fill == Color::BLACK ? 100 : 1);
    rect.Translate(x - x_off, y - y_off, 0);

    return rect;
}

double SVGRect::get_x() {
    return x;
}

double SVGRect::get_y() {
    return y;
}

SVGCircle::SVGCircle(Color color, double radius, double cx, double cy) :
           SVGObject(color, Shape::CIRCLE)
{
    this->cx = cx;
    this->cy = cy;
    this->radius = radius;
}

graphics::shapes::Cuboid SVGCircle::cuboid(double x, double y) {
    Cuboid rect(radius * 2, radius * 2, radius * 2);
    rect.Translate(cx / 2 - x, cy / 2 - y, 0);

    return rect;
}

SVGObject* SVGList::parseElement(XMLElement * elem) {
    std::string elem_type;
    elem_type = (std::string)elem->Value();

    Color color;
    std::string elem_color;
    elem_color = (std::string)elem->Attribute("fill");

    if (!elem_color.compare("red"))
        color = Color::RED;
    else if (!elem_color.compare("green"))
        color = Color::GREEN;
    else if (!elem_color.compare("blue"))
        color = Color::BLUE;
    else
        color = Color::BLACK;

    if (elem_type == "rect") {
        SVGRect* rect = new SVGRect(
            color,
            atof(elem->Attribute("width")),
            atof(elem->Attribute("height")),
            atof(elem->Attribute("x")),
            atof(elem->Attribute("y"))
        );

        return (SVGObject*)rect;
    } else {
        SVGCircle* circle = new SVGCircle(
            color,
            atof(elem->Attribute("r")),
            atof(elem->Attribute("cx")),
            atof(elem->Attribute("cy"))
        );

        return (SVGObject*)circle;
    }
} 

SVGList::SVGList(const char* svg_path) {
    XMLDocument svg;
    svg.LoadFile(svg_path);

    XMLElement* curr_elem;
    curr_elem = svg.FirstChildElement()->FirstChildElement();

    while (curr_elem) {
        SVGObject* form;
        form = parseElement(curr_elem);
        objs.push_back(form);

        if (form->get_fill() == Color::BLUE &&
            form->get_form() == Shape::RECT)
        {
            x = ((SVGRect*)form)->get_x();
            y = ((SVGRect*)form)->get_y();
        }

        if (curr_elem->NextSiblingElement())
            curr_elem = curr_elem->NextSiblingElement();
        else break;
    }
}

std::vector<Cuboid> SVGList::cuboids() {
    std::vector<Cuboid> forms;
    
    for (SVGObject* svg : objs) {
        if (svg->get_form() == Shape::RECT) {
            SVGRect* rect;
            rect = (SVGRect*)svg;
            forms.push_back(rect->cuboid(x, y));
        } else {
            SVGCircle* circ;
            circ = (SVGCircle*)svg;
            forms.push_back(circ->cuboid(x, y));
        }
    }

    return forms;
}

std::vector<SceneObject> SVGList::scene_objects() {
    std::vector<SceneObject> scene_objs;
    
    for (SVGObject* svg : objs) {
        if (svg->get_form() == Shape::RECT) {
            SVGRect* rect;
            rect = (SVGRect*)svg;

            struct SceneObject obj = {
                rect->cuboid(x, y),
                svg->get_fill() == Color::BLUE ?
                SceneObjectType::BACKGROUND :
                SceneObjectType::OBSTACLE
            };
            scene_objs.push_back(obj);

        } else {
            SVGCircle* circ;
            circ = (SVGCircle*)svg;
            
            struct SceneObject obj = {
                circ->cuboid(x, y),
                svg->get_fill() == Color::RED ?
                SceneObjectType::ENEMY :
                SceneObjectType::HERO
            };
            scene_objs.push_back(obj);
        }
    }

    return scene_objs;
}
