#include <iostream>
#include <cmath>
#include "coordinate.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int list_length(Coordinate *list_beginning);
void add_coordinate(Coordinate *list_end, float x, float y) {
	Coordinate *new_coord = new Coordinate;
	new_coord->x = x;
	new_coord->y = y;
	new_coord->coord_id = list_length(list_end) + 1;
	new_coord->next = nullptr;
	new_coord->previous = list_end;
	list_end->next = new_coord;
}

void forward_display(Coordinate *list_beginning) {
	Coordinate *current = list_beginning->next;
	while (current != nullptr) {
		cout << "Coord ID: " << current->coord_id << " (" << current->x << ", " << current->y << ")\n";
		current = current->next;
	}
}

void backward_display(Coordinate *list_end) {
	Coordinate *current = list_end;
	while (current->previous != nullptr) {
		current = current->previous;
		cout << "Coord ID: " << current->coord_id << " (" << current->x << ", " << current->y << ")\n";
	}
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
	Coordinate *current = list_beginning->next;
	while (current != nullptr) {
		if (current->coord_id == coord_id_to_delete) {
			if (current->previous != nullptr)
				current->previous->next = current->next;
			if (current->next != nullptr)
				current->next->previous = current->previous;
			delete current;
			cout << "Coordinate ID " << coord_id_to_delete << " deleted.\n";
			return;
		}
		current = current->next;
	}
	cout << "Coordinate ID " << coord_id_to_delete << " not found.\n";
}

int list_length(Coordinate *list_beginning) {
	int length = 0;
	Coordinate *current = list_beginning->next;
	while (current != nullptr) {
		length++;
		current = current->next;
	}
	return length;
}

void closest_to(Coordinate *list_beginning, float x, float y) {
	Coordinate *current = list_beginning->next;
	Coordinate *closest_coord = nullptr;
	float min_distance = -1;
	while (current != nullptr) {
		float distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
		if (min_distance == -1 || distance < min_distance) {
			min_distance = distance;
			closest_coord = current;
		}
		current = current->next;
	}
	if (closest_coord != nullptr) {
		cout << "Closest coordinate to (" << x << ", " << y << ") is Coord ID " << closest_coord->coord_id
				 << " (" << closest_coord->x << ", " << closest_coord->y << ") with distance " << min_distance << "\n";
	}
}

int main(int argc, char* argv[]) {
	int num_coords = atoi(argv[1]);
	srand(time(0));

	Coordinate *list_beginning = new Coordinate;
	list_beginning->next = nullptr;
	list_beginning->previous = nullptr;
	Coordinate *list_end = list_beginning;

	for (int i = 0; i < num_coords; i++) {
		float x = static_cast<float>(rand() % 100);
		float y = static_cast<float>(rand() % 100); 
		add_coordinate(list_end, x, y);
		list_end = list_end->next; 
	}

	cout << "Coordinates (forward):\n";
	forward_display(list_beginning);
	cout << "\nCoordinates (backward):\n";
	backward_display(list_end);

	float x = 0.0, y = 0.0;
	cout << "\nFinding closest coordinate to (" << x << ", " << y << "):\n";
	closest_to(list_beginning, x, y);
	cout << "\nDeleting coordinate with ID 1:\n";
	delete_coordinate(list_beginning, 1);
	cout << "\nCoordinates after deletion:\n";
	forward_display(list_beginning);
	return 0;
}
