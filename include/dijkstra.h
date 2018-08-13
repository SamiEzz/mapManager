/*
 * Dijkstra.h
 *
 *  Created on: Aug 29, 2016
 *	  Author: mf.sassi
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#define true 1
#define false 0
#define INT_MAX 2147483647

/* first test: 2 vertices */
void dijkstra(float graph[CARTO_NODE_NBR][CARTO_NODE_NBR], int src, int trajectory[CARTO_NODE_NBR][CARTO_NODE_NBR+1], float dist[]);

#endif /* DIJKSTRA_H_ */
