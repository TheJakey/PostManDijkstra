#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int** postman;
int** citiesRelationsMatrix;

void loadDepartureTimes(int postmanId, int numberOfDepartureTimes) {
	for (int i = 1; i < numberOfDepartureTimes + 1; i++) {
		scanf("%d ", &postman[postmanId][i]);
	}
}

int main() {
	int mapsCount;
	int citiesCount, postmanCount;
	int city_a, city_b, numberOfDepartureTimes;

	scanf("%d", &mapsCount);
	scanf("%d %d", &citiesCount, &postmanCount);

	postman = (int**)malloc(postmanCount * sizeof(int*));

	citiesRelationsMatrix = (int**)malloc(citiesCount * sizeof(int*));
	for (int city = 0; city < citiesCount + 1; city++) {							// plus one, so you can ignore 0 row and column		
		citiesRelationsMatrix[city] = (int*)malloc(citiesCount * sizeof(int));
	}

	// load citiesRelations - connections that postmen does
	for (int postmanId = 0; postmanId < postmanCount; postmanId++) {
		// load which 2 cities are connected by this postman
		scanf("%d %d %d", &city_a, &city_b, &numberOfDepartureTimes);
		
		// set matrix
		citiesRelationsMatrix[city_a][city_b] = postmanId;
		citiesRelationsMatrix[city_b][city_a] = postmanId;

		// init and load postman time-schedule
		postman[postmanId] = (int*)malloc(numberOfDepartureTimes * sizeof(int));
		postman[postmanId][0] = numberOfDepartureTimes;
		loadDepartureTimes(postmanId, numberOfDepartureTimes);
	}
	
	getchar();
	return 0;
}