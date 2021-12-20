#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <array>

#include <cmath>

constexpr int EXECUTION_COUNT{ 50 };

#pragma region Utils

struct execution_result
{
	std::chrono::nanoseconds time{};
	int execution_count{};

	std::chrono::nanoseconds time_per_execution() const
	{
		return time / execution_count;
	}

	std::string display() const
	{
		auto display_time = time / (double)execution_count;

		std::ostringstream ss{};

		if (display_time.count() < 100)
		{
			ss << display_time.count() << "ns";
			return ss.str();
		}

		auto us{ std::chrono::duration_cast<std::chrono::microseconds>(display_time) };

		if (us.count() < 100)
		{
			ss << us.count() << "us";
			return ss.str();
		}
		
		auto ms{ std::chrono::duration_cast<std::chrono::milliseconds>(display_time) };

		if (ms.count() < 100)
		{
			ss << ms.count() << "ms";
			return ss.str();
		}

		auto seconds{ std::chrono::duration_cast<std::chrono::seconds>(display_time) };

		if (seconds.count() < 100)
		{
			ss << seconds.count() << "sc";
			return ss.str();
		}

		auto minutes{ std::chrono::duration_cast<std::chrono::minutes>(display_time) };

		ss << minutes.count() << "mn";
		return ss.str();
	}
};

struct point_3d
{
	int x{};
	int y{};
	int z{};

	auto operator<=>(const point_3d&) const = default;

	int operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
		return 0;
	}
};

inline std::fstream read_input(const std::string& file)
{
	std::fstream input{ file, std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open " << file << '\n';
		throw std::runtime_error("failed to read file: " + file);
	}

	return input;
}

#pragma endregion Utils

#pragma region Advent of Code - 2015

#pragma region Day 1

std::string day_1_2015__read_input()
{
	std::fstream input{ read_input("../input/2015/day_1.txt") };

	std::string data{};
	input >> data;

	return data;
}

void day_1_2015__execute__part1(const std::string& data)
{
	int floor{};

	for (size_t i = 0; i < data.size(); i++)
	{
		const char ch{ data.at(i) };

		if (ch == '(')
		{
			floor++;
		}
		else if (ch == ')')
		{
			floor--;
		}
	}

	_ASSERT(floor == 280);
}

void day_1_2015__execute__part2(const std::string& data)
{
	int floor{};

	for (size_t i = 0; i < data.size(); i++)
	{
		const char ch{ data.at(i) };

		if (ch == '(')
		{
			floor++;
		}
		else if (ch == ')')
		{
			floor--;
		}

		if (floor == -1)
		{
			_ASSERT(i + 1 == 1797);
			break;
		}
	}
}

execution_result day_1_2015__time()
{
	std::string input{ day_1_2015__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_1_2015__execute__part1(input);
		day_1_2015__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start), EXECUTION_COUNT };
}

#pragma endregion Day 1

#pragma region Day 2

struct day_2_2015_data
{
	int length{};
	int width{};
	int height{};
};

std::vector<day_2_2015_data> day_2_2015__read_input()
{
	std::fstream input{ read_input("../input/2015/day_2.txt") };

	std::vector<day_2_2015_data> data{};

	std::string line{};

	while (getline(input, line))
	{
		size_t pos{ line.find('x') };

		day_2_2015_data value{};

		value.length = atoi(line.substr(0, pos).c_str());
		line = line.substr(pos + 1);
		pos = line.find('x');

		value.width = atoi(line.substr(0, pos).c_str());
		line = line.substr(pos + 1);
		pos = line.find('x');

		value.height = atoi(line.substr(0, pos).c_str());

		data.push_back(value);
	}

	return data;
}

void day_2_2015__execute__part1(const std::vector<day_2_2015_data>& data)
{
	int total_paper{};

	for (const day_2_2015_data& value : data)
	{
		const int side_1{ value.length * value.width };
		const int side_2{ value.width * value.height };
		const int side_3{ value.height * value.length };

		int smallest{ side_1 };

		if (side_2 < smallest)
		{
			smallest = side_2;
		}

		if (side_3 < smallest)
		{
			smallest = side_3;
		}

		total_paper += smallest + ((2 * side_1) + (2 * side_2) + (2 * side_3));
	}
	
	_ASSERT(total_paper == 1606483);
}

void day_2_2015__execute__part2(const std::vector<day_2_2015_data>& data)
{
	int total_ribbon_feet{};

	for (const day_2_2015_data& value : data)
	{
		const int side_1{ value.length * value.width };
		const int side_2{ value.width * value.height };
		const int side_3{ value.height * value.length };

		int smallest{ side_1 };
		int side_num{ 1 };

		if (side_2 < smallest)
		{
			smallest = side_2;
			side_num = 2;
		}

		if (side_3 < smallest)
		{
			smallest = side_3;
			side_num = 3;
		}

		switch (side_num)
		{
		case 1:
			total_ribbon_feet += value.length + value.length + value.width + value.width;
			break;
		case 2:
			total_ribbon_feet += value.width + value.width + value.height + value.height;
			break;
		case 3:
			total_ribbon_feet += value.height + value.height + value.length + value.length;
		}

		total_ribbon_feet += value.length * value.width * value.height;
	}

	_ASSERT(total_ribbon_feet == 3842356);
}

execution_result day_2_2015__time()
{
	unsigned volatile int keep_this_function = 0;

	std::vector<day_2_2015_data> input{ day_2_2015__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_2_2015__execute__part1(input);
		day_2_2015__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 2

#pragma endregion Advent of Code - 2015

#pragma region Advent of Code - 2016
#pragma endregion Advent of Code - 2016

#pragma region Advent of Code - 2017
#pragma endregion Advent of Code - 2017

#pragma region Advent of Code - 2018
#pragma endregion Advent of Code - 2018

#pragma region Advent of Code - 2019
#pragma endregion Advent of Code - 2019

#pragma region Advent of Code - 2020
#pragma endregion Advent of Code - 2020

#pragma region Advent of Code - 2021

#pragma region Day 19

struct day_19_2021__beacon_distances
{
	point_3d beacon{};
	std::vector<int> distances{};
	std::vector<int> scanners_seen_by{};
};

struct day_19_2021__scanner
{
	std::set<point_3d> beacons{};
};

struct day_19_2021__scanner_processed_data
{
	day_19_2021__scanner scanner{};
	std::vector<day_19_2021__beacon_distances> beacon_distances{};
};

constexpr int DAY_19_2021__THRESHOLD = 12;


std::vector<day_19_2021__scanner> day_19_2021__read_input()
{
	std::fstream input{ read_input("../input/2021/day_19.txt") };

	std::vector<day_19_2021__scanner> data{};

	std::string line{};
	day_19_2021__scanner scanner{};

	getline(input, line); // skip first scanner line

	while (getline(input, line))
	{
		if (line.empty()) continue;

		if (strcmp(line.substr(0, 3).c_str(), "---") == 0)
		{
			data.push_back(scanner);

			// new scanner
			scanner = {};
		}
		else
		{
			point_3d beacon{};

			size_t pos{ line.find(',') };

			beacon.x = atoi(line.substr(0, pos).c_str());
			line = line.substr(pos + 1);
			pos = line.find(',');

			beacon.y = atoi(line.substr(0, pos).c_str());
			line = line.substr(pos + 1);
			pos = line.find(',');

			beacon.z = atoi(line.substr(0, pos).c_str());

			scanner.beacons.insert(beacon);
		}
	}

	data.push_back(scanner); // add the last scanner

	return data;
}

//int day_19_2021__distances_in_common(const day_19_2021__beacon_distances& one, const day_19_2021__beacon_distances& two)
//{
//	int count{};
//
//	for (auto i : one.distances)
//	{
//		if (std::find(two.distances.begin(), two.distances.end(), i) != two.distances.end())
//		{
//			count++;
//		}
//	}
//	return count;
//}
//
//int day_19_2021__rotation_needed(const day_19_2021__scanner_processed_data& scanner0, const day_19_2021__scanner_processed_data& two)
//{
//	int count{};
//
//	point_3d common_one[2];
//	point_3d common_two[2];
//	int num{};
//
//	for (const auto& a : scanner0.beacon_distances)
//	{
//		for (const auto& b : two.beacon_distances)
//		{
//			if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//			{
//				count++;
//
//				common_one[num] = a.beacon;
//				common_two[num] = b.beacon;
//				num++;
//
//				if (num > 1)
//				{
//					break;
//				}
//			}
//		}
//	}
//
//	if (count < 2)
//	{
//		return -1; // not overlapping
//	}
//
//
//
//	std::cout << "points in common: " << count << '\n';
//	return count;
//}

//void day_19_2021__mark_common_beacons(int src_index, day_19_2021__scanner_processed_data& one, day_19_2021__scanner_processed_data& two)
//{
//
//	for (auto& a : one.beacon_distances)
//	{
//		for (auto& b : two.beacon_distances)
//		{
//			if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//			{
//				b.scanners_seen_by.push_back(src_index);
//			}
//		}
//	}
//}

//int day_19_2021__count_points(std::vector<day_19_2021__scanner_processed_data>& data)
//{
//	int total_beacons{};
//
//	//for (day_19_2021__scanner_processed_data& scanner1 : data)
//	for (int i = 0; i < (int)data.size(); i++)
//	{
//		day_19_2021__scanner_processed_data& scanner1{ data.at(i) };
//
//		total_beacons += (int)scanner1.beacon_distances.size();
//
//		for (day_19_2021__scanner_processed_data& scanner2 : data)
//		{
//			//day_19_2021__mark_common_beacons(i, scanner1, scanner2);
//		}
//	}
//
//	std::cout << "starting beacon count: " << total_beacons << '\n';
//
//	int unique_beacons{};
//	std::vector<int> common_beacons{};
//	int extra_counts{};
//
//	//for (day_19_2021__scanner_processed_data& scanner : data)
//	for (int i = 0; i < (int)data.size(); i++)
//	{
//		day_19_2021__scanner_processed_data& scanner1{ data.at(i) };
//
//		for (auto& beacon : scanner1.beacon_distances)
//		{
//			if (beacon.scanners_seen_by.size() > 0)
//			{
//				unique_beacons++;
//			}
//		}
//
//		// remove this scanner from all the points in the other scanners
//		for (auto& a : scanner1.beacon_distances)
//		{
//			for (int j = 0; j < (int)data.size(); j++)
//			{
//				if (i == j) continue;
//
//				for (auto& b : data.at(j).beacon_distances)
//				{
//					if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//					{
//						/*auto find = std::find(b.scanners_seen_by.begin(), b.scanners_seen_by.end(), i);
//
//						if (find != b.scanners_seen_by.end())
//						{
//							b.scanners_seen_by.erase(find);
//						}*/
//						b.scanners_seen_by = {}; // clear the list, we already counted this point
//					}
//				}
//			}
//		}
//	}
//
//	return unique_beacons;
//}

std::vector<point_3d> create_delta_positions(const std::set<point_3d>& points, const point_3d& position, point_3d& delta_point, int rx, int ry, int rz, int sx, int sy, int sz)
{
	std::vector<point_3d> deltas{};

	for (const point_3d& point : points)
	{
		deltas.push_back({ sx * (point[rx] - position[rx]), sy * (point[ry] - position[ry]), sz * (point[rz] - position[rz]) });
	}
	delta_point = { -sx * position[rx], -sy * position[ry], -sz * position[rz] };

	return deltas;
}

bool day_19_2021__attempt_merge(day_19_2021__scanner& merged_scanner, const day_19_2021__scanner& scanner_to_merge, point_3d& scanner_position)
{
	//  [facing, up, right, sign_f, sign_u, sign_r]
	static const std::vector<std::array<int, 6>> rotations {
		{0, 1, 2, 1, 1, 1},    //  x  y  z
		{0, 1, 2, 1, -1, -1},  //  x -y -z
		{0, 2, 1, 1, 1, -1},   //  x  z -y
		{0, 2, 1, 1, -1, 1},   //  x -z  y
		{0, 1, 2, -1, 1, -1},  // -x  y -z
		{0, 1, 2, -1, -1, 1},  // -x -y  z
		{0, 2, 1, -1, 1, 1},   // -x  z  y
		{0, 2, 1, -1, -1, -1}, // -x -z -y
	};

	// create all 24 orientations that we have to try
	std::vector<std::array<int, 6>> rotations_to_try{};

	for (int i = 0; i < 3; i++)
	{
		for (const auto& rots : rotations)
		{
			rotations_to_try.push_back({ (i + rots[0]) % 3, (i + rots[1]) % 3, (i + rots[2]) % 3, rots[3], rots[4], rots[5] });
		}
	}

	for (const auto& beacon : scanner_to_merge.beacons)
	{
		for (const auto& rotation : rotations_to_try)
		{
			point_3d delta_position{};

			std::vector<point_3d> delta{ create_delta_positions(scanner_to_merge.beacons, beacon, delta_position, rotation[0], rotation[1], rotation[2], rotation[3], rotation[4], rotation[5]) };

			for (const auto& merged_beacon : merged_scanner.beacons)
			{
				// check matches
				int matches{};

				for (const point_3d& delta_point : delta)
				{
					matches += merged_scanner.beacons.count({ delta_point.x + merged_beacon.x, delta_point.y + merged_beacon.y, delta_point.z + merged_beacon.z });

					if (matches >= 12) break;
				}

				if (matches >= 12)
				{
					// merge
					for (const point_3d& delta_point : delta)
					{
						merged_scanner.beacons.insert({ delta_point.x + merged_beacon.x, delta_point.y + merged_beacon.y, delta_point.z + merged_beacon.z });
					}

					scanner_position = { delta_position.x + merged_beacon.x, delta_position.y + merged_beacon.y, delta_position.z + merged_beacon.z };

					return true;
				}
				
			}
		}
	}
	return false;
}

// inspired by codefrommars
void day_19_2021__execute__part1(const std::vector<day_19_2021__scanner>& data)
{
	std::vector<int> scanners_to_merge{};

	for (int i = 1; i < (int)data.size(); i++)
	{
		scanners_to_merge.push_back(i);
	}

	day_19_2021__scanner merged_scanner{ data.at(0) };

	while (scanners_to_merge.size() > 0)
	{
		for (int i = 0; i < scanners_to_merge.size(); i++)
		{
			point_3d scanner_pos{};

			// try to merge, if successful, erase from scanners_to_merge
			if (day_19_2021__attempt_merge(merged_scanner, data.at(scanners_to_merge.at(i)), scanner_pos))
			{
				scanners_to_merge.erase(scanners_to_merge.begin() + i);
				break;
			}
		}
	}

	std::cout << "total beacons: " << merged_scanner.beacons.size() << '\n';
}

void day_19_2021__execute__part2(const std::vector<day_19_2021__scanner>& data)
{
	std::vector<int> scanners_to_merge{};

	for (int i = 1; i < (int)data.size(); i++)
	{
		scanners_to_merge.push_back(i);
	}

	day_19_2021__scanner merged_scanner{ data.at(0) };

	std::vector<point_3d> scanner_positions{};

	while (scanners_to_merge.size() > 0)
	{
		for (int i = 0; i < scanners_to_merge.size(); i++)
		{
			point_3d scanner_pos{};

			// try to merge, if successful, erase from scanners_to_merge
			if (day_19_2021__attempt_merge(merged_scanner, data.at(scanners_to_merge.at(i)), scanner_pos))
			{
				scanner_positions.push_back(scanner_pos);

				scanners_to_merge.erase(scanners_to_merge.begin() + i);
				break;
			}
		}
	}

	int max_manhattan_distance{};

	for (const point_3d& pos1 : scanner_positions)
	{
		for (const point_3d& pos2 : scanner_positions)
		{
			const int x_diff{ std::abs(pos2.x - pos1.x) };
			const int y_diff{ std::abs(pos2.y - pos1.y) };
			const int z_diff{ std::abs(pos2.z - pos1.z) };

			const int distance{ x_diff + y_diff + z_diff };

			if (distance > max_manhattan_distance)
			{
				max_manhattan_distance = distance;
			}
		}
	}

	std::cout << "max manhattan distance: " << max_manhattan_distance << '\n';
}

double day_19_2021__time()
{
	std::vector<day_19_2021__scanner> input{ day_19_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1; i++)
	{
		day_19_2021__execute__part1(input);
		day_19_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / (1 * 1000.0);
}

#pragma endregion Day 19

#pragma region Day 20

struct day_20_2021__data
{
	std::string image_enhancer{};
	std::vector<std::string> input_image{};

	int width{};
	int height{};
};

day_20_2021__data day_20_2021__read_input()
{
	std::fstream input{ read_input("../input/2021/day_20.txt") };

	day_20_2021__data data{};

	getline(input, data.image_enhancer);
	std::string line{};

	getline(input, line); // skip blank line
	getline(input, line); // first line of real data, used to size next lines

	data.width = (int)line.size();

	for (int i = 0; i < 1; i++)
	{
		data.input_image.push_back(std::string(line.size() + 2, '.'));
	}

	data.input_image.push_back("." + line + ".");

	while (getline(input, line))
	{
		data.input_image.push_back("." + line + ".");
		data.height++;
	}

	for (int i = 0; i < 1; i++)
	{
		data.input_image.push_back(std::string(line.size() + 2, '.'));
	}
	return data;
}

std::vector<std::string> day_20_2021__create_output_image(const day_20_2021__data& input)
{
	std::vector<std::string> output_image{};
	
	constexpr int EXTRA_PADDING_PER_ITERATION{ 1 };

	const std::string fill(input.input_image.at(0).size() + (EXTRA_PADDING_PER_ITERATION * 2), '.');// input.image_enhancer.at(0));

	for (size_t i = 0; i < input.input_image.size() + (EXTRA_PADDING_PER_ITERATION * 2); i++)
	{
		output_image.push_back(fill);
	}

	for (size_t y = 0; y < input.input_image.size(); y++)
	{
		const std::string& prev_line{ y < 1 ? input.input_image.at(y) : input.input_image.at(y - 1) };
		const std::string& curr_line{ input.input_image.at(y) };
		const std::string& next_line{ y >= input.input_image.size() - 1 ? input.input_image.at(y) : input.input_image.at(y + 1) };

		for (size_t x = 0; x < curr_line.size(); x++)
		{
			const bool top_left = prev_line.at(x == 0 ? x : x - 1) == '#';
			const bool top = prev_line.at(x) == '#';
			const bool top_right = prev_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';
			const bool left = curr_line.at(x == 0 ? x : x - 1) == '#';
			const bool center = curr_line.at(x) == '#';
			const bool right = curr_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';
			const bool bottom_left = next_line.at(x == 0 ? x : x - 1) == '#';
			const bool bottom = next_line.at(x) == '#';
			const bool bottom_right = next_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';

			const int top_binary{ ((top_left ? 1 : 0) << 8) | ((top ? 1 : 0) << 7) | ((top_right ? 1 : 0) << 6) };
			const int middle_binary{ ((left ? 1 : 0) << 5) | ((center ? 1 : 0) << 4) | ((right ? 1 : 0) << 3) };
			const int bottom_binary{ ((bottom_left ? 1 : 0) << 2) | ((bottom ? 1 : 0) << 1) | (bottom_right ? 1 : 0) };
		
			const int index{
				top_binary | middle_binary | bottom_binary
			};

			const char output{ input.image_enhancer.at(index) };

			output_image.at(y + EXTRA_PADDING_PER_ITERATION).at(x + EXTRA_PADDING_PER_ITERATION) = output;
		}
	}

	// fix the extra padding we added around the edge. it's infinite space and should match the layer inside of it
	const char fill_char{ output_image.at(1).at(1) };
	const size_t width{ output_image.at(0).size() };
	const size_t height{ output_image.size() };

	for (size_t x = 0; x < output_image.size(); x++)
	{
		output_image.at(0).at(x) = fill_char;
		output_image.at(height - 1).at(x) = fill_char;
	}

	for (size_t y = 0; y < output_image.size(); y++)
	{
		output_image.at(y).at(0) = fill_char;
		output_image.at(y).at(width - 1) = fill_char;
	}

	return output_image;
}

void day_20_2021__execute__part1(const day_20_2021__data& data)
{
	day_20_2021__data second{};
	second.image_enhancer = data.image_enhancer;
	second.input_image = day_20_2021__create_output_image(data);
	

	const std::vector<std::string> final_image{ day_20_2021__create_output_image(second) };

	int pixels_lit{};

	for (const auto& line : final_image)
	{
		for (const auto& pixel : line)
		{
			if (pixel == '#')
			{
				pixels_lit++;
			}
		}
	}
	_ASSERT(pixels_lit == 5218);
}

void day_20_2021__execute__part2(const day_20_2021__data& data)
{
	day_20_2021__data second{};
	second.image_enhancer = data.image_enhancer;
	second.input_image = data.input_image;


	for (int i = 0; i < 50; i++)
	{
		second.input_image = day_20_2021__create_output_image(second);
	}

	int pixels_lit{};

	for (const auto& line : second.input_image)
	{
		for (const auto& pixel : line)
		{
			if (pixel == '#')
			{
				pixels_lit++;
			}
		}
	}
	
	_ASSERT(pixels_lit == 15527);
}

execution_result day_20_2021__time()
{
	day_20_2021__data input{ day_20_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_20_2021__execute__part1(input);
		day_20_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { std::chrono::duration_cast<std::chrono::microseconds>(stop - start), EXECUTION_COUNT };
}

#pragma endregion Day 20

#pragma endregion Advent of Code - 2021

int main()
{
	std::cout << "            2015  2016  2017  2018  2019  2020  2021\n";

	std::array<std::array<execution_result, 25>, 7> times{};
	
	for (int i = 0; i < times.size(); i++)
	{
		for (int j = 0; j < times.at(i).size(); j++)
		{
			times.at(i).at(j).execution_count = 0;
		}
	}

	times.at(0).at(0) = day_1_2015__time();
	times.at(0).at(1) = day_2_2015__time();

	times.at(6).at(19) = day_20_2021__time();

	for (int i = 0; i < 25; i++)
	{
		std::cout << "day ";
		std::cout << std::setw(2) << (i + 1);
		std::cout << "      ";

		std::cout << std::setw(2);

		for (int j = 0; j < times.size(); j++)
		{
			
			if (times.at(j).at(i).execution_count > 0)
			{
				//printf("%llums  ", times.at(j).at(i));
				std::cout << times.at(j).at(i).display();
				
			}
			else
			{
				std::cout << "    ";
			}
			std::cout << "  ";
		}
		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << "total       ";
	std::cout << std::setw(2);

	execution_result all_time_total{};
	all_time_total.execution_count = 1;

	for (size_t i = 0; i < times.size(); i++)
	{
		execution_result year_total{};

		for (int day = 0; day < 25; day++)
		{
			if (times.at(i).at(day).execution_count > 0)
			{
				year_total.time += times.at(i).at(day).time_per_execution();
				all_time_total.time += times.at(i).at(day).time_per_execution();
				year_total.execution_count = 1;
			}
		}

		if (year_total.execution_count > 0)
		{
			std::cout << year_total.display();
		}
		else
		{
			std::cout << "    ";
		}
		std::cout << "  ";
	}
	std::cout << all_time_total.display();
	std::cout << '\n';

	return 0;
}
