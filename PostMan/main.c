#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int** postman;
int** citiesRelationsMatrix;
int* currentTimes;

int getEarliestDepartureTime(int postmanId, int cityFrom) {
	int numberOfDepartures = postman[postmanId][0];
	int earliestDepartureTime = 999999999;
	int departureTime;

	for (int departureTimeId = 1; departureTimeId <= numberOfDepartures; departureTimeId++) {
		departureTime = postman[postmanId][departureTimeId];

		if (departureTime < currentTimes[cityFrom]) {
			departureTime += 100;
		}

		if (departureTime < earliestDepartureTime) {
			earliestDepartureTime = departureTime;
		}

		//// TODO: This will never ever work .... you are ignoring all the departures, that are the next day, also, what if ur cityTime is more then one day? also BUG@!!!!!!!!!!@!@!#@#@!!@!#!#@!@#@!#
		//if (departuretime > currenttimes[cityfrom] && departuretime < earliestdeparturetime) {
		//	earliestdeparturetime = departuretime;
		//}
	}

	return earliestDepartureTime;
}

int calculateNextHopTime(int currentCityTime, int earliestDepartureTime) {
	int nextHopTime;
	
	if (currentCityTime )
	currentCityTime + earliestDepartureTime;
}

void makeItRain(int allCitiesCount) {
	int visitedCount = 0;
	int cityFrom = 1, cityTo;
	int postmanId, departureTime, earliestDepartureTime, currentCityTime, timeAtTheNextHop;

	while (visitedCount < allCitiesCount) {
		currentCityTime = currentTimes[cityFrom];

		for (cityTo = 2; cityTo < allCitiesCount; cityTo++) 
		{
			postmanId = citiesRelationsMatrix[cityFrom][cityTo];

			// try another city, if connection between cityFrom and cityTo doesn't exists
			if (postmanId == -1)
				continue;

			earliestDepartureTime = getEarliestDepartureTime(postmanId, cityFrom);

			timeAtTheNextHop = calculateNextHopTime();

		}
	}
}

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
	
	currentTimes = (int*)malloc(citiesCount * sizeof(int));
	for (int cityTime = 0; cityTime < citiesCount + 1; cityTime++) {				// plus one, so you can ignore 0 row and column	
		currentTimes[cityTime] = -1;
	}

	citiesRelationsMatrix = (int**)malloc(citiesCount * sizeof(int*));
	for (int city = 0; city < citiesCount + 1; city++) {							// plus one, so you can ignore 0 row and column		
		citiesRelationsMatrix[city] = (int*)malloc(citiesCount * sizeof(int));
	}

	// put -1 everywehere
	for (int row = 0; row < citiesCount; row++) {
		for (int column = 0; column < citiesCount; column++) {
			citiesRelationsMatrix[row][column] = -1;
		}
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

	makeItRain(citiesCount);
	
	getchar();
	return 0;
}