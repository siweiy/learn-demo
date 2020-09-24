#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	const std::string path{ "./" };
	const std::vector<std::string> files {"test", "Makefile", "thread.cpp", "thread.cpp"};

	for (auto& name : files) {
		const std::string tmp = path + name;
		fprintf(stdout, "file or directory name: \"%s\": ", name.c_str());
		if (access(tmp.c_str(), 0) == 0) fprintf(stdout, "exist, ");
		else fprintf(stdout, "not exist, ");
		
		if (access(tmp.c_str(), 4) == 0) fprintf(stdout, "has read premission, ");
		else fprintf(stdout, "does not have read premission, ");

		if (access(tmp.c_str(), 2) == 0) fprintf(stdout, "has  write premission, ");
		else fprintf(stdout, "does not have write premission, ");

		if (access(tmp.c_str(), 6) == 0) fprintf(stdout, "has both read and write premission\n");
		else fprintf(stdout, "has neither read nor write premission\n");
	}

	return 0;
}
