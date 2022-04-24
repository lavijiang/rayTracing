#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

//命中球
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

//命中三角形
bool hit_triangle(const point3& v0,const point3& v1,const point3& v2, const ray& r) {
    //reference https://blog.csdn.net/zhanxi1992/article/details/109903792
    vec3 E1 = v1 - v0;
    vec3 E2 = v2 - v0;
    point3 orig = r.origin();
    vec3 dir = r.direction();
    vec3 S = orig - v0;
    auto S1 = cross(dir,E2);
    auto S2 = cross(S,E1);
    float coeff = 1.0 / dot(S1,E1);
    float t = coeff * dot(S2,E2);
    float b1 = coeff * dot(S1,S);
    float b2 = coeff * dot(S2,dir);
    if(t>=0 && b1 >= 0 && b2 >= 0 && (1-b1-b2)>=0){
        return true;
    }
    return false;
}

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0); //水平方向
    auto vertical = vec3(0, viewport_height, 0); //垂直方向
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length); //左上角

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            //光线从中心射到屏幕上
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}