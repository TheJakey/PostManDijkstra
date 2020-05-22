#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int** postman;
int** citiesRelationsMatrix;
int* currentTimes;

int** nextStepList;
int lastValidStep;

int getEarliestDepartureTime(int postmanId, int cityFrom, int currentCityTime) {
	int numberOfDepartures = postman[postmanId][0];
	int earliestDepartureTime = 999999999;
	int departureTime;

	// TODO: Test this
	// get the nearest departure time
	for (int departureTimeId = 1; departureTimeId <= numberOfDepartures; departureTimeId++) {
		departureTime = postman[postmanId][departureTimeId];

		if (departureTime < currentTimes[cityFrom]) {
			departureTime += 100;
		}

		if (departureTime < earliestDepartureTime) {
			earliestDepartureTime = departureTime;
		}
	}

	// calculate earliest departure time by adding already passed days
	// (currentCityTime / 100) * 100 -> i need to get rid of ones and tens (e.g. from 542 i need only 500)
	earliestDepartureTime += (currentCityTime / 100) * 100;

	return earliestDepartureTime;
}

int calculateNextHopTime(int currentCityTime, int earliestDepartureTime) {
	int nextHopTime;
	
	if (currentCityTime )
	currentCityTime + earliestDepartureTime;
}

void insertIntoList(int cityFrom, int cityTo, int earliestDepartureTime) {
	lastValidStep++;

	nextStepList[lastValidStep][0] = cityFrom;
	nextStepList[lastValidStep][1] = cityTo;
	nextStepList[lastValidStep][2] = earliestDepartureTime;
}

void makeItRain(int allCitiesCount) {
	int visitedCount = 0;
	int cityFrom = 1, cityTo;
	int postmanId, departureTime, earliestDepartureTime, currentCityTime, timeAtTheNextHop;

	while (visitedCount < allCitiesCount) {
		currentCityTime = currentTimes[cityFrom];

		// fill the tables for all routes from currentCity
		for (cityTo = 2; cityTo < allCitiesCount; cityTo++) 
		{
			postmanId = citiesRelationsMatrix[cityFrom][cityTo];

			// try another city, if connection between cityFrom and cityTo doesn't exists
			if (postmanId == -1)
				continue;

			earliestDepartureTime = getEarliestDepartureTime(postmanId, cityFrom, currentCityTime);

			insertIntoList(cityFrom, cityTo, earliestDepartureTime);
		}
	}
}

void loadDepartureTimes(int postmanId, int numberOfDepartureTimes) {
	for (int i = 1; i < numberOfDepartureTimes + 1; i++) {
		scanf("%d ", &postman[postmanId][i]);
	}
}

void allocateNextStepList(int citiesCount) {
	int row, column;

	lastValidStep = -1;

	nextStepList = (int**)malloc(citiesCount * sizeof(int*));
	for (row = 0; row < citiesCount; row++) {
		nextStepList = (int*)malloc(4 * sizeof(int));
	}

	// put -1 everywhere
	for (int row = 0; row < citiesCount; row++) {
		for (int column = 0; column < 4; column++) {
			nextStepList[row][column] = -1;
		}
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

	allocateNextStepList(citiesCount);

	makeItRain(citiesCount);
	
	getchar();
	return 0;
}