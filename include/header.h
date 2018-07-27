#ifndef _head__
#define _head__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "jsmn.h"



typedef int8_t			Bool8;
typedef int32_t			Bool32;
typedef uint8_t			UInt8;
typedef unsigned short	UInt16;
typedef uint32_t 		UInt32;
typedef signed short	Int16;
typedef int32_t			Int32;
typedef signed long		Int64;
typedef float 			Float32;
typedef double 			Double64;

#define CARTO_NODE_NBR	653
#define MAX_NODE_ARCS 4

#define stBeacons	   "Beacons"
    #define stBeaconid      "Beaconid"
    #define stBeaconx		"Beaconx"
    #define stBeacony	    "Beacony"
    #define stBeaconz	    "Beaconz"
#define stConstants	        "Constants"
    #define stvdef "VDEF"
    #define stadef "ADEF"
    #define stv1 "V1"
    #define stv2 "V2"
#define stConstraints       "Constraints"
    #define stCid     "Cid"
    #define stCvalue  "Cvalue"
    #define stCname   "Cname"
    #define stCtype   "Ctype"
    #define stCx      "Cx"
    #define stCy      "Cy"
    #define stCz      "Cz"
#define stWaypoints	   "Waypoints"
    #define stwpid          "wpid"
    #define stwptype        "wptype"
    #define stwpx           "wpx"
    #define stwpy           "wpy"
    #define stwpz           "wpz"
#define stLegs		   "Legs"
    #define stlegId         "legId"
    #define stlegLength     "legLength"
    #define stlegStartx     "legStartx"
    #define stlegStarty     "legStarty"
    #define stlegStartz     "legStartz"
    #define stlegEndx       "legEndx"
    #define stlegEndy       "legEndy"
    #define stlegEndz       "legEndz"




typedef enum Node_type {
	DEFAULT = 0,///< standart point
	TARGET,		///< waypoint
	STATION,	///< rest point
	AUTO		///< generated point
} Node_type;

typedef struct legtoarc{
    float x,y;
    int arcsId[MAX_NODE_ARCS];
} legtoarc;
typedef struct Node Node, *Node_p;

typedef struct Arc {
	Node	*dest;
	Float32 max_speed;		///< Max linear speed,		-1.f if unset
	Float32 max_speed_up;	///< Max linear speed-up,	-1.f if unset
}Arc;

struct Node {
	Float32 x, y;
	Node_type nt;
	UInt8 nb_a;
	Arc arcs[MAX_NODE_ARCS];
};

typedef struct Cartography{
	Float32 def_max_speed;
	Float32 def_max_speed_up;
	Int16 nb_arcs;
	Int16 nb_nodes;
	Node nodes[];
} Cartography;

typedef struct Path {
	Node dest[CARTO_NODE_NBR];
	UInt16 size;
	Float32 def_max_speed;
	Float32 def_max_speed_up;
} Path;

typedef struct Mission {
	int ind[CARTO_NODE_NBR];
	UInt16 size;
} Mission;

typedef struct initParser {
    int r;
	jsmn_parser p;
	jsmntok_t * t;
} initParser;

typedef struct Beacons {
    
    int     id;
    float    x;
    float    y;
    float    z; 
}Beacons;

typedef struct Constants
{
    float vdef;
    float adef;
    float v1;
    float v2;
} Constants;

typedef struct Constraints
{
    int id;
    float value;
    char *name;
    char *type;
    float    x;
    float    y;
    float    z; 
}Constraints ;

typedef struct Waypoints
{
    int id;
    char *type;
    float    x;
    float    y;
    float    z; 
}Waypoints ;


typedef struct Legs
{
    int id;
    double length;
    double    startx;
    double    starty;
    double    startz;    
    double    endx;
    double    endy;
    double    endz;
}Legs ;


int jsoneq(const char *json, jsmntok_t *tok, const char *s);
struct Beacons beaconsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank);
struct Waypoints waypointsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank);
struct Legs legsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank);
struct Constraints ConstrExt(char *_JSON_STRING,initParser _IP,int _i,int objRank);
struct Constants CstExt(char *_JSON_STRING,initParser _IP,int _i);
int countNodes(Legs * l,int nlegs);


struct initParser getJsonToken(int expectNvalues,char * JSON_STRING);
int objectOccurance(char * objectName,char * JSON_STRING, initParser IP);
int objectRank(char * objectName,char * JSON_STRING, initParser IP);
int nextObjectTab(char * objectName,char * JSON_STRING, initParser IP);





#endif