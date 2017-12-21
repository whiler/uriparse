/*
 * filename: uriparse.c
 *
 * design ref: urlparse.urlparse from Python
 *
 * description:
 *     parse uri fields
 *
 * public functions:
 *     int uriparse(const char *src, struct uri *uri)
 *
 * notes:
 *     syntax
 *     scheme:[//[user[:password]@]host[:port]][/path][?query][#fragment]
 *
 * author: whiler wenwu500@qq.com
 * start date: 2017-05-19
 *
 * license: MIT
 *
 */

#include <stdlib.h>

#include "uriparse.h"


int uriparse(const char *src, struct uri *uri) {
    int rc = EXIT_SUCCESS;
    int i = 0, state = 0, offset = 0, length = 0, ipv6 = 0;
    char cur = src[0];
    uri->scheme = uri->buf;
    while (i + offset < URI_MAX + 1 && cur && !rc) {
        length += 1;
        switch (state) {
            case 0:
                if (':' == cur) {
                    cur = 0;
                    length = 0;
                    state = 1;
                }
                break;
            case 1:
                if (1 == length) {
                    if ('?' == cur) {
                        state = 6;
                        continue;
                    } else if ('#' == cur) {
                        state = 7;
                        continue;
                    } else if ('/' != cur) {
                        rc = EXIT_FAILURE;
                    }
                } else if (2 == length) {
                    if ('/' != cur) {
                        uri->path = &uri->buf[i + offset - 1];
                        state = 6;
                        continue;
                    }
                } else if (3 == length) {
                    if ('/' == cur) {
                        length = 0;
                        state = 5;
                        continue;
                    } else if ('[' == cur) {
                        length = 0;
                        state = 4;
                        uri->host = &uri->buf[i + offset];
                        continue;
                    } else {
                        length = 0;
                        state = 2;
                        uri->user = &uri->buf[i + offset];
                    }
                }
                break;
            case 2:
                if (':' == cur) {
                    cur = 0;
                    length = 0;
                    state = 3;
                    uri->passwd = &uri->buf[i + offset + 1];
                } else if ('@' == cur) {
                    state = 3;
                    continue;
                } else if ('/' == cur) {
                    state = 5;
                    continue;
                } else if ('?' == cur) {
                    state = 6;
                    continue;
                } else if ('#' == cur) {
                    state = 7;
                    continue;
                }
                break;
            case 3:
                if ('@' == cur) {
                    cur = 0;
                    length = 0;
                    state = 4;
                    uri->host = &uri->buf[i + offset + 1];
                } else if ('/' == cur) {
                    uri->host = uri->user;
                    uri->user = NULL;
                    uri->port = uri->passwd;
                    uri->passwd = NULL;
                    state = 5;
                    continue;
                } else if ('?' == cur) {
                    state = 6;
                    continue;
                } else if ('#' == cur) {
                    state = 7;
                    continue;
                }
                break;
            case 4:
                if (1 == length && '[' == cur) {
                    ipv6 = 1;
                } else if (ipv6 && 3 < length && ']' == cur) {
                    ipv6 = 0;
                }
                if (!ipv6 && ':' == cur) {
                    cur = 0;
                    length = 0;
                    state = 5;
                    uri->port = &uri->buf[i + offset + 1];
                } else if ('/' == cur) {
                    state = 5;
                    continue;
                } else if ('?' == cur) {
                    state = 6;
                    continue;
                } else if ('#' == cur) {
                    state = 7;
                    continue;
                }
                break;
            case 5:
                if ('/' == cur) {
                    uri->buf[i + offset] = 0;
                    offset += 1;
                    length = 1;
                    state = 6;
                    uri->path = &uri->buf[i + offset];
                } else if ('?' == cur) {
                    state = 6;
                    continue;
                } else if ('#' == cur) {
                    state = 7;
                    continue;
                }
                break;
            case 6:
                if ('?' == cur) {
                    cur = 0;
                    length = 0;
                    state = 7;
                    uri->query = &uri->buf[i + offset + 1];
                } else if ('#' == cur) {
                    state = 7;
                    continue;
                }
                break;
            case 7:
                if ('#' == cur) {
                    cur = 0;
                    length = 0;
                    state = 8;
                    uri->fragment = &uri->buf[i + offset + 1];
                }
            default:
                break;
        }
        uri->buf[i + offset] = cur;
        i += 1;
        cur = src[i];
    }
    if (!uri->host && uri->user) {
        uri->host = uri->user;
        uri->user = NULL;
        if (!uri->port && uri->passwd) {
            uri->port = uri->passwd;
            uri->passwd = NULL;
        }
    }
    return rc;
}
