#pragma once
#ifndef Client
#define Client
#include "projectGroceryHead.h"

struct client* createClient();
void freeClient(struct client* Client);
void freeList(struct list* List);
#endif // !1


