#include "lodepng.h"

#include <complex>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using Complex = std::complex<double>;

/// Try to determine if `c` is in the Mandelbrot set,
/// using at most `limit` iterations to decide.
std::optional<size_t> escape_time(Complex c, size_t limit)
{
    Complex z(0.0, 0.0);

    for (size_t i = 0; i < limit; ++i)
    {
        if (norm(z) > 4.0)
        {
            return i;
        }

        z = z * z + c;
    }

    return {};
}

/// Parse the string `s` as a coordinate pair, like `"400x600"` or `"1.0,0.5"`.
template <typename T>
std::optional<std::pair<T, T>> parse_pair(const std::string& s, char separator)
{
    size_t index = s.find(separator);

    if (index != std::string::npos)
    {
        T left, right;
        std::stringstream ss1(s.substr(0, index));
        std::stringstream ss2(s.substr(index + 1));

        if ((ss1 >> left) && (ss2 >> right))
        {
            return std::make_optional(std::make_pair(left, right));
        }
    }

    return {};
}

/// Parse a pair of floating-point numbers separated by
/// a comma as a complex number.
std::optional<Complex> parse_complex(const std::string& s)
{
    if (auto p = parse_pair<double>(s, ','))
    {
        return std::make_optional(Complex(p->first, p->second));
    }

    return {};
}

/// Given the row and column of a pixel in the output image,
/// return the corresponding point on the complex plane.
Complex pixel_to_point(std::pair<size_t, size_t> bounds,
                       std::pair<size_t, size_t> pixel, Complex upper_left,
                       Complex lower_right)
{
    double width = lower_right.real() - upper_left.real();
    double height = upper_left.imag() - lower_right.imag();

    return { upper_left.real() + static_cast<double>(pixel.first) * width /
                                     static_cast<double>(bounds.first),
             upper_left.imag() - static_cast<double>(pixel.second) * height /
                                     static_cast<double>(bounds.second) };
}

/// Render a rectangle of the Mandelbrot set into a buffer of pixels.
void render(std::vector<uint8_t>& pixels, std::pair<size_t, size_t> bounds,
            Complex upper_left, Complex lower_right)
{
    size_t width = bounds.first;
    size_t height = bounds.second;

    for (size_t row = 0; row < height; ++row)
    {
        for (size_t column = 0; column < width; ++column)
        {
            Complex point = pixel_to_point(bounds, std::make_pair(column, row),
                                           upper_left, lower_right);

            auto color = escape_time(point, 255);
            pixels[row * width + column] =
                color ? 255 - static_cast<uint8_t>(*color) : 0;
        }
    }
}

/// Write the buffer `pixels`, whose dimensions are given by `bounds`,
/// to the file named `filename`.
void write_image(const std::string& filename,
                 const std::vector<uint8_t>& pixels,
                 std::pair<size_t, size_t> bounds)
{
    unsigned width = static_cast<unsigned>(bounds.first);
    unsigned height = static_cast<unsigned>(bounds.second);

    // Encode the image
    std::vector<unsigned char> png;

    // If there's an error, display it.
    if (unsigned error =
            lodepng::encode(png, pixels, width, height, LCT_GREY, 8))
    {
        std::cerr << "Encoder error " << error << ": "
                  << lodepng_error_text(error) << '\n';
        std::terminate();
    }

    // Write the PNG to file
    lodepng::save_file(png, filename);
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0]
                  << " FILE PIXELS UPPER_LEFT LOWER_RIGHT" << '\n';
        std::cerr << "Example: " << argv[0]
                  << " mandel.png 1000x750 -1.20,0.35 -1.00,0.20" << '\n';
        return -1;
    }

    auto bounds = parse_pair<size_t>(argv[2], 'x')
                      .value_or(std::pair<size_t, size_t>{ 0, 0 });

    if (bounds.first == 0 || bounds.second == 0)
    {
        std::cerr << "Error parsing image dimensions" << '\n';
        return -1;
    }

    auto upper_left = parse_complex(argv[3]).value_or(Complex(0, 0));
    auto lower_right = parse_complex(argv[4]).value_or(Complex(0, 0));

    if (upper_left == Complex(0, 0) || lower_right == Complex(0, 0))
    {
        std::cerr << "Error parsing corner points" << '\n';
        return -1;
    }

    std::vector<uint8_t> pixels(bounds.first * bounds.second);

    // Scope of slicing up `pixels` into horizontal bands.
    {
        std::vector<std::thread> threads;
        std::mutex mtx;

        for (size_t i = 0; i < bounds.second; ++i)
        {
            auto band_bounds = std::make_pair(bounds.first, 1);
            auto band_upper_left = pixel_to_point(bounds, std::make_pair(0, i),
                                                  upper_left, lower_right);
            auto band_lower_right =
                pixel_to_point(bounds, std::make_pair(bounds.first, i + 1),
                               upper_left, lower_right);

            threads.emplace_back([&, i, band_bounds, band_upper_left,
                                  band_lower_right]() {
                std::vector<uint8_t> band(band_bounds.first);
                render(band, band_bounds, band_upper_left, band_lower_right);

                std::lock_guard lock(mtx);
                std::ranges::copy(band, pixels.begin() + static_cast<ptrdiff_t>(
                                                             i * bounds.first));
            });
        }

        for (auto& t : threads)
        {
            t.join();
        }
    }

    write_image(argv[1], pixels, bounds);

    return 0;
}
