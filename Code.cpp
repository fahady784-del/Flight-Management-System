#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

struct flight {
    int flight_id;
    std::string source;
    std::string destination;
    std::string airline;
    std::string departure_time;
    std::string arrival_time;
    double duration;
    int ticket_price;
    std::string status;

    flight* left = NULL;
    flight* right = NULL;
};

flight* root = NULL;


void insert_flight(){

    flight* new_node = new flight;

    std::cout << "Enter Flight ID: ";
    std::cin >> new_node->flight_id;
    std::cin.ignore();

    std::cout << "Enter Source: ";
    std::getline(std::cin, new_node->source);

    std::cout << "Enter Destination: ";
    std::getline(std::cin, new_node->destination);

    std::cout << "Enter Airline: ";
    std::getline(std::cin, new_node->airline);

    std::cout << "Enter Departure Time: ";
    std::cin >> new_node->departure_time;

    std::cout << "Enter Arrival Time: ";
    std::cin >> new_node->arrival_time;

    std::cout << "Enter Duration: ";
    std::cin >> new_node->duration;

    std::cout << "Enter Ticket Price: ";
    std::cin >> new_node->ticket_price;

    std::cout << "Enter Status: ";
    std::cin >> new_node->status;

    if(root == NULL){
        root = new_node;
        std::cout << "Flight Added Successfully!" << "\n";
    }else{

        flight* current = root;
        flight* previous = NULL;

        while(current != NULL){

            previous = current;

            if(new_node->flight_id == current->flight_id){
                std::cout << "Duplicate Flight ID! Insertion Rejected." << std::endl;
                delete new_node;
                return;
            }else if(new_node->flight_id < current->flight_id){
                current = current->left;
            }else{
                current = current->right;
            }
        }

        if(new_node->flight_id < previous->flight_id){
            previous->left = new_node;
        }else{
            previous->right = new_node;
        }

        std::cout << "Flight Added Successfully!" << "\n";
    }
}


void search(){

    flight* current = root;
    int id_to_search;

    std::cout << "Enter Flight ID to search: ";
    std::cin >> id_to_search;

    while(current != NULL){

        if(id_to_search < current->flight_id){
            current = current->left;
        }
        else if(id_to_search > current->flight_id){
            current = current->right;
        }else{
            std::cout << "\nFlight Found!" <<"\n";

            std::cout << "Flight ID: " << current->flight_id <<"\n";
            std::cout << "Source: " << current->source <<"\n";
            std::cout << "Destination: " << current->destination <<"\n";
            std::cout << "Airline: " << current->airline <<"\n";
            std::cout << "Departure Time: " << current->departure_time <<"\n";
            std::cout << "Arrival Time: " << current->arrival_time <<"\n";
            std::cout << "Duration: " << current->duration <<"\n";
            std::cout << "Ticket Price: " << current->ticket_price <<"\n";
            std::cout << "Status: " << current->status <<"\n";

            return;
        }
    }

    std::cout << "Flight Not Found!" <<"\n";
}



void delete_flight(){

    int id;

    std::cout << "Enter Flight ID to delete: ";
    std::cin >> id;

    flight* current = root;
    flight* previous = NULL;

    while(current != NULL && current->flight_id != id){

        previous = current;

        if(id < current->flight_id){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    if(current == NULL){
        std::cout << "Flight Not Found!" <<"\n";
        return;
    }

    if(current->left == NULL && current->right == NULL){

        if(current == root){
            root = NULL;
        }else if(previous->left == current){
            previous->left = NULL;
        }
        else{
            previous->right = NULL;
        }

        delete current;
    }

    else if(current->left == NULL){

        if(current == root){
            root = current->right;
        }
        else if(previous->left == current){
            previous->left = current->right;
        }
        else{
            previous->right = current->right;
        }

        delete current;
    }

    else if(current->right == NULL){

        if(current == root){
            root = current->left;
        }
        else if(previous->left == current){
            previous->left = current->left;
        }
        else{
            previous->right = current->left;
        }

        delete current;
    }

    else{

        flight* successor = current->right;
        flight* successor_parent = current;

        while(successor->left != NULL){
            successor_parent = successor;
            successor = successor->left;
        }

        current->flight_id = successor->flight_id;
        current->source = successor->source;
        current->destination = successor->destination;
        current->airline = successor->airline;
        current->departure_time = successor->departure_time;
        current->arrival_time = successor->arrival_time;
        current->duration = successor->duration;
        current->ticket_price = successor->ticket_price;
        current->status = successor->status;

        if(successor_parent->left == successor){
            successor_parent->left = successor->right;
        }
        else{
            successor_parent->right = successor->right;
        }

        delete successor;
    }

    std::cout << "Flight Deleted Successfully!" << std::endl;
}

void display_flights(flight* current){

    if(current != NULL){

        display_flights(current->left);

        std::cout << "\nFlight ID: " << current->flight_id;
        std::cout << "\nSource: " << current->source;
        std::cout << "\nDestination: " << current->destination;
        std::cout << "\nAirline: " << current->airline;
        std::cout << "\nDeparture Time: " << current->departure_time;
        std::cout << "\nArrival Time: " << current->arrival_time;
        std::cout << "\nDuration: " << current->duration;
        std::cout << "\nTicket Price: " << current->ticket_price;
        std::cout << "\nStatus: " << current->status << "\n";

        display_flights(current->right);
    }
}

void calculate_eta(flight* current){

    if(current != NULL){

        calculate_eta(current->left);

        int departure_hour = (current->departure_time[0] - '0') * 10 + (current->departure_time[1] - '0');

        int departure_minute = (current->departure_time[3] - '0') * 10 + (current->departure_time[4] - '0');

        int departure_total = departure_hour * 60 + departure_minute;

        int duration_minutes = current->duration * 60;

        int eta_total = departure_total + duration_minutes;

        int arrival_hour = (current->arrival_time[0] - '0') * 10 + (current->arrival_time[1] - '0');

        int arrival_minute = (current->arrival_time[3] - '0') * 10 + (current->arrival_time[4] - '0');

        int arrival_total = arrival_hour * 60 + arrival_minute;

        if(arrival_total < departure_total){
            arrival_total = arrival_total + 1440;
        }

        int eta_hour = (eta_total / 60) % 24;
        int eta_minute = eta_total % 60;

        std::cout << "\nFlight ID: " << current->flight_id;

        std::cout << "\nCalculated ETA: ";

        if(eta_hour < 10) std::cout << "0";
        std::cout << eta_hour << ":";

        if(eta_minute < 10) std::cout << "0";
        std::cout << eta_minute;

        if(eta_total < arrival_total){
            current->status = "Early";
        }else if(eta_total == arrival_total){
            current->status = "On-Time";
        }else{
            current->status = "Delayed";
        }

        std::cout << "\nFlight Status: " << current->status << "\n";

        calculate_eta(current->right);
    }
}


void save_flights(flight* current, std::ofstream& file){

    if(current != NULL){

        save_flights(current->left, file);

        file << current->flight_id << ",";
        file << current->source << ",";
        file << current->destination << ",";
        file << current->airline << ",";
        file << current->departure_time << ",";
        file << current->arrival_time << ",";
        file << current->duration << ",";
        file << current->ticket_price << ",";
        file << current->status << "\n";

        save_flights(current->right, file);
    }
}


void save_to_file(){

    std::ofstream file("flights.txt");

    if(!file){
        std::cout << "File Could Not Be Opened!" << "\n";
        return;
    }

    save_flights(root, file);

    file.close();

    std::cout << "Flights Saved Successfully!" << "\n";
}


void load_from_file(){

    std::ifstream file("flights.txt");

    if(!file){
        std::cout << "No Previous Flight Records Found!" << "\n";
        return;
    }

    std::string line;

    while(std::getline(file, line)){

        if(line == ""){
            continue;
        }

        std::stringstream record(line);

        flight* new_node = new flight;

        record >> new_node->flight_id;
        record.ignore();

        std::getline(record, new_node->source, ',');
        std::getline(record, new_node->destination, ',');
        std::getline(record, new_node->airline, ',');
        std::getline(record, new_node->departure_time, ',');
        std::getline(record, new_node->arrival_time, ',');

        record >> new_node->duration;
        record.ignore();

        record >> new_node->ticket_price;
        record.ignore();

        std::getline(record, new_node->status);

        if(root == NULL){
            root = new_node;
        }
        else{

            flight* current = root;
            flight* previous = NULL;

            while(current != NULL){

                previous = current;

                if(new_node->flight_id == current->flight_id){
                    break;
                }
                else if(new_node->flight_id < current->flight_id){
                    current = current->left;
                }
                else{
                    current = current->right;
                }
            }

            if(current != NULL){
                delete new_node;
            }
            else if(new_node->flight_id < previous->flight_id){
                previous->left = new_node;
            }
            else{
                previous->right = new_node;
            }
        }
    }

    file.close();

    std::cout << "Flight Records Loaded Successfully!" << "\n";
}


int count_flights(flight* current){

    if(current == NULL){
        return 0;
    }

    return 1 + count_flights(current->left) + count_flights(current->right);
}



int main(){

    load_from_file();
    int choice;

    do{

        std::cout << "\n===== FLIGHT MANAGEMENT SYSTEM =====\n";
        std::cout << "1. Add Flight\n";
        std::cout << "2. Search Flight\n";
        std::cout << "3. Delete Flight\n";
        std::cout << "4. Display All Flights\n";
        std::cout << "5. Calculate ETA and Flight Status\n";
        std::cout << "6. Save Flights\n";
        std::cout << "7. Count Total Flights\n";
        std::cout << "0. Exit\n";

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if(choice == 1){
            insert_flight();
        }else if(choice == 2){
            search();
        }else if(choice == 3){
            delete_flight();
        }else if(choice == 4){
            display_flights(root);
        }else if(choice == 5){
            calculate_eta(root);
        }else if(choice == 6){
            save_to_file();
        }else if(choice == 7){
            std::cout << "Total Flights: " << count_flights(root) << "\n";
        }else if(choice == 0){
            save_to_file();
            std::cout << "Program Exited!" << std::endl;
    }else{
            std::cout << "Invalid Choice!" << std::endl;
        }

    }while(choice != 0);

    return 0;
}
