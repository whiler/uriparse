#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uriparse.h"

int usage(const char *name) {
	printf("usage %s -f fields [-d delimiter] url [url ...]\n", name);
	printf("      %s -h\n\n", name);
	printf("available fields:\n");
	printf("    s = scheme\n");
	printf("    u = user\n");
	printf("    w = password\n");
	printf("    h = host\n");
	printf("    p = port\n");
	printf("    t = path\n");
	printf("    q = query\n");
	printf("    f = fragment\n");
	return EXIT_SUCCESS;
}

int main(int argc, char * const argv[]) {
	char fields[9] = {0};
	char delimiter = '\t';
	char cur = 0;
	int help = 0;
	int ch = 0;
	int i = 0;
	int l = 0;
	int j = 0;
	struct uri uri = {0};
	int rc = 0;

	while (-1 != (ch = getopt(argc, argv, "d:f:h"))) {
		switch (ch) {
			case 'd':
				delimiter = *optarg;
				break;

			case 'f':
				while (0 != (cur = *optarg) && i < 8) {
					switch(cur) {
						case 's': case 'u': case 'w': case 'h': case 'p': case 't': case 'q': case 'f':
							fields[i++] = cur;
							break;

						default:
							break;
					}
					optarg++;
				}
				break;

			case 'h':
				help = 1;
				break;

			default:
				break;
		}
	}

	if (1 == help || 0 == i || 0 == argc - optind) {
		return usage(argv[0]);
	}

	l = i;
	for (i = optind; i < argc; i++) {
		uri.scheme = uri.user = uri.passwd = uri.host = uri.port = uri.path = uri.query = uri.fragment = NULL;
		if (0 != (rc = uriparse(argv[i], &uri))) {
			break;
		}
		for (j = 0; j < l; j++) {
			switch(fields[j]) {
				case 's':
					printf("%s%c", uri.scheme, delimiter);
					break;

				case 'u':
					printf("%s%c", uri.user, delimiter);
					break;

				case 'w':
					printf("%s%c", uri.passwd, delimiter);
					break;

				case 'h':
					printf("%s%c", uri.host, delimiter);
					break;

				case 'p':
					printf("%s%c", uri.port, delimiter);
					break;

				case 't':
					printf("%s%c", uri.path, delimiter);
					break;

				case 'q':
					printf("%s%c", uri.query, delimiter);
					break;

				case 'f':
					printf("%s%c", uri.fragment, delimiter);
					break;

				default:
					break;
			}
		}
		printf("\n");
	}

	return rc;
}
