
/*
 * rpcfunc.c
 *
 *  Created on: Oct 9, 2025
 *      Author: zhaodj
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "jsonrpc-c.h"

#define PORT 1234                      // the port users will be connecting to

//struct jrpc_server my_server;

cJSON *say_hello (jrpc_context * ctx, cJSON * params, cJSON * id)
{
    cJSON *returned = NULL;
    if (id == NULL)
    {
        return cJSON_CreateString ("Hello, i`m fleetness!");
    }
    printf ("id: %s\n", id->valuestring);
    for (int i = 0; i < cJSON_GetArraySize (params); i++)
    {
        switch (cJSON_GetArrayItem (params, i)->type)
        {
            case cJSON_String:
                printf ("params[%d]: %s\n", i, cJSON_GetArrayItem (params, i)->valuestring);
                break;
            case cJSON_Number:
                printf ("params[%d]: %d\n", i, cJSON_GetArrayItem (params, i)->valueint);
                break;
            case cJSON_Object:
                printf ("params[%d]: %s\n", i, cJSON_GetArrayItem (params, i)->valuestring);
                break;
            default:
                break;
        }
        printf ("params[%d]: %s\n", i, cJSON_GetArrayItem (params, i)->valuestring);
    }

    //create a new json object
    returned = cJSON_CreateObject ();

    cJSON_AddStringToObject (returned, "id", "12345");
    cJSON_AddStringToObject (returned, "method", "say_hello");
    cJSON_AddStringToObject (returned, "message", "HI, I`m fleetness!");
    cJSON_AddNumberToObject (returned, "code", 200);
    cJSON_AddTrueToObject (returned, "success");
    cJSON_AddNumberToObject (returned, "salt", rand () % 10000);
    return returned;
}

cJSON *add (jrpc_context * ctx, cJSON * params, cJSON * id)
{
    int i = 0;
    long int sum = 0;
    for (i = 0; i < cJSON_GetArraySize (params); i++) 
    {
        sum += cJSON_GetArrayItem (params, i)->valueint;
    }

    return cJSON_CreateNumber (sum);
}

cJSON *notify (jrpc_context * ctx, cJSON * param, cJSON * id)
{
    return NULL;
}

/////file end/////
