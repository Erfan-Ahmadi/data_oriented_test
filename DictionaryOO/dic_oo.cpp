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

struct key_value
{
	std::string key;
	value value;
};

struct dictionary
{
	std::vector<key_value> dic;

	value find_value(const std::string& key)
	{
		for (int i = 0; i < dic.size(); i++)
		{
			if (dic[i].key == key)
			{
				return dic[i].value;
			}
		}
	}
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

int main()
{
	srand(time(NULL));

	dictionary d;
	d.dic = std::vector<key_value>(count);

	value obj;
	obj.name = "hi";

	for (int i = 0; i < count; i++)
	{
		d.dic[i] = { "asas", rand_value() };
	}

	d.dic[count - 1] = { "hello", obj };

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
