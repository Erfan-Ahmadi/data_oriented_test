#include <iostream>
#include <chrono>
#include <vector>
#include <string>

static constexpr int count = 1'000'000;
static constexpr int num_runs = 20;

struct value
{
	std::string name;
	float color[4];
	float position[3];
	float velocity[3];
};

inline float rand_float()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

inline value rand_value()
{
	value v;
	v.name = "fdfdsdfdsf";

	v.color[0] = rand_float();
	v.color[1] = rand_float();
	v.color[2] = rand_float();
	v.color[3] = rand_float();

	v.position[0] = rand_float();
	v.position[1] = rand_float();
	v.position[2] = rand_float();

	v.velocity[0] = rand_float();
	v.velocity[1] = rand_float();
	v.velocity[2] = rand_float();

	return v;
}

struct dictionary
{
	std::vector<std::string> keys;
	std::vector<value> values;

	value find_value(const std::string& key)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				return values[i];
			}
		}
	}
};

int main()
{
	srand(time(NULL));

	dictionary d;
	d.keys = std::vector<std::string>(count);
	d.values = std::vector<value>(count);

	for (int i = 0; i < count; i++)
	{
		d.values[i] = rand_value();
	}

	value obj;
	obj.name = "hi";
	d.keys[count - 1] = "hello";
	d.values[count - 1] = obj;

	double total_time = 0;

	for (int i = 0; i < num_runs; i++)
	{
		const auto _start_time = std::chrono::high_resolution_clock::now();
		{
			d.find_value("hello");
		}
		const auto _end_time = std::chrono::high_resolution_clock::now();

		total_time += std::chrono::duration_cast<std::chrono::milliseconds>(_end_time - _start_time).count();
	}

	const auto average_time = total_time / static_cast<double>(num_runs);

	std::cout << "Average Time Consumed For One Update = " << average_time << "(ms)" << std::endl;

	system("pause");
}
