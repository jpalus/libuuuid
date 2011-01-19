#include <stdlib.h>
#include <uuid/uuid.h>

#include "uuuid.h"

struct uuuid_t {
	uuid_t uuid;
};

static struct uuuid_t* uuuid_new(void)
{
	return (struct uuuid_t*) malloc(sizeof(struct uuuid_t));
}

static void _uuuid_create(struct uuuid_t** uuuid, int* status, int nil)
{
	struct uuuid_t* u;

	u = uuuid_new();

	if (!u) {
		*status = UUUID_ERR;
		return;
	}

	if (nil)
		uuid_clear(u->uuid);
	else
		uuid_generate(u->uuid);

	*uuuid = u;
	*status = UUUID_OK;
}

void uuuid_create(struct uuuid_t** uuuid, int* status)
{
	_uuuid_create(uuuid, status, 0);
}

void uuuid_create_nil(struct uuuid_t** uuuid, int* status)
{
	_uuuid_create(uuuid, status, 1);
}

int uuuid_is_nil(struct uuuid_t* uuuid, int* status)
{
	*status = UUUID_OK;
	return uuid_is_null(uuuid->uuid);
}

int uuuid_compare(struct uuuid_t* u1, struct uuuid_t* u2, int* status)
{
	*status = UUUID_OK;
	return uuid_compare(u1->uuid, u2->uuid);
}

void uuuid_to_string(struct uuuid_t* uuuid, char** out, int* status)
{
	*out = malloc(sizeof(char) * 37);
	uuid_unparse(uuuid->uuid, *out);
	*status = UUUID_OK;
}

void uuuid_from_string(const char* in, struct uuuid_t** uuuid, int* status)
{
	int st;
	struct uuuid_t* u;

	u = uuuid_new();

	st = uuid_parse(in, u->uuid);

	if (st != 0) {
		uuuid_free(u);
		*status = UUUID_ERR;
		return;
	}

	*uuuid = u;
	*status = UUUID_OK;
}

void uuuid_free(struct uuuid_t* uuuid)
{
	free(uuuid);
}
