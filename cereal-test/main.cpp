#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

struct Test
{
	unsigned int id_;
	std::string name_;
	
	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(id_, name_);
	}
};

int main()
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive out(os);

	Test outData;
	outData.id_ = 5;
	outData.name_ = "test";
	out(outData);

	os.close();

	std::ifstream is("out.cereal", std::ios::binary);
	Test myData2;

	cereal::BinaryInputArchive in(is);
	in(myData2);

	std::cout << myData2.id_ << std::endl;
	std::cout << myData2.name_.c_str() << std::endl;

	is.close();

	rewind(stdin);
	getchar();

	return 0;
}