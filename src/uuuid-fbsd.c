#include <stdlib.h>
#include </usr/include/uuid.h>

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
	uint32_t st;

	u = uuuid_new();

	if (!u) {
		*status = UUUID_ERR;
		return;
	}

	if (nil)
		uuid_create_nil(&u->uuid, &st);
	else
		uuid_create(&u->uuid, &st);

	if (st != uuid_s_ok) {
		uuuid_free(u);
		*status = UUUID_ERR;
		return;
	}

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
	uint32_t st;
	int ret;

	ret = uuid_is_nil(&uuuid->uuid, &st);

	if (st != uuid_s_ok) {
		*status = UUUID_ERR;
		return -1;
	}

	*status = UUUID_OK;

	return ret;
}

int uuuid_compare(struct uuuid_t* u1, struct uuuid_t* u2, int* status)
{
	uint32_t st;
	int ret;

	ret = uuid_compare(&u1->uuid, &u2->uuid, &st);

	if (st != uuid_s_ok) {
		*status = UUUID_ERR;
		return -1;
	}

	*status = UUUID_OK;

	return ret;
}

void uuuid_to_string(struct uuuid_t* uuuid, char *str, size_t buffersize, int* status)
{
	uint32_t st;

	char** out;
	uuid_to_string(&uuuid->uuid, out, &st);

	if (st == uuid_s_ok)
	{
		int len = strlen(*out) + 1;
		if (buffersize >= len)
		{
			memcpy(str, o=*out, len);
			*status = UUUID_OK;
			return;
		}

		free(out);
	}

	// otherwise error
	*status = UUUID_ERR;
}

void uuuid_from_string(const char* in, struct uuuid_t** uuuid, int* status)
{
	uint32_t st;
	struct uuuid_t* u;

	u = uuuid_new();

	uuid_from_string(in, &u->uuid, &st);

	if (st != uuid_s_ok) {
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
