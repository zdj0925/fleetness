
/*
 * rpcfunc.h
 *
 *  Created on: Oct 11, 2024
 *      Author: zhaodj
 */

#ifndef RPCFUNC_H_
#define RPCFUNC_H_

#include "cJSON.h"
#include <ev.h>
cJSON *say_hello (jrpc_context * ctx, cJSON * params, cJSON * id);
cJSON *add (jrpc_context * ctx, cJSON * params, cJSON * id);
cJSON *notify (jrpc_context * ctx, cJSON * param, cJSON * id);
#endif
