/**
 * Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++
 *      library for processing and rendering 3D data. 2018.
 * ------------------------------------------------------------------
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EASY3D_CORE_CURVE_H
#define EASY3D_CORE_CURVE_H


#include <vector>


namespace easy3d {

    /*
    unsigned int steps = 20;
    {
        vec3 a(0, 0, 0);
        vec3 b(800, 0, 0);
        vec3 c(800, 800, 0);

        std::vector<vec3> points;
        curve::quadratic(a, b, c, steps, points);
        std::cout << "first point: " << points.front() << ", last point: " << points.back() << std::endl;

        std::vector<unsigned int> indices;
        for (unsigned int i=0; i<points.size() - 1; ++i) {
            indices.push_back(i);
            indices.push_back(i+1);
        }
        LinesDrawable *curve = new LinesDrawable;
        curve->update_vertex_buffer(points);
        curve->update_element_buffer(indices);
        curve->set_impostor_type(easy3d::LinesDrawable::CYLINDER);
        curve->set_line_width(5);
        curve->set_uniform_coloring(vec4(0, 0, 1, 1));
        viewer.add_drawable(curve);
    }

    {
        vec3 a(0, 0, 0);
        vec3 b(400, 0, 0);
        vec3 c(400, 800, 0);
        vec3 d(800, 800, 0);
        std::vector<vec3> points;
        curve::cubic(a, b, c, d, steps, points);
        std::cout << "first point: " << points.front() << ", last point: " << points.back() << std::endl;

        std::vector<unsigned int> indices;
        for (unsigned int i = 0; i < points.size() - 1; ++i) {
            indices.push_back(i);
            indices.push_back(i + 1);
        }
        LinesDrawable *curve = new LinesDrawable;
        curve->update_vertex_buffer(points);
        curve->update_element_buffer(indices);
        curve->set_impostor_type(easy3d::LinesDrawable::CYLINDER);
        curve->set_line_width(5);
        curve->set_uniform_coloring(vec4(0, 1, 0, 1));
        viewer.add_drawable(curve);
    }
     */

    namespace curve {

        /**
         * De Casteljau algorithm evaluating a quadratic or conic (second degree) curve.
         * Works for both 2D and 3D.
         * @param curve Returns the sequence of points on the curve.
         */
        template<typename Point>
        inline
        void quadratic(const Point &A, const Point &B, const Point &C, unsigned int steps, std::vector<Point> &curve) {
            typedef typename Point::FT FT;
            for (unsigned int i = 0; i < steps + 1; i++) {
                const FT t = static_cast<FT>(i) / steps;

                Point U = (1.0 - t) * A + t * B;
                Point V = (1.0 - t) * B + t * C;

                curve.push_back((1.0 - t) * U + t * V);
            }
        }

        /**
         * De Casteljau algorithm evaluating a cubic (third degree) curve.
         * Works for both 2D and 3D.
         * @param curve Returns the sequence of points on the curve.
         */
        template<typename Point>
        inline
        void cubic(const Point &A, const Point &B, const Point &C, const Point &D, unsigned int steps,
                   std::vector<Point> &curve) {
            typedef typename Point::FT FT;
            for (unsigned int i = 0; i < steps + 1; i++) {
                const FT t = static_cast<FT>(i) / steps;

                const Point U = (1.0 - t) * A + t * B;
                const Point V = (1.0 - t) * B + t * C;
                const Point W = (1.0 - t) * C + t * D;

                const Point M = (1.0 - t) * U + t * V;
                const Point N = (1.0 - t) * V + t * W;

                curve.push_back((1.0 - t) * M + t * N);
            }
        }

    }   // namespace curve

}   // namespace easy3d


#endif  // EASY3D_CORE_CURVE_H
