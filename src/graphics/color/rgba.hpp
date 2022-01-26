#pragma once

namespace graphics::color
{
    class RGBA
    {
    public:
        RGBA();
        RGBA(unsigned int red, unsigned int green, unsigned int blue);
        RGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
        RGBA(const RGBA &other);
        RGBA(const RGBA &&other);

        RGBA &operator=(const RGBA &other);
        RGBA &operator=(const RGBA &&other);

        unsigned int get_red() const;
        unsigned int get_green() const;
        unsigned int get_blue() const;
        unsigned int get_alpha() const;

        void set_red(unsigned int red);
        void set_green(unsigned int green);
        void set_blue(unsigned int blue);
        void set_alpha(unsigned int alpha);

    private:
        unsigned int red_;
        unsigned int green_;
        unsigned int blue_;
        unsigned int alpha_;
    };
}