#pragma once

#include "day.h"

#include <vector>

struct day_16_literal_value
{
    unsigned char packet_version{};
    unsigned char packet_type_id{};

    uint64_t value{};
};

struct day_16_operator
{
    int packet_version{};
    int typeID{-1};

    std::vector<day_16_operator> operators{};
    std::vector<day_16_literal_value> values{};

    int version_total()
    {
        int total{ packet_version };

        for (auto& v : operators)
        {
            total += v.version_total();
        }
        for (auto& v : values)
        {
            total += v.packet_version;
        }
        return total;
    }
    uint64_t value()
    {
        uint64_t val{};

        std::vector<uint64_t> sub_values{};

        char ch{};
        switch (typeID)
        {
        case 0:
            ch = '+';
            printf("(");
            break;
        case 1:
            ch = '*';
        }

        //for (auto& v : values)
        for (int i = 0; i < values.size(); i++)
        {
            if (i > 0)
            {
                printf(" %c ", ch);
            }
            printf("%I64d", values.at(i).value);
            auto& v = values.at(i);

            sub_values.push_back(v.value);
        }

        for (auto& v : operators)
        {
            auto va = v.value();
            sub_values.push_back(va);
        }

        switch (typeID)
        {
        case 0:
        case 1:
            printf(")");
            break;

        }
        _ASSERT(sub_values.size() > 0);

        switch (typeID)
        {
        case 0: // sum
            for (auto v : sub_values)
            {
                val += v;
            }
            break;
        case 1: // product
            val = sub_values.at(0);

            for (int i = 1; i < sub_values.size(); i++)
            {
                val *= sub_values.at(i);
            }
            break;
        case 2: // min
            val = sub_values.at(0);

            for (size_t i = 1; i < sub_values.size(); i++)
            {
                if (sub_values.at(i) < val) val = sub_values.at(i);
            }
            break;
        case 3: // max
            val = sub_values.at(0);

            for (size_t i = 1; i < sub_values.size(); i++)
            {
                if (sub_values.at(i) > val) val = sub_values.at(i);
            }
            break;
        case 5: // greater than
            _ASSERT(sub_values.size() == 2);
            return sub_values.at(0) > sub_values.at(1) ? 1 : 0;
        case 6: // less than
            _ASSERT(sub_values.size() == 2);
            return sub_values.at(0) < sub_values.at(1) ? 1 : 0;
        case 7: // equal to
            _ASSERT(sub_values.size() == 2);
            return sub_values.at(0) == sub_values.at(1) ? 1 : 0;
        }

        return val;
    }
};

struct buffer
{
    std::vector<uint8_t> values{};
    //uint8_t* start{};

    //size_t length{};

    int32_t byte_offset{};
    int32_t bit_offset{};

    buffer(std::vector<uint8_t>& data)
        : values(data)
    {
    }

    template<typename T>
    T read(size_t bit_length = sizeof(T) * 8) const
    {
        int32_t shift_amount{ bit_offset + (int8_t)bit_length };

        if (sizeof(T) == 1 && (sizeof(T) * 8) - bit_offset >= bit_length)
        {
            //shift_amount -= sizeof(T) * 8;
            shift_amount = (sizeof(T) * 8) - bit_offset - bit_length;
        }

        const int32_t byte_off{ byte_offset + (shift_amount / 8) };

        if (shift_amount >= 8)
        {
            shift_amount = 8 - (shift_amount % 8);
        }

        const size_t shift{ (size_t)shift_amount };// (1 << shift_amount) - 1 };

        const int mask{ ((1 << bit_length) - 1) << shift };

        //auto* ptr = values.data() + byte_offset;// +byte_off;// -sizeof(T);
        /*T val{};
        memcpy(&val, ptr, sizeof(T));*/

        uint64_t val{};

        int val_shift = 0;
        for (int i = byte_off; i >= 0 && i >= byte_offset && i < values.size(); i--)
        {
            uint8_t b = values.at(i);
            val |= b << val_shift;
            val_shift += 8;
        }
        uint64_t value{ val & mask };

        value >>= shift;

        return value;
    }

    template<typename T>
    T read_and_advance(size_t bit_length = sizeof(T) * 8)
    {
        T value{ read<T>(bit_length) };

        bit_offset += bit_length;

        byte_offset += bit_offset / 8;
        bit_offset %= 8;

        return value;
    }
};

class Day_16 : public Day
{
public:
	void run_part_1() const override;
	std::string run_part_1(std::fstream& input) const;

	void run_part_2() const override;
	std::string run_part_2(std::fstream& input) const;

    day_16_operator read_packet(buffer& buffer) const;
    day_16_literal_value read_literal_value_packet(buffer& buffer, int& version_total) const;
	day_16_operator read_operator_packet(buffer& buffer, int& version_total) const;
};
