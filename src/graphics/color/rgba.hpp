#pragma once

namespace graphics::color
{
    class RGBA
    {
    public:
        RGBA();
        RGBA(unsigned int r, unsigned int g, unsigned int b);
        RGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
        RGBA(const RGBA &other);
        RGBA(const RGBA &&other);

        RGBA &operator=(const RGBA &other);
        RGBA &operator=(const RGBA &&other);

        unsigned int getR() const;
        unsigned int getG() const;
        unsigned int getB() const;
        unsigned int getA() const;

        void setR(unsigned int r);
        void setG(unsigned int g);
        void setB(unsigned int b);
        void setA(unsigned int a);

    private:
        unsigned int r;
        unsigned int g;
        unsigned int b;
        unsigned int a;
    };
}