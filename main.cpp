#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <string>
using namespace std;
double randomFactor()
{
random_device rd;
return generate_canonical<double, 10>(rd);
}

class ISensor
{
public:
	virtual double readSensor() = 0;
	virtual const char *getType() = 0;
};

class Temperature : public ISensor
{
	const double min = -40;
	const double max = 80;
	const double d = max - min;
	const char *type = "temperature";

	double generateTemperature()
	{
		return min + d * randomFactor();
	}

public:
	double readSensor()
	{
		return generateTemperature();
	}

	const char *getType()
	{
		return type;
	};
};

class Humidity : public ISensor
{
	const double min = 0;
	const double max = 100;
	const double d = max - min;
	const char *type = "humidity";

	double generateHumidity()
	{
		return min + d * randomFactor();
	}

public:
	double readSensor()
	{
		return generateHumidity();
	}

	const char *getType()
	{
		return type;
	};
};

class Pressure : public ISensor
{
	const double min = 300;
	const double max = 1100;
	const double d = max - min;
	const char *type = "pressure";

	double generatePressure()
	{
		return min + d * randomFactor();
	}

public:
	double readSensor()
	{
		return generatePressure();
	}

	const char *getType()
	{
		return type;
	};
};

class IRoom
{
public:
	virtual void createRoom() = 0;
	virtual void readRoom() = 0;
	virtual void updateRoom() = 0;
	virtual void deleteRoom() = 0;
};

using Sensors = vector<ISensor *>;

class Living : public IRoom
{
	Sensors sensors;
	string name;
	string filename;
	const std::string type = "living";

public:
	Living(const string &name, const Sensors &vec)
		: name(name), sensors(vec)
	{
		filename = "data/" + type + "-" + name + ".txt";
		sensors.push_back(new Temperature);
		sensors.push_back(new Humidity);
		sensors.push_back(new Pressure);
	}

	virtual void createRoom()
	{
		ofstream f(filename);
	}
	virtual void readRoom()
	{
		ifstream f(filename);

		cout << "\tRoom " << name << " which is a " << type << ":"
			<< endl;

		string sensorType;
		double value;
		while (f >> sensorType && f >> value)
		{
			cout << "\t\t" << sensorType << ": " << value << endl;
		}
	}
	virtual void updateRoom()
	{
		ofstream f(filename);
		for (auto sensor : sensors)
		{
			f << sensor->getType() << " " << sensor->readSensor() << endl;
		}
	}
	virtual void deleteRoom()
	{
		remove(filename.c_str());
	}
};

class Bedroom : public IRoom
{
	Sensors sensors;
	string name;
	string filename;
	const string type = "bedroom";

public:
	Bedroom(const string &name, const Sensors &vec)
		: name(name), sensors(vec)
	{
		filename = "data/" + type + "-" + name + ".txt";
		sensors.push_back(new Temperature);
		sensors.push_back(new Humidity);
		sensors.push_back(new Pressure);
	}

	virtual void createRoom()
	{
		ofstream f(filename);
	}
	virtual void readRoom()
	{
		ifstream f(filename);

		cout << "\tRoom " << name << " which is a " << type << ":"<< endl;

		string sensorType;
		double value;
		while (f >> sensorType && f >> value)
		{
			cout << "\t\t" << sensorType << ": " << value << endl;
		}
	}
	virtual void updateRoom()
	{
		ofstream f(filename);
		for (auto sensor : sensors)
		{
			f << sensor->getType() << " " << sensor->readSensor() << endl;
		}
	}
	virtual void deleteRoom()
	{
		remove(filename.c_str());
	}
};

class Bathroom : public IRoom
{
	Sensors sensors;
	string name;
	string filename;
	const string type = "bathroom";

public:
	Bathroom(const string &name, const Sensors &vec)
		: name(name), sensors(vec)
	{
		filename = "data/" + type + "-" + name + ".txt";
		sensors.push_back(new Temperature);
		sensors.push_back(new Humidity);
		sensors.push_back(new Pressure);
	}

	virtual void createRoom()
	{
		ofstream f(filename);
	}
	virtual void readRoom()
	{
		ifstream f(filename);

		cout<< "\tRoom " << name << " which is a " << type << ":"
			<< endl;

		string sensorType;
		double value;
		while (f >> sensorType && f >> value)
		{
			cout << "\t\t" << sensorType << ": " << value << endl;
		}
	}
	virtual void updateRoom()
	{
		ofstream f(filename);
		for (auto sensor : sensors)
		{
			f << sensor->getType() << " " << sensor->readSensor() << endl;
		}
	}
	virtual void deleteRoom()
	{
		remove(filename.c_str());
	}
};

class Kitchen : public IRoom
{
	Sensors sensors;
	string name;
	string filename;
	const string type = "kitchen";

public:
	Kitchen(const string &name, const Sensors &vec)
		: name(name), sensors(vec)
	{
		filename = "data/" + type + "-" + name + ".txt";
		sensors.push_back(new Temperature);
		sensors.push_back(new Humidity);
		sensors.push_back(new Pressure);
	}

	virtual void createRoom()
	{
		ofstream f(filename);
	}
	virtual void readRoom()
	{
		ifstream f(filename);

		cout << "\tRoom " << name << " which is a " << type << ":"
			<< endl;
		string sensorType;
		double value;
		while (f >> sensorType && f >> value)
		{
			cout << "\t\t" << sensorType << ": " << value << endl;
		}
	}
	virtual void updateRoom()
	{
		ofstream f(filename);
		for (auto sensor : sensors)
		{
			f << sensor->getType() << " " << sensor->readSensor() << endl;
		}
	}
	virtual void deleteRoom()
	{
		remove(filename.c_str());
	}
};

class House
{
	vector<IRoom *> rooms;

public:
	void addRoom(IRoom *room)
	{
		room->createRoom();
		rooms.push_back(room);
	}

	void removeRoom(size_t index)
	{
		rooms.at(index)->deleteRoom();
		rooms.erase(rooms.begin() + index);
	}
	void collectRoomData()
	{
		for (auto room : rooms)
		{
			room->updateRoom();
		}
	}
	void viewRoomData()
	{
		cout << "Displaying your house's rooms and their sensors data"
			<< endl;
		for (auto room : rooms)
		{
			room->readRoom();
		}
	}
};

int main()
{
	House h;
	h.addRoom(new Living("main",
		{ new Temperature, new Humidity, new Pressure }));

	h.addRoom(new Bedroom(
		"secondary", { new Temperature, new Humidity, new Pressure }));


	h.addRoom(new Bathroom("small",
		{ new Temperature, new Humidity, new Pressure}));

	h.addRoom(new Bathroom(
		"big", { new Temperature, new Humidity, new Pressure}));

	h.addRoom(new Kitchen(
		"big", { new Temperature, new Humidity, new Pressure }));

	h.addRoom(new Bedroom("first",
		{ new Temperature, new Humidity, new Pressure }));

	h.collectRoomData();

	h.viewRoomData();

	h.removeRoom(3);

	cout << "|||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||||||||||||||||||||||||||||||||||" << endl;
	cout << "    ||||    ||          ||       ||" << endl;
	cout << "    ||||     ||        ||        ||" << endl;
	cout << "    ||||      ||      ||         ||" << endl;
	cout << "    ||||       ||    ||          ||" << endl;
	cout << "    ||||        ||  ||           ||" << endl;
	cout << "    ||||	 ||||            ||" << endl;

	h.collectRoomData();
	h.viewRoomData();

	return 0;
}
