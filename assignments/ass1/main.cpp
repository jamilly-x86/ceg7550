#include <opencv2/core/matx.hpp>

import assignments.ass1.image;

auto main() -> int
{
	assignments::ass1::Image image1;
	image1.load("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1.png");

	// scale image (1)
	// constexpr assignments::ass1::Image::Dimensions dimensions;
	// image1.scale(dimensions);

	// reflect image (2)
	// image1.reflect(assignments::ass1::Image::Axis::X);

	// rotate image (3)
	// constexpr auto rotation_degrees = 30.0;
	// image1.rotate(rotation_degrees);

	// shear image (4)
	// constexpr auto shear_value = 0.5;
	// image1.shear(assignments::ass1::Image::Axis::X, shear_value);

	// translate image (5)
	// constexpr assignments::ass1::Image::TranslationDirection translation_direction;
	// image1.translate(translation_direction);
	//
	// constexpr auto rotation_degrees = -20.0;
	// image1.rotate(rotation_degrees);
	//
	// constexpr assignments::ass1::Image::Dimensions dimensions{ .height = 1270 / 2, .width = 1294 / 2};
	// image1.scale(dimensions);

	// project image (affines and homographies) (6 & 7)
	// const auto matrix1 = cv::Matx33d(1.0, 0.4, 0.4, 0.1, 1.0, 0.3, 0.0, 0.0, 1.0);
	// image1.projection(matrix1);

	// const auto matrix2 = cv::Matx33d(2.1, -0.35, 1.0, -0.3, 0.7, 0.3, 0.0, 0.0, 1.0);
	// image1.projection(matrix2);

	// const auto matrix3 = cv::Matx33d(0.8, 0.2, 0.3, -0.1, 0.9, -0.1, 0.0005, -0.0005, 1.0);
	// image1.projection(matrix3);

	// const auto matrix4 = cv::Matx33d(29.25, 13.95, 20.25, 4.95, 35.55, 9.45, 0.045, 0.09, 45);
	// image1.projection(matrix4);

	assignments::ass1::Image image2;
	image2.load("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2.png");

	// scale image (1)
	// constexpr assignments::ass1::Image::Dimensions dimensions;
	// image2.scale(dimensions);

	// reflect image (2)
	// image2.reflect(assignments::ass1::Image::Axis::X);

	// rotate image (3)
	// constexpr auto rotation_degrees = 30.0;
	// image2.rotate(rotation_degrees);

	// shear image (4)
	// constexpr auto shear_value = 0.5;
	// image2.shear(assignments::ass1::Image::Axis::X, shear_value);

	// translate image (5)
	// constexpr assignments::ass1::Image::TranslationDirection translation_direction;
	// image2.translate(translation_direction);
	//
	// constexpr auto rotation_degrees = -20.0;
	// image2.rotate(rotation_degrees);
	//
	// constexpr assignments::ass1::Image::Dimensions dimensions{ .height = 1270 / 2, .width = 1294 / 2};
	// image2.scale(dimensions);

	// project image (affines and homographies) (6 & 7)
	// const auto matrix1 = cv::Matx33d(1.0, 0.4, 0.4, 0.1, 1.0, 0.3, 0.0, 0.0, 1.0);
	// image2.projection(matrix1);

	// const auto matrix2 = cv::Matx33d(2.1, -0.35, 1.0, -0.3, 0.7, 0.3, 0.0, 0.0, 1.0);
	// image2.projection(matrix2);

	// const auto matrix3 = cv::Matx33d(0.8, 0.2, 0.3, -0.1, 0.9, -0.1, 0.0005, -0.0005, 1.0);
	// image2.projection(matrix3);

	// const auto matrix4 = cv::Matx33d(29.25, 13.95, 20.25, 4.95, 35.55, 9.45, 0.045, 0.09, 45);
	// image2.projection(matrix4);

	return 0;
}