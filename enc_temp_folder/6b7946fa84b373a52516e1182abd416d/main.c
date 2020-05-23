#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define CITY_FROM 0
#define CITY_TO 1
#define DEPARTURE_TIME 2

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

int notAllCitiesVisited(int citiesCount) {
	for (int i = 1; i <= citiesCount; i++) {
		if (currentTimes[i] == 999999999)
			return 1;
	}

	return 0;
}

void insertIntoList(int cityFrom, int cityTo, int earliestDepartureTime) {
	lastValidStep++;

	nextStepList[lastValidStep][CITY_FROM] = cityFrom;
	nextStepList[lastValidStep][CITY_TO] = cityTo;
	nextStepList[lastValidStep][DEPARTURE_TIME] = earliestDepartureTime;

	return lastValidStep;
}

int makeMove() {
	int nextStep[3];
	int bestMoveIndex, bestMoveTime = 999999999;
	int stepIndex;

	for (stepIndex = 0; stepIndex <= lastValidStep; stepIndex++) {
		if (nextStepList[stepIndex][DEPARTURE_TIME] < bestMoveTime && (nextStepList[stepIndex][DEPARTURE_TIME] < currentTimes[nextStepList[stepIndex][CITY_TO]])) {
			bestMoveTime = nextStepList[stepIndex][DEPARTURE_TIME];
			bestMoveIndex = stepIndex;
		}
	}

	// out of options
	if (bestMoveTime == 999999999) {
		printf("out of options...");
		return -1;
	}

	nextStep[CITY_FROM] = nextStepList[bestMoveIndex][CITY_FROM];
	nextStep[CITY_TO] = nextStepList[bestMoveIndex][CITY_TO];
	nextStep[DEPARTURE_TIME] = nextStepList[bestMoveIndex][DEPARTURE_TIME];

	currentTimes[nextStep[CITY_TO]] = nextStep[DEPARTURE_TIME];

	return nextStep[CITY_TO];
}

void makeItRain(int allCitiesCount) {
	int visitedCount = 0;
	int cityFrom = 1, cityTo;
	int postmanId, departureTime, earliestDepartureTime, currentCityTime, timeAtTheNextHop;

	while (notAllCitiesVisited(allCitiesCount)) {
		currentCityTime = currentTimes[cityFrom];

		// fill the tables for all routes from currentCity		// TODO: BUG go trought all the cities except ONE you came from
		for (cityTo = 2; cityTo <= allCitiesCount; cityTo++) 
		{
			postmanId = citiesRelationsMatrix[cityFrom][cityTo];

			// try another city, if connection between cityFrom and cityTo doesn't exists
			if (postmanId == -1)
				continue;

			earliestDepartureTime = getEarliestDepartureTime(postmanId, cityFrom, currentCityTime);

			insertIntoList(cityFrom, cityTo, earliestDepartureTime);
		}

		// pick best option
		cityFrom = makeMove();

		// cityFrom++;
	}
}

void loadDepartureTimes(int postmanId, int numberOfDepartureTimes) {
	for (int i = 1; i < numberOfDepartureTimes + 1; i++) {
		scanf("%d ", &postman[postmanId][i]);
	}
}

void allocateNextStepList(int postmanCount) {
	int row, column;

	lastValidStep = -1;

	nextStepList = (int**)malloc(postmanCount * sizeof(int*));
	for (row = 0; row < postmanCount; row++) {
		nextStepList[row] = (int*)malloc(4 * sizeof(int));
	}

	// put -1 everywhere
	for (int row = 0; row < postmanCount; row++) {
		for (int column = 0; column < 3; column++) {
			nextStepList[row][column] = -1;
		}
	}
}

int getResultTime(int citiesCount) {
	int currentMax = -1;

	for (int i = 1; i <= citiesCount; i++) {
		if (currentTimes[i] > currentMax)
			currentMax = currentTimes[i];
	}

	return currentMax;
}

int isMinimumNumberOfEdges(int citiesCount, int postmenCount) {
	int minimumNumberOfEdges = citiesCount - 1;

	if (minimumNumberOfEdges > postmenCount)
		return 0;
	else
		return 1;
}

int main() {
	int mapsCount;
	int citiesCount, postmanCount;
	int city_a, city_b, numberOfDepartureTimes;
	int result;
	int mapId;

	scanf("%d", &mapsCount);

	for (mapId = 0; mapId < mapsCount; mapId++) {
		scanf("%d %d", &citiesCount, &postmanCount);

		postman = (int**)malloc((postmanCount + 2) * sizeof(int*));

		currentTimes = (int*)malloc((citiesCount + 2) * sizeof(int));
		for (int cityTime = 0; cityTime < citiesCount + 1; cityTime++) {				// plus one, so you can ignore 0 row and column	
			currentTimes[cityTime] = 999999999;
		}
		currentTimes[0] = -99;
		currentTimes[1] = 0;

		citiesRelationsMatrix = (int**)malloc((citiesCount + 2) * sizeof(int*));
		for (int city = 0; city < citiesCount + 1; city++) {							// plus one, so you can ignore 0 row and column		
			citiesRelationsMatrix[city] = (int*)malloc((citiesCount + 2) * sizeof(int));
		}

		// put -1 everywehere
		for (int row = 0; row <= citiesCount; row++) {
			for (int column = 0; column <= citiesCount; column++) {
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
			// printf("Postmanid: %d -- numberOfDepartureTimes: %d\n", postmanId, numberOfDepartureTimes);
			int kokot = numberOfDepartureTimes;
			postman[postmanId] = (int*)malloc((numberOfDepartureTimes + 1) * sizeof(int));
			postman[postmanId][0] = numberOfDepartureTimes;
			loadDepartureTimes(postmanId, numberOfDepartureTimes);
			// printf("PostMan loaded\n");
		}

		allocateNextStepList(postmanCount);

		if (isMinimumNumberOfEdges(citiesCount, postmanCount)) {
			makeItRain(citiesCount);

			result = getResultTime(citiesCount);

			printf("%d\n", result);
		}
		else {
			printf("-1\n");
		}
	}
	// printf("done");


	return 0;
}