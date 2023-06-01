#pragma once
#ifndef clientFunc
#define clientFunc
#include "projectGroceryHead.h"

struct client* createClient();
void freeClient(struct client* client);
void freeList(struct list* List);
#endif // !1


