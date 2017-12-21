/*
 * filename: uriparse.h
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

#ifndef _URIPARSE_
#define _URIPARSE_

#define URI_MAX 2083

struct uri {
    char *scheme;
    char *user;
    char *passwd;
    char *host;
    char *port;
    char *path;
    char *query;
    char *fragment;
    char buf[URI_MAX + 1 + 1];
};

int uriparse(const char *src, struct uri *uri);

#endif
