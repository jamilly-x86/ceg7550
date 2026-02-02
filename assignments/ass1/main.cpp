#include <opencv2/core/matx.hpp>

import assignments.ass1.image;

auto main() -> int
{
	assignments::ass1::Image image1;
	image1.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1.png");

	// scale image (1)
	assignments::ass1::Image image1_1 = image1;
	constexpr assignments::ass1::Image::Dimensions dimensions;
	image1_1.scale(dimensions);
	image1_1.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-1.png");

	// reflect image (2)
	assignments::ass1::Image image1_2 = image1;
	image1_2.reflect(assignments::ass1::Image::Axis::X);
	image1_2.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-2.png");

	// rotate image (3)
	assignments::ass1::Image image1_3 = image1;
	constexpr auto rotation_degrees = 30.0;
	image1_3.rotate(rotation_degrees);
	image1_3.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-3.png");

	// shear image (4)
	assignments::ass1::Image image1_4 = image1;
	constexpr auto shear_value = 0.5;
	image1_4.shear(assignments::ass1::Image::Axis::X, shear_value);
	image1_4.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-4.png");

	// translate image (5)
	assignments::ass1::Image image1_5 = image1;
	constexpr assignments::ass1::Image::TranslationDirection translation_direction;
	image1_5.translate(translation_direction);

	constexpr auto rotation_degrees2 = -20.0;
	image1_5.rotate(rotation_degrees2);

	// TODO: implement scale with optional parameter for percent scale
	constexpr assignments::ass1::Image::Dimensions dimensions2{.height = 1270 / 2, .width = 1294 / 2};
	image1_5.scale(dimensions2);
	image1_5.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-5.png");

	// project image (affines and homographies) (6 & 7)
	assignments::ass1::Image image1_61 = image1;
	const auto matrix1 = cv::Matx33d(1.0, 0.4, 0.4, 0.1, 1.0, 0.3, 0.0, 0.0, 1.0);
	image1_61.projection(matrix1);
	image1_61.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-61.png");

	assignments::ass1::Image image1_62 = image1;
	const auto matrix2 = cv::Matx33d(2.1, -0.35, 1.0, -0.3, 0.7, 0.3, 0.0, 0.0, 1.0);
	image1_62.projection(matrix2);
	image1_62.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-62.png");

	assignments::ass1::Image image1_71 = image1;
	const auto matrix3 = cv::Matx33d(0.8, 0.2, 0.3, -0.1, 0.9, -0.1, 0.0005, -0.0005, 1.0);
	image1_71.projection(matrix3);
	image1_71.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-71.png");

	assignments::ass1::Image image1_72 = image1;
	const auto matrix4 = cv::Matx33d(29.25, 13.95, 20.25, 4.95, 35.55, 9.45, 0.045, 0.09, 45);
	image1_72.projection(matrix4);
	image1_72.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1-72.png");

	// IMAGE 2
	assignments::ass1::Image image2;
	image2.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2.png");

	// scale image (1)
	assignments::ass1::Image image2_1 = image2;
	image2_1.scale(dimensions);
	image2_1.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-1.png");

	// reflect image (2)
	assignments::ass1::Image image2_2 = image2;
	image2_2.reflect(assignments::ass1::Image::Axis::X);
	image2_2.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-2.png");

	// rotate image (3)
	assignments::ass1::Image image2_3 = image2;
	image2_3.rotate(rotation_degrees);
	image2_3.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-3.png");

	// shear image (4)
	assignments::ass1::Image image2_4 = image2;
	image2_4.shear(assignments::ass1::Image::Axis::X, shear_value);
	image2_4.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-4.png");

	// translate image (5)
	assignments::ass1::Image image2_5 = image2;
	image2_5.translate(translation_direction);

	image2_5.rotate(rotation_degrees2);

	// TODO: implement scale with optional parameter for percent scale
	image2_5.scale(dimensions2);
	image2_5.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-5.png");

	// project image (affines and homographies) (6 & 7)
	assignments::ass1::Image image2_61 = image2;
	image2_61.projection(matrix1);
	image2_61.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-61.png");

	assignments::ass1::Image image2_62 = image2;
	image2_62.projection(matrix2);
	image2_62.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-62.png");

	assignments::ass1::Image image2_71 = image2;
	image2_71.projection(matrix3);
	image2_71.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-71.png");

	assignments::ass1::Image image2_72 = image2;
	image2_72.projection(matrix4);
	image2_72.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2-72.png");

	// IMAGE 3
	assignments::ass1::Image image3;
	image3.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3.jpg");

	// scale image (1)
	assignments::ass1::Image image3_1 = image3;
	image3_1.scale(dimensions);
	image3_1.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-1.jpg");

	// reflect image (2)
	assignments::ass1::Image image3_2 = image3;
	image3_2.reflect(assignments::ass1::Image::Axis::X);
	image3_2.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-2.jpg");

	// rotate image (3)
	assignments::ass1::Image image3_3 = image3;
	image3_3.rotate(rotation_degrees);
	image3_3.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-3.jpg");

	// shear image (4)
	assignments::ass1::Image image3_4 = image3;
	image3_4.shear(assignments::ass1::Image::Axis::X, shear_value);
	image3_4.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-4.jpg");

	// translate image (5)
	assignments::ass1::Image image3_5 = image3;
	image3_5.translate(translation_direction);

	image3_5.rotate(rotation_degrees2);
	// TODO: implement scale with optional parameter for percent scale
	image3_5.scale(dimensions2);
	image3_5.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-5.jpg");

	// project image (affines and homographies) (6 & 7)
	assignments::ass1::Image image3_61 = image3;
	image3_61.projection(matrix1);
	image3_61.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-61.jpg");

	assignments::ass1::Image image3_62 = image3;
	image3_62.projection(matrix2);
	image3_62.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-62.jpg");

	assignments::ass1::Image image3_71 = image3;
	image3_71.projection(matrix3);
	image3_71.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-71.jpg");

	assignments::ass1::Image image3_72 = image3;
	image3_72.projection(matrix4);
	image3_72.write("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3-72.jpg");

	return 0;
}