#include "HashMap.hpp"
#include "HashNode.hpp"
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {

	mapSize = 227;
	map = new hashNode*[mapSize];
	for (int i = 0; i < mapSize; i++) {
		map[i] = NULL;
	}
	numKeys = 0;
	collfn = coll1;
	hashfn = hash1;
	collisions = 0;
	hashcoll = 0;

}

void hashMap::addKeyValue(string k, string v) {

	int map_idx = getIndex(k);
	if (map[map_idx] == NULL) {
		map[map_idx] = new hashNode(k);
		map[map_idx]->addValue(v);
		numKeys += 1;
	} else if (map[map_idx]->keyword == k) {
		map[map_idx]->addValue(v);
	}
	if (numKeys / ((float) mapSize) > 0.7) {
		reHash();
	}

}
int hashMap::getIndex(string k) {

	int map_idx;
	if (hashfn) {
		map_idx = calcHash1(k);
	} else {
		map_idx = calcHash2(k);
	}
	if (map[map_idx] != NULL && map[map_idx]->keyword != k) {
		hashcoll += 1;
		if (collfn) {
			map_idx = coll1(map_idx, 1, k);
			collisions -= 1;
		} else {
			map_idx = coll2(map_idx, 1, k);
			collisions -= 1;
		}
	}
	return map_idx;

}

int hashMap::calcHash1(string k) {
	int tmp_i = 0;
	int tmp_l = k.length();
	for (int i = tmp_l - 1; i >= 0; i--) {
		tmp_i = (353 * tmp_i + (int) k[i]) % mapSize;
	}
	return tmp_i;
}

int hashMap::calcHash2(string k) {
	int hash_val = 131;
	for (size_t i = 0; i < k.size(); ++i)
		hash_val = 55 * hash_val + int(k[i]);
	return hash_val % mapSize;
}

void hashMap::getClosestPrime() {

	mapSize = mapSize * 2;
	bool isprime = false;
	while (!isprime) {
		for (int i = 1; i < mapSize; i++) {
			if (mapSize % i == 0) {
				mapSize++;
				continue;
			}
		}
		isprime = true;
	}

}
void hashMap::reHash() {
	hashMap *reMap = new hashMap(hashfn, collfn);
	reMap->mapSize = mapSize;
	reMap->getClosestPrime();
	reMap->map = new hashNode*[reMap->mapSize];
	for (int i = 0; i < reMap->mapSize; i++) {
		reMap->map[i] = NULL;
	}
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			int k = reMap->getIndex(map[i]->keyword);
			reMap->map[k] = map[i];
		}
	}
	map = reMap->map;
	mapSize = reMap->mapSize;
	delete reMap;

}
int hashMap::coll1(int h, int i, string k) {

	if (map[h] == NULL) {
		return h;
	} else if (map[h]->keyword == k) {
		return h;
	}
	h = (h + ((int) pow(i, 2)) % 997) % mapSize;
	int index = coll1(h, i + 1, k);
	collisions += 1;
	return index;

}
int hashMap::coll2(int h, int i, string k) {

	// a different method
	//for dealing with collisions

	collisions++;
	int h2;
	while (map[h] != NULL && map[h]->keyword != k) {
		i++;
		h2 = i * i + 1;
		h = h2 % mapSize;
		collisions++;
	}
	return h;

}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize; j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}

