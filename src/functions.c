#include "../include/header.h"



/*
 * @brief 
 * 
 * @param IN n1
 * @param IN
 * @return if nodes position difference is less than 1 on x and y axes, the  
 * 
 */ 
Bool8 isneighbour(Node n1, Node n2){
	float epsilon = 1;
	if((n1.x-n2.x)<epsilon && (n1.y-n2.y)<epsilon){
		return 1;
	}
	return 0;
}
/*
 * @brief 
 * 
 * @param n1
 * @param 
 * @retval 
 * 
 */ 
int isnewnode(Node* N, float x,float y,int imax){
	for(int i=0;i<imax;i++){
		if(N->x==x && N->y==y){
			return i;
		}
	}
	return -1;
}

/*
 * @brief read the contenant of a table of legs structure, and create nodes
 *  every node contain a table of arcs, and an arc contain a table of pointers to linked nodes.
 * + at first, fill node[knode].nb_a by looking for legs with same (start/end) position
 * + create a temporary table with {* "knode" as id and * arcs from this knode node}
 * |knode|arcs|
 * | --- | --- |
 * | 0 | * arc |
 * 
 * @param IN
 * @return  
 * 
 */ 

/**
 * @brief 
 * 
 * @return legtoarc 
 */
Node * convertLegs(Legs legs[]){
	int nleg=sizeof(legs)/sizeof(legs[0]);
	Node * n = malloc(2*nleg*sizeof(Node));
	int id=0,madeNodes=0;

	/**
	 * @brief loop to calculate number of arcs for each  node
	 * 
	 */
	for(int i=0;i<nleg;i++){
		for(int j =0;j<madeNodes;j++){
			bool notReconized = legs[i].startx!=n[j].x || legs[i].starty != n[j].y;
			bool reconizedStart = legs[i].startx==n[j].x && legs[i].starty == n[j].y;
			bool reconizedEnd = legs[i].endx==n[j].x && legs[i].endy == n[j].y;
			
			if(notReconized){
				/* node not reconized, create a new one
				 * 
				 */
				n[madeNodes].x=legs[i].startx;
				n[madeNodes].y=legs[i].starty;
				n[madeNodes].nb_a=0;
				madeNodes++;
			}
			else if(reconizedStart){
				/* node reconized, create an arc
				 * 
				 */
				n[madeNodes].x=legs[i].startx;
				n[madeNodes].y=legs[i].starty;
				n[madeNodes].nb_a=0;
			}
			

		}
	}
	return n;
}



/*
 * @brief read the contenant of a table of legs structure, and create nodes
 *  every node contain a table of arcs, and an arc contain a table of pointers to linked nodes.
 * + at first, fill node[knode].nb_a by looking for legs with same (start/end) position
 * + create a temporary table with {* "knode" as id and * arcs from this knode node}
 * |knode|arcs|
 * | --- | --- |
 * | 0 | * arc |
 * 
 * @param IN
 * @return  
 * 
  Node * getnodes(Legs legs[],int nb_n){
	int src,dest;
	int nb_Legs = sizeof(legs)/sizeof(legs[0]); 
	Node * n = malloc(nb_n*sizeof(Node)); 
	int knode=0;
	//Legs * useLegs = malloc(sizeof(legs));
	for(int i = 0; i < nb_Legs; i++){
		int occuArc[nb_Legs][2];
		Legs compareLeg=legs[i];
		for(int j=0;j<nb_Legs;j++){
			if(i!=j){
				bool condition1 = legs[j].startx==compareLeg.endx && legs[j].starty==compareLeg.endy;
				bool condition2 = legs[j].startx==compareLeg.startx && legs[j].starty==compareLeg.starty;
				bool condition3 = ;
				bool condition4 = ;
				bool conditions = condition1 && condition2 && condition3;
				
				if(condition1){
					int isnew=isnewnode(&n[knode],compareLeg.endx,compareLeg.endy,i);
					if(isnew==-1){
						Arc arcsrc,arcdest;
						arcsrc.dest=&n[i];
						arcdest.dest=&n[j];
						n[knode].nb_a++;
						n[knode].arcs=;
					}
					n[knode].x=compareLeg.endx;
					n[knode].y=compareLeg.endy;
					
					++knode;
				}
				else if(condition2){
					n[knode].x=compareLeg.startx;
					n[knode].y=compareLeg.starty;
					++knode;
				}
				else if(condition3){
					#
					++knode;
				}
			}
		}
	}
	
	return n;
}
*/
/**
 * @brief 
 * 
 * @param legs 
 * @param cst 
 * @param nb_n 
 * @return Cartography 
 */
Cartography carto(Legs legs[], Constants cst,int nb_n){
	Cartography c;
	// CONSTANTS
	c.def_max_speed = cst.vdef;
	c.def_max_speed_up= cst.adef;

	// Nodes
	c.nb_nodes = nb_n;
	Node * tempN = getnodes(legs,nb_n);
	c.nodes[c.nb_nodes];

	return c;
}
//=====================================================================================
int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

struct Constants CstExt(char *_JSON_STRING,initParser _IP,int _i){
		struct Constants C;
		char * tempchar;
		jsmntok_t *_t = _IP.t;
		//char * jsonobjectname=stBeaconid";
		int constantsrank = objectRank(stConstants,_JSON_STRING, _IP)-1;
		int vdefrank=objectRank(stvdef,_JSON_STRING, _IP)-constantsrank;
		int adefrank=objectRank(stadef,_JSON_STRING, _IP)-constantsrank;
		int v1rank=objectRank(stv1,_JSON_STRING, _IP)-constantsrank;
		int v2rank=objectRank(stv2,_JSON_STRING, _IP)-constantsrank;
		//---
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ vdefrank].start, sizeof(double));
		C.vdef=strtof(tempchar,NULL);
		free(tempchar);
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ adefrank].start, sizeof(double));
		C.adef=strtof(tempchar,NULL);
		free(tempchar);
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ v1rank].start, sizeof(double));
		C.v1=strtof(tempchar,NULL);
		free(tempchar);
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ v2rank].start, sizeof(double));
		C.v2=strtof(tempchar,NULL);
		free(tempchar);
		return C;
  }

struct Constraints ConstrExt(char *_JSON_STRING,initParser _IP,int _i,int objRank){
		struct Constraints ct;
		char * tempchar;
		char * namechar;
		char * typechar;
		
		
		jsmntok_t *_t = _IP.t;
		//char * jsonobjectname=stBeaconid";

		int ctrank = objectRank(stConstraints,_JSON_STRING, _IP)-1;
		int tab=nextObjectTab(stCid,_JSON_STRING, _IP);

		int idrank=objectRank(stCid,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int valuerank=objectRank(stCvalue,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int namerank=objectRank(stCname,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int typerank=objectRank(stCtype,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int xrank=objectRank(stCx,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int yrank=objectRank(stCy,_JSON_STRING, _IP)-ctrank+objRank*tab;
		int zrank=objectRank(stCz,_JSON_STRING, _IP)-ctrank+objRank*tab;
		
		//---
		tempchar = malloc(sizeof(int));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ idrank].start, sizeof(int));
		ct.id=atoi(tempchar);
		free(tempchar);
		//---
		typechar = malloc(14*sizeof(char));
		strncpy(typechar,  _JSON_STRING + _t[_i+ typerank].start, 14*sizeof(char));
		ct.type=typechar;
		//free(typechar);
		//---
		namechar = malloc(5*sizeof(char));
		strncpy(namechar,  _JSON_STRING + _t[_i+ namerank].start, 4*sizeof(char));
		ct.name=namechar;
		//free(namechar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ valuerank].start, sizeof(double));
		ct.value=strtof(tempchar,NULL);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ xrank].start, sizeof(double));
		ct.x=strtof(tempchar,NULL);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ yrank].start, sizeof(double));
		ct.y=strtof(tempchar,NULL);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ zrank].start, sizeof(double));
		ct.z=strtof(tempchar,NULL);
		free(tempchar);

		
		
		return ct;
  }

struct Legs legsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank){
		struct Legs lg;
		char * tempchar;
		
		jsmntok_t *_t = _IP.t;
		//char * jsonobjectname=stBeaconid";

		int lgrank = objectRank(stLegs,_JSON_STRING, _IP)-1;
		int tab=nextObjectTab(stlegId,_JSON_STRING, _IP);

		int idrank=objectRank(stlegId,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int lengthrank=objectRank(stlegLength,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int sxrank=objectRank(stlegStartx,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int syrank=objectRank(stlegStarty,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int szrank=objectRank(stlegStartz,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int exrank=objectRank(stlegEndx,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int eyrank=objectRank(stlegEndy,_JSON_STRING, _IP)-lgrank+objRank*tab;
		int ezrank=objectRank(stlegEndz,_JSON_STRING, _IP)-lgrank+objRank*tab;
				
		//---
		tempchar = malloc(sizeof(int));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ idrank].start, sizeof(int));
		lg.id=atoi(tempchar);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ lengthrank].start, sizeof(double));
		lg.length=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ sxrank].start, sizeof(double));
		lg.startx=strtof(tempchar,NULL);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ syrank].start, sizeof(double));
		lg.starty=strtof(tempchar,NULL);
		free(tempchar);

		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ szrank].start, sizeof(double));
		lg.startz=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ exrank].start, sizeof(double));
		lg.endx=strtof(tempchar,NULL);
		free(tempchar);
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ eyrank].start, sizeof(double));
		lg.endy=strtof(tempchar,NULL);
		free(tempchar);
		tempchar = malloc(sizeof(double));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ ezrank].start, sizeof(double));
		lg.endz=strtof(tempchar,NULL);
		free(tempchar);
		
		
		return lg;
  }

struct Waypoints waypointsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank){
		struct Waypoints wp;
		char * tempchar;
		char * typechar;
		
		jsmntok_t *_t = _IP.t;
		int wprank = objectRank(stWaypoints,_JSON_STRING, _IP)-1;
		int tab=nextObjectTab(stwpid,_JSON_STRING, _IP);
		int idrank=objectRank(stwpid,_JSON_STRING, _IP)-wprank+objRank*tab;
		int xrank=objectRank(stwpx,_JSON_STRING, _IP)-wprank+objRank*tab;
		int yrank=objectRank(stwpy,_JSON_STRING, _IP)-wprank+objRank*tab;
		int zrank=objectRank(stwpz,_JSON_STRING, _IP)-wprank+objRank*tab;
		int typerank=objectRank(stwptype,_JSON_STRING, _IP)-wprank+objRank*tab;
		
		//---
		typechar = malloc(13*sizeof(char));
		strncpy(typechar,  _JSON_STRING + _t[_i+ typerank].start, 13*sizeof(char));
		wp.type=typechar;
		//free(typechar);

		tempchar = malloc(sizeof(int));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ idrank].start, sizeof(int));
		wp.id=atoi(tempchar);
		free(tempchar);
		
		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ xrank].start, sizeof(float));
		wp.x=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ yrank].start, sizeof(float));
		wp.y=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ zrank].start, sizeof(float));
		wp.z=strtof(tempchar,NULL);
		free(tempchar);
		
		return wp;
  }

struct Beacons beaconsExt(char *_JSON_STRING,initParser _IP,int _i,int objRank){
		struct Beacons B;
		char * tempchar;
		jsmntok_t *_t = _IP.t;
		//char * jsonobjectname=stBeaconid";
		int Beaconrank = objectRank(stBeacons,_JSON_STRING, _IP)-1;
		int tab=nextObjectTab(stBeaconid,_JSON_STRING, _IP);
		int idrank=objectRank(stBeaconid,_JSON_STRING, _IP)-Beaconrank+objRank*tab;
		int xrank=objectRank(stBeaconx,_JSON_STRING, _IP)-Beaconrank+objRank*tab;
		int yrank=objectRank(stBeacony,_JSON_STRING, _IP)-Beaconrank+objRank*tab;
		int zrank=objectRank(stBeaconz,_JSON_STRING, _IP)-Beaconrank+objRank*tab;
		//---
		tempchar = malloc(sizeof(char));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ idrank].start, sizeof(int));
		B.id=atoi(&tempchar[0]);
		free(tempchar);

		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ xrank].start, sizeof(float));
		B.x=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ yrank].start, sizeof(float));
		B.y=strtof(tempchar,NULL);
		free(tempchar);
		
		tempchar = malloc(sizeof(float));
		strncpy(tempchar,  _JSON_STRING + _t[_i+ zrank].start, sizeof(float));
		B.z=strtof(tempchar,NULL);
		free(tempchar);
		
		return B;
  }


initParser getJsonToken(int expectNvalues,char * JSON_STRING){
	initParser IP;
	int r;
	jsmn_parser p;
	jsmntok_t  t[expectNvalues]; /* We expect no more than 128 tokens */

	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
    IP.r=r;
	IP.p=p;
	IP.t=t;
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		//return 1;
	}

	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		//return 1;
	}
    
    return IP;
}

int objectRank(char * objectName,char * JSON_STRING, initParser IP){
	int rank;
	jsmntok_t * t = IP.t;
	int r = IP.r;
	for (int i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], objectName) == 0) {
			return i;
		}
	}
	return -1;
}

int objectOccurance(char * objectName,char * JSON_STRING, initParser IP){
	int occurance=0;
	jsmntok_t * t = IP.t;
	int r = IP.r;
	for (int i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], objectName) == 0) {
			occurance++;
		}
	}
	return occurance;
}

int nextObjectTab(char * objectName,char * JSON_STRING, initParser IP){
	int tab=0;
	int lasti=-1;
	jsmntok_t * t = IP.t;
	int r = IP.r;
	for (int i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], objectName) == 0) {
			if(lasti==-1){
				lasti=i;
			}
			else{
				tab=i-lasti;
				return tab;
			}
		}
	}
}
