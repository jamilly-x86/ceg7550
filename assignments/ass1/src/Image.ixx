/// @file image.ixx
/// @module assignments.ass1.image
/// @brief Image container and geometric transformation utilities for Assignment 1.
///
/// This module provides a lightweight grayscale image wrapper built on OpenCV
/// and implements common geometric transformations (scaling, rotation,
/// translation, reflection, shear, and projective transforms) using
/// inverse-mapping techniques.
module;

#include <filesystem>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <ranges>
#include <string_view>

export module assignments.ass1.image;

export namespace assignments::ass1
{
	/// @class Image
	/// @brief Grayscale image abstraction supporting manual geometric transformations.
	///
	/// The Image class encapsulates a single-channel (grayscale) OpenCV matrix
	/// and provides implementations of common image transformations without
	/// relying on OpenCV's built-in warp utilities. All transformations use
	/// inverse mapping to avoid holes in the output image.
	class Image
	{
	public:
		/// @enum Axis
		/// @brief Axis selection for reflection and shear operations.
		enum class Axis : std::uint8_t
		{
			/// Reflect or shear along the X axis
			X,
			/// Reflect or shear along the Y axis
			Y,
			/// Reflect along both X and Y axes
			XY
		};

		/// @struct Dimensions
		/// @brief Target dimensions for scaling operations.
		struct Dimensions
		{
			/// Output image height in pixels
			int height = Height;
			/// Output image width in pixels
			int width = Width;
		};

		/// @struct TranslationDirection
		/// @brief Translation offsets for image translation.
		struct TranslationDirection
		{
			/// Horizontal translation in pixels
			double x_translation = XDirection;
			/// Vertical translation in pixels
			double y_translation = YDirection;
		};

		/// @brief Constructs an empty Image.
		Image() noexcept = default;

		/// @brief Read a grayscale image from disk.
		/// @param file_name Path to the image file.
		///
		/// The image is loaded using OpenCV in grayscale mode. If loading fails,
		/// the internal image remains unchanged.
		auto read(std::string_view file_name) -> void
		{
			if (const auto image = cv::imread(std::string{file_name}, cv::IMREAD_GRAYSCALE); image.empty() == false)
			{
				image_ = image;

				const auto path = std::filesystem::path(file_name);

				set_name(path.stem().string());
				set_extension(path.extension().string());
			}
		}

		/// @brief Writes an image to disk
		/// @param file_name Path to the image file.
		auto write(std::string_view file_name) const -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			cv::imwrite(std::string{file_name}, image_);
		}

		/// @brief Set image file name
		/// @param image_name Name of the image file.
		auto set_name(std::string_view image_name) -> void
		{
			if (image_name_ != image_name)
			{
				image_name_ = image_name;
			}
		}

		/// @brief Get image file name
		/// @return Image file name represented as a string_view.
		auto get_name() const -> std::string_view
		{
			return image_name_;
		}

		/// @brief Set image file extension
		/// @param image_extension File extension of the image.
		auto set_extension(std::string_view image_extension) -> void
		{
			if (image_extension_ != image_extension)
			{
				image_extension_ = image_extension;
			}
		}

		/// @brief Get image file extension.
		/// @return Image file extension represented as a string_view.
		auto get_extension() const -> std::string_view
		{
			return image_extension_;
		}

		/// @brief Scale the image to the given dimensions.
		/// @param dimensions Target width and height.
		///
		/// Scaling is performed using nearest-neighbor sampling via inverse
		/// coordinate mapping.
		auto scale(Dimensions dimensions) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			auto scaled_image = cv::Mat(dimensions.height, dimensions.width, image_.type());

			const auto x_scale_factor = static_cast<double>(dimensions.width) / width;
			const auto y_scale_factor = static_cast<double>(dimensions.height) / height;

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, scaled_image.rows})
			{
				for (auto x_out : std::ranges::iota_view{0, scaled_image.cols})
				{
					const auto x_in = static_cast<int>(x_out / x_scale_factor);

					if (const auto y_in = static_cast<int>(y_out / y_scale_factor); x_in >= 0 && x_in < width && y_in >= 0 && y_in < height)
					{
						scaled_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_in, x_in);
					}
					else
					{
						scaled_image.at<std::uint8_t>(y_out, x_out) = 0;
					}
				}
			}

			image_ = scaled_image;
		}

		/// @brief Rotate the image by an angle.
		/// @param angle_degress Rotation angle in degrees (counter-clockwise).
		///
		/// The output image is expanded to fully contain the rotated result.
		auto rotate(double angle_degress) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			const auto theta = angle_degress * M_PI / 180.0;
			const auto cos_theta = std::cos(theta);
			const auto sin_theta = std::sin(theta);

			// compute bounding box of rotated image
			const auto new_width = static_cast<int>(std::ceil(std::abs(width * cos_theta) + std::abs(height * sin_theta)));
			const auto new_height = static_cast<int>(std::ceil(std::abs(width * sin_theta) + std::abs(height * cos_theta)));

			auto rotated_image = cv::Mat(new_height, new_width, image_.type(), cv::Scalar(0));

			// center images
			const auto old_x_center = (width - 1) / 2.0;
			const auto old_y_center = (height - 1) / 2.0;
			const auto new_x_center = (new_width - 1) / 2.0;
			const auto new_y_center = (new_height - 1) / 2.0;

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, new_height})
			{
				for (auto x_out : std::ranges::iota_view{0, new_width})
				{
					// translate output pixel to new image center
					const auto x = x_out - new_x_center;
					const auto y = y_out - new_y_center;

					const auto x_in = (cos_theta * x) + (sin_theta * y) + old_x_center;
					const auto y_in = (-sin_theta * x) + (cos_theta * y) + old_y_center;

					const auto x_int = static_cast<int>(std::round(x_in));
					const auto y_int = static_cast<int>(std::round(y_in));

					if (x_int >= 0 && x_int < width && y_int >= 0 && y_int < height)
					{
						rotated_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_int, x_int);
					}
				}
			}

			image_ = rotated_image;
		}

		/// @brief Translate the image by the given offsets.
		/// @param td Translation direction and magnitude.
		///
		/// The output image is resized as necessary to accommodate the shift.
		auto translate(TranslationDirection td) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			// compute bounding box
			const auto min_x = std::min(0.0, td.x_translation);
			const auto min_y = std::min(0.0, td.y_translation);
			const auto max_x = std::max(static_cast<double>(width), width + td.x_translation);
			const auto max_y = std::max(static_cast<double>(height), height + td.y_translation);

			const auto new_width = static_cast<int>(std::ceil(max_x - min_x));
			const auto new_height = static_cast<int>(std::ceil(max_y - min_y));

			auto translated_image = cv::Mat(new_height, new_width, image_.type(), cv::Scalar(0));

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, new_height})
			{
				for (auto x_out : std::ranges::iota_view{0, new_width})
				{
					// shift back into original coordinate space
					const auto x = x_out + min_x;
					const auto y = y_out + min_y;

					const auto x_in = x - td.x_translation;
					const auto y_in = y - td.y_translation;

					const int x_int = static_cast<int>(std::round(x_in));
					const int y_int = static_cast<int>(std::round(y_in));

					if (x_int >= 0 && x_int < width && y_int >= 0 && y_int < height)
					{
						translated_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_int, x_int);
					}
				}
			}

			image_ = translated_image;
		}

		/// @brief Reflect the image across the specified axis.
		/// @param axis Axis of reflection.
		auto reflect(Axis axis) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			auto reflected_image = cv::Mat(height, width, image_.type());

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, height})
			{
				for (auto x_out : std::ranges::iota_view{0, width})
				{
					auto x_in = x_out;
					auto y_in = y_out;

					switch (axis)
					{
						case Axis::X:
						{
							y_in = (height - 1) - y_out;
							break;
						}
						case Axis::Y:
						{
							x_in = (width - 1) - x_out;
							break;
						}
						case Axis::XY:
						{
							x_in = (width - 1) - x_out;
							y_in = (height - 1) - y_out;
							break;
						}
						default:
						{
							break;
						}
					}

					reflected_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_in, x_in);
				}
			}

			image_ = reflected_image;
		}

		/// @brief Apply a shear transformation.
		/// @param axis Shear direction.
		/// @param k Shear factor.
		auto shear(Axis axis, double k) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			// transform the 4 corners
			// clang-format off
			std::vector<cv::Point2d> corners = {
				{0, 0},
				{static_cast<double>(width), 0},
				{0, static_cast<double>(height)},
				{static_cast<double>(width), static_cast<double>(height)}
			};
			// clang-format on

			for (auto& corner : corners)
			{
				switch (axis)
				{
					case Axis::X:
					{
						corner.x = corner.x + (k * corner.y);
						break;
					}
					case Axis::Y:
					{
						corner.y = corner.y + (k * corner.x);
					}
					default:
					{
						break;
					}
				}
			}

			auto min_x = corners.at(0).x;
			auto max_x = corners.at(0).x;
			auto min_y = corners.at(0).y;
			auto max_y = corners.at(0).y;

			for (const auto& corner : corners)
			{
				min_x = std::min(min_x, corner.x);
				max_x = std::max(max_x, corner.x);
				min_y = std::min(min_y, corner.y);
				max_y = std::max(max_y, corner.y);
			}

			const auto new_width = static_cast<int>(std::ceil(max_x - min_x));
			const auto new_height = static_cast<int>(std::ceil(max_y - min_y));

			auto sheared_image = cv::Mat(new_height, new_width, image_.type(), cv::Scalar(0));

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, new_height})
			{
				for (auto x_out : std::ranges::iota_view{0, new_width})
				{
					// shift output pixel back into original coordinate space
					const auto x = x_out + min_x;
					const auto y = y_out + min_y;

					auto x_in = x;
					auto y_in = y;

					switch (axis)
					{
						case Axis::X:
						{
							x_in = x - (k * y);
							break;
						}
						case Axis::Y:
						{
							y_in = y - (k * x);
							break;
						}
						default:
						{
							break;
						}
					}

					const auto x_int = static_cast<int>(std::round(x_in));

					if (const auto y_int = static_cast<int>(std::round(y_in)); x_int >= 0 && x_int < width && y_int >= 0 && y_int < height)
					{
						sheared_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_int, x_int);
					}
				}
			}

			image_ = sheared_image;
		}

		/// @brief Apply a projective (homography) transformation.
		/// @param h 3x3 homography matrix.
		///
		/// The image is warped using inverse homography mapping to avoid gaps.
		auto projection(const cv::Matx33d& h) -> void
		{
			if (image_.empty() == true)
			{
				return;
			}

			const auto width = image_.cols;
			const auto height = image_.rows;

			// transform the 4 corners
			// clang-format off
			const std::vector<cv::Point2d> corners = {
				{0, 0},
				{static_cast<double>(width), 0},
				{0, static_cast<double>(height)},
				{static_cast<double>(width), static_cast<double>(height)}
			};
			// clang-format on

			auto min_x = std::numeric_limits<double>::max();
			auto min_y = std::numeric_limits<double>::max();
			auto max_x = std::numeric_limits<double>::lowest();
			auto max_y = std::numeric_limits<double>::lowest();

			for (const auto& corner : corners)
			{
				cv::Vec3d h_projected = h * cv::Vec3d(corner.x, corner.y, 1.0);

				const auto x = h_projected(0) / h_projected(2);
				const auto y = h_projected(1) / h_projected(2);

				min_x = std::min(min_x, x);
				min_y = std::min(min_y, y);
				max_x = std::max(max_x, x);
				max_y = std::max(max_y, y);
			}

			const auto new_width = static_cast<int>(std::ceil(max_x - min_x));
			const auto new_height = static_cast<int>(std::ceil(max_y - min_y));

			auto projected_image = cv::Mat(new_height, new_width, image_.type(), cv::Scalar(0));

			// invert transform
			const cv::Matx33d h_inverted = h.inv();

			// inverse matrix mapping
			for (auto y_out : std::ranges::iota_view{0, new_height})
			{
				for (auto x_out : std::ranges::iota_view{0, new_width})
				{
					const auto x = x_out + min_x;
					const auto y = y_out + min_y;

					cv::Vec3d p = h_inverted * cv::Vec3d(x, y, 1.0);

					const auto x_in = p(0) / p(2);
					const auto y_in = p(1) / p(2);

					const auto x_int = static_cast<int>(std::round(x_in));

					if (const auto y_int = static_cast<int>(std::round(y_in)); x_int >= 0 && x_int < width && y_int >= 0 && y_int < height)
					{
						projected_image.at<std::uint8_t>(y_out, x_out) = image_.at<std::uint8_t>(y_int, x_int);
					}
				}
			}

			image_ = projected_image;
		}

	private:
		/// Internal OpenCV image storage (grayscale)
		cv::Mat image_;
		std::string image_name_;
		std::string image_extension_;
		/// Default image height
		static constexpr auto Height = 1080;
		/// Default image width
		static constexpr auto Width = 1920;
		/// Default X translation
		static constexpr auto XDirection = 300;
		/// Default Y translation
		static constexpr auto YDirection = 500;
	};
}