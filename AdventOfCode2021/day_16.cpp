#include "day_16.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>
#include <deque>
#include <set>





std::vector<uint8_t> read_day_16_input(std::fstream& input)
{
    std::string data{};
    input >> data;

    std::vector<uint8_t> bytes{};

    for (size_t i = 0; i < data.size() - 1; i += 2)
    {
        int high_nibble{ data.at(i) - 48 };
        int low_nibble{ data.at(i + 1) - 48 };

        if (high_nibble > 10)
        {
            high_nibble = data.at(i) - 55;
        }

        if (low_nibble > 10)
        {
            low_nibble = data.at(i + 1) - 55;
        }

        bytes.push_back((high_nibble << 4) | low_nibble);
    }
    return bytes;
}

void Day_16::run_part_1() const
{
    std::cout << "[Day 16] [Part 1]\n";

    std::fstream example_input{ read_input("day_16_example.txt") };
    std::fstream actual_input{ read_input("day_16_actual.txt") };

    std::cout << "Example: " << run_part_1(example_input) << '\n';
    std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
    std::cout << '\n';
}

std::string Day_16::run_part_1(std::fstream& input) const
{
    std::vector<uint8_t> bytes{ read_day_16_input(input) };

    buffer buf{ bytes };

    day_16_operator version_total = read_packet(buf);


    return std::to_string(version_total.version_total());
}

void Day_16::run_part_2() const
{
    std::cout << "[Day 16] [Part 2]\n";

    std::fstream example_input{ read_input("day_16_example.txt") };
    std::fstream actual_input{ read_input("day_16_actual.txt") };

    std::cout << "Example: " << run_part_2(example_input) << '\n';
    std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
    std::cout << '\n';
}

std::string Day_16::run_part_2(std::fstream& input) const
{
    std::vector<uint8_t> bytes{ read_day_16_input(input) };

    buffer buf{ bytes };

    auto packet = read_packet(buf);

    return std::to_string(packet.value());
}

day_16_operator Day_16::read_packet(buffer& buffer) const
{
    uint8_t packet_version{ buffer.read_and_advance<uint8_t>(3) };
    uint8_t packet_type_ID{ buffer.read_and_advance<uint8_t>(3) };

    int version_total{ packet_version };

    day_16_operator packet{};

    if (packet_type_ID == 4)
    {
        auto literal_packet = read_literal_value_packet(buffer, version_total);

        literal_packet.packet_version = packet_version;
        literal_packet.packet_type_id = packet_type_ID;
        packet.values.push_back(literal_packet);
    }
    else
    {
        auto op_pack = read_operator_packet(buffer, version_total);
        op_pack.packet_version = packet_version;
        op_pack.typeID = packet_type_ID;

        packet.operators.push_back(op_pack);

        return op_pack;
    }
    return packet;
}

day_16_literal_value Day_16::read_literal_value_packet(buffer& buffer, int& version_total) const
{
    day_16_literal_value value{};

    bool loop{};
    int loops{};

    do
    {
        loops++;
        _ASSERT(loops <= 16);

        loop = buffer.read_and_advance<uint8_t>(1) != 0;

        value.value <<= (uint64_t)4;
        value.value |= static_cast<uint64_t>(buffer.read_and_advance<uint8_t>(4) & 0xFF);
    } while (loop);

    return value;
}

day_16_operator Day_16::read_operator_packet(buffer& buffer, int& version_total) const
{
    day_16_operator value{};

    uint8_t length_type_id{ buffer.read_and_advance<uint8_t>(1) };

    if (length_type_id == 1)
    {
        // 11-bit number representing the number of sub-packets
        uint16_t number_of_sub_packets{ buffer.read_and_advance<uint16_t>(11) };

        for (unsigned int i = 0; i < number_of_sub_packets; i++)
        {
            uint8_t typeID{ buffer.read<uint8_t>(6) };

            if ((typeID & 0x7) == 4) {
                uint8_t packet_version{ buffer.read_and_advance<uint8_t>(3) };
                uint8_t packet_type_ID{ buffer.read_and_advance<uint8_t>(3) };
                auto literal_packet = read_literal_value_packet(buffer, version_total);

                literal_packet.packet_version = packet_version;
                literal_packet.packet_type_id = packet_type_ID;
                value.values.push_back(literal_packet);
            }
            else {
                value.operators.push_back(read_packet(buffer));
            }
        }
    }
    else if (length_type_id == 0)
    {
        // 15-bit
        uint16_t bits_in_sub_packet{ buffer.read_and_advance<uint16_t>(15) };

        _ASSERT(bits_in_sub_packet > 0);

        int start_offset{ (buffer.byte_offset * 8) + buffer.bit_offset };

        bool cont{};

        do
        {
            uint8_t typeID{ buffer.read<uint8_t>(6) };

            if ((typeID & 0x7) == 4) {
                uint8_t packet_version{ buffer.read_and_advance<uint8_t>(3) };
                uint8_t packet_type_ID{ buffer.read_and_advance<uint8_t>(3) };
                auto literal_packet = read_literal_value_packet(buffer, version_total);

                literal_packet.packet_version = packet_version;
                literal_packet.packet_type_id = packet_type_ID;
                value.values.push_back(literal_packet);
            }
            else {
                value.operators.push_back(read_packet(buffer));
            }
            const int new_offset{ (buffer.byte_offset * 8) + buffer.bit_offset };

            cont = new_offset - start_offset < bits_in_sub_packet;

            if (!cont)
            {
                _ASSERT(new_offset - start_offset == bits_in_sub_packet);
            }
        } while (cont);
    }

    return value;
}
