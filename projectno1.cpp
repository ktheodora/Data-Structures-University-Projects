//οι βιβλιοθήκες που θα χρειαστούμε
#include<iostream>
#include<string>
#include <vector>

//αρχικοποίηση του node και των μεταβλητών που θα χρησιμοποιηθούν στην κλάση της ουράς
struct node
{
	int priority;
	std::string info;
	struct node *link;
};
// Κλαση αρχικοποιησεων μεταβλητων και μεθοδων της ουρας αναμονης
class Priority_Queue
{
private:
	node *front; //οριζεται ως δεικτης node του πρωτου στοιχειου ο front
public:
	Priority_Queue()
	{
		front = NULL; //οριζουμε ως αρχικη τιμή του μπροστινού στοιχείου της ουράς το κενό
	}
	// μεθοδος εισαγωγης στοιχειου
	void insert(std::string& item, int priority)
	{
		node *tmp, *q; //οριζονται ως δεικτες node οι tmp και q
		tmp = new node;
		tmp->info = item; //στην διευθυνση που δειχνει o tmp την πληροφορία(info) τοποθετείται το προιόν που εισάγουμε
		tmp->priority = priority; // στην διευθυνση που δειχνει o tmp την προτεραιότητα(priority) τοποθετείται το ορισμα της προτεραιοτητας
		if (front == NULL || priority < front->priority) //αν η πρωτη θεση ειναι κενη ή η προτεραιοτητα που εχει δωσει ο χρηστης ειναι μικροτερη απο την προτεραιοτητα του πρωτου στοιχειου
		{
			tmp->link = front; //καταχωρησε τον δεικτη του πρωτου στοιχειου στην τοποθεσια μνημης που δειχνει το link
			front = tmp; //ο δεικτης front γινεται ισος με τον tmp
		}
		else //στην αντιθετη περιπτωση
		{
			q = front; //ορισε τον δεικτη του πρωτου στοιχειου ισο με τον q
			while (q->link != NULL && q->link->priority <= priority) { //οσο τo link που βρισκεται στην τοποθεσια του q δεν ειναι κενο 
				// και η προτεραιοτητα που δειχνουν οι δεικτες ειναι μικροτερη η ιση της προτεραιοτητας που εχει δωσει ο χρηστης 
				q = q->link; //ορισε ως δεικτη q το q που δειχνει τον δεικτη link
			}
			tmp->link = q->link; // ο δεικτης tmp που δειχνει στο link γινεται ισος με τον δεικτη q που δειχνει στο link
			q->link = tmp; //και τελος ο q που δειχνει στον link γινεται ισος με τον tmp
		}
	}
	// μεθοδος διαγραφης αρχαιοτερου στοιχειου
	std::string del()
	{
		node *tmp;
		if (front == NULL) //αν το πρωτο στοιχειο δεν υπαρχει
			std::cout << "Queue Underflow\n"; //δεν μπορουμε να το διαγραψουμε και πραγματοποιειται υποχειληση
		else //αλλιως αν υπαρχει
		{
			tmp = front; //οριζουμε ως tmp τον δεικτη του πρωτου στοιχειου
			std::cout << "Deleted item is: " << tmp->info << std::endl;// το στοιχειο π θα διαγραφει ειναι αυτο που δειχνει ο δεικτης tmp
			front = front->link; //το πρωτο στοιχειο γινεται τωρα το αμεσως επομενο
			free(tmp); //ελευθερωνεται ο tmp που εδειχχνε στο πλεον διεγεγραμμενο στοιχειο
			return tmp->info;
		}
	}
};
// μεθοδος εκτυπωσης της γραμμης του δισδιαστατου δυναμικου πινακα που περιεχει τις πτησεις
void printvector2dline(const std::vector<std::vector<std::string>> &vec, std::vector<std::vector<std::vector<std::string>>> reservations, int q)//δεχεται ως ορισματα τον vector και το νουμερο της γραμμης
{
	std::cout << "\n";
	std::cout << "Flight code: " << vec[q][0] << "\n";
	std::cout << "Starting point: " << vec[q][1] << "\n";
	std::cout << "Destination: " << vec[q][2] << "\n";
	std::cout << "Departure time: " << vec[q][3] << "\n";
	std::cout << "Arrival time: " << vec[q][4] << "\n";
	std::cout << "Ticket price: " << vec[q][5] << "\n";
	std::cout << "Aircraft type: " << vec[q][6] << "\n";
	std::cout << "Number of seats in the flight: " << vec[q][7] << "\n";
	std::cout << "Reservations in the flight: " << reservations[q].size() << "\n"; //το πληθος των κρατησεων της πτησhς 
	// που βρισκεται στην σειρα q του πινακα reservations
}

int main() {
	//Αρχικοποιήσεις καθολικών μεταβλητών των οποίων η λειτουργία θα εξηγηθεί στην συνέχεια του προγράμματος
	int index = 0;
	std::vector<std::string> flight_info;
	std::vector<std::vector<std::string>> flights;
	std::vector<std::string> passenger_info;
	std::vector<std::vector<std::vector<std::string>>> reservations;
	std::vector<Priority_Queue> reserv_queues;
	int priority = 0;
	Priority_Queue pq;
	std::vector<std::vector<std::string>> pelates_se_anamonh;
	std::string flight_code;
	std::string starting_point;
	std::string destination;
	std::string dep_time;
	std::string ar_time;
	std::string tix_price;
	std::string aircraft_type;
	std::string num_of_seats;
	while (true) {//εκτύπωση του κεντρικου μενου επιλογης λειτουργιων του προγραμματος
		printf("MAIN MENU\nPress 1 if you want to insert, delete or print flight information \nPress 2 if you want to book, delete or print a reservation \nPress 3 if you want to exit programme\n");
		int x;
		std::cin >> x; // o χρηστης επιλεγει 1,2,3 αναλογα με αυτο που θελει
		if (x == 1) {//Επιλογη επεξεργασιας πτησεων
			char fchoice;
			std::cout << "\nFLIGHT MENU\nPress character 'a' if you want to insert the information of a flight \nPress character 'b' if you want to delete a flight's information \nPress 'c' if you want to print  a flight's information\n";
			std::cin >> fchoice; //επιλογη μιας απο τις 3 λειτουργιες επεξεργασιας των πτησεων
			while (true) {//ελεγχος επιλογης χρηστη
				if ((fchoice == 'a') || (fchoice == 'b') || (fchoice == 'c')) {
					break;
				}
				else {
					std::cout << "You did not gave the right character! \nPlease choose a, b or c again -> ";
					std::cin >> fchoice;
				}
			}
			if (fchoice == 'a') {//ο χρηστης επιλεγει να καταχωρησει τα στοιχεια της πτησης.

				std::cout << "\nPlease enter flight code: "; //εισαγωγη κωδικου πτησης
				std::cin >> flight_code;
				std::cout << "\nPlease enter starting point: "; //εισαγωγη σημειου αφετηριας
				std::cin >> starting_point;
				std::cout << "\nPlease enter destination: "; //εισαγωγη προορισμου πτησης
				std::cin >> destination;
				std::cout << "\nPlease enter departure time: "; //εισαγωγη ωρας αναχωρησης
				std::cin >> dep_time;
				std::cout << "\nPlease enter arrival time: "; //εισαγωγη ωρας αφιξης
				std::cin >> ar_time;
				std::cout << "\nPlease enter ticket price: "; //εισαγωγη τιμης εισητηριου
				std::cin >> tix_price;
				std::cout << "\nPlease enter aircraft type: "; //εισαγωγη τυπου αεροπλανου
				std::cin >> aircraft_type;
				std::cout << "\nPlease enter number of seats in the flight: "; //εισαγωγη χωρητικοτητας αεροσκαφους
				std::cin >> num_of_seats;
				flight_info.push_back(flight_code);
				flight_info.push_back(starting_point);
				flight_info.push_back(destination);
				flight_info.push_back(dep_time);
				flight_info.push_back(ar_time);
				flight_info.push_back(tix_price);
				flight_info.push_back(aircraft_type);
				flight_info.push_back(num_of_seats);
				flights.push_back(flight_info); //δημιουργουμε γραμμη καταχωρησεων κρατησεων
				//με το μεγεθος των διαθεσιμων θεσεων της πτησης
				reserv_queues.push_back(pq); // δημιουργια ουρας προτεραιοτητας της τρεχουσας πτησης
				std::cout << "\nCongrats! The flight info has been saved. \nPress character '!' to print your flight info or press any other button and then enter to go straight back to the main menu: ";
				std::string pr; //ο επιβατης επιλεγει αν θελει να δει εκεινη την στιγμη την κρατηση του αλλιως να προχωρησει στο κυριο μενου
				std::cin >> pr;
				if ((pr == "!") && (flights[index] == flight_info)) {
					printvector2dline(flights, reservations, index);
				}
				index++;
				flight_info.clear(); // gia na mhn desmeyetai epipleon axriasth mnhmh
				// εδω αρχικοποιουμε λιστα επιβατων και ουρα				
			}
			else if (fchoice == 'b') { //αν η επιλογη του χρηστη ειναι η b

				if (flights.size() == 0) { //αν δεν υπαρχει καμια καταχωρηση  στον πινακα των πτησεων
					std::cout << "\nYou haven't added a flight yet!\nGoing back to main menu!\n";
				}
				else { //αν υπαρχει ετσω και μια καταχωρηση
					std::string code;
					std::cout << "\nWhat is the code of the flight that you want to delete? ";
					std::cin >> code; // ο χρηστης δινει τον κωδικο της πτησης που πρεπει να διαγραψει
					bool c = false;
					unsigned int q = 0; //αρχικοποιηση μετρητη που θα χρειαστει για την προσπελαση του πινακα flights
					while (q < flights.size() && c == false) { //οσο ο μετρητης ειναι μικροτερος ισος των καταχωρημενων πτησεων
						if (code == flights[q][0]) { //αν το πρωτο στοιχειο καθε πτησης ειναι ισος με τον κωδικο που εισηγαγε ο χρηστης
							std::cout << "\nErasing flight info...\n";
							flights.erase(flights.begin() + q); //γινεται η διαγραφη της καταχωρησης απο τον  πινακα των πτησεων
							reservations.erase(reservations.begin() + q); // και η διαγραφη της καταχωρησης απο τον  πιανακα των κρατησεων
							reserv_queues[q].del(); //και η διαγραφη της ουρας που αντιστοιχει στην πτηση μεσω της μεθοδου del της priority queue
							std::cout << "ERASING FLIGHT WITH CODE " << code << " SUCCEDEED!\n"; //εμφανιζεται μυνημα με το διαγεγραμμενο στοιχειο
							c = true;
							index--;
							break; //η επαναληψη σταματα αφου η πτηση βρεθηκε
						}
						else {
							c = false; //αλλιως δεν βρεθηκε στην συγκεκριμενη πτηση
						}
						q++;
					}
					if (c == false) { //αν δεν βρηκε καμια καταχωρηση με αυτο τον κωδικο
						std::cout << "\nNo such element found! Going back to main menu! \n"; //επιστροφη στο κυριο μενου
					}
				}
			}
			else { // ο χρηστης επιλεγει την εκτυπωση μιας πτησης
				std::cout << "Please enter your flight code.:";
				std::string code;
				std::cin >>  code;
					bool t = false;
					int q = 0;
					while (q < flights.size() && t == false) { // αν βρισκεται στον γενικο πινακα των πτησεων
						if (flights[q][0] == code) { 	// epeidh to flight code vrisketai sthn prwth thesh kathe grammhs
							t = true; // το στοιχειο επαληθευεται
							int index = q; //αποθηκευεται ο δεικτης της πτησης απο τον αρχικο πινακα στον indexes
						}
						if (t = true) {
							std::cout << "\n Flight Code:" << flights[index][0];
							std::cout << "\n Starting point:" << flights[index][1];
							std::cout << "\n Destination:" << flights[index][2];
							std::cout << "\n Departure time:" << flights[index][3];
							std::cout << "\n Arrival time:" << flights[index][4];
							std::cout << "\n Ticket price:" << flights[index][5];
							std::cout << "\n Aircraft type:" << flights[index][6];
							std::cout << "\n Number of seats in the flight:" << flights[index][7];
						}
						q++;
					}
			}
		}
		else if (x == 2) { // ο χρηστης επιλεγει την επεξεργασια των θεσεων
			if (flights.size() == 0) { //αν δεν εχει γινει καμια καταχωρηση
			 //οχρηστης δεν μπορει να επιλεξει την επεξεργασια θεσεων
				std::cout << "\nYou cannot reserve or delete a seat when there are no flight information given!\n"; 
			}
			else {//ελεγχος εισόδου και κράτηση, διαγραφη η εκτυπωση θεσεων.
				char fchoice;
				std::cout << "\nSEAT MENU\nPress character 'a' if you want to make a reservation \nPress character 'b' if you want to delete a seat in a flight \nPress character 'c' if you want to print your reservation:\n";
				std::cin >> fchoice; //ο χρηστης επιλεγει απο το μενου των επιβατων
				while (true) {//ελεγχος επιλογης χρηστη
					if ((fchoice == 'a') || (fchoice == 'b') || (fchoice == 'c')) {
						break; //αν το στοιχειο ειναι σωστο σταματα την επαναληψη
					}
					else { //αλλιως
						std::cout << "You did not gave the right character! \nPlease choose a, b or c again -> ";
						std::cin >> fchoice; //ξαναδινει την επιλογη του επειδη η αρχικη δεν ηταν σωστη
					}
				}
				if (fchoice == 'a') {//ο χρηστης επελεξε να καταχωρησει τα στοιχεια της πτησης.
					std::cout << "How many flights do you want to book ?";
					int num_of_flights;
					std::cin >> num_of_flights;
					std::string *passenger_flights = new std::string[num_of_flights - 1]; // ο πινακας αρχιζει απο το 0
					bool t = true;
					for (int i = 0; i < num_of_flights; i++) {
						std::cout << "Please give flight code no. " << i + 1 << '\n';
						std::cin >> passenger_flights[i];
					}
					t = false;
					int *indexes = new int[num_of_flights - 1]; // ο πινακας αρχιζει απο το 0
					for (int i = 0; i < num_of_flights; i++) { //ελεγχεται η ορθοτητα των κωδικων
						unsigned int q = 0;
						while (q < flights.size() && t == false) { // αν βρισκεται στον γενικο πινακα των πτησεων
							if (passenger_flights[i] == flights[q][0]) { 	// epeidh to flight code vrisketai sthn prwth thesh kathe grammhs
								t = true; // το στοιχειο επαληθευεται
								indexes[i] = q; //αποθηκευεται ο δεικτης της πτησης απο τον αρχικο πινακα στον indexes
								std::cout << "The code no " << i + 1 << " is correct!\n";
							}
							else {
								t = false; // ο κωδικος της πτησης στον αρχικο πινακα που μολις ελεγχθηκε δεν ταιριαζει
							}
							q++;
						}
						if (t == false) {//εκτυπωνει και σταματαει την διαδικασια κρατησης εισητηριων.
							std::cout << "\nThe code no " << i + 1 << " doesn't exist!  Going back to main menu! \n";
							break;
						}
					}
					if (t != false) { // μπες εδω μονο αν οι κωδικοι που εδωσες υπαρχουν
						bool check = true;
						if (num_of_flights > 1) { // κανε ελεγχους μονο αν το πληθος των πτησεων ειναι >1
							for (int i = 0; i < num_of_flights; i++) {
								if ((flights[indexes[i]][2] != flights[indexes[i + 1]][1])) {
									//αν η αφετηρια της πτησης δεν ειναι ίδια με τον προορισμο της επόμενης
									check = false;
									std::cout << "The starting point of flight " << flights[indexes[i + 1]][0] << "is different\nthan the destination of flight " << flights[indexes[i]][0];
									break;//σταματει την επαναληψη.
								}
								else {
									std::string::size_type sz;
									if (std::stoi(flights[indexes[i]][4], &sz) >= std::stoi(flights[indexes[i + 1]][3], &sz)) {
										//αν η ωρα αφιξης της προηγουμενης πτησης ειναι μεγαλυτερη η ιση απο την ωρα αναχωρησης της επομενης
										check = false;
										//Εκτυπώνει το λάθος
										std::cout << "The arrival time of flight " << flights[indexes[i]][0] << " is different\nthan the departure time of " << flights[indexes[i + 1]][3];
										break;//σταματει την επαναληψη.
									}
								}
							}
						}
						if (check == false) { //αν εχουν βρεθει λαθη στην εισαγωγη των στοιχειων
							std::cout << "\nGoing back to main menu!\n";
						}
						else {
							//ελεγχος πινακα πτησης διαθεσιμων θεσεων, αν ναι τοτε δινει στοιχεια
							bool flag;
							for (int i = 0; i < num_of_flights; i++) {
								std::string::size_type sz;
								unsigned int availability = std::stoi(flights[indexes[i]][7], &sz); //το μεγεθος χωρητικοτητας του αεροπλανου
								if (reservations[indexes[i]].size() < availability) {
									//αν το μεγεθος των υπαρχουσων κρατησεων της πτησης ειναι μικροτερο απο τις διαθεσιμες θεσεις της καθε πτησης
									flag = true; // τοτε ολα οκ
								}
								else { //αν εστω και μια πτηση εχει φτασει στο οριο των θεσεων
									flag = false; // τοτε ο χρηστης μπαινει σε αναμονη
								}
							}
							std::cout << "Please give your personal info!\n";//Τωρα δινει ο χρηστης τα στοιχεια
							std::string on, passp, ethn, addr, phone, pthsh;
							std::cout << "\nEnter your name and surname: ";
							std::cin >> on;
							std::cout << "\nEnter your passport number: ";
							std::cin >> passp;
							std::cout << "\nEnter your nationality: ";
							std::cin >> ethn;
							std::cout << "\nEnter your address number: ";
							std::cin >> addr;
							std::cout << "\nEnter your phone number: ";
							std::cin >> phone;
							/* καταχωρουνται τα στοιχεια
							*/
							passenger_info.push_back(on);
							passenger_info.push_back(passp);
							passenger_info.push_back(ethn);
							passenger_info.push_back(addr);
							passenger_info.push_back(phone);
							if (flag == true) {
								std::cout << "\nTickets almost booked!";
								for (int i = 0; i < num_of_flights; i++) {
									reservations[indexes[i]].push_back(passenger_info); //βαλε τα στοιχεια του πελατη στην πτηση
								}
								std::cout << "\nWell done! You have reserved a seat in all the flights you gave! \n";
							}
							else { // εστω και μια πτηση δεν εχει διαθεσιμες θεσεις
								for (int i = 0; i < num_of_flights; i++) {
									reserv_queues[indexes[i]].insert(on, priority); //εισχωρειται στην ουρα καθε δοθεισας πτήσης το ονομα του επιβατη
								}
								priority += 1;
								std::cout << "\nYour info has been saved, but unfortunately you cannot book a seat now!\nYour reservation will be completed as soon as some seats are cancelled! \n";
								pelates_se_anamonh.push_back(passenger_info);
							}
							passenger_info.clear(); //αποδεσμευονται τα στοιχεια που καταχωρησε ο τελευταιος χρηστης
						}
						delete[] passenger_flights; // an den diagrapsoyme tous pinakes meta to peras twn ergasiwn tote dhmiourgeitai memory leak
						delete[] indexes;
					}
				}
				else if (fchoice == 'b') { //διαγραφη θεσης σε πτηση και τοποθετηση πελατη σε θεση που ειναι διαθεσιμη
					//δινει ο χρηστης το ονομα της κρατησης του και την πτηση του
					std::string name;
					std::cout << "\nWhat name did you gave in your reservation? ";
					std::cin >> name;
					std::cout << "\nThe reservation with name " << name << " is about to be deleted! ";
					bool flag = true;
					std::vector<int> indexes2;
					int q = 0;
					for (unsigned int i = 0; i < reservations.size(); i++) { //αναζητειται ο χρηστης σε ολες τις πτησεις και διαγραφεταο απ τον πινακα κρατησεων
						for (unsigned int j = 0; j < reservations[i].size(); j++) { //αναζετειται ο χρηστης σε καθε πτηση ξεχωριστα
							if (reservations[i][j][0] == name) {
								indexes2[q] = i;
								q++;
								reservations[i].erase(reservations[i].begin() + j);// η κρατηση διαγραφεται
								break;  // ο επιβατης βρεθηκε και η εσωτερικη επαναληψη σταματαει
							}
							else {
								flag = false;
							}
						}
					}
					if (flag == false) {
						std::cout << "\nNo such name found in reservations! Going back to main menu!\n";
					}
					else {
						// εδω ο αρχαιοτερος χρηστης διαγραφεται απο την ουρα, αναζητειται το ονομα του στον πινακα πελατες_σε_αναμονη
						//οταν βρεθει o αρχαιοτερος τον κανουμε push_back στον reservations
						for ( int i = 0; i < indexes2.size(); i++) {
							std::string name2 = reserv_queues[indexes2[i]].del(); //διαγραφη αρχαιοτερου στοιχειου απο καθε πτηση που βρισκοταν ο πελατης που διεγραφη
							for (q = 0; q < pelates_se_anamonh.size(); q++) { // αν βρισκεται στον γενικο πινακα των πτησεων
								if (pelates_se_anamonh[q][0] == name2) { 	// epeidh to flight code vrisketai sthn prwth thesh kathe grammhs
									reservations[indexes2[i]].push_back(pelates_se_anamonh[q]); //καταχωρειται ο αρχαιοτερος πελατης
									break;
								}
							}
						}
					}
				}
				else { //αν ο χρηστης επελεξε να εκτυπωσει την κρατηση του
					std::cout << "Please enter your name.";
					std::string name;
					std::cin >> name;
					bool flag = true;
					for (unsigned int i = 0; i < reservations.size(); i++) { //αναζητειται ο χρηστης σε ολες τις πτησεις και διαγραφεταο απ τον πινακα κρατησεων
						for (unsigned int j = 0; j < reservations[i].size(); j++) { //αναζετειται ο χρηστης σε καθε πτηση ξεχωριστα
							if (reservations[i][j][0] == name) {
								std::cout << "Name:" << reservations[i][j][0];
								std::cout << "Passport number:" << reservations[i][j][1];
								std::cout << "Nationality:" << reservations[i][j][2];
								std::cout << "Address:" << reservations[i][j][3];
								std::cout << "phone:" << reservations[i][j][4];
								break;  // ο επιβατης βρεθηκε και η εσωτερικη επαναληψη σταματαει
							}
							else {
								flag = false;
							}
						}
					}
					if (flag == false) {
						std::cout << "No one with that name made a reservation.Please try an other one.";
					}
				}
			}
		}
		else if (x == 3) {//Επιλογη 3 κλεινει το προγραμμα.
			std::cout << "\nEXITING PROGRAMME...";
			break;
		}
		else {// Ελεγχει ολες τις υπολοιπες επιλογες
			std::cin.clear();
			std::cout << "\nYou did not enter the right character. Please enter your choice again(1 or 2 or 3): ";
			std::cin >> x;
		}
	}
	std::cout << "\nGOODBYE!!! ";
	system("pause");
	return 0;
}

