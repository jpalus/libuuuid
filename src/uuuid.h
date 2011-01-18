#ifndef UUUID_H
#define UUUID_H

#ifdef UUUID_EXPORT
#ifdef WIN32
#define UUUID_EXPORT __declspec(dllexport)
#endif
#else
#define UUUID_EXPORT
#endif

#define UUUID_OK	0
#define UUUID_ERR	-1

struct uuuid_t;

#ifdef __cplusplus
extern "C" {
#endif

UUUID_EXPORT void uuuid_create(struct uuuid_t**, int*);
UUUID_EXPORT void uuuid_create_nil(struct uuuid_t**, int*);
UUUID_EXPORT int uuuid_is_nil(struct uuuid_t*, int*);
UUUID_EXPORT int uuuid_compare(struct uuuid_t*, struct uuuid_t*, int*);
UUUID_EXPORT void uuuid_to_string(struct uuuid_t*, char**, int*);
UUUID_EXPORT void uuuid_from_string(const char*, struct uuuid_t**, int*);
UUUID_EXPORT void uuuid_free(struct uuuid_t*);

#ifdef __cplusplus
}
#endif

#endif
