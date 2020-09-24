#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    // main param
    //*******************************************************
    struct option long_options[] = {
        {"config_file", required_argument, NULL, 'c'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
    };

    int opt, option_index;
	while( (opt = getopt_long(argc, argv, "c:h:j", long_options, &option_index)) != -1) {
		switch(opt) {
		case 'c':
			puts(optarg);// ./stOption -c <file name>
			break;
		case 'h':
			printf("./stOption -c <file name>\n");
			printf("ps:./stOption -c visual-ai.yaml\n");
			return 0;
        case 'j':// information -> not register
            printf("1111\n");
            break;
		}
	}

	return 0;
}