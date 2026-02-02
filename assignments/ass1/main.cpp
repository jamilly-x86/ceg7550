#include <opencv2/core/matx.hpp>

import assignments.ass1.image;

auto main() -> int
{
	assignments::ass1::Image image1;
	image1.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image1.png");
	assignments::ass1::Image image2;
	image2.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image2.png");
	assignments::ass1::Image image3;
	image3.read("/Users/jamalbrown/src/ceg7550/assignments/ass1/images/Image3.jpg");

	std::vector<assignments::ass1::Image> images;
	images.emplace_back(image1);
	images.emplace_back(image2);
	images.emplace_back(image3);

	std::ranges::for_each(images,
						  [&](auto& image)
						  {
							  const auto name = std::string(image.get_name());
							  const auto ext = std::string(image.get_extension());
							  const auto base = "/Users/jamalbrown/src/ceg7550/assignments/ass1/images/";

							  // (1) scale
							  {
								  assignments::ass1::Image out = image;
								  constexpr assignments::ass1::Image::Dimensions dims;

								  out.scale(dims);
								  out.write(base + name + "-1" + ext);
							  }

							  // (2) reflect
							  {
								  assignments::ass1::Image out = image;
								  out.reflect(assignments::ass1::Image::Axis::X);
								  out.write(base + name + "-2" + ext);
							  }

							  // (3) rotate
							  {
								  assignments::ass1::Image out = image;
								  out.rotate(30.0);
								  out.write(base + name + "-3" + ext);
							  }

							  // (4) shear
							  {
								  assignments::ass1::Image out = image;
								  out.shear(assignments::ass1::Image::Axis::X, 0.5);
								  out.write(base + name + "-4" + ext);
							  }

							  // (5) translate + rotate + scale
							  {
								  assignments::ass1::Image out = image;
								  constexpr assignments::ass1::Image::TranslationDirection td;

								  out.translate(td);
								  out.rotate(-20.0);

								  constexpr assignments::ass1::Image::Dimensions dims2{.height = 1270 / 2, .width = 1294 / 2};

								  out.scale(dims2);
								  out.write(base + name + "-5" + ext);
							  }

							  // (6) affine
							  {
								  assignments::ass1::Image out = image;
								  const cv::Matx33d h(1.0, 0.4, 0.4, 0.1, 1.0, 0.3, 0.0, 0.0, 1.0);

								  out.projection(h);
								  out.write(base + name + "-61" + ext);
							  }

							  // (7) homography
							  {
								  assignments::ass1::Image out = image;
								  const cv::Matx33d h(0.8, 0.2, 0.3, -0.1, 0.9, -0.1, 0.0005, -0.0005, 1.0);

								  out.projection(h);
								  out.write(base + name + "-71" + ext);
							  }
						  });

	return 0;
}