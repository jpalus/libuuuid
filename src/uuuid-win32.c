#include <stdlib.h>
#include <windows.h>

#include "uuuid.h"

struct uuuid_t {
	UUID uuid;
};

static struct uuuid_t* uuuid_new(void)
{
	return (struct uuuid_t*) malloc(sizeof(struct uuuid_t));
}

static void _uuuid_create(struct uuuid_t** uuuid, int* status, int nil)
{
	struct uuuid_t* u;
	RPC_STATUS st;

	u = uuuid_new();

	if (!u) {
		*status = UUUID_ERR;
		return;
	}

	if (nil)
		st = UuidCreateNil(&u->uuid);
	else
		st = UuidCreate(&u->uuid);

	if (st != RPC_S_OK) {
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
	RPC_STATUS st;
	int ret;

	ret = UuidIsNil(&uuuid->uuid, &st);

	if (st != RPC_S_OK) {
		*status = UUUID_ERR;
		return -1;
	}

	*status = UUUID_OK;

	return ret;
}

int uuuid_compare(struct uuuid_t* u1, struct uuuid_t* u2, int* status)
{
	RPC_STATUS st;
	int ret;

	ret = UuidCompare(&u1->uuid, &u2->uuid, &st);

	if (st != RPC_S_OK) {
		*status = UUUID_ERR;
		return -1;
	}

	*status = UUUID_OK;

	return ret;
}

void uuuid_to_string(struct uuuid_t* uuuid, char *str, size_t buffersize, int* status)
{
	RPC_STATUS st;

	RPC_CSTR rpcStringBuffer;
	st = UuidToStringA(&uuuid->uuid, &rpcStringBuffer);

	if (st == RPC_S_OK)
	{
		// we could make the assumption that the string is always in the 
		// expected size (36) if the call to UuidToStringA is correctly completed
		size_t strlength = strlen((const char *)rpcStringBuffer) + 1;
		if (buffersize >= strlength)
		{
			memcpy(str, rpcStringBuffer, strlength);
			*status = UUUID_OK;
		}
		else
			*status = UUUID_ERR;

		RpcStringFreeA(&rpcStringBuffer);
	}
	else
		*status = UUUID_ERR;
}

void uuuid_from_string(const char* in, struct uuuid_t** uuuid, int* status)
{
	RPC_STATUS st;
	struct uuuid_t* u;

	u = uuuid_new();

	st = UuidFromStringA((unsigned char*) in, &u->uuid);

	if (st != RPC_S_OK) {
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
