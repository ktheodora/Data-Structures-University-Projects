// domes2hergasia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h> //συμπεριλαμβάνουμε την stdlib.h για να χρησιμοποιήσουμε τις συναρτήσεις malloc και free στην υλοποίηση του δένδρου
#include <iostream>
#include <string>
using namespace std;
//ορίζουμε τις search1 και delete1 χωρίς να γράψουμε την υλοποίηση τους, 
//διότι στην συνέχεια καλούνται αναδρομικά μεταξύ τους
void search1(struct treenode *t, int data);
void delete1(struct treenode *t);
struct treenode //ορισμός κονστράκτορα treenode
{
	int value;//θα περιβαλμάνει το κλειδί του κόμβου
	struct treenode *l; //δείκτης αριστερού κλειδιού
	struct treenode *r;//δείκτης δεξιού κλειδιού
}
//αρχικοποίηση της ρίζας και των προσωρινών δεικτών 
*root = NULL, *temp = NULL, *t2, *t1;


void create(int dep_time)
{
	temp = (struct treenode *)malloc(1 * sizeof(struct treenode));
	temp->value = dep_time;
	temp->l = temp->r = NULL;

}
void search(struct treenode *t)
{
	if ((temp->value > t->value) && (t->r != NULL))      /* value more than root node value insert at right */
		search(t->r);
	else if ((temp->value > t->value) && (t->r == NULL))
		t->r = temp;
	else if ((temp->value < t->value) && (t->l != NULL))    /* value less than root node value insert at left */
		search(t->l);
	else if ((temp->value < t->value) && (t->l == NULL))
		t->l = temp;
}

/* To insert a node in the tree */
void insert(int dep_time)
{
	create(dep_time);
	if (root == NULL)
		root = temp;
	else
		search(root);
}

/* To find the smallest element in the right sub tree */
int smallest(struct treenode *t)
{
	t2 = t;
	if (t->l != NULL)
	{
		t2 = t;
		return(smallest(t->l));
	}
	else
		return (t->value);
}

/* To find the largest element in the left sub tree */
int largest(struct treenode *t)
{
	if (t->r != NULL)
	{
		t2 = t;
		return(largest(t->r));
	}
	else
		return(t->value);
}

void search1(struct treenode *t, int data)
{
	if ((data>t->value))
	{
		t1 = t;
		search1(t->r, data);
	}
	else if ((data < t->value))
	{
		t1 = t;
		search1(t->l, data);
	}
	else if ((data == t->value))
	{
		delete1(t);
	}
}


void delete1(struct treenode *t)
{
	int k;

	/* To delete leaf node */
	if ((t->l == NULL) && (t->r == NULL))
	{
		if (t1->l == t)
		{
			t1->l = NULL;
		}
		else
		{
			t1->r = NULL;
		}
		t = NULL;
		free(t);
		return;
	}

	/* To delete node having one left hand child */
	else if ((t->r == NULL))
	{
		if (t1 == t)
		{
			root = t->l;
			t1 = root;
		}
		else if (t1->l == t)
		{
			t1->l = t->l;

		}
		else
		{
			t1->r = t->l;
		}
		t = NULL;
		free(t);
		return;
	}

	/* To delete node having right hand child */
	else if (t->l == NULL)
	{
		if (t1 == t)
		{
			root = t->r;
			t1 = root;
		}
		else if (t1->r == t)
			t1->r = t->r;
		else
			t1->l = t->r;
		t = NULL;
		free(t);
		return;
	}

	/* To delete node having two child */
	else if ((t->l != NULL) && (t->r != NULL))
	{
		t2 = root;
		if (t->r != NULL)
		{
			k = smallest(t->r);
		}
		else
		{
			k = largest(t->l);
		}
		search1(root, k);
		t->value = k;
	}
}

void deletenode(int data)
{
	t1 = root;
	t2 = root;
	search1(root, data);
}

int main()
{
	int ch, space, i = 0;
	bool booly = true;
	cout << "Welcome to the flight booking system simulation!\n";
	cout << "Select the maximum number of flights that you want to insert in the system\n(minus the ones that you will delete): ";
	cin >> space;
	int* departures = new int[space];
	string* codes = new string[space];
	float* arrivals = new float[space];
	float* max_arrivals = new float[space];
	while (booly) {
		cout << "\nOPERATIONS";
		cout << "\n1 - INSERT FLIGHT\n";
		cout << "2 - DELETE FLIGHT\n";
		cout << "3 - ENTER A TIME SPAN, TO SHOW THE CODES OF FLIGHTS \nTHAT HAVE STARTED OR BEEN COMPLETED WITHIN THIS SPAN\n";
		cout << "4 - ENTER TIME, TO SHOW THE ARRIVAL TIME OF THE FLIGHT WITH THE LONGEST DURATION, \nWHOSE DEPARTURE TIME IS EARLIER THAN THE TIME YOU ENTERED\n";
		cout << "5 - ENTER TIME, TO SHOW THE DEPARTURE TIME OF THE CLOSEST FUTURE FLIGHT\n";
		cout << "6 - Exit\n";
		cout << "\nPlease enter your choice: ";
		cin >> ch;
		if (ch == 1) {
			cout << "\nEnter flight code: ";
			cin >> codes[i];
			cout << "\nEnter departure time(01-24): ";
			cin >> departures[i];
			while ((departures[i] < 1) && (departures[i] > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter departure time: ";
				cin >> departures[i];
			}
			insert(departures[i]);
			cout << "\nEnter arrival time(01-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> arrivals[i];
			while ((arrivals[i] < 1) && (arrivals[i] > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter arrival time: ";
				cin >> arrivals[i];
			} //δεν βγαίνω απο την επανάληψη αν δεν βεβαιωθώ ότι έχει δοθεί πραγματική ώρα
			while (arrivals[i] <= departures[i]) {
				cout << "\nArrival time must be greater than departure time! Please re - enter arrival time of flight: ";
				cin >> arrivals[i];
			}
			cout << "\nEnter maximum time of arrival(01-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> max_arrivals[i];
			while ((max_arrivals[i] < 1) && (max_arrivals[i] > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter maximum arrival time: ";
				cin >> max_arrivals[i];
			} //δεν βγαίνω απο την επανάληψη αν δεν βεβαιωθώ ότι έχει δοθεί πραγματική ώρα
			while (max_arrivals[i] < arrivals[i]) {
				cout << "\nMaximum arrival time must be equal or greater than estimated arrival time!\nPlease re-enter maximum arrival time: ";
			}
			i += 1;
			cout << "\nFlight inserted!";
		}
		else if (ch == 2) {
			if (i == 0) {
				cout << "\nNo flights to delete! Please choose the insert operation first.";
			}
			else {
				string deletion_code;
				cout << "\nEnter code of the flight that you want to delete: ";
				cin >> deletion_code;
				int del_number;
				for (int count = 0; count < i; count++) {
					if (codes[count] == deletion_code) {
						del_number = count;
						codes[count] = "0";
						arrivals[count] = 0;
						max_arrivals[count] = 0;
						break;
					}
				}
				deletenode(departures[del_number]);
				departures[del_number] = 0;
				i -= 1;
				if (i != 0) { //an yparxei toulaxiston enas komvos gia na metatopistoun ta stoixeia
					for (int c = del_number; c < i; c++) {
						codes[c] = codes[c + 1];
						departures[c] = departures[c + 1];
						arrivals[c] = arrivals[c + 1];
						max_arrivals[c] = max_arrivals[c + 1];
					}
				}
				cout << "\nFlight with code " << deletion_code << " deleted!\n";
			}
		}
		else if (ch == 3) {
			int check = 0;
			float hour1, hour2;
			cout << "Please enter hour to begin the span(1-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> hour1;
			while ((hour1< 1) && (hour1 > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter hour: ";
				cin >> hour1;
			}
			cout << "Please enter hour to end the span(1-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> hour2;
			while ((hour2< 1) && (hour2 > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter hour: ";
				cin >> hour2;
			}
			cout << "Ongoing flights between " << hour1 << " and " << hour2 << ": ";
			for (int j = 0; j < i; j++) {
				if ((arrivals[j] > hour1) && (arrivals[j] <= hour2)) { //αν η ώρα αφιξης ειναι μεγαλυτερη της εναρξης του χρονικου διατηματος
																	   //και μικροτερη ή ίση του τελους του χρον. διαστήματος
					cout << "\n" << codes[j];
					check = 1;
				}
			}
			if (check == 0) {
				cout << "0 flights found!!!\n";
			}
		}
		else if (ch == 4) {
			float h, max_duration = 0;
			int max_number;
			cout << "Please enter hour(1-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> h;
			while ((h< 1) && (h > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter hour: ";
				cin >> h;
			}
			for (int j = 0; j < i; j++) {
				if (departures[j] < h) {
					if ((arrivals[j] - departures[j]) > max_duration) {
						max_duration = arrivals[j] - departures[j];
						max_number = j;
					}
				}
			}
			if (max_duration == 0) {
				cout << "No flights found departing before the time that you gave! ";
			}
			else {
				cout << "Arrival time is " << arrivals[max_number] << " of flight " << codes[max_number] << ".\n";
			}
		}
		else if (ch == 5) {
			float h, min_span = 24;
			int min_number;
			cout << "Please enter hour(1-24)(in form of xx.yy - e.g. 16.30 stands for 16:30): ";
			cin >> h;
			while ((h < 1) && (h > 24)) {
				cout << "\nTime must be between 1 & 24! Please re- enter hour: ";
				cin >> h;
			}
			for (int j = 0; j < i; j++) {
				if (departures[j] > h) {
					if ((departures[j] - h) < min_span) {
						min_span = departures[j] - h;
						min_number = j;
					}
				}
			}
			if (min_span != 24) {
				cout << "The closest departure time is " << departures[min_number] << " of flight " << codes[min_number];
			}
			else {
				cout << "No flights found departing after the time that you gave! ";
			}
		}
		else if (ch == 6) {
			cout << "\nExiting Programme... ";
			delete[] departures;
			delete[] codes;
			delete[] arrivals;
			delete[] max_arrivals;
			booly = false;
		}
		else {
			cout << "\nYou haven't choose one of the numbers 1 - 6! Please try again!";
		}
	}
	cout << "\nGOODBYE!!! ";
	system("pause");
	return 0;
}

