#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

// ./gflags_test -help
//    1          2       3
// FLAGS_gray  默认值   帮助信息
DEFINE_bool(gray, false, "When this option is on, treat images as grayscale ones");
DEFINE_int32(resize_width, 0, "Width images are resized to");
DEFINE_int64(resize_height, 0, "Height images are resized to");
DEFINE_string(encode_type, "222", "Optional: What type should we encode the image as ('png','jpg',...).");

// 在另一文件使用，澄清
// DECLARE_string(encode_type);

// ./gflags_test -encode_type=123456 传参
int main(int argc, char const *argv[])
{
    // 初始化日志库
    ::google::InitGoogleLogging(argv[0]);

    // 输出到文件
    FLAGS_logtostderr = 0;  //是否打印到控制台
    FLAGS_alsologtostderr = 0;  //打印到日志同时是否打印到控制台
    ::google::SetLogDestination(google::GLOG_INFO, "log-");// 输出到文件

    //下面设置帮助信息
    // bool类型特殊
    ::google::SetUsageMessage("gray --encode_type=yuv --resize_width=200 --resize_height=200 ...\n");

    //解析命令行参数，参数true时，解析完参数后argc=1，argv只保留了argv[0]
    //参数flase时，解析完参数后argc个数不变，argv顺序会变化
    ::google::ParseCommandLineFlags(&argc, const_cast<char ***>(&argv), true);

    // if (argc < 4) { //如果参数个数小于指定值，显示帮助信息
    //     ::google::ShowUsageWithFlagsRestrict(argv[0], "tools/convert_imageset");
    //     return 1;
    // }

    //参数的使用
    const bool is_gray = FLAGS_gray;
    const int32_t resize_width = FLAGS_resize_width;
    const int64_t resize_height = FLAGS_resize_height;
    const std::string encode_type = FLAGS_encode_type;

    LOG(ERROR) << is_gray << ":" << resize_width << ":" << resize_height << ":" << encode_type;

    LOG(INFO) << "Hello, World!";

    

    return 0;
}
