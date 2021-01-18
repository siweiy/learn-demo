#include <iostream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void read_pic(const char *path, std::vector<std::string> &v) {
    DIR *dir = opendir(path);
    if (dir == nullptr) {
        std::cout << "opendir error" << std::endl;
        exit(1);
    }

    std::string dst_path = path;
    dst_path += '/';
    struct dirent *s_info;
    while ((s_info = readdir(dir)) != nullptr) {

        if (s_info->d_type == DT_DIR) {
            if (strcmp(s_info->d_name, ".") == 0 ||
                strcmp(s_info->d_name, "..") == 0) {
                    continue;
            }
            dst_path += s_info->d_name;
            read_pic(dst_path.c_str(), v);
        }
        
        if (s_info->d_type == DT_REG){
            v.push_back(std::move(dst_path+s_info->d_name));
        }
    }

    closedir(dir);
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        return 0;
    }

    clock_t start, end;
    start = clock();

    std::vector<std::string> v;
    read_pic(argv[1], v);

    end = clock();
    std::cout << (end-start) << std::endl;

    for (auto str: v) {
        std::cout << str << std::endl;
    }

    return 0;
}
