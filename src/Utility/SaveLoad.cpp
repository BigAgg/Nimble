#include "SaveLoad.hpp"


void DeleteObject(std::unique_ptr<GameObject> &toErase, std::vector<std::unique_ptr<GameObject>> &objects) 
{
	std::erase(objects, toErase);
	toErase.release();
}

void DeleteObjects(std::vector<std::unique_ptr<GameObject>> &objs, std::vector<std::unique_ptr<GameObject>> &objects) 
{
	for (auto &&toErase : objs) 
	{
		DeleteObject(toErase, objects);
	}
}

bool SaveObjects(std::string path, std::string filename, std::vector<std::unique_ptr<GameObject>> &list)
{
	if (list.size() == 0)
		return false;

	using namespace std;
	namespace fs = filesystem;

	fs::create_directories(path);

	ofstream file;

	file.open(path + filename, ios::binary);
	for (auto &&obj : list)
	{
		if (file.is_open() && file.good())
		{
			std::string strtype = "";
			char type[30];
			type[0] = '\0';
			strncpy_s(type, obj->type.c_str(), sizeof(type));
			strtype = type;

			if (obj->type == "GameObject")
			{
				file.write((char*)&type, sizeof(type));
				file.write((char*)obj.get(), sizeof(GameObject));
			}
			// TODO: Add all types when created
			else {
				printf("Unkown format: %s\n", strtype.c_str());
				continue;
			}
		}
	}
	return true;
}

bool LoadObjects(std::string path, std::string filename, std::vector<std::unique_ptr<GameObject>> &list)
{
	using namespace std;
	namespace fs = filesystem;

	if (!fs::exists(path + filename))
		return false;

	list.clear();

	ifstream file;

	file.open(path + filename, ios::binary);

	while (file.is_open() && file.good() && !file.eof())
	{
		std::string strtype = "";
		char type[30];
		type[0] = '\0';
		file.read((char*)&type, sizeof(type));
		strtype = type;
		uint16_t tid[3] = { 0,0,0 };
		GameObject* obj = new GameObject({ 0,0 }, {0,0,0,0}, { 0,0,0,0 }, 0, tid);
		if (strtype == "GameObject")
		{
			file.read((char*)obj, sizeof(GameObject));
		}
		// @TODO: Add all types when created
		else
		{
			printf("Unkown format: %s\n", strtype.c_str());
			continue;
		}
		list.emplace_back(obj);
	}
	list.pop_back();
	std::sort(objects.begin(), objects.end(), less_than_key());
	return true;
}